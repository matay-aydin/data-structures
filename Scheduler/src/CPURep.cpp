/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

CPURep::CPURep()
{
    this->mFinishedProcess = new FIFORep;
}

CPURep::~CPURep()
{
    delete this->mFinishedProcess;
    this->mFinishedProcess = NULL;
}

ProcessRep *CPURep::runCPU(ProcessRep *p, int time)
{
    if (p == NULL)
    {
        return NULL;
    }
    if (p->remainingTime == -1)
    {
        p->remainingTime = p->getProcessTime();
        p->startTime = time;
    }
    p->remainingTime -= 1;
    if (p->remainingTime == 0)
    {
        p->endTime = time + 1;
        this->mFinishedProcess->queue(p);
        return NULL;
    }
    return p;
}

FIFORep *CPURep::getFinishedProcess()
{
    return this->mFinishedProcess;
}

void CPURep::setFinishedProcess(FIFORep *finishedProcess)
{
    delete this->mFinishedProcess;
    this->mFinishedProcess = finishedProcess;
}