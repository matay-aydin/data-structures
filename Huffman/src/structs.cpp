//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Matay Aydin
//---Student Number: 150200075
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue()
{
    this->head = NULL;
};

// Destructor
PriorityQueue::~PriorityQueue()
{
    // Catch dequeued node
    Node *n = this->dequeue();
    // delete nodes until the queue becomes empty.
    while (n != NULL)
    {
        delete n;
        n = this->dequeue();
    }
}

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node *newnode)
{
    // Ensuring next is not a dangling pointer
    newnode->next = NULL;
    if (this->head == NULL) // If the queue is empty, assign newnode as head.
    {
        this->head = newnode;
    }
    else if (newnode->token.val < this->head->token.val) // If the value inside newnode is less than of the root, push newnode to head
    {
        newnode->next = this->head;
        this->head = newnode;
    }
    else if (newnode->token.val >= this->head->token.val && this->head->next == NULL)
    {
        // If there is only one node in the queue and the value inside newnode is greater than
        // or equal to that node, then push newnode to the end.
        this->head->next = newnode;
    }
    else
    {
        Node *ptr = this->head; // Guide pointer.
        int value = newnode->token.val;
        while (ptr != NULL)
        {
            int val_ptr = ptr->token.val;
            if (value < val_ptr) // If newnode has smaller value than the value of the node that is pointed by ptr,
            // then push it in front of that node by following steps provided.
            {
                newnode->next = ptr;
                Node *ptr2 = this->head;
                while (ptr2->next != ptr) // Move ptr2 until it comes to just before of ptr.
                {
                    ptr2 = ptr2->next;
                }
                ptr2->next = newnode;
                break;
            }
            ptr = ptr->next; // Advence ptr to the next node.
        }
        if (ptr == NULL) // If the entire queue is traversed yet no suitable place is found to newnode,
        // then push it to the end.
        {
            Node *ptr2 = this->head;
            while (ptr2->next != NULL)
            {
                ptr2 = ptr2->next;
            }
            ptr2->next = newnode;
        }
    }
};

//-------------Remove Node From Priority Queue-------------//
Node *PriorityQueue::dequeue()
{
    if (this->head != NULL) // Head node removal.
    {
        Node *top = this->head;
        this->head = this->head->next;
        top->next = NULL;
        return top;
    }
    else // return NULL if the queue is empty
    {
        return NULL;
    }
};

//-------------Initialize Tree-------------//
Tree::Tree()
{
    this->root = NULL; // Avoid dangling pointer
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree()
{
    this->deleteTree(this->root); // Call auxilary deleteNode function.
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node *node)
{
    if (node != NULL) // Recursively delete nodes from the tree.
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = NULL;
    }
    return;
}

//-------------Merges Two Node Into One-------------//
Node *Tree::mergeNodes(Node *temp1, Node *temp2)
{
    Node *merged = new Node;
    merged->token.val = temp1->token.val + temp2->token.val;          // Merge values.
    merged->token.symbol = temp1->token.symbol + temp2->token.symbol; // Merge symbols.
    return merged;
};

void Tree::printTree(Node *traverse, int level)
{
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t";

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if (traverse->left)
        printTree(traverse->left, level + 1);
    if (traverse->right)
        printTree(traverse->right, level + 1);
};