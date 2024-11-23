#include "bst.h"
#include <queue>

using namespace std;

std::ostream &operator<<(std::ostream &os, const BST::Node &node)
{
    os << "Node(" << node.value << ") ";
    if (node.left)
    {
        os << "Node(" << node.left->value << ") ";
    }
    else
    {
        os << "NULL" << " ";
    }

    if (node.right)
    {
        os << "Node(" << node.right->value << ") ";
    }
    else
    {
        os << "NULL" << " ";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const BST &bst)
{
    bst.bfs([&os](auto &node)
            { os << *node << endl; });
    return os;
}
bool operator<(BST::Node node, int n)
{
    return node.value < n;
}
bool operator<(int n, BST::Node node)
{
    return node.value > n;
}
bool operator>(BST::Node node, int n)
{
    return n < node.value;
}
bool operator>(int n, BST::Node node)
{
    return node.value < n;
}
bool operator==(int n, BST::Node node)
{
    return node.value == n;
}
bool operator==(BST::Node node, int n)
{
    return node.value == n;
}
bool operator<=(BST::Node node, int n)
{
    return node == n || node < n;
}
bool operator<=(int n, BST::Node node)
{
    return node == n || node > n;
}
bool operator>=(BST::Node node, int n)
{
    return node == n || node > n;
}
bool operator>=(int n, BST::Node node)
{
    return node == n || node < n;
}

void BST::bfs(std::function<void(Node *&node)> func) const
{
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *cur = q.front();
        // cout << cur << endl;
        q.pop();
        if (cur == nullptr)
        {
            continue;
        }
        q.push(cur->left);
        q.push(cur->right);
        func(cur);
    }
}

size_t BST::length()
{
    size_t ret = 0;
    bfs([&ret](const Node *const &node) -> void
        { ret++; });
    return ret;
}
bool BST::add_node(int value)
{
    cout << "add" << value << endl;
    if (root == nullptr)
    {
        root = new Node(value, nullptr, nullptr);
        return true;
    }
    Node *cur = root;
    while (true)
    {
        if (*cur < value)
        {
            if (cur->right)
            {
                cur = cur->right;
                continue;
            }
            else
            {
                cur->right = new Node(value, nullptr, nullptr);
                return true;
            }
        }
        else if (*cur > value)
        {
            if (cur->left)
            {
                cur = cur->left;
                continue;
            }
            else
            {
                cur->left = new BST::Node(value, nullptr, nullptr);
                return true;
            }
        }
        else
        {
            return false;
        }
    }
}

BST::Node **BST::find_node(int value)
{
    Node *cur = root;
    if (cur->value == value)
    {
        return &root;
    }
    while (cur != nullptr)
    {
        if (cur->left && cur->left->value == value)
        {
            return &cur->left;
        }
        if (cur->right && cur->right->value == value)
        {
            return &cur->right;
        }
        if (*cur > value)
        {
            cur = cur->left;
        }
        else if (*cur < value)
        {
            cur = cur->right;
        }
    }
    return nullptr;
}

BST::Node **BST::find_parrent(int value)
{
    vector<BST::Node *> parents;
    Node *cur = root;
    while (cur)
    {
        parents.push_back(cur);
        if (*cur > value)
        {
            cur = cur->left;
        }
        else if (*cur < value)
        {
            cur = cur->right;
        }
        else
        {
            if (parents.size() == 2)
            {
                return &root;
            }
            else if (parents.size() == 1)
            {
                return nullptr;
            }
            else
            {
                Node *parent = parents[parents.size() - 2];
                Node *grandParent = parents[parents.size() - 3];
                if (grandParent->value > parent->value)
                {
                    return &grandParent->left;
                }
                else
                {
                    return &grandParent->right;
                }
            }
        }
    }
    return nullptr;
}
vector<BST::Node *> find_node_path(BST::Node *root, int value)
{
    vector<BST::Node *> ret;
    BST::Node *cur = root;
    bool found = false;
    while (cur != nullptr)
    {
        ret.push_back(cur);
        if (*cur > value)
        {
            cur = cur->left;
        }
        else if (*cur < value)
        {
            cur = cur->right;
        }
        else
        {
            found = true;
            break;
        }
    }
    if (found)
    {
        return ret;
    }
    else
    {
        return vector<BST::Node *>();
    }
}
BST::Node **BST::find_successor(int value)
{
    cout << value << endl;
    Node *node = *find_node(value);
    if (node->left)
    {
        Node *cur = node->left;
        Node *last = node;
        while (cur->right)
        {
            last = cur;
            cur = cur->right;
        }
        return last->left == cur ? &last->left : &last->right;
    }
    else
    {
        auto path = find_node_path(root, value);
        if (path.size() <= 1)
        {
            return nullptr;
        }
        for (int i = path.size() - 2; i >= 1; i--)
        {
            if (path[i] == path[i - 1]->right)
            {
                if (i >= 2)
                {
                    return path[i - 2]->left == path[i - 1] ? &path[i - 2]->left : &path[i - 2]->right;
                }
                else
                {
                    return &root;
                }
            }
        }
        return nullptr;
    }
}
BST::~BST()
{
    std::vector<Node *> nodes;
    bfs([&nodes](BST::Node *&node)
        { nodes.push_back(node); });
    for (auto &node : nodes)
        delete node;
}
bool BST::delete_node(int value)
{
    Node **parent = find_parrent(value);
    Node **node = find_node(value);
    if (node == nullptr)
    {
        return false;
    }
    if ((*node)->left && (*node)->right)
    {
        Node **successor = find_successor(value);
        int newValue = (*successor)->value;
        delete_node(newValue);
        (*node)->value = newValue;
        return true;
    }
    else if ((*node)->left)
    {
        if (parent == nullptr)
        {
            Node *toDelete = root;
            root = root->left;
            delete toDelete;
            return true;
        }
        Node *updatedNode = (*node)->left;
        delete *node;
        *node = updatedNode;
        return true;
    }
    else if ((*node)->right)
    {
        if (parent == nullptr)
        {
            Node *toDelete = root;
            root = root->right;
            delete toDelete;
            return true;
        }
        Node *updatedNode = (*node)->right;
        delete *node;
        *node = updatedNode;
        return true;
    }
    else
    {
        if (parent == nullptr)
        {
            delete root;
            root = nullptr;
            return true;
        }
        delete *node;
        *node = nullptr;
        return true;
    }
}

BST::BST(const BST &bst)
{
    // cout << bst << endl;
    // cout << "copy" << endl;
    root = nullptr;
    bst.bfs([this](auto &node)
            { this->add_node(node->value); });
}

BST &BST::operator=(const BST &bst)
{
    if (root == bst.root)
    {
        return *this;
    }
    root = nullptr;
    bst.bfs([this](auto &node)
            { this->add_node(node->value); });
    return *this;
}

BST &BST::operator=(BST &&bst)
{
    root = bst.root;
    bst.root = nullptr;
}
BST::BST(BST &&bst)
{
    root = bst.root;
    bst.root = nullptr;
}
BST::BST(std::initializer_list<int> values)
{
    for (int value : values)
    {
        add_node(value); // Insert each value into the BST
    }
}
BST &BST::operator++()
{
    bfs([](auto node) {
        node->value++;
    });
    return *this;
}
BST BST::operator++(int)
{
    BST bst = *this;
    bfs([](auto node) {
        node->value++;
    });
    return bst;
}