#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
using std::cout;
using std::endl;
using std::cerr;

template<typename T>
class AVLTreeNode			// 平衡树结点
{
public:
	AVLTreeNode(T _key, AVLTreeNode<T>* _lchild,
		AVLTreeNode<T>* _rchild) : key(_key), lchild(_lchild), rchild(_rchild) {
		height = 1;
	}
	T key;
	int height;
	AVLTreeNode<T> *lchild;
	AVLTreeNode<T> *rchild;
};

template<typename T>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();

private:
	AVLTreeNode<T> *root;

public:
	int height();			
	void preOrder();
	void inOeder();
	void postOrder();
	void treeOutput();
	void destory();

	T maximum();		// 最大值
	T minimum();		// 最小值

	void insert(T key);
	void remove(T key);
	bool contain(T key);
	
private:
	void preOrder(AVLTreeNode<T> *proot);		//	前序遍历
	void inOrder(AVLTreeNode<T> *proot);		//	中序遍历
	void postOrder(AVLTreeNode<T> *proot);		//	后序遍历
	void destory(AVLTreeNode<T> *&proot);		//	后序删除
	void treeOutput(AVLTreeNode<T> *proot, int dep);	// 打印树形结构

	AVLTreeNode<T>* maximum(AVLTreeNode<T> *proot);
	AVLTreeNode<T>* minimum(AVLTreeNode<T> *proot);
	
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &proot, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &proot, T key);
	AVLTreeNode<T>* search(AVLTreeNode<T>* proot, T key);

	AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* &proot);		//	左旋
	AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* &proot);		//	右旋
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* &proot);	//	先左旋再右旋
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* &proot);	//	先右旋再左旋

	int height(AVLTreeNode<T> *pnode);
};