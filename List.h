// File Name: List.h
// Programmer: Tabitha Roemish
// Date: Oct. 15, 2017
// File contains: List class declaration and definition
//				  node Class declaration and definition
#ifndef LIST_H
#define LIST_H
#include<iostream>
#include<string>

#define PERCENT 100
#define MIN_MATCH 50

#include "Food.h"

using namespace std;

template <class T>
class node
{
public:
	// note: nullptr was changed to NULL for g++
	node(T & thing) : thing(thing), next(NULL), prev(NULL) {};
	node<T>* next;
	node<T>* prev;
	T thing;
};

template <class T>
class List
{
	
public:
	List() : head(NULL), tail(NULL), size(0) {};
	~List() { clearList(); };
	void addNode(T & thing);
	bool clearList();
	
	bool deleteNode(string name);
	void printList(ostream& out);

	int letterMatches(string search, string list);
	int placeMatches(string search, string list);

	int indexOf(string name, int beginPosition,char ch);
	string search(string searchString);
	node<T>* searchListLocation(string name);
	node<T>* alternateSuggestions(string name, bool &alternatesFound);
	
	void sortDescending();
	void sortAscending();
	
	node<T>* next(node<T>* nd);
	node<T>* prev(node<T>* nd);
private:
	node<T>* head;
	node<T>* tail;
	int size;
};


template <class T>
node<T>* List<T>::next(node<T>* nd)
{
	node<T> * temp = nd->next;
	return temp;
}

template <class T>
node<T>* List<T>::prev(node<T>* nd)
{
	node<T> * temp = nd->prev;
	return temp;
}
//List definitions-----------------------------

//addFood(Food& fd) uses new for memory allocation
// throws bad_alloc if memory cannot be obtained
template <class T>
void List<T>::addNode(T & thing)
{
	size++;
	try
	{
		node<T> * newNode = new node<T>(thing);

		if (head == NULL && tail == NULL)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	}
	catch (bad_alloc & ba)
	{
		cerr << "Memory error: " << ba.what();
	}
}
// method for destructor
template <class T>
bool List<T>::clearList()
{
	node<T> * temp = head;
	if (head = NULL)
		return false;
	else
	{
		for (int i = 1; i < size; i++)
		{
			temp = next(temp);
			delete temp->prev;
		}
		delete temp;
		//reset list properties
		size = 0;
		head = NULL;
		tail = NULL;
	}
	return true;
}
// deleteFood(string) uses searchLocation() to delete
// at specific place in list
template <class T>
bool List<T>::deleteNode(string name)
{
	node<T>* temp = searchListLocation(name);
	if (temp == NULL)
		cout << "\nItem not found.\n";
	else if (size != 0)
	{
		if (next(temp) != NULL && prev(temp) != NULL) // in middle
		{
			next(temp)->prev = prev(temp);
			prev(temp)->next = next(temp);
		}
		else if (next(temp) == NULL) // at tail
		{
			tail = prev(temp);
			tail->next = NULL;
		}
		else // at head
		{
			head = next(temp);
			head->prev = NULL;
		}

		delete temp;
		size--;
		cout << "\n" << name << " deleted. Current list size is " << size << ".\n";
		return true;
	}
	else
		cout << "\nList is empty.\n";

	return false;
}
template <class T>
string List<T>::search(string searchString)
{
	bool altsFound = true;
	node<T>* temp = alternateSuggestions(searchString, altsFound);
	string retString = "";
	if (temp == NULL)
	{
		if (altsFound)
			cout << "Selection cancelled" << endl;
		else
			cout << "Item not found. No suggestions available." << endl;
	}
	else
		retString = "You selected " + temp->thing.getName();

	return retString;
}

template <class T>
node<T>* List<T>::searchListLocation(string name) // Big O = O(n)
												  // iterates through n items in while loop so n is max iteration count
{
	node<T> * temp = head;
	while (temp->next != NULL)
		if (name == temp->thing.getName())
			return temp;
		else
			temp = next(temp);
	if (name == temp->thing.getName()) // check last element
		return temp;
	else
		return NULL;
}

