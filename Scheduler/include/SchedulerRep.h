/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#ifndef _SCHEDULERREP
#define _SCHEDULERREP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ProcessRep.h"
#include "FIFORep.h"
#include "CPURep.h"

using namespace std;

class SchedulerRep
{
    /*
        The process scheduler subrutoine that puts in order the processes
        in 3 different priority level.
    */
private:
    FIFORep *mpProcessFIFO[3];
    ProcessRep *mpRunningProcess;

public:
    CPURep *pCpuObj;
    int timeSliceCount;
    int totalTime;

    SchedulerRep();
    ~SchedulerRep();

    /**
     * Gets from mpProcessFIFO array.
     * @param level specifies the ProcessFIFO which holds processes at that level.
     * @return this->mpProcessFIFO[index];
     */
    FIFORep *getProcessFIFO(int);
    /**
     * Sets a ProcessFIFO in the mpProcessFIFO array.
     * @param newFIFO heir.
     * @param level which ProcessFIFO will be deleted.
     */
    void setProcessFIFO(FIFORep *, int);

    /**
     * Sets the current process in the CPU.
     * @param process a process that is going to be sent to CPU.
     */
    void setRunningProcess(ProcessRep *);
    /**
     * Gets the current process from CPU.
     * @return a pointer to current process.
     */
    ProcessRep *getRunningProcess();

    /**
     * Pushes the process into mpProcessFIFO according to its process type.
     * @param process a process that is going to be scheduled.
     */
    void pushProcess(ProcessRep *);
    /**
     * Dequeues the suitable process from mpProcessFIFO
     * @return a process from mpProcessFIFO.
     */
    ProcessRep *popProcess();

    /**
     * It check the quantum time of running process. If it reaches the limits return true.
     * @return a boolean value.
     */
    bool checkTimeSlice();
    /**
     * It sends process to pCpuObj object.
     * @return pointer from runProcessCPU().
     */
    ProcessRep *sendProcessToCPU(ProcessRep *);
    /**
     * It takes the process properties and organize the process according to given rules.
     */
    void schedule(string, int, int, int);
    /**
     * It is a func overload and also copy of the previous schedule function. Just its arguments is changed.It is called only with NULL.
     */
    void schedule(ProcessRep *);
};

#endif