

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| Binary Search Tree

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void traverse(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Traverse();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/*
Constructor
*/
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

/*
Destructor
*/
BinarySearchTree::~BinarySearchTree() {
    //TODO: Implemented destructor
}

/*
Traverse the tree in order
*/
void BinarySearchTree::Traverse() {
    this->traverse(root);
}

/*
Method which is used to remove a node
*/
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    if (node == nullptr) {
        return node;
    }

    if (bidId.compare(node->bid.bidId) < 0) {
        node->left = removeNode(node->left, bidId);
    }
    else if (bidId.compare(node->bid.bidId) > 0) {
        node->right = removeNode(node->right, bidId);
    }
    else
    {
        //If node has no children, delete the node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        //If there is a left child...
        else if (node->left != nullptr && node->right == nullptr) {
            Node* tempNode = node;
            node = node->left;
            delete tempNode;

        }
        //If there is a right child...
        else if (node->left == nullptr && node->right != nullptr) {
            Node* tempNode = node;
            node = node->right;
            delete tempNode;
        }
        //Otherwise...
        else
        {
            Node* temp = node->right;
            while (&temp->left == nullptr) {
                temp = temp->left;
            }
            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }
    return node;
}

/*
Method which is used to insert a bid
*/
void BinarySearchTree::Insert(Bid bid) {
    if (root == nullptr) {
        root = new Node(bid);
    }
    else
    {
        this->addNode(root, bid);
    }
}

/*
Method which is used to remove a bid
*/
void BinarySearchTree::Remove(string bidId) {
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    Node* current = root;

    while (current != nullptr) {
        if (current->bid.bidId.compare(bidId) == 0) {
            return current->bid;
        }

        if (bidId.compare(current->bid.bidId) < 0) {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (node->bid.bidId.compare(bid.bidId) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(bid);
        }
        else
        {
            this->addNode(node->left, bid);
        }
    }
    else
    {
        if (node->right == nullptr) {
            node->right = new Node(bid);
        }
        else
        {
            this->addNode(node->right, bid);
        }
    }
}

void BinarySearchTree::traverse(Node* node) {
    if (node != nullptr) {
        traverse(node->left);

        Bid bid = node->bid;
        cout << "#" << bid.bidId << " - Title: " << bid.title << " | Amount: " << bid.amount << " | Fund: " << bid.fund << endl;

        traverse(node->right);
    }
}

