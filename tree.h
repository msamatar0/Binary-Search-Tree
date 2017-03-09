#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
using namespace std;

template<typename t> struct node{
	t obj;
	node<t> *p = nullptr,
		*left = nullptr,
		*right = nullptr;
	node(t o): obj(o){}
};

template<typename t> class binSearchTree{
	node<t> *root = nullptr;
	//Recursively adds elements based on natural ordering
	void addRec(t o, node<t> *l){
		if(l->obj > o)
			if(l->left == nullptr)
				l->left = new node<t>(o);
			else
				addRec(o, l->left);
		else
			if(l->right == nullptr)
				l->right = new node<t>(o);
			else
				addRec(o, l->right);
	}
	//Recursively searches tree using binary search
	node<t> *searcRec(t k, node<t> *l){
		if(l != nullptr){
			if(k == l->obj)
				return l;
			else if(k < l->obj)
				return search(k, l->left);
			else if(k > l->obj)
				return search(k, l->right);
		}
		else
			return nullptr; //Not found
	}
	//Recursively adds up nodes until end of tree
	int countRec(node<t> *l){
		if(l == nullptr)
			return 0;
		else
			return countRec(l->left) + countRec(l->right) + 1;
	}
	//Returns height of larger node's subtree
	int heightRec(node<t> *l){
		if(l == nullptr)
			return 0;
		else
			return heightRec(l->left->obj > l->right->obj ? l->left : l->right) + 1;	//Steps into node with higher obj
	}
	//Removes a node and shifts its descendant nodes
	bool removeRec(node<t> *p, node<t> *l, t o){
		if(l == nullptr)
			return false;
		if(l->obj == o){
			if(l->left == nullptr || l->right == nullptr){
				node<t> *temp = l->left;
				if(l->right != nullptr)
					temp = l->right;
				if(p != nullptr)
					if(p->left == l)
						p->left = temp;
					else
						p->right = temp;
				else
					root = temp;
			}
			else{
				node<t> *s = l->right;
				while(s->left != nullptr)
					s = s->left;
				t tempObj = l->obj;
				l->obj = s->obj;
				s->obj = tempObj;
				return removeRec(l, l->right, tempObj);
			}
			delete l;
			return true;
		}
		return removeRec(l, l->left, o) || removeRec(l, l->right, o);
	}
	//Recursively deletes tree
	void clearRec(node<t> *l){
		if(l == nullptr){
			clearRec(l->left);
			clearRec(l->right);
			delete l;
		}
	}
	//The following functions recursively traverse and print the tree based on postorder, inorder, and preorder
	void postorderRec(node<t> *l){
		if(l == nullptr)
			return;
		postorderRec(l->left);
		postorderRec(l->right);
		cout << l->obj << ' ';
	}
	void inorderRec(node<t> *l){
		if(l == nullptr)
			return;
		inorderRec(l->left);
		cout << l->obj << ' ';
		inorderRec(l->right);
	}
	void preorderRec(node<t> *l){
		if(l == nullptr)
			return;
		cout << l->obj << ' ';
		preorderRec(l->left);
		preorderRec(l->right);
	}
public:
	binSearchTree(){}
	binSearchTree(const binSearchTree<t> &b){
		addRec(b->root);
	}
	~binSearchTree(){
		clearRec(root);
	}
	//Uses recursion to count # of nodes
	int size(){
		return countRec(root);
	}
	//Returns true if no nodes added
	bool empty(){
		return root == nullptr;
	}
	//Uses private recursive function to add a node
	void add(t o){
		if(empty())
			root = new node<t>(o);
		else
			addRec(o, root);
	}
	//Uses the binary search tree's ordering to preform binary search
	node<t> *search(t k){
		return searcRec(k, root);
	}
	//Counts while searching for deepest node
	int height(){
		return heightRec(root);
	}
	//Calls recursive function to delete a node
	bool remove(t o){
		return removeRec(nullptr, root, o);
	}
	//Calls recursive traversal functions
	void postorder(){
		cout << "postorder: ";
		postorderRec(root);
		cout << endl;
	}
	void inorder(){
		cout << "inorder: ";
		inorderRec(root);
		cout << endl;
	}
	void preorder(){
		cout << "preorder: ";
		preorderRec(root);
		cout << endl;
	}
	//Prints elements of tree using breadth-first ordering
	void breadth(){
		queue<node<t> *> nq;	//Queue holds elements to be traversed later
		node<t> *temp;
		if(root == nullptr)
			return;
		cout << "breadth-first: ";
		nq.push(root);
		while(!nq.empty()){
			temp = nq.front();
			cout << temp->obj << ' ';
			nq.pop();
			if(temp->left != nullptr)
				nq.push(temp->left);
			if(temp->right != nullptr)
				nq.push(temp->right);
		}
		cout << endl;
	}
	//Prints tree level-by-level
	friend ostream &operator<<<t>(ostream &tout, binSearchTree &b){
		tout << endl;
		queue<node<t> *> nq;	//Queue holds elements to be traversed later
		node<t> *temp;
		if(b.root == nullptr)
			return tout;
		nq.push(b.root);
		tout << "Tree:\n";
		while(true){
			int nodes = nq.size();
			if(nodes == 0)
				break;
			while(nodes > 0){
				temp = nq.front();
				tout << temp->obj << "  ";
				nq.pop();
				if(temp->left != nullptr){
					nq.push(temp->left);
					//cout << "  ";
				}
				if(temp->right != nullptr){
					nq.push(temp->right);
					//cout << "  ";
				}
				nodes--;
			}
			cout << endl;
		}
		return tout << endl;
	}
};

