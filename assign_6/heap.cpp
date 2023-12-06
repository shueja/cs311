#include "heap.h"

// @brief gets the maximum value in the heap
// @return the highest value integer in the heap
T Heap::getMax() const
{
    if (count <= 0)
    {
        return -1;
    }
    else
    {
        return heaparray[0];
    }
}

// @brief default constructor. Construct an empty heap with initial capacity
Heap::Heap(int capacity)
{
    this->capacity = capacity;
    count = 0;
    heaparray = new int[capacity];
}

// @brief destructor
Heap::~Heap()
{
    delete[] heaparray;
}

/**
 * @brief constructor to build a heap from an array of values
 * @param values array of values to be added to the heap
 * @param length the size of the array
 */
Heap::Heap(T *values, int length)
{
    heaparray = new int[length];
    capacity = length;
    count = 0;
    for (int i = 0; i < length; i++)
    {
        insert(values[i]);
    }
}

/**
 * @brief Copy constructor
 * @param other the heap to be copied
 */
Heap::Heap(const Heap &other)
{
    this->capacity = other.capacity;
    this->count = other.count;
    this->heaparray = new int[count];
    for (int i = 0; i < count; i++)
    {
        this->heaparray[i] = other.heaparray[i];
    }
}

/**
 * @brief Assignment operator
 * @param other the heap to be copied
 * @return Heap& a reference to the heap
 */
Heap &Heap::operator=(const Heap &other)
{
    if (&other == this)
    {
        return *this;
    }
    this->capacity = other.capacity;
    this->count = other.count;
    delete[] heaparray;
    this->heaparray = new int[count];
    for (int i = 0; i < count; i++)
    {
        this->heaparray[i] = other.heaparray[i];
    };
    return *this;
}
/**
 * @brief   organizes the values in the heap to satisfy heap property.
 */
void Heap::heapify()
{
    // Heapify numbers array
    int i = count / 2 - 1;
    while (i >= 0)
    {
        percolateDown(i);
        i--;
    }
}

/**
 * @brief  Runs percolate down on the heap for the node stored in index.
 */
void Heap::percolateDownSubheap(int index, int size)
{

    int childIndex = 2 * index + 1;
    int value = heaparray[index];

    while (childIndex < size)
    {
        int maxValue = value;
        int maxIndex = -1;
        int i = 0;
        while (i < 2 && i + childIndex < size)
        {
            if (heaparray[i + childIndex] > maxValue)
            {
                maxValue = heaparray[i + childIndex];
                maxIndex = i + childIndex;
            }
            i++;
        }

        if (maxValue == value)
        {
            return;
        }
        else
        {
            swap(index, maxIndex);
            index = maxIndex;
            childIndex = 2 * index + 1;
        }
    }
}

void Heap::percolateDown(int index)
{
    percolateDownSubheap(index, count);
}

/**
 * @brief  Runs percolate up on the heap for the node stored in index.
 */
void Heap::percolateUp(int index)
{
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (heaparray[index] <= heaparray[parentIndex])
        {
            return;
        }
        else
        {
            swap(index, parentIndex);
            index = parentIndex;
        }
    }
}

void Heap::resizeArray()
{
    int newCapacity = capacity * 2;
    int *newArray = new int[newCapacity];
    if (newArray)
    {
        for (int i = 0; i < capacity; i++)
        {
            newArray[i] = heaparray[i];
        }

        delete[] heaparray;
        heaparray = newArray;

        capacity = newCapacity;
    }
}
/**
 * @brief  inserts a value into the heap
 *
 */
void Heap::insert(T value)
{
    if (count == capacity)
    {
        resizeArray();
    }

    heaparray[count] = value;
    count++;
    percolateUp(count - 1);
}

/**
 * @brief  Removes the max value from the heap
 * @return the value that was removed
 */
T Heap::removeMax()
{
    int maxValue = heaparray[0];
    int replaceValue = heaparray[--count];
    if (count > 0)
    {
        heaparray[0] = replaceValue;
        percolateDown(0);
    }
    return maxValue;
}

//@brief converts the heap into a string
string Heap::toString()
{
    string s = "[ ";
    for (int i = 0; i < count; i++)
    {
        s += to_string(heaparray[i]) + " ";
    }
    s += "]";
    return s;
}

/**
 * @brief  Prints the values in the heap
 */
void Heap::printHeap()
{
    cout << toString() << endl;
}

/**
 * @brief  Prints the values in an array
 */
void printArray(int values[], int length)
{
    int i;
    cout << "[ ";
    for (i = 0; i < length; i++)
    {
        cout << values[i] << " ";
    }
    cout << "]\n";
}

/**
 * @brief  Swaps the values in the heap at index1 and index2
 */
void Heap::swap(int index1, int index2)
{
    int temp = heaparray[index1];
    heaparray[index1] = heaparray[index2];
    heaparray[index2] = temp;
}

/**
 * @brief  Sorts the values of an array by using the heap
 */
void heapSort(T values[], int length)
{
    cout << "Array Before Sorting: \n";
    printArray(values, length);

    Heap heap(values, length);
    for (int i = 0; i < length; i++)
    {
        values[length - i - 1] = heap.removeMax();
    }
    cout << "Array After Sorting: \n";
    printArray(values, length);
}

/**
 * @brief Change the key of the element at position i to the new value.
 *        It maintains the heap property.
 * @param i the position of the element to be decreased
 * @param value the new value
 */
void Heap::changeKey(int i, T new_val)
{
    heaparray[i] = new_val;
    heapify();
}
