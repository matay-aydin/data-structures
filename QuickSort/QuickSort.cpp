#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include <vector>
#include <map>
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

// Default equals comparator
template <typename T>
class Equal
{
public:
    // Overload the function call operator
    bool operator()(const T &obj1, const T &obj2) const
    {
        return obj1 == obj2;
    }
};

// Customizable converter to get the string representation of an object
template <typename T>
class Stringify
{
public:
    std::string operator()(const T &obj1) const
    {
        return std::to_string(obj1);
    }
};

template <typename T, typename CmpLess = Less<T>, typename CmpEqu = Equal<T>, typename StringVal = Stringify<T>>
class QuickSort
{
public:
    QuickSort();
    QuickSort(std::vector<T> &array, char inputStrategy = 'm', size_t threshold = 1, char log = 'x');
    void logPartition(std::string logFileName = "log.txt");
    void quickSort(std::vector<T> &A, size_t begin, size_t end);
    void insertionSort(std::vector<T> &A, size_t begin, size_t end) const;

private:
    CmpLess less;
    CmpEqu equal;
    StringVal strval;
    size_t k;                     // Threshold
    char strategy;                // Pivot strategy
    char verbose;                 // Enable logging
    std::stringstream logDetails; // Store log info before saving to a file
    static std::random_device rd; // rand num seed
    static std::mt19937 gen;      // rand num generator
    size_t partition(std::vector<T> &A, size_t begin, size_t end);
    size_t randomIndex(size_t begin, size_t end) const;
};

// Static attribute initialization
template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
std::random_device QuickSort<T, CmpLess, CmpEqu, StringVal>::rd;

// Static attribute initialization
template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
std::mt19937 QuickSort<T, CmpLess, CmpEqu, StringVal>::gen = std::mt19937(rd());

// Custom less than comparator to compare std::pair<T, std::string> objects
template <typename T>
class PairFirstLess
{
public:
    bool operator()(const std::pair<T, std::string> &obj1, const std::pair<T, std::string> &obj2) const
    {
        return obj1.first < obj2.first; // Compare first elements
    }
};

// Custom equals comparator to compare std::pair<T, std::string> objects
template <typename T>
class PairFirstEqual
{
public:
    bool operator()(const std::pair<T, std::string> &obj1, const std::pair<T, std::string> &obj2) const
    {
        return obj1.first == obj2.first; // Compare first elements
    }
};

// Custom string representation of std::pair<T, std::string> objects
template <typename T>
class PairStringify
{
public:
    std::string operator()(const std::pair<T, std::string> &obj1) const
    {
        return std::to_string(obj1.first);
    }
};

// Handle csv operations
template <typename T>
class DataSort
{
public:
    DataSort(std::string ifileName, std::string ofileName = "sorted.csv",
             char inputStrategy = 'm', size_t threshold = 5, char verbose = 'x');

private:
    std::vector<std::pair<T, std::string>> data; // Store csv info
    void readData(std::string ifileName);
    void sortData(char inputStrategy, size_t threshold, char verbose = 'x');
    void saveData(std::string ofileName) const;
    std::pair<T, std::string> pairUp(std::string line) const; // Utility method to convert a line form csv to a pair
    void reportSortingTime(const std::chrono::nanoseconds &elapsed, char inputStrategy, size_t threshold) const;
};

// Constructor
template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
QuickSort<T, CmpLess, CmpEqu, StringVal>::QuickSort()
    : k{1}, strategy{'m'}, verbose{'v'}, less{}, equal{}, logDetails{}
{
}

// Constructor
template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
QuickSort<T, CmpLess, CmpEqu, StringVal>::QuickSort(std::vector<T> &array, char inputStrategy, size_t threshold, char log)
    : less{}, equal{}, logDetails{}
{
    if (inputStrategy != 'l' && inputStrategy != 'r' && inputStrategy != 'm')
        throw "Invalid strategy!\n";
    this->strategy = inputStrategy;
    this->k = threshold;
    this->verbose = log;
    this->quickSort(array, 0, array.size()); // Sort the array
}

// Save log data
template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
void QuickSort<T, CmpLess, CmpEqu, StringVal>::logPartition(std::string logFileName)
{
    switch (this->verbose)
    {
    case 'v':
    {
        std::ofstream logFile(logFileName);
        if (!logFile.is_open())
            throw "Error: Could not open the file.";
        logFile << "Pivot,PivotIndex,Begin,End,Subarray\n"; // Header info
        logFile << this->logDetails.str();                  // Partition data
        logFile.close();
        break;
    }
    default:
        break;
    }
}

template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
void QuickSort<T, CmpLess, CmpEqu, StringVal>::quickSort(std::vector<T> &A, size_t begin, size_t end)
{
    if (begin >= end) // Base case
        return;
    else if (end - begin <= this->k) // Check threshold
    {
        this->insertionSort(A, begin, end); // Advance to insertionSort
        return;
    }

    switch (this->strategy)
    {
    case 'r': // random pivot
    {
        size_t randomPivotIndex = this->randomIndex(begin, end);
        swapValues(A[randomPivotIndex], A[end - 1]); // swap with the last element
        break;
    }
    case 'm': // median of 3
    {
        size_t trinity[3] = {
            this->randomIndex(begin, end),
            this->randomIndex(begin, end),
            this->randomIndex(begin, end)};
        size_t median;
        if ((trinity[0] >= trinity[1]) && (trinity[1] >= trinity[2]))
            median = trinity[1];
        else if ((trinity[1] >= trinity[0]) && (trinity[0] >= trinity[2]))
            median = trinity[0];
        else
            median = trinity[2];
        swapValues(A[median], A[end - 1]); // swap with the last element
        break;
    }
    default: // last element is the pivot by default
        break;
    }
    size_t pivotIndex = this->partition(A, begin, end);
    this->quickSort(A, begin, pivotIndex);   // lastElementIndex = pivotIndex - 1
    this->quickSort(A, pivotIndex + 1, end); // lastElementIndex = end - 1
}

