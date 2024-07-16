/**
 * @file lab8.cpp
 * @author Khalid Mengal
 * @description BST Tree implementation in C++
 * @date 2022-11-03
 */
#pragma once
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<cstring>
#include<iomanip>
#include<math.h>
#include<queue>
#include<vector>
#include "hotel.h"

using namespace std;
template <typename T1, typename T2>
class Node
{
	private:
		T1 key;					//city name
		vector<T2> value;		//list of hotels in the city
		Node<T1,T2>* left;		//left child
		Node<T1,T2>* right;		//right child
		Node<T1,T2>* parent;	//pointer to the parent node
	public:
		Node(T1 key): key(key),left(nullptr),right(nullptr), parent(nullptr) 
		{}
		void print(string stars="")	//print all or only those hotels with specific stars.
		{
			int counter=0;
			cout<<std::left<<setw(50)<<"Name"<<" "<<setw(10)<<"City"<<" "<<setw(5)<<"Stars"<<" "<<setw(10)<<"Price"<<" "<<setw(20)<<"Country"<<" "<<"Address"<<endl;
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;

			for (typename std::vector<T2>::iterator it = value.begin(); it != value.end(); ++it)
            {
                if (stars == "" or stars == (*it)->getStars()) // Use *it to access the pointed object
                {
                    (*it)->print(); // Use (*it) to call member functions
                    counter++;
                }
            }
			
			cout<<"------------------------------------------------------------------------------------------------------------"<<endl;
			cout<<counter<<" records found."<<endl;
		}

		template<typename,typename> friend class BST;
};
//=============================================================================

template <typename T1, typename T2>
class BST
{
	private:
		Node<T1,T2> *root;
        void destroyTree(Node<T1, T2>* node) {
            if (node) {
                destroyTree(node->left);
                destroyTree(node->right);
                delete node;
            }
        }
	public:
		BST();                                    //constructor
        ~BST();                                 //destructor
        Node<T1, T2>* getRoot();
;                     //returns the root of the Tree
        void insert(Node<T1, T2>* ptr, T1 key, T2 value);         //Insert key into tree/subtree with root ptr
        int height(Node<T1, T2>* ptr);                   //Find the height of a tree/subtree with root ptr
        Node<T1,T2>* find(Node<T1,T2> *ptr,T1 key,string stars);        //Find and returns the node with key
        Node<T1,T2>* findMin(Node<T1,T2> *ptr);             //Find and return the Node<T1,T2> with minimum key value from a tree/subtree with root ptr
        list<T2> findAll(T1 key);
        void findAllUtil(Node<T1, T2>* node, T1 key, list<T2>& hotels);
        void remove(Node<T1,T2> *ptr,T1 key, T2 value);         //Remove a node with key from the tree/subtree with root
};
//=====================================================================
//write implementation of all methods below

//constructor
template <typename T1, typename T2>
BST<T1, T2>::BST() : root(nullptr) {}

//destructor
template <typename T1, typename T2>
BST<T1, T2>::~BST() {
    destroyTree(root);
}
// Get the root of the trr
template <typename T1, typename T2>
Node<T1, T2>* BST<T1, T2>::getRoot() {
    return root;
}

//get the hotels of a specific city(key)
template <typename T1, typename T2>
list<T2> BST<T1, T2>::findAll(T1 key) {
    list<T2> hotels;
    findAllUtil(root, key, hotels);
    return hotels;
}

//a helper method to help fin all the cities according to the search filer
template <typename T1, typename T2>
void BST<T1, T2>::findAllUtil(Node<T1, T2>* node, T1 key, list<T2>& hotels) {
    if (node == nullptr) {// if the node is the empty
        return;
    }

    if (node->key == key) {//if we find the name of the city
        hotels.insert(hotels.end(), node->value.begin(), node->value.end());
    }

    if (key < node->key) {//if the key is the smaller one, find in the left half
        findAllUtil(node->left, key, hotels);
    } else if (key > node->key) {//if the key is the bigger one, find in the right half
        findAllUtil(node->right, key, hotels);
    }
}


