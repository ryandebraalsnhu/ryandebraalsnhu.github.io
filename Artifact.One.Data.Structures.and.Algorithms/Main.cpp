// Name         : eBid Search                                        
// Author       : Ryan DeBraal
// Date         : 2021-07-18
// Version      : 1.1

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include "CSVparser.hpp"
using namespace std;

#pragma region Global definitions

//Constants
const string APP_NAME = "eBid Search";
const string DEFAULT_CSV_PATH = "eBid_Monthly_Sales_Dec_2016.csv";
const string DEFAULT_BID_ID = "98109";
const string DIVIDER = "  ----------------------------------------------------- ";
const int QUIT = 9;

//Variables
int menuSelection;
string csvPath;
string searchID;
bool isLoaded = false;

enum class Mode {
    None = 0,
    LinkedList = 1,
    HashTable = 2,
    BinaryTreeSearch = 3
};

struct Bid {
    string bidID;
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

struct Node {
    Bid bid;
    Node* right;
    Node* left;

    Node() {
        right = left = nullptr;
    }

    Node(Bid bid) : Node() {
        this->bid = bid;
    }
};

/*
Method which is used to convert a string to a double
Source: http://stackoverflow.com/a/24875936
@param ch The character to strip out
*/
double ConvertToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/*
Method which is used to determine if a string is null or whitespace
@param str The string being tested for null or whitespace
*/
bool IsNullOrWhitespace(string str) {
    return (str.find_first_not_of(' ') == std::string::npos);
}

/*
Method which is used to calculate elapsed time and display result
@param ticks A clock_t representing a moment in time
*/
void PrintElapsedTime(clock_t ticks) {
    ticks = clock() - ticks; // current clock ticks minus starting clock ticks
    cout << endl << "  Elapsed Time: " << endl;
    cout << "  " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
}

/*
Method which is used to display bid information to the console
@param bid struct containing the bid info
*/
void PrintBid(Bid bid) {
    if (IsNullOrWhitespace(bid.title)
        || bid.amount == 0
        || IsNullOrWhitespace(bid.fund)) {
        return;
    }

    cout << "  Bid #   :  " << bid.bidID << endl;
    cout << "  Title   :  " << bid.title << endl;
    cout << "  Amount  :  " << bid.amount << endl;
    cout << "  Fund    :  " << bid.fund << endl;
    cout << endl;
}

#pragma endregion

#pragma region Linked List

struct node {
    Bid bid;
    node* nextNode;
};

/*
Class containing data members and methods to implement a linked list
*/
class LinkedList {

private:
    node* head;
    node* tail;
    int size;

public:
    LinkedList();
    virtual ~LinkedList();
    void LoadBids(string csvPath);
    void Append(Bid* bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidID);
    Bid Search(string bidID);
    int Size();
};

/*
Constructor
*/
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

/*
Destructor
*/
LinkedList::~LinkedList() {
}

/*
Method which is used to load a CSV file containing bids into a container
@param csvPath the path to the CSV file to load
@return a container holding all the bids read
*/
void LinkedList::LoadBids(string csvPath) {
    if (IsNullOrWhitespace(csvPath)) {
        cout << "ERROR: csvPath is null or whitespace." << endl;
        return;
    }

    cout << "  Loading CSV file: " << csvPath << endl;

    //Initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            //Initialize a new bid
            Bid bid;
            bid.bidID = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = ConvertToDouble(file[i][4], '$');

            //Append bid
            this->Append(&bid);
        }
    }
    catch (csv::Error & e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
Method which is used to append a bid
@param bid The bid to append
*/
void LinkedList::Append(Bid* bid) {
    node* newNode = new node;
    newNode->bid = *bid;
    newNode->nextNode = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        size++;
    }
    else
    {
        tail->nextNode = newNode;
        tail = newNode;
        size++;
    }
}

/*
Method which is used to prepend a new bid to the start of the list
*/
void LinkedList::Prepend(Bid bid) {
    node* newNode = new node;
    newNode->bid = bid;
    newNode->nextNode = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        size++;
    }
    else
    {
        newNode->nextNode = head;
        head = newNode;
        size++;
    }
}

/*
Method which is used to remove a bid
@param bidID The bid id to search for
*/
void LinkedList::Remove(string bidID) {
    node* temp = head;
    node* prevNode{};
    if (temp == nullptr) {
        return;
    }
    else if (head->bid.bidID == bidID && head->nextNode == nullptr)
    {
        head = nullptr;
        tail = nullptr;
        delete temp;
    }
    else
    {
        while (temp->bid.bidID != bidID) {
            prevNode = temp;
            temp = temp->nextNode;
        }

        prevNode->nextNode = temp->nextNode;
        delete temp;
    }

    cout << endl << "  Bid #" << bidID << " has been removed." << endl;
}

