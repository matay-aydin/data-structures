#ifndef _DOUBLYLINKED
#define _DOUBLYLINKED
#include <iostream>

// Forward decleration
template <typename>
class DList;

template <typename T>
class DNode
{
private:
    T data;
    DNode *next;
    DNode *prev;
    friend class DList<T>;
};

template <typename T>
class DList
{
public:
    DList();
    ~DList();
    /// @brief Adds a new node that stores the given data to the front of the list.
    /// @param elem data to be stored in the list
    void addFront(const T &elem);
    /// @brief Adds a new node that stores the given data to the back of the list.
    /// @param elem data to be stored in the list
    void addBack(const T &elem);
    /// @brief Deletes the node at the very front.
    void delFront();
    /// @brief Deletes the last node.
    void delBack();
    /// @brief Gets the data stored in the beggining node of the list.
    /// @return constant reference to data member of the node that is pointted by head.
    const T &getFront() const;
    /// @brief Gets the data stored in the last node of the list.
    /// @return constant reference to data member of the node that is pointted by tail.
    const T &getBack() const;
    /// @brief Gets the number of nodes in the list.
    /// @return number of nodes
    int getSize() const;
    /// @brief Checks if head points to tail.
    /// @return true is the list is empty, false otherwise.
    bool isEmpty() const;
    /// @brief Checks nodes of the list if they store the given data
    /// @param data data to be checked.
    /// @return number of nodes that store the given data
    int hasData(const T &data) const;

private:
    DNode<T> *head;
    DNode<T> *tail;
    int size;

protected:
    void add(DNode<T> *before, const T &elem);
    void del(DNode<T> *deleted);
};

template <typename T>
DList<T>::DList()
{
    this->head = new DNode<T>;
    this->tail = new DNode<T>;
    this->head->next = this->tail;
    this->tail->next = this->head;
    this->head->prev = NULL;
    this->tail->next = NULL;
    this->size = 0;
}

template <typename T>
DList<T>::~DList()
{
    while (!this->isEmpty())
    {
        this->delFront();
    }
    delete this->head;
    delete this->tail;
    this->size = 0;
}

template <typename T>
void DList<T>::addFront(const T &elem)
{
    this->add(this->head, elem);
}

template <typename T>
void DList<T>::addBack(const T &elem)
{
    this->add(this->tail->prev, elem);
}

template <typename T>
void DList<T>::delFront()
{
    if (!this->isEmpty())
    {
        this->del(this->head->next);
    }
    else
    {
        throw std::length_error("\nDoublyLinked.h delFront()>>> Current DList is empty.\n");
    }
}

template <typename T>
void DList<T>::delBack()
{
    if (!this->isEmpty())
    {
        this->del(this->tail->prev);
    }
    else
    {
        const char *msg = "\nDoublyLinked.h delBack()>>> Current DList is empty.\n";
        throw msg;
    }
}

template <typename T>
const T &DList<T>::getFront() const
{
    return this->head->next->data;
}

template <typename T>
const T &DList<T>::getBack() const
{
    return this->tail->prev->data;
}

template <typename T>
int DList<T>::getSize() const
{
    return this->size;
}

template <typename T>
bool DList<T>::isEmpty() const
{
    return this->head->next == this->tail;
}

template <typename T>
int DList<T>::hasData(const T &data) const
{
    int count = 0;
    DNode<T> *ptr = this->head;
    if (this->isEmpty())
    {
        const char *msg = "\nDoublyLinked.h hasData()>>> Current DList is empty.\n";
        throw msg;
    }
    while (ptr != this->tail)
    {
        if (data == ptr->data)
        {
            count++;
        }
        ptr = ptr->next;
    }
    return count;
}

template <typename T>
void DList<T>::add(DNode<T> *before, const T &elem)
{
    DNode<T> *after = new DNode<T>;
    after->data = elem;
    after->prev = before;
    after->next = before->next;
    before->next->prev = after;
    before->next = after;
    this->size += 1;
}

template <typename T>
void DList<T>::del(DNode<T> *deleted)
{
    deleted->next->prev = deleted->prev;
    deleted->prev->next = deleted->next;
    delete deleted;
    this->size -= 1;
}

#endif