template <class T>
void List<T>::printList(ostream& out)
{
	node<T>* curr = head;
	for (int x = 1; x <= size; x++)
	{
		cout << x << ": " << curr->thing;
		curr = next(curr);
	}
}
template <class T> //O(n^2) - n iterations times n iterations
int List<T>::letterMatches(string search, string list)
{
	string smallWord = (search.length() < list.length()) ? search : list;
	string largeWord = (smallWord == search) ? list : search;
	int count = 0;
	for (unsigned int i = 0; i < smallWord.length(); i++)
	{
		for (unsigned int j = 0; j < largeWord.length(); j++)
			if (toupper(smallWord[i]) == toupper(largeWord[j]))
			{
				count++;
				largeWord.erase(j, j);
				break;
			}
	}
	return count;
}
template <class T> //O(n) - n times in loop
int List<T>::indexOf(string name, int beginPosition, char ch)
{
	for (unsigned int i = beginPosition; i < name.length()-beginPosition; i++)
	{	
		if (toupper(name[i]) == toupper(ch))
			return i;
	}
	return -1;
}
//Big O notation = O(n^c) c=3 polynomial,
// because there are n iterations in the for loop,
// n iterations in the while loop, and
// n iterations in the nested forloop (n x n x n)
template <class T>
int List<T>::placeMatches(string search, string list)
{
	string smallWord = (search.length() < list.length()) ? search : list;
	string largeWord = (smallWord == search) ? list : search;

	bool matchIndex = false;
	int count = 0;
	int maxCount = 0;
	int index = 0;
	int largeWordStart = 0;
	int smallWordLeft = smallWord.length();
	int stringLeft = largeWord.length();
	for (unsigned int i = 0; i < smallWord.length() - 1; i++)
	{
		index = indexOf(largeWord, 0, smallWord[i]);
		largeWordStart = index;
		while (index != -1)
		{ 
			// find search length
			stringLeft = stringLeft - index;
			smallWordLeft = (smallWordLeft < stringLeft) ? smallWordLeft : stringLeft;
			for (unsigned int k = i; k < smallWordLeft; k++)
			{
				if (toupper(smallWord[k]) == toupper(largeWord[largeWordStart]))
				{
					if (i == index)
						matchIndex = true;
					count++;
				}
				largeWordStart++;
			}
			if (count == 1 && matchIndex == false)
				count = 0;
			if (count > maxCount)
				maxCount = count;
			count = 0;
			stringLeft = largeWord.length();
			index = indexOf(largeWord, index + 1, smallWord[i]);
			largeWordStart = index;
		}
	}
	return maxCount;

}
// no match returns null and sets bool false
// Big O notation O(n) if you don't count the O^3 and O^2 for the match and place count
template <class T>
node<T>* List<T>::alternateSuggestions(string searchName, bool &altsFound)
{
	int matchCount = 0;
	int placeCount = 0;
	int ranking = 0;
	int wordLength = 0;
	BST<T> suggTree;
	string listName = "";
	node<T> * temp = head;
	while (temp != NULL)
	{
		listName = temp->thing.getName(); // get list name
		//get least length
		wordLength = (searchName.length() < listName.length()) ? searchName.length() : listName.length();
	
		int testMatch = letterMatches(searchName, temp->thing.getName()); //O(n^2)
		int testPlace = placeMatches(searchName, temp->thing.getName()); //O(n^3)
		
		//find ranking & add to BST if over 50 percent match
		matchCount = (testMatch / static_cast<double>(wordLength)) * PERCENT;
		placeCount = (testPlace / static_cast<double>(wordLength)) * PERCENT; 
		
		ranking = (matchCount + placeCount) / 2; // get average
		if (ranking > MIN_MATCH)
			suggTree.insert(ranking, temp, suggTree.getRoot());
		
		//reset variables
		temp = next(temp);
		matchCount = 0;
		placeCount = 0;
	} 
	
	if (suggTree.isEmpty())
	{
		altsFound = false; 
		return NULL;
	}
	else
	{
		altsFound = true;
		cout << "\nPlease confirm your selection by entering the menu number: " << endl;
		suggTree.print();
		node<T> * returnNode = suggTree.getInput();
		return returnNode;
	}
}

// Big O = O(n^2)
// bubble sort, iterates through n items in while loop
//n times in for loop so n*n
template <class T>
void List<T>::sortAscending()
{
	if (size > 0) // don't sort empty list
	{
		node<T>* temp = head;
		node<T>* nextThing = next(temp);
		int swapCount = 0;

		for (int i = 1; i < size; i++)
		{
			if (swapCount == 0 && i != 1)
				break;
			swapCount = 0;
			while (nextThing != NULL)
			{
				if (temp->thing < nextThing->thing) // < ---- only difference between sortDescending()
				{
					swapCount++; // track swap

					//establish nodes
					node<T>* swap = next(temp);
					node<T>* outsideLeft = prev(temp);
					node<T>* outsideRight = next(swap);

					// swap pointers to each other
					temp->prev = swap;
					swap->next = temp;

					// swap pointers to outside nodes
					temp->next = outsideRight;
					swap->prev = outsideLeft;

					if (outsideLeft == NULL) //watch for head of list
					{
						head = swap;
					}
					else outsideLeft->next = swap;

					if (outsideRight == NULL) // watch for tail of list
					{
						tail = temp; break;
					}
					else outsideRight->prev = temp;

					//get new next food
					nextThing = next(temp);
				}
				else // advance nodes 
				{
					temp = next(temp);
					nextThing = next(temp);
				}
			}

			temp = head; // reset to beginning of list
			nextThing = next(temp);

		}
	}
}

template <class T>
void List<T>::sortDescending() // Big O = O(n^2)
{
	if (size > 0) // don't sort empty list
	{
		node<T>* temp = head;
		node<T>* nextThing = next(temp);
		int swapCount = 0;

		for (int i = 1; i < size; i++)
		{
			if (swapCount == 0 && i != 1)
				break;
			swapCount = 0;
			while (nextThing != NULL)
			{
				if (temp->thing > nextThing->thing) //<----only difference between sortAscending()
				{
					swapCount++; // track swap

								 //establish nodes
					node<T>* swap = next(temp);
					node<T>* outsideLeft = prev(temp);
					node<T>* outsideRight = next(swap);

					// swap pointers to each other
					temp->prev = swap;
					swap->next = temp;

					// swap pointers to outside nodes
					temp->next = outsideRight;
					swap->prev = outsideLeft;

					if (outsideLeft == NULL) //watch for head of list
					{
						head = swap;
					}
					else outsideLeft->next = swap;

					if (outsideRight == NULL) // watch for tail of list
					{
						tail = temp; break;
					}
					else outsideRight->prev = temp;

					//get new next food
					nextThing = next(temp);
				}
				else // advance nodes 
				{
					temp = next(temp);
					nextThing = next(temp);
				}
			}
			temp = head; // reset to beginning of list
			nextThing = next(temp);
		}
	}
}


#endif


