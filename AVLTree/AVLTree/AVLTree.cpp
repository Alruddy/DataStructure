#include "AVLTree.h"

template<typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
}

template<typename T>
AVLTree<T>::~AVLTree()
{
	destory();
	if (root != nullptr)
	{
		delete root;
	}
}

template<typename T>
void AVLTree<T>::preOrder(AVLTreeNode<T> *proot)
{
	if (proot != nullptr)
	{
		cout << proot->key << " ";
		preOrder(proot->lchild);
		preOrder(proot->rchild);
	}
}

template<typename T>
void AVLTree<T>::inOrder(AVLTreeNode<T> *proot)
{
	if (proot != nullptr)
	{
		inOrder(proot->lchild);
		cout << proot->key << " ";
		inOrder(proot->rchild);
	}
}

template<typename T>
void AVLTree<T>::postOrder(AVLTreeNode<T> *proot)
{
	if (proot != nullptr)
	{
		postOrder(proot->lchild);
		postOrder(proot->rchild);
		cout << proot->key << " ";
	}
}

template<typename T>
void AVLTree<T>::destory(AVLTreeNode<T>* &proot)
{
	if (proot != nullptr)
	{
		destory(proot->lchild);
		destory(proot->rchild);
		AVLTreeNode<T> *pnode = proot;
		proot = nullptr;
		delete pnode;
	}
}

template<typename T>
void AVLTree<T>::treeOutput(AVLTreeNode<T>* proot, int dep)
{
	for (int i = 0; i < dep-1; i++)
	{
		cout << "|        ";
	}
	if (dep > 0)
	{
		cout << "|--------";
	}
	if (proot == nullptr)
	{
		cout << "NULL" << endl;
		return;
	}
	else
	{
		cout << proot->key << endl;
		treeOutput(proot->lchild, dep + 1);
		treeOutput(proot->rchild, dep + 1);
	}
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* proot)
{
	if (proot != nullptr)
	{
		while (proot->rchild != nullptr)
		{
			proot = proot->rchild;
		}
		return proot;
	}
	return nullptr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* proot)
{
	if (proot != nullptr)
	{
		while (proot->lchild != nullptr)
		{
			proot = proot->lchild;
		}
		return proot;
	}
	return nullptr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& proot, T key)
{
	if (proot == nullptr) 
	{
		proot = new AVLTreeNode<T>(key, nullptr, nullptr);		// 插入节点
	}
	else
	{
		if (key == proot->key)		// 有重复节点，不插入
		{
			return proot;
		}
		else if (key > proot->key)
		{
			insert(proot->rchild, key);
			if (height(proot->rchild) - height(proot->lchild) == 2)	// 插入右子树导致右子树比左子树高2
			{
				AVLTreeNode<T> *pnode = proot->rchild;
				if (key > pnode->key)
				{
					leftRotation(proot);		// 高的地方在右子树的右子树上， 左旋
				}
				else if(key < pnode->key)
				{
					rightLeftRotation(proot);	// 高的地方在右子树的左子树上， 右旋后左旋
				}
			}
		}
		else if (key < proot->key)
		{
			insert(proot->lchild, key);
			if (height(proot->lchild) - height(proot->rchild) == 2)
			{
				AVLTreeNode<T> *pnode = proot->lchild;
				if (key < pnode->key)
				{
					rightRotation(proot);
				}
				else if(key > pnode->key)
				{
					leftRightRotation(proot);
				}
			}
		}
	}
	proot->height = std::max(height(proot->lchild), height(proot->rchild)) + 1;
	return proot;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& proot, T key)
{
	if (proot != nullptr)
	{
		if (key > proot->key)
		{
			remove(proot->rchild, key);
			if (height(proot->lchild) - height(proot->rchild) == 2)
			{
				if (height(proot->lchild->lchild) > height(proot->lchild->rchild))
				{
					rightRotation(proot);
				}
				else
				{
					leftRightRotation(proot);
				}
			}
		}
		else if (key < proot->key)
		{
			remove(proot->lchild, key);
			if (height(proot->rchild) - height(proot->lchild) == 2)
			{
				if (height(proot->rchild->lchild) > height(proot->rchild->rchild))
				{
					rightLeftRotation(proot);
				}
				else
				{
					leftRotation(proot);
				}
			}
		}
		else
		{
			if (proot->lchild != nullptr && proot->rchild != nullptr)
			{
				if (height(proot->lchild) > height(proot->rchild))
				{
					AVLTreeNode<T> *pnode = maximum(proot->lchild);
					proot->key = pnode->key;
					remove(proot->lchild, pnode->key);
				}
				else
				{
					AVLTreeNode<T> *pnode = minimum(proot->rchild);
					proot->key = pnode->key;
					remove(proot->rchild, pnode->key);
				}
			}
			else
			{
				AVLTreeNode<T> *pnode = proot->lchild;
				if (proot->rchild != nullptr)
				{
					pnode = proot->rchild;
				}
				AVLTreeNode<T> *td = proot;
				proot = pnode;
				delete td;
				return nullptr;
			}
		}
		return proot;
	}
	return nullptr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* proot, T key)
{
	if (proot != nullptr)
	{
		if (key == proot->key)
		{
			return proot;
		}
		else if (key < proot->key)
		{
			return search(proot->lchild, key);
		}
		else
		{
			return search(proot->rchild, key);
		}
	}
	return nullptr;
}

template<typename T>
int AVLTree<T>::height()
{
	return height(root);
}

template<typename T>
void AVLTree<T>::preOrder()
{
	preOrder(root);
	cout << endl;
}

template<typename T>
void AVLTree<T>::inOeder()
{
	inOrder(root);
	cout << endl;
}

template<typename T>
void AVLTree<T>::postOrder()
{
	postOrder(root);
	cout << endl;
}

template<typename T>
void AVLTree<T>::treeOutput()
{
	treeOutput(root, 1);
}

template<typename T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T> *pnode = maximum(root);
	if (pnode != nullptr)
	{
		return pnode->key;
	}
	return T();
}

template<typename T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T> *pnode = minimum(root);
	if (pnode != nullptr)
	{
		return pnode->key;
	}
	return T();
}

template<typename T>
void AVLTree<T>::insert(T key)
{
	insert(root, key);
}

template<typename T>
void AVLTree<T>::remove(T key)
{
	remove(root, key);
}

template<typename T>
bool AVLTree<T>::contain(T key)
{
	return search(root, key) != nullptr;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>*& proot)
{
	AVLTreeNode<T> *xroot = proot->rchild;
	proot->rchild = xroot->lchild;
	xroot->lchild = proot;
	
	proot->height = std::max(height(proot->lchild), height(proot->rchild)) + 1;
	xroot->height = std::max(height(xroot->lchild), height(xroot->rchild)) + 1;
	proot = xroot;
	return proot;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>*& proot)
{
	AVLTreeNode<T> *xroot = proot->lchild;
	proot->lchild = xroot->rchild;
	xroot->rchild = proot;

	proot->height = std::max(height(proot->lchild), height(proot->rchild)) + 1;
	xroot->height = std::max(height(xroot->lchild), height(xroot->rchild)) + 1;
	proot = xroot;
	return proot;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>*& proot)
{
	leftRotation(proot->lchild);
	rightRotation(proot);
	return proot;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>*& proot)
{
	rightRotation(proot->rchild);
	leftRotation(proot);
	return proot;
}

template<typename T>
int AVLTree<T>::height(AVLTreeNode<T> *pnode)
{
	if (pnode != nullptr)
	{
		return pnode->height;
	}
	return 0;
}

template<typename T>
void AVLTree<T>::destory()
{
	destory(root);
}
