/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#ifndef _CPUREP
#define _CPUREP

#include <iostream>
#include <stdio.h>
#include <string.h>
// #include "node.h"
#include "ProcessRep.h"
#include "FIFORep.h"

using namespace std;

class CPURep
{
    /*
        The CPU representation class that run  processes.
    */  
private:
    FIFORep* mFinishedProcess;
public:
    CPURep();
    ~CPURep();

    /**
     * Returns with mFinishedProcess
     * @return FIFORep* mFinishedProcess.
    */
    FIFORep* getFinishedProcess();
    void setFinishedProcess(FIFORep*);

    /**
     *  It execute the process by subtracting one from remainingTime. If process finishes, it add to mFinishedProcess.
     * @param runningProcess a pointer
     * @param time running time
     * @return ProcessRep*.
    */
    ProcessRep* runCPU(ProcessRep*, int);
};

#endif