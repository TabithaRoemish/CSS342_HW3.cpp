// File Name: BST.h
// Programmer: Tabitha Roemish
// Date: 10/17/2017
#ifndef BST_H
#define BST_H

#include "List.h"
#define BUFFER 50
template <class T>
class element
{
public:
	element(int ranking, node<T> * ptr) : ranking(ranking), ptrToNode(ptr), order(0) {};
	node<T> * getNode() {return ptrToNode;};
	int getRank() { return ranking; };
	int getOrder() { return order; };
	void setOrder(int o) { order = o; };
	element<T> * left() { return leftPtr; };
	element<T> * right() { return rightPtr; };
	void setLeft(element<T> * ptr) { leftPtr = ptr; };
	void setRight(element<T> * ptr) { rightPtr = ptr; };
private:
	int ranking;
	int order;
	node<T> * ptrToNode;
	element<T> * leftPtr;
	element<T> * rightPtr;
};

template <class T>
class BST
{
public:
	BST() : root(NULL) {};
	~BST() { deleteTree(root); };
	element<T> * getRoot() { return root; };
	bool isEmpty() const { return root == NULL; };
	int getSize() {return size;};
	bool insert(int rank, node<T>* ptr, element<T>* curr);
	void print(ostream& out, element<T>* curr);
	void print() { print(cout, root); }; //ostream and root default
	void setOrder(element<T>* curr);
	element<T> * searchOrder(int listOrder, element<T> * curr);
	void deleteTree(element<T>* curr);
	node<T>* getInput();
	static int order;
private:
	element<T> * root;
	int size;
};

template <class T>
int BST<T>::order = 0; //initialize static variable

template <class T>
bool BST<T>::insert(int rank, node<T>* ptr, element<T>* curr)
{
	bool canInsert = true;
	element<T> * tempPtr = NULL;
	if (curr == NULL)
	{
		curr = new element<T>(rank, ptr);
		if (isEmpty())
		{
			root = curr;
			size++;
		}
		setOrder(curr);
	}
	else
	{
		if (rank < curr->getRank())
		{
			if (curr->left() == NULL)
			{
				curr->setLeft(tempPtr = new element<T>(rank, ptr)); 
				size++;
			}
			else
				return insert(rank, ptr, curr->left());
		}
		else if (rank >= curr->getRank())
		{
			if (curr->right() == NULL)
			{
				curr->setRight(tempPtr = new element<T>(rank, ptr));
				size++;
			}
			else
				return insert(rank, ptr, curr->right());
		}
		order = 0;
		setOrder(root);
	}
	return canInsert;
}

template <class T>
void BST<T>::print(ostream& out, element<T>* curr)
{
	if (curr != NULL)
	{
		print(out, curr->right());
		out << curr->getOrder() << ": " << curr->getNode()->thing.getName() << endl;
		print(out, curr ->left());
	}
}

template <class T>
void BST<T>::setOrder(element<T>* curr)
{
	if (curr != NULL)
	{
		setOrder(curr->right());
		curr->setOrder(++order);
		setOrder(curr->left());
	}
}
template <class T>
void BST<T>::deleteTree(element<T>*  curr)
{
	if (curr != NULL)
	{
		deleteTree(curr->left());
		deleteTree(curr->right());
		delete curr;
		curr = NULL;
		order = 0;
	}
}
//Big O notation = O(log n) because for every iteration the path is cut down by half
template <class T>
element<T> * BST<T>::searchOrder(int listOrder, element<T> * curr)
{
	if (listOrder == curr->getOrder())
		return curr;
	else if (listOrder < curr->getOrder())
	{
		if (curr->right() == NULL)
			return NULL;
		else
			return searchOrder(listOrder, curr->right());
	}
	else if (listOrder > curr->getOrder())
	{
		if (curr->left() == NULL)
			return NULL;
		else
			return searchOrder(listOrder, curr->left());
	}
	return NULL;
		
}
// input & output used in function to cancel input enter Q
template <class T>
node<T>* BST<T>::getInput()
{
	int input;
	char check = cin.peek();
	while (!(cin >> input)|| input < 1 || input > size)
	{
		if (toupper(check) == 'Q')
		{
			cin.clear();
			cin.ignore(BUFFER, '\n'); 
			return NULL;
		}
		cin.clear();
		cin.ignore(BUFFER, '\n');
		cout << "Invalid Input. Please enter a menu number or 'Q': " << endl;
		check = cin.peek();
	}
	cin.clear();
	cin.ignore(BUFFER, '\n');

	element<T> * nodeOutput = searchOrder(input, root);
	return nodeOutput->getNode();
}

#endif