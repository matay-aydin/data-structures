#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

// Utility function
template <typename T>
void swapValues(T &val1, T &val2)
{
    T temp = val1;
    val1 = val2;
    val2 = temp;
}

// Default less than comparator
template <typename T>
class Less
{
public:
    // Overload the function call operator
    bool operator()(const T &obj1, const T &obj2) const
    {
        return obj1 < obj2;
    }
};

// Retrieve the key of the user defined type
template <typename T>
class Key
{
public:
    // Overload the function call operator
    T& operator()(T& obj1) const
    {
        return obj1;
    }
};

// Max Binary Heap
// T : User defined type of elements
// KeyType : Type of the key of an element
// KeyField : A key corresponding to an element
// CmpLess : A comparator that is used to compare elements with user defined type w.r.t. their keys
template <typename T, typename KeyType = T, 
    typename KeyField = Key<T>, typename CmpLess = Less<KeyType>>
class MaxHeap 
{
public:
    /// @brief Constructor of the MaxHeap
    /// @param array Pointer to the vector where the heap will be stored
    MaxHeap(std::vector<T>* array);
    void max_heapify(size_t index);
    void build_max_heap();
    void heapsort();

    void max_heap_insert(const T& elem);
    T& heap_extract_max();
    void heap_increase_key(size_t index, KeyType& k);
    T& heap_maximum();
    /// @brief Getter for the heap size
    /// @return Size of the heap
    size_t get_heap_size() const { return this->heapSize; }

private:
    /// @brief Hold the address of the heap
    std::vector<T>* heapPtr;
    /// @brief The size of the heap is not same as the size of the vector always
    size_t heapSize;
    CmpLess less;
    KeyField key;
    /// @brief Hold the max value in the heap
    T max;
    /// @brief Place inserted element into the correct spot
    /// @param index Index of the inserted element
    void _heapifyUp(size_t index);
    /// @brief Get parent index of an element
    /// @param index Index of the child
    /// @return Index of the parent
    size_t _getParent(size_t index) const 
    { return (index - 1) >> 1; }
    /// @brief Get the left child of an element
    /// @param index Index of the parent
    /// @return Index of the left child
    size_t _getLeft(size_t index) const 
    { return (index << 1) + 1; }
    /// @brief Get the right child of an element
    /// @param index Index of the parent
    /// @return Index of the right child
    size_t _getRight(size_t index) const 
    { return (index << 1) + 2; }
    /// @brief Get the element from the heap
    /// @param index Index of the element inside the heap
    /// @return Reference to the element
    T& _getFromIndex(size_t index) const
    { return (*(this->heapPtr))[index]; }
    /// @brief Get the key of the element
    /// @param index Index of the element inside the heap
    /// @return Reference to the key of the specified element
    KeyType& _getKeyFromIndex(size_t index) const
    { return this->key(this->_getFromIndex(index)); }
    /// @brief Change the key of an element
    /// @param index Index of the element inside the heap
    /// @param key New key
    void _storeToKey(size_t index, KeyType& key)
    { this->key((*(this->heapPtr))[index]) = key; }
};


// Max D-ary Heap
// T : User defined type of elements
// KeyType : Type of the key of an element
// KeyField : A key corresponding to an element
// CmpLess : A comparator that is used to compare elements with user defined type w.r.t. their keys
template <typename T, typename KeyType = T, 
    typename KeyField = Key<T>, typename CmpLess = Less<KeyType>>
class DaryHeap 
{
public:
    /// @brief Constructor of the DaryHeap
    /// @param array Pointer to the vector where the heap will be stored
    /// @param d Number of children that element can have
    DaryHeap(std::vector<T>* array, u_int d = 2);
    void dary_heapify(size_t index);
    void build_dary_heap();
    void heapsort();

    T& heap_maximum();

    u_int dary_calculate_height() const;
    T& dary_extract_max();
    void dary_insert_element(const T& elem);
    void dary_increase_key(size_t index, KeyType& k);

