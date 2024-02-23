/* @Author
Student Name: Matay Aydin
Student ID : 150200075
Date: 27-10-2022
*/
#ifndef _FIFOREP
#define _FIFOREP

#include <iostream>
#include <stdio.h>
#include "ProcessRep.h"
class FIFORep 
{
    /*
        The class construct a FIFO queue.
    */

private:
    ProcessRep* mpHead;
    ProcessRep* mpTail;
public:
    FIFORep();
    FIFORep(ProcessRep*);
    ~FIFORep();

    /**
     * Sets mpHead to a new pointer.
     * @param nodePtr new location for mpHead.
    */
    void setHead(ProcessRep*);
    /**
     * Gets the location of the head node.
     * @return mpHead.
    */
    ProcessRep* getHead();

    /**
     * Sets mpTail to a new pointer.
     * @param nodePtr new location for mpTail.
    */
    void setTail(ProcessRep*);
    /**
     * Gets the location of the tail node.
     * @return mpTail.
    */
    ProcessRep* getTail();

    /**
     * Adds a new process to the end of the list.
     * @param newProcess new tail process.
    */
    void queue(ProcessRep*);
    /**
     * Removes and returns the first element of the list.
     * @return head node.
    */
    ProcessRep* dequeue();

    /**
     * The function search a process by id and returns it if it exist otherwise returns NULL.
     * @param id desired node id.
    */
    ProcessRep* searchID(int);
    /**
     * The function prints the processes in the queue starting from Head to tail.
    */
    void printFIFO();
};


#endif