template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
void QuickSort<T, CmpLess, CmpEqu, StringVal>::insertionSort(std::vector<T> &A, size_t begin, size_t end) const
{
    size_t i, j;
    T key;
    for (i = begin + 1; i < end; i++)
    {
        key = A[i];
        j = i - 1;
        while (j > 0 && this->less(key, A[j])) // Sort the sub-array
        {
            A[j + 1] = A[j];
            j--;
        }
        if (this->less(A[j], key) || this->equal(A[j], key)) // Do the last iteration
            A[j + 1] = key;
        else
        {
            A[j + 1] = A[j];
            A[j] = key;
        }
    }
}

template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
size_t QuickSort<T, CmpLess, CmpEqu, StringVal>::partition(std::vector<T> &A, size_t begin, size_t end)
{
    T pivot = A[end - 1]; // Select the last element as pivot
    size_t i = begin - 1;
    for (size_t j = begin; j < end - 1; j++)
    {
        if (this->less(pivot, A[j]) || this->equal(pivot, A[j])) // pivot <= A[j]
            continue;
        i++;
        swapValues(A[i], A[j]); // Sweep small numbers to the left
    }
    swapValues(A[i + 1], A[end - 1]); // Replace the pivot to the correct place
    switch (this->verbose)            // logging
    {
    case 'v':
    {
        std::string line = this->strval(A[i + 1]) + "," + std::to_string(i + 1) + ",";
        line += std::to_string(begin) + "," + std::to_string(end - 1) + ",{";
        for (size_t i = begin; i < end; i++)
        {
            line += this->strval(A[i]) + ",";
        }
        line.pop_back();
        line += "}\n";
        this->logDetails << line; // Store in std::stringstream
        break;
    }

    default:
        break;
    }
    return i + 1; // return the pivotIndex
}

template <typename T, typename CmpLess, typename CmpEqu, typename StringVal>
size_t QuickSort<T, CmpLess, CmpEqu, StringVal>::randomIndex(size_t begin, size_t end) const
{
    // Create a distribution for the array.
    std::uniform_int_distribution<size_t> distribution(begin, end - 1);
    return distribution(this->gen);
}

template <typename T>
DataSort<T>::DataSort(std::string ifileName, std::string ofileName,
                      char inputStrategy, size_t threshold, char verbose)
{
    this->readData(ifileName);
    this->sortData(inputStrategy, threshold, verbose);
    this->saveData(ofileName);
}

template <typename T>
void DataSort<T>::readData(std::string ifileName)
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
        this->data.push_back(this->pairUp(ifileLine)); // Convert and store inside the vector line by line
    }
}

template <typename T>
void DataSort<T>::sortData(char inputStrategy, size_t threshold, char verbose)
{
    const auto start{std::chrono::steady_clock::now()}; // Start timer
    QuickSort<std::pair<T, std::string>, PairFirstLess<T>, PairFirstEqual<T>, PairStringify<T>> q{this->data, inputStrategy, threshold, verbose};
    const auto end{std::chrono::steady_clock::now()};       // Stop timer
    const std::chrono::nanoseconds elapsed_ns{end - start}; // Calc. elapsed time
    this->reportSortingTime(elapsed_ns, inputStrategy, threshold);
    q.logPartition();
}

template <typename T>
void DataSort<T>::saveData(std::string ofileName) const
{
    std::stringstream buffer;
    std::string line;
    for (size_t i = 0; i < this->data.size(); i++)
    {
        line = this->data[i].second + ";" + std::to_string(this->data[i].first) + "\n";
        buffer << line;
    }

    std::ofstream ofile(ofileName);
    if (!ofile.is_open())
        throw "Error: Could not open the file.";
    ofile << buffer.str();
    ofile.close();
}

template <typename T>
std::pair<T, std::string> DataSort<T>::pairUp(std::string line) const
{
    int separate = line.find_first_of(";");
    std::string city = line.substr(0, separate);
    T population = std::stoul(line.substr(separate + 1, line.size() - 1 - separate));
    std::pair<T, std::string> p{population, city}; // Create a pair
    return p;
}

template <typename T>
void DataSort<T>::reportSortingTime(const std::chrono::nanoseconds &elapsed, char inputStrategy, size_t threshold) const
{
    std::cout << "Time taken by QuickSort with pivot strategy \'" << inputStrategy
              << "\' and threshold " << threshold << ": " << elapsed.count() << " ns.\n";
}

int main(int argc, char *argv[])
{
    // Get CLI args
    std::string dataFileName = argv[1];
    char pivotingMethod = argv[2][0];
    size_t k = std::stoul(argv[3]);
    std::string outFileName = argv[4];
    char verbose = 'x';
    if (argc == 6)
        verbose = argv[5][0];
    // Sort and save
    DataSort<u_int> d{
        dataFileName,
        outFileName,
        pivotingMethod,
        k,
        verbose};
    return 0;
}