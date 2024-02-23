//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Matay Aydin
//---Student Number: 150200075
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char *argv)
{
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if (readKeyFile.is_open())
    {
        while (!readKeyFile.eof())
        {
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey()
{
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency()
{
    // DO NOT CHANGE THIS
    sortKey();
    // DO NOT CHANGE THIS
    Tree t; // Construct a tree to store letters of Key
    string::iterator q;
    for (q = this->sortedKey.begin(); q != this->sortedKey.end(); q++)
    {
        Node *n = new Node;
        n->left = NULL;
        n->right = NULL;
        n->next = NULL;
        n->token.symbol = *q; // Dereference the iterator to get letters.
        if (t.root == NULL)   // If the tree is empty, then n is the new root of the tree.
        {
            t.root = n;
        }
        else
        {
            Node *ptr = t.root;
            while (true) // Traverse the tree to find a suitable place for n
            {
                if (ptr->token.symbol == n->token.symbol) // All left children have equal symbols.
                {
                    while (ptr->left != NULL) // Advence ptr to the leftmost external node.
                    {
                        ptr = ptr->left;
                    }
                    ptr->left = n; // Connect n
                    n->next = ptr; // ptr is the parent of n
                    ptr = t.root;
                    break;
                }
                if (ptr->right != NULL) // Advance ptr to the right child if the symbols are different.
                    ptr = ptr->right;
                else // Tree is entirely traversed, but no suitable place for n is found.
                    break;
            }
            if (n->next == NULL) // If n is not inside of the tree
            {
                ptr->right = n; // Connect n to the rightmost node.
                n->next = ptr;
            }
        }
    }
    // Traverse the tree and insert nodes to queue
    Node *rightTrace = t.root; // Pointer to point right children
    while (rightTrace != NULL) // Traversing from right
    {
        Node *leftTrace = rightTrace; // Pointer to point left children of the node pointed by rightTrace.
        Node *n = new Node;           // A new node to be sent to this->queue
        n->left = NULL;
        n->right = NULL;
        n->next = NULL;
        n->token.val = 0;
        n->token.symbol = leftTrace->token.symbol;
        while (leftTrace != NULL) // Count left children
        {
            n->token.val += 1;           // Increment per left child
            leftTrace = leftTrace->left; // Advence leftTrace to the left
        }
        this->queue.enque(n);           // Enque the node
        rightTrace = rightTrace->right; // advance rightTrace to the right
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree()
{
    this->findFrequency();            // Fill this->queue
    Node *n1 = this->queue.dequeue(); // Hold dequeued node
    Node *n2 = this->queue.dequeue();
    while (n1 != NULL && n2 != NULL) // .dequeue() returns NULL if this->queue is empty
    {
        Node *nMerged = this->huffmanTree.mergeNodes(n1, n2); // Merge nodes that contain minimum values
        nMerged->left = n1;                                   // nMerged is the parent of merged nodes.
        nMerged->right = n2;
        this->huffmanTree.root = nMerged; // nMerged is the root until a new nMerged occurs.
        this->queue.enque(nMerged);
        n1 = this->queue.dequeue(); // Bring new nodes from this->queue
        n2 = this->queue.dequeue();
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree()
{
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node *traverse, string tokenBinary)
{
    string bin = "";
    Node *ptr = traverse;
    while (ptr->left != NULL && ptr->right != NULL) // Traverse the tree
    {
        string nstr = ptr->token.symbol;             // Hold the symbol
        for (unsigned i = 0; i < nstr.length(); i++) // Iterate over nstr
        {
            if (nstr[i] == tokenChar) // If tokenChar is found inside nstr, then ...
            {
                string lstr = ptr->left->token.symbol;       // Hold the symbol of the left child
                bool found = false;                          // The node with symbol tokenChar is not found yet.
                for (unsigned j = 0; j < lstr.length(); j++) // Iterate over lstr
                {
                    if (lstr[j] == tokenChar) // If tokenChar is found inside lstr,
                    {
                        ptr = ptr->left; // Advence ptr to the left
                        found = true;
                        bin += "0"; // Append 0 to bin whenever visiting left.
                        break;
                    }
                }
                if (found)
                    break;
                string rstr = ptr->right->token.symbol;      // lstr does not contain tokenChar.
                for (unsigned j = 0; j < rstr.length(); j++) // Iterate over rstr
                {
                    if (rstr[j] == tokenChar)
                    {
                        ptr = ptr->right;
                        found = true;
                        bin += "1"; // Append 1 to bin whenever visiting right
                        break;
                    }
                }
                if (found)
                    break;
            }
        }
    }
    return bin;
};
//-----------------------------------------------------//

// Auxiliary function to obtain depth of a token
string Huffman::getTokenVal(char tokenChar, Node *traverse)
{
    string val = "";
    int level = 0; // depth
    Node *ptr = traverse;
    while (ptr != NULL && ptr->left != NULL && ptr->right != NULL) // Traverse the tree
    {
        string nstr = ptr->token.symbol;
        for (unsigned i = 0; i < nstr.length(); i++)
        {
            if (nstr[i] == tokenChar)
            {
                // Visit the left child if the symbol of it contains tokenChar
                string lstr = ptr->left->token.symbol;
                bool found = false;
                for (unsigned j = 0; j < lstr.length(); j++)
                {
                    if (lstr[j] == tokenChar)
                    {
                        ptr = ptr->left;
                        found = true;
                        level++; // Increment depth
                        break;
                    }
                }
                if (found)
                    break;
                // Visit the right child if the symbol of it contains tokenChar
                string rstr = ptr->right->token.symbol;
                for (unsigned j = 0; j < rstr.length(); j++)
                {
                    if (rstr[j] == tokenChar)
                    {
                        ptr = ptr->right;
                        found = true;
                        level++;
                        break;
                    }
                }
                if (found)
                    break;
            }
        }
    }
    val = to_string(level); // Convert to string
    return val;
}

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password)
{
    string::iterator q;               // Declare an iterator
    this->encodedBinaryPassword = ""; // Make sure the passwords are empty
    this->encodedValPassword = "";
    for (q = password.begin(); q != password.end(); q++) // Iterate over password
    {
        // Encode the given char, then append the returned string to the passwords.
        this->encodedBinaryPassword += this->getTokenBinary(*q, this->huffmanTree.root, "");
        this->encodedValPassword += this->getTokenVal(*q, this->huffmanTree.root);
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword()
{
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword)
{
    this->encodedBinaryPassword = encodedBinaryPassword;
    this->encodedValPassword = encodedValPassword;
    this->decodedPassword = ""; // Make sure it to be empty
    int count = 0;              // Hold the sum of values
    unsigned i = 0;
    while (i < this->encodedValPassword.length())
    {
        int val = this->encodedValPassword[i] - 48;                        // Recall that '0' = 48 from ascii table
        this->decodeToken(this->encodedBinaryPassword.substr(count, val)); // Decode suitable number of bits per iteration
        count += val;
        i++;
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken)
{
    string::iterator q;
    Node *ptr = this->huffmanTree.root;
    for (q = encodedToken.begin(); q != encodedToken.end(); q++)
    {
        if (*q == '0') // Move to the left whenever you get 0
        {
            ptr = ptr->left;
        }
        else // Move to the left whenever you get 1
        {
            ptr = ptr->right;
        }
    }
    this->decodedPassword += ptr->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword()
{
    cout << "Decoded Password: " << decodedPassword << endl;
};