/*
Method which is used to print all bids in the linked list
*/
void LinkedList::PrintList() {
    node* ptr = head;

    while (ptr != nullptr) {
        PrintBid(ptr->bid);
        ptr = ptr->nextNode;
    }
}

/*
Method which is used to retrieve a specific bid by ID
@param bidID The unique identifier of a bid
*/
Bid LinkedList::Search(string bidID) {
    node* temp = head;
    node* result = new node;
    result->bid.bidID = "";

    while (temp != nullptr) {
        if (temp->bid.bidID == bidID) {
            return temp->bid;
        }
        temp = temp->nextNode;
    }

    return result->bid;
}

/*
Method which is used to return the current size (number of elements) in the linked list
*/
int LinkedList::Size() {
    return size;
}

#pragma endregion

#pragma region Hash Table

/*
Class containing data members and methods to implement a hash table with chaining
*/
class HashTable {

private:
    const unsigned int HASH_TABLE_SIZE = 1000;

    struct Node {
        Bid Bids;
        unsigned int Key;
        Node* NextNode;
        Node() {
            Key = UINT_MAX;
            NextNode = nullptr;
        }
        Node(Bid bid) : Node() {
            Bids = bid;
        }
        Node(unsigned int key, Bid bid) : Node() {
            key = key;
            Bids = bid;
        }
    };

    vector<Node>node;
    unsigned int hash(int key);

public:
    HashTable();
    virtual ~HashTable();
    void LoadBids(string csvPath);
    void Insert(Bid bid);
    void PrintList();
    void Remove(string bidID);
    Bid Search(string bidID);
};

/*
Constructor
*/
HashTable::HashTable() {
    node.resize(HASH_TABLE_SIZE);
}

/*
Destructor
*/
HashTable::~HashTable() {
    node.erase(node.begin());
}

/*
Method which is used to calculate the hash value of a given key.
@param key The key to hash
@return The calculated hash
*/
unsigned int HashTable::hash(int key) {
    return key % HASH_TABLE_SIZE;
}

/*
Method which is used to load a CSV file containing bids into a container
@param csvPath the path to the CSV file to load
@return a container holding all the bids read
*/
void HashTable::LoadBids(string csvPath) {
    if (IsNullOrWhitespace(csvPath)) {
        cout << "ERROR: csvPath is null or whitespace." << endl;
        return;
    }

    cout << "  Loading CSV file: " << csvPath << endl;

    //Initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            //Initialize a new bid
            Bid bid;
            bid.bidID = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = ConvertToDouble(file[i][4], '$');

            //Push bid to the end
            this->Insert(bid);
        }
    }
    catch (csv::Error & e) {
        std::cerr << e.what() << std::endl;
    }
    cout << endl;
}

/*
Method which is used to insert a bid
@param bid The bid to insert
*/
void HashTable::Insert(Bid bid) {
    int key = hash(atoi(bid.bidID.c_str()));
    Node* n = &(node.at(key));

    if (n != nullptr) {
        if (n->Key == UINT_MAX) {
            n->Key = key;
            n->Bids = bid;
            n->NextNode = nullptr;
        }
        else
        {
            while (true) {
                if (n->NextNode == nullptr) {
                    n = n->NextNode;
                    n = new Node(key, bid);
                }
            }
        }
    }
    else
    {
        Node* newNode = new Node(key, bid);
        node.insert(node.begin() + key, *newNode);
    }
}

/*
Method which is used to remove a bid
@param bidID The bid id to search for
*/
void HashTable::Remove(string bidID) {
    if (IsNullOrWhitespace(bidID)) {
        cout << "ERROR: bidID is null or whitespace." << endl;
        return;
    }

    int key = hash(atoi(bidID.c_str()));
    node.erase(node.begin() + key);
    cout << endl << "  Bid #" << bidID << " has been removed." << endl;
}

/*
Method which is used to print all bids in the hash table
*/
void HashTable::PrintList() {
    for (unsigned int i = 0; i < node.size(); i++) {
        Bid bid = node[i].Bids;
        PrintBid(bid);
    }
    cout << endl;
}

