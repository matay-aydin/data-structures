/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "SchedulerRep.h"

using namespace std;

SchedulerRep::SchedulerRep()
{
    for (int i = 0; i < 3; i++)
    {
        this->mpProcessFIFO[i] = new FIFORep;
    }
    this->mpRunningProcess = NULL;
    this->pCpuObj = new CPURep;
    this->timeSliceCount = 0;
    this->totalTime = 0;
}

SchedulerRep::~SchedulerRep()
{
    for (int i = 0; i < 3; i++)
    {
        delete this->mpProcessFIFO[i];
    }
    delete this->pCpuObj;
    delete this->mpRunningProcess;
}

FIFORep *SchedulerRep::getProcessFIFO(int index)
{
    if (index < 3 && index >= 0)
    {
        return this->mpProcessFIFO[index];
    }
}

void SchedulerRep::setProcessFIFO(FIFORep *fifo, int index)
{
    if (index < 3 && index >= 0 && fifo->getHead()->getNext() != NULL)
    {
        delete this->mpProcessFIFO[index];
        ProcessRep *popped;
        do
        {
            popped = fifo->dequeue();
            this->mpProcessFIFO[index]->queue(popped);
        } while (popped != NULL);
    }
}

void SchedulerRep::setRunningProcess(ProcessRep *p)
{
    this->mpRunningProcess = p;
}

ProcessRep *SchedulerRep::getRunningProcess()
{
    return this->mpRunningProcess;
}

void SchedulerRep::pushProcess(ProcessRep *p)
{
    string type = p->getProcessType();
    if (type == "A")
    {
        this->mpProcessFIFO[0]->queue(p);
    }
    else if (type == "B")
    {
        this->mpProcessFIFO[1]->queue(p);
    }
    else if (type == "C")
    {
        this->mpProcessFIFO[2]->queue(p);
    }
}

ProcessRep *SchedulerRep::popProcess()
{
    if (this->mpProcessFIFO[0]->getHead() != NULL)
    {
        return this->mpProcessFIFO[0]->dequeue();
    }
    else if (this->mpProcessFIFO[1]->getHead() != NULL)
    {
        return this->mpProcessFIFO[1]->dequeue();
    }
    else if (this->mpProcessFIFO[2]->getHead() != NULL)
    {
        return this->mpProcessFIFO[2]->dequeue();
    }
    else
    {
        return NULL;
    }
}

bool SchedulerRep::checkTimeSlice()
{
    bool flag = false;
    string type = this->mpRunningProcess->getProcessType();
    if (type == "A")
    {
        if (this->timeSliceCount == 2)
            flag = true;
    }
    else if (type == "B")
    {
        if (this->timeSliceCount == 4)
            flag = true;
    }
    else if (type == "C")
    {
        if (this->timeSliceCount == 8)
            flag = true;
    }
    return flag;
}

ProcessRep *SchedulerRep::sendProcessToCPU(ProcessRep *p)
{
    return this->pCpuObj->runCPU(p, this->totalTime);
}

void SchedulerRep::schedule(string type, int id, int arrivalTime, int processTime)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */
    if (this->totalTime == arrivalTime)
    {
        ProcessRep *process = new ProcessRep(type, id, arrivalTime, processTime);
        this->pushProcess(process);
        if (this->getRunningProcess() == NULL)
        {
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
        }
        if (this->getRunningProcess() == NULL)
        {
            return;
        }
        if (this->getRunningProcess()->getLevel() > process->getLevel())
        {
            this->pushProcess(this->getRunningProcess());
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
        }
        if (this->checkTimeSlice())
        {
            this->pushProcess(this->getRunningProcess());
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
        }
        if (this->getRunningProcess() == process)
        {
            this->timeSliceCount = 0;
        }
        ProcessRep *ptr = this->sendProcessToCPU(this->getRunningProcess());
        this->totalTime += 1;
        this->timeSliceCount += 1;
        if (ptr == NULL)
        {
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
            if (this->getRunningProcess() == NULL)
            {
                return;
            }
        }
    }
}

void SchedulerRep::schedule(ProcessRep *p)
{
    /*
        The function is used to schedule the processes. If a process is reached the function it will be scheduled by the function
        according to the rules which is defined below.

            1) All process types have their own time slice (quantum). When running a process, If the scheduler reachs the time slice
                (quantum) of the running process, the process will be preempted and put back to the queue.
            2) if a process that has higher priority comes, the running process will be preempted and put back to the queue.
            3) if a process that has less or same priority with running process comes, the running process will continue to run.
                The new process will be put back to the queue.
            4) If running process and new process have same priority and they are put back to the queue, the new process will
                be put back to the queue first.


    */
    if (p == NULL)
    {
        if (this->getRunningProcess() == NULL)
        {
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
        }
        if (this->getRunningProcess() == NULL)
        {
            return;
        }
        if (this->checkTimeSlice())
        {
            this->pushProcess(this->getRunningProcess());
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
        }
        ProcessRep *ptr = this->sendProcessToCPU(this->getRunningProcess());
        this->totalTime += 1;
        this->timeSliceCount += 1;
        if (ptr == NULL)
        {
            this->setRunningProcess(this->popProcess());
            this->timeSliceCount = 0;
            if (this->getRunningProcess() == NULL)
            {
                return;
            }
        }
    }
}
