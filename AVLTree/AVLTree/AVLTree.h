#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
using std::cout;
using std::endl;
using std::cerr;

template<typename T>
class AVLTreeNode			// ƽ�������
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

	T maximum();		// ���ֵ
	T minimum();		// ��Сֵ

	void insert(T key);
	void remove(T key);
	bool contain(T key);
	
private:
	void preOrder(AVLTreeNode<T> *proot);		//	ǰ�����
	void inOrder(AVLTreeNode<T> *proot);		//	�������
	void postOrder(AVLTreeNode<T> *proot);		//	�������
	void destory(AVLTreeNode<T> *&proot);		//	����ɾ��
	void treeOutput(AVLTreeNode<T> *proot, int dep);	// ��ӡ���νṹ

	AVLTreeNode<T>* maximum(AVLTreeNode<T> *proot);
	AVLTreeNode<T>* minimum(AVLTreeNode<T> *proot);
	
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &proot, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &proot, T key);
	AVLTreeNode<T>* search(AVLTreeNode<T>* proot, T key);

	AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* &proot);		//	����
	AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* &proot);		//	����
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* &proot);	//	������������
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* &proot);	//	������������

	int height(AVLTreeNode<T> *pnode);
};