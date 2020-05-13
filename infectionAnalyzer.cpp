//this is one of the two files that you need to submit

#include "infectionAnalyzer.h"
#include <fstream> //for reading file
#include <queue> //you may use STL queue
#include <algorithm> //you may use STL algorithm

using namespace std;
//you are NOT allowed to include additional libraries yourself

//destructor
//dellocate all the trees
InfectionAnalyzer::~InfectionAnalyzer() {
    vector<Tree<string> *>::const_iterator it;
    for (it = trees.begin(); it < trees.end(); ++it) delete *it;
    trees.clear();
}

//load the infection file of the specified filename, and construct the infection trees, return true at the end
//for the file format and examples of the resulting trees, see webpage and sample output
//if the file cannot be loaded, do nothing and return false
//note: it is one of the more challenging tasks. if you cannot implement it completely, you may simply manually construct some trees for testing the other parts of your assignment
bool InfectionAnalyzer::loadInfectionFile(const string filename) {

    vector<pair<string, string>> relations;
    std::ifstream infile(filename);


    string str;
    while (std::getline(infile, str)) {
        string word, parent, child;
        for (auto x : str) {
            if (x == ' ') {
                parent = word;
                word = "";
            } else if (isalnum(x))
                word += x;
        }
        child = word;
        relations.push_back(make_pair(parent, child));
    }

    vector<pair<string, string>>::iterator pair_it;
    for (pair_it = relations.begin(); pair_it < relations.end(); pair_it++) {
        vector<Tree<string> *>::iterator it;
        string parent = pair_it->first, child = pair_it->second;
        Tree<string> *parent_tree = nullptr;
        Tree<string> *child_tree = nullptr;
        for (it = trees.begin(); it < trees.end(); ++it) {
            if (parent_tree == nullptr) parent_tree = (*it)->find(parent);
        }

        vector<Tree<string> *>::iterator it_child;
        for (it_child = trees.begin(); it_child < trees.end();) {
            if (child_tree == nullptr) child_tree = (*it_child)->find(child);
            if (parent_tree != nullptr and child_tree != nullptr) {
                it_child = trees.erase(it_child);
            } else
                it_child++;
        }

        if (parent_tree == nullptr and child_tree == nullptr) {
            Tree<string> *tree = new Tree<string>;
            tree->addRoot(parent);
            tree->addChild(parent, child);
            trees.push_back(tree);
        } else if (parent_tree != nullptr and child_tree == nullptr) {
            parent_tree->addChild(parent, child);
        } else if (parent_tree == nullptr and child_tree != nullptr) {
            child_tree->addRoot(parent);
        } else {
            parent_tree->addChild(parent, child);
            parent_tree->root->children[parent_tree->root->childCount - 1] = *child_tree;
            delete child_tree;
        }
//        printInfectionTrees(cout);
    }


    return true;
}

//return true if the specified name can be found in any of the infection trees
//return false otherwise
bool InfectionAnalyzer::isInfected(const string name) const {
    vector<Tree<string> *>::const_iterator it;
    for (it = trees.begin(); it < trees.end(); ++it)
        if ((*it)->find(name) != nullptr) return true;
    return false;
}

//check all trees, and find the node with the specified name, and return the name of its parent
//if the node with the specified name is a root node of a tree (i.e. no parent), then return "ZERO" to indicate that the person might be a patient-zero
//if the specified name is not found at all in all trees, return "NA"
//see the sample output for examples
//you cannot use recursion for this function
//for hints on solving this iteratively, you may refer to the webpage
string InfectionAnalyzer::getInfectionSource(const string name) const {
    vector<Tree<string> *>::const_iterator it;
    queue<Tree<string>> q;
    for (it = trees.begin(); it < trees.end(); ++it) {
        q.push(**it);
        while (!q.empty()) {
            Tree<string> tmp_tree = q.front();
            if (tmp_tree.root->data == name) return "ZERO";
            for (int i = 0; i < tmp_tree.root->childCount; ++i) {
                if (tmp_tree.root->children[i].root->data == name) return tmp_tree.root->data;
                q.push(tmp_tree.root->children[i]);
            }
            q.pop();
        }
    }
    return "NA";
}

//return the depth of the node with the specified name
//if the specified name is not found at all in all trees, return -1
int InfectionAnalyzer::getInfectionGeneration(const string name) const {
    vector<Tree<string> *>::const_iterator it;
    for (it = trees.begin(); it < trees.end(); ++it)
        if ((*it)->find(name) != nullptr) return (*it)->getDepth(name);
    return -1;
}

//generate the infectionPowerVector and return it
//the infection power of a person is defined as the number of descendants it has in a tree
//the name-power pairs should be ordered by the infection power in descending order
//if two pairs have the the same power, then they are ordered by their names in ascending order (hint: you can directly use > or < to compare strings)
//see the sample output for examples
//you cannot use recursion for this function
//for hints on solving this iteratively, you may refer to the webpage
//note: you should clear the infectionPowerVector at the beginning of this function
const vector<pair<string, int>> &InfectionAnalyzer::getInfectionPowerVector() {
    infectionPowerVector.clear();

    vector<Tree<string> *>::const_iterator it;
    queue<Tree<string>> q;
    for (it = trees.begin(); it < trees.end(); ++it) {
        q.push(**it);
        while (!q.empty()) {
            Tree<string> tmp_tree = q.front();
            infectionPowerVector.push_back(make_pair(tmp_tree.root->data, tmp_tree.getDescendantCount()));
            for (int i = 0; i < tmp_tree.root->childCount; ++i)
                q.push(tmp_tree.root->children[i]);
            q.pop();
        }
    }
    sort(infectionPowerVector.begin(), infectionPowerVector.end(), [](auto &left, auto &right) {
        if (left.second == right.second)
            return left.first < right.first;
        else
            return left.second > right.second;
    });
    return infectionPowerVector;
}