/*
Method which is used to retrieve a specific bid by ID
@param bidID The unique identifier of a bid
*/
Bid HashTable::Search(string bidID) {
    int key = hash(atoi(bidID.c_str()));
    Node* n = &(node.at(key));
    bool isMaxKey = (n->Key == UINT_MAX);
    Bid bid;

    if (n == nullptr || isMaxKey)
        return bid;

    if ((n->Bids.bidID.compare(bidID) == 0) && !isMaxKey) {
        return n->Bids;
    }

    unsigned int count = 0;
    while (count <= HASH_TABLE_SIZE) {
        if (n == nullptr) {
            break;

            if ((n->Bids.bidID.compare(bidID) == 0) && !isMaxKey) {
                return n->Bids;
                n = n->NextNode;
            }
        }
        count++;
    }

    return bid;
}

#pragma endregion

#pragma region Binary Search Tree

/*
Class containing data members and methods to implement a binary search tree
*/
class BinarySearchTree {

private:
    Node* root;
    void addNode(Node* node, Bid bid);
    void traverse(Node* node);
    Node* removeNode(Node* node, string bidID);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void LoadBids(string csvPath);
    void PrintList();
    void Insert(Bid bid);
    void Remove(string bidID);
    Bid Search(string bidID);
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
}

/*
Method which is used to load a CSV file containing bids into a container
@param csvPath the path to the CSV file to load
@return a container holding all the bids read
*/
void BinarySearchTree::LoadBids(string csvPath) {
    if (IsNullOrWhitespace(csvPath)) {
        cout << "ERROR: csvPath is null or whitespace." << endl;
        return;
    }

    cout << "  Loading CSV file: " << csvPath << endl;

    //Initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidID = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = ConvertToDouble(file[i][4], '$');

            //Push this bid to the end
            this->Insert(bid);
        }
    }
    catch (csv::Error & e) {
        std::cerr << e.what() << std::endl;
    }
}

/*
Method which is used to print bids
*/
void BinarySearchTree::PrintList() {
    this->traverse(root);
}

/*
Method which is used to remove a node
*/
Node* BinarySearchTree::removeNode(Node* node, string bidID) {
    if (node == nullptr) {
        return node;
    }

    if (bidID.compare(node->bid.bidID) < 0) {
        node->left = removeNode(node->left, bidID);
    }
    else if (bidID.compare(node->bid.bidID) > 0) {
        node->right = removeNode(node->right, bidID);
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
            node->right = removeNode(node->right, temp->bid.bidID);
        }
    }
    return node;
}

