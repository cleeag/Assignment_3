//this is one of the two files that you need to submit

using namespace std;
//you are NOT allowed to include additional libraries yourself

//you do NOT need to include "tree.h" in this file
//this is NOT a cpp file, but simply a part of "tree.h"
//see the bottom of tree.h for explanation
//just write your tree implementation here right away


template <typename T>
Tree<T>::Tree(const Tree& another){

}

template <typename T>
const Tree<T>& Tree<T>::operator=(const Tree& another){

}

//search in the whole tree
//and return the tree pointer to the tree with the root node that contains the specified data
//return nullptr if the specified data is not found
template <typename T>
Tree<T>* Tree<T>::find(const T& data){
    if (isEmpty()) return nullptr;
    if (root->data == data) return this;

    for (int i = 0; i < root->childCount; ++i) {
        Tree<T>* target_tree = find(data);
        if (target_tree!= nullptr) return target_tree;
    }
    return nullptr;
}

template <typename T>
const Tree<T>* Tree<T>::find(const T& data) const{
    if (isEmpty()) return nullptr;
    if (root->data == data) return this;

    for (int i = 0; i < root->childCount; ++i) {
        Tree<T>* target_tree = root->children[i].find(data);
        if (target_tree!= nullptr) return target_tree;
    }
    return nullptr;
}

//return the depth of the node that contains the specified data in this whole tree
//return -1 if the tree is empty or the data is not found
//note: root node has a depth of 0
template <typename T>
int Tree<T>::getDepth(const T& data) const{
    if (isEmpty()) return -1;
    else if (root->data == data) return 0;
    else{
        for (int i = 0; i < root->childCount; ++i) {
            int res = root->children[i].getDepth(data);
            if (res != -1) {
                return 1 + res;
            }
        }
        return -1;
    }
}




