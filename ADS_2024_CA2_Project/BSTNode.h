#pragma once
#include <iostream>

using namespace std;
template <class T>
class BSTNode
{
	
	BSTNode<T> *parent;
	BSTNode<T> *left;
	BSTNode<T> *right;
	T data;
	
public:
	BSTNode();
	BSTNode(const BSTNode<T>& other);
	BSTNode<T>& operator=(const BSTNode<T>& other);
	BSTNode(T data);
	void setItem(T item);
	int count() const;
	void add(T& item);
	BSTNode<T>* getParent();
	BSTNode<T>* getLeft() const;
	BSTNode<T>* getRight() const;
	void setLeft(BSTNode<T> *l);
	void setRight(BSTNode<T> *r);
	T& getItem();
	const T& getItem() const;
	~BSTNode();

};

template <class T>
BSTNode<T>::BSTNode(const BSTNode<T>& other)
{
	data = other.data;
	left = right = nullptr;
	if (other.left != nullptr)
		this->left = new BSTNode<T>(*other.left);
	if (other.right != nullptr)
		this->right = new BSTNode<T>(*other.right);
}

template <class T>
BSTNode<T>& BSTNode<T>::operator=(const BSTNode<T>& other)
{
	if (this == &other)
		return *this;

	delete left;
	delete right;

	data = other.data;

	if (other.left != nullptr)
		left = new BSTNode<T>(*other.left);
	else
		left = nullptr;

	if (other.right != nullptr)
		right = new BSTNode<T>(*other.right);
	else
		right = nullptr;

	return *this;
}


template <class T>
BSTNode<T>::~BSTNode()
{
	if (left != nullptr)
	{
		delete left;
		left = nullptr;
	}
	if(right!= nullptr)
	{
		delete right;
		right = nullptr;
	}

}
template <class T>
T& BSTNode<T>::getItem() {
	return this->data;
}
template <class T>
const T& BSTNode<T>::getItem() const {
	return this->data;
}
template <class T>
BSTNode<T>* BSTNode<T>::getLeft() const {
	return this->left;
}
template <class T>
BSTNode<T>* BSTNode<T>::getRight() const {
	return this->right;
}
template <class T>
BSTNode<T>* BSTNode<T>::getParent()
{
	return this->parent;
}
template <class T>
void BSTNode<T>::setLeft(BSTNode<T> *l)
{
	this->left = l;
}
template <class T>
void BSTNode<T>::setRight(BSTNode<T> *r)
{
	this->right = r;
}


template <class T>
BSTNode<T>::BSTNode()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}


template <class T>
BSTNode<T>::BSTNode(T data)
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	this->data = data;
}
template <class T>
int BSTNode<T>::count() const {
	int c = 1;
	if (left != nullptr) {
		c += left->count();
	}
	if (right != nullptr) {
		c += right->count();
	}
	return c;
}

template <class T>
void BSTNode<T>::add(T& item)
{
	if (item == this->data)
	{
		return;
	}
	else if (item < this->data)
	{
		if (left == nullptr)
		{
			left = new BSTNode<T>();
			left->data = item;
			left->parent = this;
		}
		else
		{
			left->add(item);
		}
	}
	else
	{
		if (right == nullptr)
		{
			right = new BSTNode<T>();
			right->data = item;
			right->parent = this;
		}
		else
		{
			right->add(item);
		}
	}
}

template <class T>
void BSTNode<T>::setItem(T item)
{
	this->data = item;
}

