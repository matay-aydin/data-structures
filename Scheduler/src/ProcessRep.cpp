/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#include <iostream> 
#include <stdio.h>
#include <string.h>
#include <string>
#include "ProcessRep.h"


using namespace std;

ProcessRep::ProcessRep(string processType, int processID, int deliverTime, int processTime)
{   
    this->mProcessType = processType;
    this->mProcessID = processID;
    this->mDeliverTime = deliverTime;
    this->mProcessTime = processTime;
    this->remainingTime = -1;
    this->startTime = -1;
    this->endTime = -1;
    this->mpNext = NULL;
}

ProcessRep::~ProcessRep()
{
    if(this->mpNext != NULL)
    {
        delete mpNext;
    }
}

ProcessRep* ProcessRep::getNext()
{
    return this->mpNext;
}

void ProcessRep::setNext(ProcessRep *next)
{
    this->mpNext = next;
}

string ProcessRep::getProcessType()
{
    return this->mProcessType;
}

void ProcessRep::setProcessType(string processType)
{
    this->mProcessType = processType;
}

int ProcessRep::getLevel()
{
    if(this->mProcessType == "A")
        return 1;
    else if(this->mProcessType == "B")
        return 2;
    else if(this->mProcessType == "C")
        return 3;
}

int ProcessRep::getDeliverTime()
{
    return this->mDeliverTime;
}

void ProcessRep::setDeliverTime(int deliverTime)
{
    this->mDeliverTime = deliverTime;
}

int ProcessRep::getProcessID()
{
    return this->mProcessID;
}

void ProcessRep::setProcessID(int processID)
{
    this->mProcessID = processID;
}

int ProcessRep::getProcessTime()
{
    return this->mProcessTime;
}

void ProcessRep::setProcessTime(int ProcessTime)
{
    this->mProcessTime = ProcessTime;
}