// insert method
template <typename T1, typename T2>
void BST<T1, T2>::insert(Node<T1, T2>* ptr, T1 key, T2 value) {

    if (ptr == nullptr) {// if the tree is empty, insert at root
        root = new Node<T1, T2>(key);
        root->value.push_back(value);

    } else if (key < ptr->key) {//if the key is the smaller one, go to the left childresn
        if (ptr->left == nullptr) {//if left child doesnt exist
            ptr->left = new Node<T1, T2>(key);//add at the left child
            ptr->left->parent = ptr;//make the node its parent
            ptr->left->value.push_back(value);//insert the value
        } else {//if left child exists, recursively calll
            insert(ptr->left, key, value);
        }


    } else if (key > ptr->key) { //if the key is the bigger one, go to the right childresn
        if (ptr->right == nullptr) {//if right child doesnt exist
            ptr->right = new Node<T1, T2>(key);//add at the right child
            ptr->right->parent = ptr;//make the node its parent
            ptr->right->value.push_back(value);//insert the value
        } else {
            insert(ptr->right, key, value);//if right child exists, recursively calll
        }
    } else {
        ptr->value.push_back(value);
    }
}


// to get the height of the tree
template <typename T1, typename T2>
int BST<T1, T2>::height(Node<T1, T2> *ptr) {
    if (ptr == nullptr) {//if it is empty, return -1
        return -1;
    } else {
        return 1 + max(height(ptr->left), height(ptr->right));//unless add 1 to its child's height(which has the maximum height)
    }
}




// Find according to the given key
template <typename T1, typename T2>
Node<T1, T2>* BST<T1, T2>::find(Node<T1, T2> *ptr, T1 key, string stars) {
    if (ptr == nullptr || ptr->key == key) {// if the tree is empty, or the key  is at the root
        return ptr;
    } else if (key < ptr->key) {//if the key is the smaller one, find in the left half
        return find(ptr->left, key, stars);
    } else {
        return find(ptr->right, key, stars);//if the key is the bigger one, find in the right half
    }
}
// Find the Minimum(left most)
template <typename T1, typename T2>
Node<T1, T2>* BST<T1, T2>::findMin(Node<T1, T2> *ptr) {
    while (ptr && ptr->left != nullptr) {// if the tree is not empty, continue until it can find a descendent which does not ahve left child
        ptr = ptr->left;
    }
    return ptr;
}

//remove a node from the tree
template <typename T1, typename T2>
void BST<T1, T2>::remove(Node<T1, T2>* ptr, T1 key, T2 value) {
    if (!ptr) {
        ptr = root;
    }

    Node<T1, T2> **target = &ptr;
    while (*target) {
        if (key < (*target)->key) {//if the key is the smaller one, find in the left half
            target = &((*target)->left);


        } else if (key > (*target)->key) {//if the key is the bigger one, find in the right half
            target = &((*target)->right);

            
        } else {
            typename std::vector<T2>& values = (*target)->value;
            typename std::vector<T2>::iterator newEnd = std::remove(values.begin(), values.end(), value);
            values.erase(newEnd, values.end());
            if (values.empty()) {
                // Node to be deleted
                if (!(*target)->left) {
                    Node<T1, T2> *rightChild = (*target)->right;
                    delete *target;
                    *target = rightChild;
                } else if (!(*target)->right) {
                    Node<T1, T2> *leftChild = (*target)->left;
                    delete *target;
                    *target = leftChild;
                } else {
                    // Node with two children: Find in-order successor
                    Node<T1, T2> **succ = &((*target)->right);
                    while ((*succ)->left) {
                        succ = &((*succ)->left);
                    }
                    // Swap values
                    (*target)->key = (*succ)->key;
                    (*target)->value = (*succ)->value;
                    // Remove successor
                    Node<T1, T2> *succRight = (*succ)->right;
                    delete *succ;
                    *succ = succRight;
                }
                return;
            }
        }
    }
}


template class BST<string, Hotel*>;
template class Node<string, Hotel*>;


