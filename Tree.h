#ifndef TREE_AKINATOR_H
#define TREE_AKINATOR_H

#include <cstdio>
#include <cstdlib>
#include <iostream>

using std::string;

template <class T>
class Tree
{
private:
	T data_;
	class Tree* left;
	class Tree* right;
	class Tree* parent;

public:
	explicit Tree() :
		data_(), left(nullptr), right(nullptr),
		parent(nullptr) { }
	explicit Tree(T data) :
		data_(data), left(nullptr), right(nullptr),
		parent(nullptr) { }
	explicit Tree(T data, Tree* parent) :
		data_(data), left(nullptr), right(nullptr),
		parent(parent) { }
	explicit Tree(Tree* left, Tree* right, T data) :
		data_(data), left(left), right(right),
		parent(nullptr) { }
	explicit Tree(Tree* parent) :
		data_(), left(nullptr), right(nullptr),
		parent(parent) { }

	Tree* push(T data, Tree* parent);
	Tree* push(Tree* parent);
	void write(T data);
	Tree* find_one(T data);
	Tree* parent_l() { return parent; }
	Tree* right_l() { return right; }
	Tree* left_l() { return left; }
	T return_data() { return data_; }
	~Tree();
	Tree* Copy(Tree* that);

	void print(Tree* head) const;
};

template<class T>
Tree<T>* Tree<T>::Copy(Tree* that)
{
	Tree* node = new Tree(that->data_, that);
	if (that->left != nullptr)
	{
		node->left = Copy(that->left);
	}
	if (that->right != nullptr)
	{
		node->right = Copy(that->right);
	}
	return node;
}

template <class T>
Tree<T>* Tree<T>::push(T data, Tree* parent)
{
	Tree* new_node = new Tree(data, parent);
	if (left == nullptr)
	{
		left = new_node;
		return new_node;
	}
	if (right == nullptr)
	{
		right = new_node;
		return new_node;
	}
	else
	{
		delete new_node;
		return nullptr;
	}
}

template <class T>
Tree<T>* Tree<T>::push(Tree* parent)
{
	Tree* new_node = new Tree(parent);
	if (left == nullptr)
	{
		left = new_node;
		return new_node;
	}
	if (right == nullptr)
	{
		right = new_node;
		return new_node;
	}
	else
	{
		delete new_node;
		return nullptr;
	}
}

template <class T>
void Tree<T>::write(T data)
{
	data_ = data;
}

template <class T>
Tree<T>::~Tree()
{	
	if (left)
		delete left;
	if (right)
		delete right;
}

template <class T>
Tree<T>* Tree<T>::find_one(T data)
{
	if (data == data_)
	{
		return this;
	}
	Tree* tmp = nullptr;
	if (left != nullptr) 
	{
		tmp = left->find_one(data);
		if (tmp != nullptr)
			return tmp;
	}
	if (right != nullptr)
	{
		tmp = right->find_one(data);
		if (tmp != nullptr)
			return tmp;
	}
	return nullptr;
}

template <>
void Tree<int>::print(Tree* head) const
{
	std::cout << data_ << std::endl;
	if (left)
		print(left);
	if (right)
		print(right);
}

#endif TREE_AKINATOR_H