/*
Method which is used to insert a bid
@param bid The bid to insert
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
void BinarySearchTree::Remove(string bidID) {
    if (IsNullOrWhitespace(bidID)) {
        cout << "ERROR: bidID is null or whitespace." << endl;
        return;
    }

    this->removeNode(root, bidID);
    cout << endl << "  Bid #" << bidID << " has been removed." << endl;
}

/*
Method which is used to retrieve a specific bid by ID
@param bidID The unique identifier of a bid
*/
Bid BinarySearchTree::Search(string bidID) {
    Node* current = root;

    while (current != nullptr) {
        if (current->bid.bidID.compare(bidID) == 0) {
            return current->bid;
        }

        if (bidID.compare(current->bid.bidID) < 0) {
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

/*
Method which is used to add a bid to some node (recursive)
@param node Current node in tree
@param bid Bid to be added
*/
void BinarySearchTree::addNode(Node* node, Bid bid) {
    if (node->bid.bidID.compare(bid.bidID) > 0) {
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

/*
Method which is used to recursively travere nodes on the binary search tree
*/
void BinarySearchTree::traverse(Node* node) {
    if (node != nullptr) {
        traverse(node->left);
        Bid bid = node->bid;
        PrintBid(bid);
        traverse(node->right);
    }
}

#pragma endregion

#pragma region UI

Mode mode = Mode::None;
string modeName = "None";

LinkedList* ll = new LinkedList();
HashTable* ht = new HashTable();
BinarySearchTree* bst = new BinarySearchTree();

/*
Method whch is used to process command line arguments supplied at runtime
*/
void ParseArgs(int argc, char* argv[]) {
    switch (argc) {
    case 2:
        csvPath = argv[1];
        searchID = DEFAULT_BID_ID;
        break;
    case 3:
        csvPath = argv[1];
        searchID = argv[2];
        break;
    default:
        csvPath = DEFAULT_CSV_PATH;
        searchID = DEFAULT_BID_ID;
    }
}

/*
Method whch is used to load bids into collection based on mode
*/
void LoadBids() {
    cout << endl;
    cout << DIVIDER << "Load Bids (Mode: " << modeName << ")" << endl;
    cout << endl;

    clock_t ticks = clock();

    switch (mode) {
    case Mode::LinkedList:
        ll = new LinkedList();
        ll->LoadBids(csvPath);
        break;
    case Mode::HashTable:
        ht = new HashTable();
        ht->LoadBids(csvPath);
        break;
    case Mode::BinaryTreeSearch:
        bst = new BinarySearchTree();
        bst->LoadBids(csvPath);
        break;
    }

    isLoaded = true;

    PrintElapsedTime(ticks);
}

/*
Method which is used to select the mode used for loading, searching, adding and removing a bid
*/
void SelectMode() {
    cout << endl;
    cout << DIVIDER << "Select Mode" << endl;
    cout << endl;

    isLoaded = false;
    int modeSelection = 0;

    cout << "  1. Linked List" << endl;
    cout << "  2. Hash Table" << endl;
    cout << "  3. Binary Search Tree" << endl;
    cout << endl;
    cout << "  Enter choice: ";
    cin >> modeSelection;

    switch (modeSelection) {
    case 1:
        mode = Mode::LinkedList;
        modeName = "Linked List";
        break;
    case 2:
        mode = Mode::HashTable;
        modeName = "Hash Table";
        break;
    case 3:
    default:
        mode = Mode::BinaryTreeSearch;
        modeName = "Binary Search Tree";
        break;
    }

    LoadBids();
}

/*
Method which is used for printing bids
*/
void PrintBids() {
    cout << endl;
    cout << DIVIDER << "Display Bid (Mode: " << modeName << ")" << endl;
    cout << endl;

    clock_t ticks = clock();

    switch (mode) {
    case Mode::LinkedList:
        ll->PrintList();
        break;
    case Mode::HashTable:
        ht->PrintList();
        break;
    case Mode::BinaryTreeSearch:
        bst->PrintList();
        break;
    }

    PrintElapsedTime(ticks);
}

/*
Method which is used to find a bid
*/
void Search() {
    if (IsNullOrWhitespace(searchID)) {
        cout << "ERROR: searchID is null or whitespace." << endl;
        return;
    }

    cout << endl;
    cout << DIVIDER << "Find Bid (Mode: " << modeName << ")" << endl;
    cout << endl;

    clock_t ticks = clock();
    Bid bid;

    switch (mode) {
    case Mode::LinkedList:
        bid = ll->Search(searchID);
        break;
    case Mode::HashTable:
        bid = ht->Search(searchID);
        break;
    case Mode::BinaryTreeSearch:
        bid = bst->Search(searchID);
        break;
    }

    if (!bid.bidID.empty()) {
        PrintBid(bid);
    }
    else
    {
        cout << endl << "  Bid #" << searchID << " was not found." << endl;
    }

    PrintElapsedTime(ticks);
}

/*
Method which is used to remove a bid
*/
void RemoveBid() {
    cout << endl;
    cout << DIVIDER << "Remove Bid (Mode: " << modeName << ")" << endl;
    cout << endl;

    clock_t ticks = clock();

    switch (mode) {
    case Mode::LinkedList:
        ll->Remove(searchID);
        break;
    case Mode::HashTable:
        ht->Remove(searchID);
        break;
    case Mode::BinaryTreeSearch:
        bst->Remove(searchID);
        break;
    }

    PrintElapsedTime(ticks);
}

void RenderMenu() {
    cout << endl;
    cout << DIVIDER << APP_NAME << endl;
    cout << "  This application was designed to simplify locating " << endl;
    cout << "  records related to eBid Monthly Sales data." << endl;
    cout << endl;
    cout << "  To begin, select a mode:" << endl;

    SelectMode();

    while (menuSelection != 9) {
        cout << endl;
        cout << DIVIDER << "Main Menu (Mode: " << modeName << ")" << endl;
        cout << endl;
        cout << "  1. Display All Bids" << endl;
        cout << "  2. Search" << endl;
        cout << "  3. Remove Bid" << endl;
        cout << "  4. Reload Bids" << endl;
        cout << "  5. Select Mode" << endl;
        cout << "  9. Quit" << endl;
        cout << endl;
        cout << "  Enter choice: ";
        cin >> menuSelection;

        switch (menuSelection) {
        case 1:
            PrintBids();
            break;
        case 2:
            Search();
            break;
        case 3:
            RemoveBid();
            break;
        case 4:
            LoadBids();
            break;
        case 5:
            SelectMode();
            break;
        case 9:
            //Quit
            break;
        }
    }
}

#pragma endregion

int main(int argc, char* argv[]) {
    ParseArgs(argc, argv);
    RenderMenu();
    cout << "  Thank you for using " << APP_NAME << "!" << endl;
    return 0;
}