    /// @brief Setter for d
    /// @param d new d value
    void set_d(u_int d) { this->dary = d; }
    /// @brief Getter for the heap size
    /// @return Size of the heap
    size_t get_heap_size() const { return this->heapSize; }

private:
    /// @brief Pointer to the vector where the heap is stored
    std::vector<T>* heapPtr;
    /// @brief Store the size of the heap
    size_t heapSize;
    /// @brief Count how many children can an element has
    u_int dary;
    CmpLess less;
    KeyField key;
    /// @brief Store the maximum element inside the heap
    T max;
    /// @brief Place inserted element into the correct spot
    /// @param index Index of the inserted element
    void _heapifyUp(size_t index);
    /// @brief Get parent index of an element
    /// @param index Index of the child
    /// @return Index of the parent
    size_t _getParent(size_t index) const 
    { return (index - 1) / this->dary; }
    /// @brief Get a child of a parent element
    /// @param index Index of the parent element
    /// @param which Order of the child starting from 1 to d
    /// @return Index of the child
    size_t _getChild(size_t index, u_int which) const 
    { return index * this->dary + which; }
    /// @brief Get the element from the heap
    /// @param index Index of the element inside the heap
    /// @return Reference to the element
    T& _getFromIndex(size_t index) const
    { return (*(this->heapPtr))[index]; }
    /// @brief Get the key of the element
    /// @param index Index of the element inside the heap
    /// @return Reference to the key of the specified element
    KeyType& _getKeyFromIndex(size_t index) const
    { return this->key(this->_getFromIndex(index)); }
    /// @brief Change the key of an element
    /// @param index Index of the element inside the heap
    /// @param key New key
    void _storeToKey(size_t index, KeyType& key)
    { this->key((*(this->heapPtr))[index]) = key; }
};

/// @brief Store the data of each row inside the csv files
struct Row
{
    std::string city;
    u_int population;
};

/// @brief Comparator to compare pointers to Rows of data
class RowPtrLess
{
public:
    // Overload the function call operator
    bool operator()(Row* const& rptr1, Row* const& rptr2) const
    {
        return rptr1->population < rptr2->population;
    }
};

/// @brief Get key from a given row (population in this case)
class RowKey
{
public:
    // Overload the function call operator
    u_int& operator()(Row*& rptr) const
    {
        return rptr->population;
    }
};

/// @brief Read csv files into the given vector
class DataOps
{
public:
    /// @brief Constructor for the DataOps class
    /// @param array Pointer to the vector where pointers to the rows will be stored
    DataOps(std::vector<Row*>* array);
    /// @brief Delete each row from the memory
    ~DataOps();
    /// @brief Read the given csv file and store the data into the vector
    /// @param ifileName Name of the input csv file
    void readData(std::string ifileName);
    /// @brief Prompt the manipulated data to a csv file
    /// @param ofileName Name of the output csv file
    void writeData(std::string ofileName = "out.csv") const;
    /// @brief Write a single row of information inside a csv file
    /// @param result Single row of information
    /// @param ofileName Name of the output csv file
    void writeRow(Row result, std::string ofileName = "out.csv") const;

private:
    /// @brief Pointer to the vector of row pointers that holds the data inside the csv files
    std::vector<Row*>* data;
    /// @brief Create a Row object from a line of string from the csv files
    /// @param line A string of comma seperated values
    /// @return Pointer to the Row object that has been allocated
    Row* _pairUp(std::string line);
    /// @brief Get the data stored in the vector
    /// @param index Index of the data
    /// @return Reference to the pointer to the Row of data
    Row*& _getFromIndex(size_t index) const
    { return (*(this->data))[index]; }
    /// @brief Modify the content of the data stored in the given index
    /// @param index Index of the data that will be modified
    /// @param rptr New data to be stored
    void _storeToIndex(size_t index, Row*& rptr)
    { delete (*(this->data))[index]; (*(this->data))[index] = rptr; }
};

