//this is one of the two files that you need to submit

using namespace std;
//you are NOT allowed to include additional libraries yourself

//you do NOT need to include "tree.h" in this file
//this is NOT a cpp file, but simply a part of "tree.h"
//see the bottom of tree.h for explanation
//just write your tree implementation here right away


template<typename T>
Tree<T>::Tree(const Tree &another) {
    if (another.isEmpty()) return;
    root = new Node<T>(*another.root);
}

template<typename T>
Tree<T>::~Tree() {
    delete root;
}

template<typename T>
const Tree<T> &Tree<T>::operator=(const Tree &another) {
    if (this != &another) {
        if (root != nullptr) delete root;
        root = new Node<T>(*another.root);
    }
    return *this;
}

//search in the whole tree
//and return the tree pointer to the tree with the root node that contains the specified data
//return nullptr if the specified data is not found
template<typename T>
Tree<T> *Tree<T>::find(const T &data) {
    if (isEmpty()) return nullptr;
//    cout << "root data: "<< root->data << endl;
//    cout << "target data: "<<data << endl;
//    cout << root->data.compare(data) << endl;
    if (root->data.compare(data) == 0) {
//        cout << data << " got it " << this << endl;
        return this;
    }

    for (int i = 0; i < root->childCount; ++i) {
        Tree<T> *target_tree = root->children[i].find(data);
        if (target_tree != nullptr) return target_tree;
    }
    return nullptr;
}

template<typename T>
const Tree<T> *Tree<T>::find(const T &data) const {
    if (isEmpty()) return nullptr;
    if (root->data == data) return this;

    for (int i = 0; i < root->childCount; ++i) {
        const Tree<T> *target_tree = root->children[i].find(data);
        if (target_tree != nullptr) return target_tree;
    }
    return nullptr;
}

//return the depth of the node that contains the specified data in this whole tree
//return -1 if the tree is empty or the data is not found
//note: root node has a depth of 0
template<typename T>
int Tree<T>::getDepth(const T &data) const {
    if (isEmpty()) return -1;
    else if (root->data == data) return 0;
    else {
        for (int i = 0; i < root->childCount; ++i) {
            int res = root->children[i].getDepth(data);
            if (res != -1) {
                return 1 + res;
            }
        }
        return -1;
    }
}

//return the descendant count of the node that contains the specified data in this whole tree
//return -1 if the tree is empty or the data is not found
//note: any direct or indirect child of a node is considered as a descendant of a node
//see sample output for examples
//hint: you may make use of the overloaded version of this function that takes no parameter
template<typename T>
int Tree<T>::getDescendantCount(const T &data) const {
    const Tree<T> *tree = find(data);
    if (isEmpty() or tree == nullptr)
        return -1;
    else
        return tree->getDescendantCount();
}

//return the descendant count of the root node in this whole tree
//return -1 if the tree is empty or the data is not found
template<typename T>
int Tree<T>::getDescendantCount() const {
    if (isEmpty()) return -1;
    else {
        int count = 0;
        for (int i = 0; i < root->childCount; ++i) {
            int res = root->children[i].getDescendantCount();
            if (res != -1) count += res;
        }
        return count + root->childCount;
    }
}


//add a new root with the specified data to the tree, and return true at the end
//if the tree already has a root (i.e. non-empty tree), then make a new root while keeping the existing tree
//that means, you will create a new root node with the specified data; it also has exactly one child which is the old root
//note: if the specified data already exists in the tree, do nothing and return false
template<typename T>
bool Tree<T>::addRoot(const T &data) {
    if (find(data) != nullptr) return false;
    if (root != nullptr) {
        Node<T> *new_root = new Node<T>(data, 1);
        Tree<T> new_tree = Tree<T>();
        new_tree.root = this->root;
        new_root->children[0] = new_tree;
        root = new_root;
    } else root = new Node<T>(data);
    return true;
}

//add a new node (child with data being childData) to an existing node (parent with data being parentData) in the tree, and return true at the end
//however, if the parent node is not found in the tree or if the child data is already in the tree, do nothing and return false
//you should add the child to the parent node's children array so that the children[0] is the first child ever added, children[1] is the second one, and so on
//this is to make sure your output is always the same as ours
template<typename T>
bool Tree<T>::addChild(const T &parentData, const T &childData) {
    Tree<T> *parent_tree = find(parentData);
    if (parent_tree == nullptr or find(childData) != nullptr) return false;
    Tree<T> child_tree{};
    child_tree.root = new Node<T>(childData);

    Node<T> *new_root = new Node<T>(parent_tree->root->data, parent_tree->root->childCount + 1);
    for (int i = 0; i < parent_tree->root->childCount; ++i) {
        new_root->children[i] = parent_tree->root->children[i];
    }
    new_root->children[parent_tree->root->childCount] = child_tree;

    delete parent_tree->root;
    parent_tree->root = new_root;
    return true;
}