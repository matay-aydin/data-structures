#ifndef _SINGLYLINKED
#define _SINGLYLINKED
#include <iostream>

// Forward decleration
template <typename>
class SList;

template <typename T>
class SNode
{
private:
    T data;
    SNode<T> *next;
    friend class SList<T>;
};

template <typename T>
class SList
{
public:
    SList();
    ~SList();
    /// @brief Adds the given element in front of the list.
    /// @param elem
    void addFront(const T &elem);
    /// @brief Deletes the most recently added element.
    void delFront();
    /// @brief Gets data from the head node.
    /// @return constant reference to data member of the head node.
    const T &getFront() const;
    /// @brief Accessor.
    /// @return Current number of nodes in the list.
    int getSize() const;
    bool isEmpty() const;
    /// @brief Checks wether the given parameter is stored somewhere in the list.
    /// @param data
    /// @return number of nodes that store the given data
    int hasData(const T &data) const;

private:
    int size;
    SNode<T> *head;
};

template <typename T>
SList<T>::SList()
{
    this->head = NULL;
    this->size = 0;
}

template <typename T>
SList<T>::~SList()
{
    while (!this->isEmpty())
    {
        this->delFront();
    }
    this->head = NULL;
    this->size = 0;
}

template <typename T>
void SList<T>::addFront(const T &elem)
{
    SNode<T> *p = new SNode<T>;
    p->data = elem;
    p->next = this->head;
    this->head = p;
    this->size += 1;
}

template <typename T>
void SList<T>::delFront()
{
    if (!this->isEmpty())
    {
        SNode<T> *ptr = this->head;
        this->head = this->head->next;
        this->size -= 1;
        delete ptr;
    }
    else
    {
        throw std::logic_error("\nSinglyLinked.h delFront()>>> Current SList is empty.\n");
    }
}

template <typename T>
const T &SList<T>::getFront() const
{
    if (!this->isEmpty())
    {
        return this->head->data;
    }
    else
    {
        throw std::logic_error("\nSinglyLinked.h getFront()>>> Current SList is empty.\n");
    }
}

template <typename T>
int SList<T>::getSize() const
{
    return this->size;
}

template <typename T>
bool SList<T>::isEmpty() const
{
    return this->head == NULL;
}

template <typename T>
int SList<T>::hasData(const T &data) const
{
    int count = 0;
    SNode<T> *ptr = this->head;
    if (this->isEmpty())
    {
        throw std::logic_error("\nSinglyLinked.h hasData()>>> Current SList is empty.\n");
    }
    while (ptr != NULL)
    {
        if (data == ptr->data)
        {
            count++;
        }
        ptr = ptr->next;
    }
    return count;
}

#endif