///////////// MaxHeap

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
MaxHeap<T, KeyType, KeyField, CmpLess>::MaxHeap(std::vector<T>* array)
    : heapPtr{array}, heapSize{0}, less{}, max{}
{
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void MaxHeap<T, KeyType, KeyField, CmpLess>::max_heapify(size_t index) {
    size_t left = this->_getLeft(index); // Calculate the index of the left child
    size_t right = this->_getRight(index);
    size_t largest = index; // Assign the index of the given node as it has the largest key
    // If the key of the left child is bigger, then assign largest with left
    if (left < this->heapSize && 
        this->less(this->_getKeyFromIndex(largest), this->_getKeyFromIndex(left))) 
        largest = left;
    // If the key of the right child is bigger, then assign largest with right
    if (right < this->heapSize && 
        this->less(this->_getKeyFromIndex(largest), this->_getKeyFromIndex(right))) 
        largest = right;
    // If one of the children has a larger key, then swap it with its parent
    if (largest != index) 
    {
        swapValues(this->_getFromIndex(index), this->_getFromIndex(largest));
        this->max_heapify(largest); // Recurse until largest == index
    }
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void MaxHeap<T, KeyType, KeyField, CmpLess>::build_max_heap() 
{
    this->heapSize = this->heapPtr->size(); // The vector is completely turned into a heap
    for (size_t i = this->heapSize / 2 + 1; i > 0; i--) 
        this->max_heapify(i); // Put the nodes into correct spots excluding leaves
    this->max_heapify(0);
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void MaxHeap<T, KeyType, KeyField, CmpLess>::heapsort() 
{
    if(this->heapSize == 0) // If the vector is not already a heap
        this->build_max_heap();
    for (size_t i = this->heapSize - 1; i > 0; i--) 
    {
        // Swap the max with the node at the end of the heap (not same as the end of the vector)
        swapValues(this->_getFromIndex(0), this->_getFromIndex(i));
        this->heapSize--; // Pop from the heap, and deacrease the size of it
        this->max_heapify(0); // Put the root into a correct place
    }
    this->heapSize--; // Make sure the heap size is 0
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void MaxHeap<T, KeyType, KeyField, CmpLess>::max_heap_insert(const T& elem)
{
    // Assume the vector is a heap
    this->heapPtr->push_back(elem); // Insert the new element to the end of the heap 
    this->heapSize++; 
    this->_heapifyUp(this->heapSize - 1); // Find the correct place for it at upper levels
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
T& MaxHeap<T, KeyType, KeyField, CmpLess>::heap_extract_max()
{
    // Assume the vector is a heap
    // Swap max element with elem. at the end of the heap
    swapValues(this->_getFromIndex(0), this->_getFromIndex(this->heapSize - 1));
    this->heapSize--;
    this->max_heapify(0); // Keep heap property
    this->max = this->heapPtr->back(); // The max is at the end
    this->heapPtr->pop_back(); // Pop max from the heap
    return this->max;
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void MaxHeap<T, KeyType, KeyField, CmpLess>::heap_increase_key(size_t index, KeyType& k)
{
    // Compare old key with the new one
    if(!this->less(this->_getKeyFromIndex(index), k))
        return;
    this->_storeToKey(index, k); // Increase the key of the specified element
    this->_heapifyUp(index); // Keep heap property
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
T& MaxHeap<T, KeyType, KeyField, CmpLess>::heap_maximum() 
{
    this->max = this->heapPtr->front();
    return this->max;
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void MaxHeap<T, KeyType, KeyField, CmpLess>::_heapifyUp(size_t index)
{
    size_t parent;
    while (index > 0) // Iterate up until reaching to the root
    {
        parent = this->_getParent(index);
        // If the key of the parent is not less then the child, then exit from the loop
        if(!this->less(this->_getKeyFromIndex(parent), this->_getKeyFromIndex(index)))
            break;
        // Swap the small parent with the big child
        swapValues(this->_getFromIndex(index), this->_getFromIndex(parent));
        index = parent;
    }
}

///////////// DaryHeap

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
DaryHeap<T, KeyType, KeyField, CmpLess>::DaryHeap(std::vector<T>* array, u_int d)
    : heapPtr{array}, heapSize{0}, less{}, dary{d}, max{}
{
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void DaryHeap<T, KeyType, KeyField, CmpLess>::dary_heapify(size_t index) 
{
    size_t largest = index;
    
    size_t ch;
    for(u_int i = 1; i <= this->dary; i++) // Iterate over the children of the parent
    {
        ch = this->_getChild(index, i);
        // If the current largest key is less then the key of the child, then update largest
        if (ch < this->heapSize &&
            this->less(this->_getKeyFromIndex(largest), this->_getKeyFromIndex(ch)))
            largest = ch;
    }

    if (largest != index) // If the largest value is updated
    {
        // Swap the node with the node that has the largest value
        swapValues(this->_getFromIndex(index), this->_getFromIndex(largest));
        this->dary_heapify(largest); // Recurse until largest == index
    }
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void DaryHeap<T, KeyType, KeyField, CmpLess>::build_dary_heap() 
{
    this->heapSize = this->heapPtr->size();
    // Heapify all nodes excluding leaves
    for (size_t i = this->heapSize / this->dary + 1; i > 0; i--)
        this->dary_heapify(i);
    this->dary_heapify(0);
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void DaryHeap<T, KeyType, KeyField, CmpLess>::heapsort() 
{
    if(this->heapSize == 0) // If the vector is not already a heap
        this->build_dary_heap();
    for (size_t i = this->heapSize - 1; i > 0; i--) 
    {
        // Swap the max with the node at the end of the heap (not same as the end of the vector) 
        swapValues(this->heapPtr->front(), this->_getFromIndex(i));
        this->heapSize--; // Pop from the heap, and deacrease the size of it
        this->dary_heapify(0); // Put the root into a correct place
    }
    this->heapSize--; // Make sure the size of the heap is 0
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
T& DaryHeap<T, KeyType, KeyField, CmpLess>::heap_maximum() 
{
    this->max = this->heapPtr->front();
    return this->max;
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void DaryHeap<T, KeyType, KeyField, CmpLess>::dary_insert_element(const T& elem)
{
    // Assume the vector is already a heap
    this->heapPtr->push_back(elem); // Insert the new elem. to the vector
    this->heapSize++;
    this->_heapifyUp(this->heapSize - 1); // Place it to a correct spot
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
u_int DaryHeap<T, KeyType, KeyField, CmpLess>::dary_calculate_height() const
{
    u_int h = 0; // Height
    size_t ptr = 0; // Keep index
    while(ptr < this->heapSize) // Iterate until the end of the heap
    {
        h++; // increase the height by one
        ptr = this->_getChild(ptr, 1); // Go down one level below
    }
    return h;
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
T& DaryHeap<T, KeyType, KeyField, CmpLess>::dary_extract_max()
{
    // Assume a heap structure
    // Swap the root with the last element
    swapValues(this->_getFromIndex(0), this->_getFromIndex(this->heapSize - 1));
    this->heapSize--;
    this->dary_heapify(0); // Place the new root to a correct spot
    this->max = this->heapPtr->back(); // Get the max value from the back
    this->heapPtr->pop_back();
    return this->max;
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void DaryHeap<T, KeyType, KeyField, CmpLess>::dary_increase_key(size_t index, KeyType& k)
{
    // Assume a heap structure
    // Compare the old key with the new one
    if(!this->less(this->_getKeyFromIndex(index), k))
        return;
    this->_storeToKey(index, k); // Update with the new one if it is bigger
    this->_heapifyUp(index); // Keep the heap property
}

template <typename T, typename KeyType, 
    typename KeyField, typename CmpLess>
void DaryHeap<T, KeyType, KeyField, CmpLess>::_heapifyUp(size_t index)
{
    size_t parent;
    while (index > 0) // Iterate up until reaching to the root
    {
        parent = this->_getParent(index);
        // If the key of the parent is not less then the child, then exit from the loop
        if(!this->less(this->_getKeyFromIndex(parent), this->_getKeyFromIndex(index)))
            break;
        // Swap the small parent with the big child
        swapValues(this->_getFromIndex(index), this->_getFromIndex(parent));
        index = parent;
    }
}

///////////// DataOps

DataOps::DataOps(std::vector<Row*>* array)
    : data{array}
{
}

DataOps::~DataOps()
{
    for(size_t i = 0; i < this->data->size(); i++)
        delete this->_getFromIndex(i);
}

void DataOps::readData(std::string ifileName)
{
    std::ifstream ifile(ifileName, std::ios::binary);
    if (!ifile.is_open())
        throw "Error: Could not open the file.";

    // Check for the BOM and skip it if present
    if (ifile.peek() == 0xEF)
    {
        char dummy[3]; // Create a dummy array to read and discard the BOM
        ifile.read(dummy, 3);
    }

    std::stringstream buffer;
    buffer << ifile.rdbuf(); // Get the whole info
    ifile.close();

    std::string ifileLine;
    while (std::getline(buffer, ifileLine))
    {
        if (ifileLine.find_first_of(";") < 0)
            continue;
        this->data->push_back(this->_pairUp(ifileLine)); // Convert and store inside the vector line by line
    }
}

void DataOps::writeData(std::string ofileName) const
{
    std::stringstream buffer;
    std::string line;
    size_t dataSize = this->data->size();
    // Concatenate data to form lines
    for (size_t i = 0; i < dataSize - 1; i++)
    {
        line = this->_getFromIndex(i)->city + ";" + 
            std::to_string(this->_getFromIndex(i)->population) + "\n";
        buffer << line; // Feed the line to the buffer
    }
    line = this->_getFromIndex(dataSize - 1)->city + ";" + 
        std::to_string(this->_getFromIndex(dataSize - 1)->population);
    buffer << line; // Feed the last line

    std::ofstream ofile(ofileName);
    if (!ofile.is_open())
        throw "Error: Could not open the file.";
    ofile << buffer.str(); // Write to the file
    ofile.close();
}

void DataOps::writeRow(Row result, std::string ofileName) const
{
    std::string line;
    line = result.city + ";" + std::to_string(result.population);

    std::ofstream ofile(ofileName);
    if (!ofile.is_open())
        throw "Error: Could not open the file.";
    ofile << line;
    ofile.close();
}

Row* DataOps::_pairUp(std::string line)
{
    int separate = line.find_first_of(";");
    std::string city = line.substr(0, separate);
    u_int population = std::stoul(line.substr(separate + 1, line.size() - 1 - separate));
    return new Row{city, population}; // Create a new object out of a line of string
}

// Utility function
u_int getDfromCLI(char* argv[], int arg) 
{
    u_int d;
    std::string dParam = argv[arg];
    dParam.erase(0, 1);
    d = std::stoul(dParam);
    return d;
}

int main(int argc, char *argv[]) 
{
    std::vector<Row*> array;
    DataOps ops{&array};
    ops.readData(argv[1]); // read the csv file
    MaxHeap<Row*, u_int, RowKey> mh{&array};
    DaryHeap<Row*, u_int, RowKey> dh{&array};

    std::string func = argv[2]; // get the function name
    if (func == "max_heapify") {
        std::string iParam = argv[4]; // get index
        size_t index = std::stoul(iParam.erase(0, 1));
        mh.max_heapify(index - 1); // Index starts from 1 within the heap context
        ops.writeData(argv[3]);
    } else if (func == "build_max_heap") {
        switch (argc) // Determine the heap type based on the no. of args
        {
        case 5: {
            dh.set_d(getDfromCLI(argv, 4));
            dh.build_dary_heap();
            break;
        }
        case 4:
            mh.build_max_heap();
            break;
        }
        ops.writeData(argv[3]);
    } else if (func == "heapsort") {
        switch (argc) // determine the heap type based on the no. of args
        {
        case 5: {
            dh.set_d(getDfromCLI(argv, 4));
            const auto start{std::chrono::steady_clock::now()}; // Start timer
            dh.heapsort();
            const auto end{std::chrono::steady_clock::now()};       // Stop timer
            const std::chrono::nanoseconds elapsed_ns{end - start}; // Calc. elapsed time
            std::cout << elapsed_ns.count() << '\n';
            break;
        }
        case 4:
            const auto start{std::chrono::steady_clock::now()}; // Start timer
            mh.heapsort();
            const auto end{std::chrono::steady_clock::now()};       // Stop timer
            const std::chrono::nanoseconds elapsed_ns{end - start}; // Calc. elapsed time
            std::cout << elapsed_ns.count() << '\n';
            break;
        }
        ops.writeData(argv[3]);
    } else if (func == "max_heap_insert") {
        std::string kParam = argv[4]; // get new city and population info
        kParam.erase(0, 2);
        int under = kParam.find_first_of('_');
        std::string city = kParam.substr(0, under); // extract city name
        kParam.erase(0, under + 1);
        u_int population = std::stoul(kParam); // extract population
        mh.build_max_heap();
        mh.max_heap_insert(new Row{city, population}); // Insert new data
        ops.writeData(argv[3]);
    } else if (func == "heap_extract_max") {
        mh.build_max_heap();
        Row* maxptr = mh.heap_extract_max(); // get the max
        ops.writeRow(*maxptr, argv[3]); // write only the max row
        delete maxptr; // free the memory
    } else if (func == "heap_increase_key") {
        std::string arg1 = argv[4], arg2 = argv[5];
        char ch1 = arg1[0];
        size_t index;
        u_int key;
        arg1.erase(0, 1);
        arg2.erase(0, 1);
        switch (ch1) {
        case 'i': {
            index = std::stoul(arg1);
            key = std::stoul(arg2);
            break;
        }
        case 'k': {
            key = std::stoul(arg1);
            index = std::stoul(arg2);
            break;
        }
        }
        mh.build_max_heap();
        mh.heap_increase_key(index - 1, key); // Index starts from 1 within the heap context
        ops.writeData(argv[3]);
    } else if (func == "heap_maximum") { 
        Row* maxptr = NULL;
        switch (argc) // Determine the heap type based on the no. of args
        {
        case 5: {
            dh.set_d(getDfromCLI(argv, 4));
            dh.build_dary_heap();
            maxptr = dh.heap_maximum();
            break;
        }
        case 4:
            mh.build_max_heap();
            maxptr = mh.heap_maximum();
            break;
        }
        ops.writeRow(*maxptr, argv[3]);
    } else if (func == "dary_calculate_height") {
        dh.set_d(getDfromCLI(argv, 4)); // get d
        dh.build_dary_heap();
        u_int height = dh.dary_calculate_height();
        Row h{"height", height};
        ops.writeRow(h, argv[3]);
    } else if (func == "dary_extract_max") {
        dh.set_d(getDfromCLI(argv, 4));
        dh.build_dary_heap();
        const auto start{std::chrono::steady_clock::now()}; // Start timer
        Row* maxptr = dh.dary_extract_max();
        const auto end{std::chrono::steady_clock::now()};       // Stop timer
        const std::chrono::nanoseconds elapsed_ns{end - start}; // Calc. elapsed time
        std::cout << elapsed_ns.count() << '\n';
        ops.writeRow(*maxptr, argv[3]);
        delete maxptr;
    } else if (func == "dary_insert_element") {
        std::string arg1 = argv[4], arg2 = argv[5];
        char ch1 = arg1[0];
        std::string kParam;
        switch (ch1) {
        case 'd': {
            dh.set_d(getDfromCLI(argv, 4));
            kParam = argv[5];
            break;
        }
        case 'k': {
            dh.set_d(getDfromCLI(argv, 5));
            kParam = argv[4];
            break;
        }
        }
        kParam.erase(0, 2);
        int under = kParam.find_first_of('_');
        std::string city = kParam.substr(0, under); // extract city name
        kParam.erase(0, under + 1);
        u_int population = std::stoul(kParam); // extract population
        dh.build_dary_heap();
        dh.dary_insert_element(new Row{city, population});
        ops.writeData(argv[3]);
    } else if (func == "dary_increase_key") {
        std::string arg1 = argv[4], arg2 = argv[5], arg3 = argv[6];
        char ch1 = arg1[0], ch2 = arg2[0];
        size_t index;
        u_int key;

        arg1.erase(0, 1);
        arg2.erase(0, 1);
        arg3.erase(0, 1);
        switch (ch1) {
        case 'd': {
            dh.set_d(getDfromCLI(argv, 4));
            switch (ch2){
                case 'i': {
                    index = std::stoul(arg2);
                    key = std::stoul(arg3);
                    break;
                }
                case 'k': {
                    index = std::stoul(arg3);
                    key = std::stoul(arg2);
                    break;
                }
            }
            break;
        }
        case 'i': {
            index = std::stoul(arg1);
            switch (ch2){
                case 'd': {
                    dh.set_d(getDfromCLI(argv, 5));
                    key = std::stoul(arg3);
                    break;
                }
                case 'k': {
                    dh.set_d(getDfromCLI(argv, 6));
                    key = std::stoul(arg2);
                    break;
                }
            }
            break;
        }
        case 'k': {
            key = std::stoul(arg1);
            switch (ch2){
                case 'd': {
                    dh.set_d(getDfromCLI(argv, 5));
                    index = std::stoul(arg3);
                    break;
                }
                case 'i': {
                    dh.set_d(getDfromCLI(argv, 6));
                    index = std::stoul(arg2);
                    break;
                }
            }
            break;
        }
        }
        dh.build_dary_heap();
        dh.dary_increase_key(index - 1, key); // Index starts from 1 within the heap context
        ops.writeData(argv[3]);
    } else {
        throw "Invalid command!\n";
    }
    return 0;
}