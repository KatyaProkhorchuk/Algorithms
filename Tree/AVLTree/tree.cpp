#include <iostream>
template <typename T>
class Node
{
public:
    Node *left;
    Node *right;
    Node *parent;
    T value;
    bool visit = false;
    std::size_t height;
    Node(T val) : value(val), height(1), left(nullptr), right(nullptr), parent(nullptr) {}
};
template <typename T>
class AVLTree
{
public:
    class Iterator
    {
    public:
        Iterator(Node<T> *root, bool flagVisit) : root_(root), flagVisit_(flagVisit) { root_->visit = flagVisit; }
        Iterator &operator--()
        {
            return *this;
        }
        Node<T> *operator->()
        {
            return root_;
        }
        Node<T> &operator*()
        {
            if (root_ == nullptr)
            {
                return *(root_->parent);
            }
            return *root_;
        }
        Iterator &operator++()
        {
            if (root_ == nullptr)
            {
                throw std::out_of_range("nullptr");
            }
            else if (root_->right == nullptr)
            {
                if (root_->parent == nullptr)
                {
                    flagParent = true;
                    height = 0;
                }
                if (flagParent == false)
                {
                    for (int i = 0; i < height; i++)
                    {
                        root_ = root_->parent;
                        root_->visit = true;
                    }
                    height++;
                }
            }
            else
            {
                if (root_->parent == nullptr)
                    height = 1;
                root_ = AVLTree::getLeft(root_->right);
                root_->visit = true;
            }
            return *this;
        }
        bool operator==(Iterator &it)
        {
            return it.root_ == root_;
        }
        bool operator!=(Iterator &it)
        {
            return it.root_ != root_;
        }

    private:
        Node<T> *root_;
        // Node <T> * null_node_;
        bool flagVisit_, flagParent = false;
        int height = 1;
        int flag_;
    };
    static Node<T> *getLeft(Node<T> *root)
    {
        if (root == nullptr)
            return nullptr;
        else if (root->left == nullptr)
            return root;
        else
            return getLeft(root->left);
    }
    static Node<T> *getRight(Node<T> *root)
    {
        if (root == nullptr)
            return nullptr;
        else if (root->right == nullptr)
            return root->right;
        else
            return getRight(root->right);
    }
    Iterator begin()
    {
        return Iterator(getLeft(root_), true);
    }
    Iterator end()
    {
        std::cout << getRight(root_)->value;
        return Iterator(getRight(root_), true);
    }
    AVLTree() : root_(nullptr) {}
    void insert(T val)
    {
        Insert(root_, nullptr, val);
    }
    int getHeight(Node<T> *root)
    {
        if (root == nullptr)
        {
            return 0;
        }
        else
        {
            return root->height;
        }
    }
    Node<T> *rotateright(Node<T> *&root)
    {
        Node<T> *node = root->left;
        root->left = node->right;
        node->right->parent = root;
        node->right = root;
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        node->parent = root->parent;
        root->parent = node;
        root = node;
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        return node;
    }
    Node<T> *rotateleft(Node<T> *&root)
    {
        Node<T> *node = root->right;
        root->right = node->left;
        node->left = root;
        node->left->parent = root;
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        node->parent = root->parent;
        root->parent = node;
        root = node;
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        return node;
    }
    int bfactor(Node<T> *root)
    {
        return getHeight(root->right) - getHeight(root->left);
    }
    Node<T> *balance(Node<T> *&root)
    {

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        if (bfactor(root) == 2)
        {
            if (bfactor(root->right) < 0)
                root->right = rotateright(root->right);
            return rotateleft(root);
        }
        if (bfactor(root) == -2)
        {
            if (bfactor(root->left) > 0)
                root->left = rotateleft(root->left);
            return rotateright(root);
        }
        return root;
    }
    void Insert(Node<T> *&root, Node<T> *p, T val)
    {
        if (root == nullptr)
        {
            root = new Node<T>(val);
            root->parent = p;
            return;
        }
        if (root->value > val)
        {
            Insert(root->left, root, val);
        }
        else
        {
            Insert(root->right, root, val);
        }
        balance(root);
    }
    Node<T> *findmin(Node<T> *p)
    {
        return p->left ? findmin(p->left) : p;
    }
    Node<T> *removemin(Node<T> *p)
    {
        if (p->left == nullptr)
            return p->right;
        p->left = removemin(p->left);
        return balance(p);
    }
    Node<T> *Delete(Node<T> *&root, T val)
    {
        if (root == nullptr)
            return nullptr;
        if (root->value == val)
        {
            Node<T> *node;
            if (!root->right && !root->left)
            {
                root = nullptr;
                return root;
            }
            else if (!root->right)
            {
                return root->left;
            }
            else if (!root->left)
            {
                return root->right;
            }
            else
            {
                Node<T> *p = root->parent;
                Node<T> *q = root->left;
                Node<T> *r = root->right;
                root = nullptr;
                Node<T> *min = findmin(r);

                min->right = removemin(r);
                min->left = q;
                q->parent = min;

                min->height = 1 + std::max(getHeight(min->left), getHeight(min->right));
                balance(min);

                return min;
            }
        }
        else if (root->value > val)
        {
            root->left = Delete(root->left, val);
        }
        else
        {
            root->right = Delete(root->right, val);
        }
        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        balance(root);
        return root;
    }
    void Delete(T val)
    {
        root_ = Delete(root_, val);
    }

private:
    Node<T> *root_;
};
int main()
{
    AVLTree<int> avl;
    avl.insert(21);
    avl.insert(5);
    avl.insert(45);
    avl.insert(13);
    avl.insert(31);
    avl.insert(4);
    avl.insert(50);
    avl.Delete(5);
    auto it = avl.begin();
    // std::cout<<it.root_->value<<"\n";
    // ++it;
    // std::cout<<it.root_->value<<"\n";

    // ++it;
    // std::cout<<it.root_->value<<"\n";
    // ++it;
    // std::cout<<it.root_->value<<"\n";
    // ++it;
    // std::cout<<it.root_->value<<"\n";
    // ++it;
    // std::cout<<it.root_->value<<"\n";
    // ++it;
    // std::cout<<it.root_->value<<"\n";
    // ++it;
    // std::cout<<it.root_->value<<"\n\n";
    for (auto a : avl)
    {
        std::cout << a.value << "\n";
    }
    std::cout << "\n";
}