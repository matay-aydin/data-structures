/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#ifndef _PROCESSREP
#define _PROCESSREP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

class ProcessRep
{
    /*
        Node of a linked list data structues
    */
private:
    ProcessRep *mpNext;
    string mProcessType;
    int mProcessID;
    int mDeliverTime;
    int mProcessTime;

public:
    int remainingTime;
    int startTime;
    int endTime;

    /**
        ProcessRep constructor.
        @param processType a string variable that specifies the level of the process.
        @param processID an identifier for the process.
        @param deliverTime the time when the process is ready to run.
        @param processTime specifies how much time is required to complete the process.
    */
    ProcessRep(string processType = "", int processID = 0, int deliverTime = 0, int processTime = 0);
    ~ProcessRep();

    /**
        Gets the pointer that points to the next node.
        @return mpNext pointer.
    */
    ProcessRep* getNext();
    /**
        Sets mpNext for another node.
        @param newNode new mpNext.
    */
    void setNext(ProcessRep* newNode);

    /**
        Gets process level.
        @return specifies the level of the current node.
    */
    string getProcessType();
    /**
        Sets the node process level.
        @param type defines process level.
    */
    void setProcessType(string type);
    /**
     * Returns an integer according to its type. A = 1, B = 2, C = 3.
     * @return level
    */
    int getLevel();
    /**
        Gets the time when the process arrives.
        @return arrival time.
    */
    int getDeliverTime();
    /**
        Sets deliver time for the current node.
        @param arrival the time when the process is going to be handled by scheduler.
    */
    void setDeliverTime(int arrival);

    /**
        Gets identifier for the current node.
        @return integer ID.
    */
    int getProcessID();
    /**
        Sets ID for the current node.
        @param id identification number.
    */
    void setProcessID(int id);

    /**
        Gets the total execution time of the process.
        @return required time for the CPU to execute the process.
    */
    int getProcessTime();
    /**
        Sets execution duration for the process.
        @param execution time needed for the CPU to finish the process.
    */
    void setProcessTime(int execution);
};

#endif
