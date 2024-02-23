/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

FIFORep::FIFORep()
{
    this->mpHead = NULL;
    this->mpTail = NULL;
}

FIFORep::FIFORep(ProcessRep *head)
{
    this->mpHead = head;
    this->mpTail = head;
}

FIFORep::~FIFORep()
{
    while (this->mpHead != NULL)
    {
        delete this->dequeue();
    }
    this->mpTail = NULL;
}

void FIFORep::setHead(ProcessRep *head)
{
    this->mpHead = head;
}

ProcessRep *FIFORep::getHead()
{
    return this->mpHead;
}

void FIFORep::setTail(ProcessRep *tail)
{
    this->mpTail = tail;
}

ProcessRep *FIFORep::getTail()
{
    return this->mpTail;
}

void FIFORep::queue(ProcessRep *ptr)
{
    if (this->mpTail != NULL)
    {
        this->mpTail->setNext(ptr);
        this->mpTail = ptr;
        ptr->setNext(NULL);
    }
    else
    {
        this->mpTail = ptr;
        this->mpHead = ptr;
        ptr->setNext(NULL);
    }
}

ProcessRep *FIFORep::dequeue()
{
    ProcessRep *ptr = this->mpHead;
    if (this->mpHead != NULL)
    {
        if (this->mpHead->getNext() == NULL)
        {
            this->setHead(NULL);
            this->setTail(NULL);
        }
        else
        {
            this->setHead(this->mpHead->getNext());
            ptr->setNext(NULL);
            if (this->mpHead == NULL)
            {
                this->setTail(NULL);
            }
        }
    }
    return ptr;
}

ProcessRep *FIFORep::searchID(int id)
{
    ProcessRep *desired = this->getHead();
    for (;;)
    {
        if (desired->getProcessID() == id)
        {
            break;
        }
        else if (desired->getNext() == NULL)
        {
            return NULL;
        }
        desired = desired->getNext();
    }
    return desired;
}

void FIFORep::printFIFO()
{
    ProcessRep *sentinel = this->mpHead;
    while (sentinel != NULL)
    {
        cout << sentinel->getProcessType()
             << sentinel->getProcessID()
             << " " << sentinel->startTime
             << " " << sentinel->endTime
             << " ";

        sentinel = sentinel->getNext();
    }
}