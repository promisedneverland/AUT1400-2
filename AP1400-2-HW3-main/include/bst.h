#ifndef BST_H
#define BST_H
#include <iostream>
#include <functional>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node *left, Node *right) : value(value), left(left), right(right) {}
        Node() : value(0), left(nullptr), right(nullptr) {}
        Node(const Node &node)
        {
            value = node.value;
            left = node.left;
            right = node.right;
        }

        int value = 0;
        Node *left = nullptr;
        Node *right = nullptr;
    };

    Node *&get_root() {return root;}
    void bfs(std::function<void(Node *&node)> func) const;
    size_t length() ;
    bool add_node(int value);
    Node **find_node(int value);
    Node **find_parrent(int value);
    Node **find_successor(int value);
    bool delete_node(int value);
    ~BST();
    BST() {root = nullptr;}
    BST(const BST& bst);
    BST(BST&& bst);
    BST& operator=(const BST &bst);
    BST& operator=(BST &&bst);
    BST(std::initializer_list<int> values);
    BST& operator++();
    BST operator++(int);


private:
    Node *root = nullptr;
};
std::ostream &operator<<(std::ostream &os, const BST::Node& node);
std::ostream &operator<<(std::ostream &os, const BST& bst);
bool operator<(BST::Node node, int n);
bool operator<(int n, BST::Node node);
bool operator>(BST::Node node, int n);
bool operator>(int n, BST::Node node);
bool operator==(int n, BST::Node node);
bool operator==(BST::Node node, int n);
bool operator<=(BST::Node node, int n);
bool operator<=(int n, BST::Node node);
bool operator>=(BST::Node node, int n);
bool operator>=(int n, BST::Node node);
#endif // BST_H