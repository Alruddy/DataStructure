#include "AVLTree.cpp"
#include <cstdlib>
#include <time.h>

int main(int argc, char* argv[])
{
	AVLTree<int> avl;
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < 20; i++)
	{
		avl.insert(rand()%10000);
	}
	avl.inOeder();
	avl.treeOutput();
	for (int i = 0; i < 10000; i++)
	{
		if (avl.contain(i))
		{
			cout << "avl contains " << i << endl;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		avl.remove(avl.minimum());
		avl.inOeder();
	}
	cout << avl.height();
	avl.destory();
	system("pause");
	return 0;
}
