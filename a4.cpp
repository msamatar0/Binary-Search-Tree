/*
 * Mohamed Samatar - 101848
 * Assignment 4 - Binary Search Tree
 * Description - Creates a binary search tree and traverses it in 4 ways
 */
#include "tree.h"

int main(){
	cout << "/*\n * Mohamed Samatar - 101848\n * Assignment 4 - Binary Search Tree\n"
		<< " * Description - Creates a binary search tree and traverses it in 4 ways\n */\n\n";
	int val[14]{88, 12, 24, 49, 7, 25, 55, 18, 19, 13, 109, 18, 44, 1001};
	binSearchTree<int> *bst = new binSearchTree<int>;
	for(int i = 0; i < 14; ++i)
		bst->add(val[i]);
	bst->postorder();
	bst->inorder();
	bst->preorder();
	bst->breadth();
	delete bst;
}