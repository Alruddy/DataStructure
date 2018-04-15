#include <iostream>
#include <iterator>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;


struct TreeNode
{
	int val;
	TreeNode *lchild;
	TreeNode *rchild;
	TreeNode(int v) : val(v), lchild(nullptr), rchild(nullptr) { }
};

TreeNode *createTree(istream_iterator<int> &beg, istream_iterator<int> &end, TreeNode *&p) {
	if (beg == end) {
		return nullptr;
	}
	if (*beg == -1) {
		p = nullptr;
		beg++;
		return p;
	}
	p = new TreeNode(*beg);
	beg++;
	p->lchild = createTree(beg, end, p->lchild);
	p->rchild = createTree(beg, end, p->rchild);
	return p;
}

void visit(int val) {
	cout << val << ' ';
}

void PreOrder(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	visit(root->val);
	if (root->lchild) {
		PreOrder(root->lchild, visit);
	}
	if (root->rchild) {
		PreOrder(root->rchild, visit);
	}
}

void InOrder(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	if (root->lchild) {
		InOrder(root->lchild, visit);
	}
	visit(root->val);
	if (root->rchild) {
		InOrder(root->rchild, visit);
	}
}

void PostOrder(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	if (root->lchild) {
		PostOrder(root->lchild, visit);
	}
	if (root->rchild) {
		PostOrder(root->rchild, visit);
	}
	visit(root->val);
}

void PreOrder_N(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		TreeNode *p = s.top();
		visit(p->val);
		s.pop();
		if (p->rchild) {
			s.push(p->rchild);
		}
		if (p->lchild) {
			s.push(p->lchild);
		}
	}
}

void PreOrder_N_1(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	stack<TreeNode *> s;
	TreeNode *p = root;
	while (p != nullptr || !s.empty()) {
		while (p != nullptr) {
			s.push(p);
			visit(p->val);
			p = p->lchild;
		}
		p = s.top();
		s.pop();
		p = p->rchild;
	}
}

void InOrder_N(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	stack<TreeNode *> s;
	TreeNode *p = root;
	while (p != nullptr || !s.empty())
	{
		while (p != nullptr) {
			s.push(p);
			p = p->lchild;
		}
		p = s.top();
		visit(p->val);
		s.pop();
		p = p->rchild;
	}
}

void InOrder_N_1(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	TreeNode *pcur = nullptr;
	// goFirst
	TreeNode *p = root;
	stack<TreeNode*> s;
	while (p->lchild != nullptr) {
		s.push(p);
		p = p->lchild;
	}
	pcur = p;
	visit(pcur->val);
	// next
	while (true) {
		p = pcur;
		if (p->rchild != nullptr) {
			p = p->rchild;
			while (p->lchild != nullptr) {
				s.push(p);
				p = p->lchild;
			}
			pcur = p;
			visit(pcur->val);
		}
		else if (!s.empty()) {
			pcur = s.top();
			s.pop();
			visit(pcur->val);
		}
		else {
			pcur = nullptr;
			break;
		}
	}
}

void PostOrder_N(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	stack<TreeNode* > s;
	stack<TreeNode *> order;
	TreeNode *p = root;
	s.push(root);
	while (!s.empty()) {
		p = s.top();
		order.push(p);
		s.pop();
		if (p->lchild) {
			s.push(p->lchild);
		}
		if (p->rchild) {
			s.push(p->rchild);
		}
	}
	while (!order.empty()) {
		visit(order.top()->val);
		order.pop();
	}
}


int VisitNodeAtLevel(TreeNode *root, int level, void(*visit)(int val)) {
	if (root == nullptr || level < 0) {
		return 0;
	}
	if (level == 0) {
		visit(root->val);
		return 1;
	}
	return VisitNodeAtLevel(root->lchild, level - 1, visit) +
		VisitNodeAtLevel(root->rchild, level - 1, visit);
}

void LevelOrder(TreeNode *root, void(*visit)(int val)) {
	for (int i = 0; ; i++) {
		if (!VisitNodeAtLevel(root, i, visit)) {
			break;
		}
	}
}

void LevelOrder_N(TreeNode *root, void(*visit)(int val)) {
	if (root == nullptr) {
		return;
	}
	queue<TreeNode *> Q;
	Q.push(root);
	while (!Q.empty())
	{
		TreeNode *pt = Q.front();
		visit(pt->val);
		Q.pop();
		if (pt->lchild) {
			Q.push(pt->lchild);
		}
		if (pt->rchild) {
			Q.push(pt->rchild);
		}
	}
}


int main()
{
	TreeNode *root = nullptr;
	ifstream in("data.txt");
	istream_iterator<int> int_it(in);
	istream_iterator<int> int_end;
	root = createTree(int_it, int_end, root);
	cout << "二叉树遍历" << endl << endl;
	cout << "递归版先序遍历: " << endl;
	PreOrder(root, visit); cout << endl;
	cout << "非递归版先序遍历1: " << endl;
	PreOrder_N(root, visit); cout << endl;
	cout << "非递归版先序遍历2: " << endl;
	PreOrder_N_1(root, visit); cout << endl << endl;
	cout << "递归版中序遍历: " << endl;
	InOrder(root, visit); cout << endl;
	cout << "非递归版中序遍历1: " << endl;
	InOrder_N(root, visit); cout << endl;
	cout << "非递归版中序遍历2: " << endl;
	InOrder_N_1(root, visit); cout << endl << endl;
	cout << "递归版后序遍历: " << endl;
	PostOrder(root, visit); cout << endl;
	cout << "非递归版后序遍历:" << endl;
	PostOrder_N(root, visit); cout << endl << endl;
	cout << "非递归版层序遍历: " << endl;
	LevelOrder_N(root, visit); cout << endl;
	cout << "递归版层序遍历: " << endl;
	LevelOrder(root, visit); cout << endl;
	system("pause");
	return 0;
}