/**
 * @file dtypes.h
 *
 * @brief Data types used (Matrix, Heap, HeapList).
 */

#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

#include "utils.h"


namespace nndescent {


/**
 * @brief A template class representing a 2D matrix of elements of type T.
 */
template <class T>
class Matrix
{
public:
    /**
     * Default constructor. Creates an empty matrix.
     */
    Matrix() {}

    /**
     * Constructor to create a matrix with the specified number of rows and
     * columns. The matrix elements are uninitialized.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     */
    Matrix(size_t rows, size_t cols);


    /**
     * Constructor to create a matrix with the specified number of rows and
     * columns, and initialize all elements to a constant value.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     * @param const_val The constant value to initialize all elements.
     */
    Matrix(size_t rows, size_t cols, const T &const_val);

    /**
     * Constructor to create a matrix with the specified number of rows and
     * columns, and initialize elements from a pointer to external data.
     *
     * @param rows The number of rows in the matrix.
     * @param cols The number of columns in the matrix.
     * @param data_ptr A pointer to the external data to be used as matrix
     * elements.
     */
    Matrix(size_t rows, size_t cols, T *data_ptr);

    /**
     * Constructor to create a matrix with the specified number of rows and
     * columns, and initialize elements from a vector.
     *
     * @param rows The number of rows in the matrix.
     * @param data A vector containing the data elements to be used as matrix
     * elements.
     */
    Matrix(size_t rows, std::vector<T> &data);

    /**
     * Copy constructor. Creates a new matrix as a copy of another matrix.
     *
     * @param other The matrix to be copied.
     */
    Matrix(const Matrix<T>& other);

    /**
     * Move constructor. Creates a new matrix by moving the data from another
     * matrix.
     *
     * @param other The matrix to be moved.
     */
    Matrix(Matrix<T>&& other) noexcept;

    /**
     * Copy assignment operator. Assigns the contents of another matrix to
     * this matrix.
     *
     * @param other The matrix to be copied.
     * @return A reference to this matrix after the assignment.
     */
    Matrix<T>& operator=(const Matrix<T>& other);

    /**
     * Resizes an empty matrix to the specified number of rows and columns.
     *
     * @param rows The new number of rows in the matrix.
     * @param cols The new number of columns in the matrix.
     */
    void resize(size_t rows, size_t cols);

    /**
     * Accesses the element at the specified row and column index in the
     * matrix.
     *
     * @param i The row index.
     * @param j The column index.
     * @return A reference to the element at the specified position.
     */
    inline T& operator()(size_t i, size_t j)
    {
        return m_ptr[i * m_cols + j];
    }

    /**
     * Accesses the element at the specified row and column index in the
     * matrix (const version).
     *
     * @param i The row index.
     * @param j The column index.
     * @return The value of the element at the specified position.
     */
    inline const T operator()(size_t i, size_t j) const
    {
        return m_ptr[i * m_cols + j];
    }

    /**
     * Returns the number of rows in the matrix.
     *
     * @return The number of rows.
     */
    size_t nrows() const { return m_rows; }

    /**
     * Returns the number of columns in the matrix.
     *
     * @return The number of columns.
     */
    size_t ncols() const { return m_cols; }

    /**
     * Accesses the element at the specified row index in the matrix.
     *
     * @param i The row index.
     * @return A pointer to the elements of the specified row.
     */
    T* operator[](size_t i){ return m_ptr + i*m_cols; }

    /**
     * Returns a pointer to the beginning of the specified row in the matrix.
     *
     * @param i The row index.
     * @return A pointer to the beginning of the specified row.
     */
    T* begin(size_t i) const { return m_ptr + i*m_cols; }

    /**
     * Returns a pointer to the end of the specified row in the matrix.
     *
     * @param i The row index.
     * @return A pointer to the end of the specified row.
     */
    T* end(size_t i) const { return m_ptr + (i + 1)*m_cols; }

    /**
     * Returns the count of non-none elements in the matrix.
     *
     * @return The count of non-none elements.
     */
    int non_none_cnt();

    /**
     * A vector containing the data elements of the matrix.
     */
    std::vector<T> m_data;

    /**
     * A pointer to the raw data of the matrix.
     */
    T* m_ptr;


private:
    /**
     * The number of rows in the matrix.
     */
    size_t m_rows;

    /**
     * The number of columns in the matrix.
     */
    size_t m_cols;
};


template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
    : m_data(rows * cols)
    , m_ptr(&m_data[0])
    , m_rows(rows)
    , m_cols(cols)
{
}


template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols, T *data_ptr)
    : m_data(0)
    , m_ptr(data_ptr)
    , m_rows(rows)
    , m_cols(cols)
{
}


template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols, const T &const_val)
    : m_data(rows * cols, const_val)
    , m_ptr(&m_data[0])
    , m_rows(rows)
    , m_cols(cols)
{
}


template <class T>
Matrix<T>::Matrix(size_t rows, std::vector<T> &data)
    : m_data(data)
    , m_ptr(&m_data[0])
    , m_rows(rows)
    , m_cols(data.size()/rows)
{
}


template <class T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : m_data(other.m_data)
    , m_ptr(m_data.empty() ? other.m_ptr : &m_data[0])
    , m_rows(other.m_rows)
    , m_cols(other.m_cols)
{
}


template <class T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept
    : m_data(std::move(other.m_data))
    , m_ptr(m_data.empty() ? other.m_ptr : &m_data[0])
    , m_rows(other.m_rows)
    , m_cols(other.m_cols)
{
    other.m_ptr = nullptr;
}


template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if (this != &other)
    {
        m_data = other.m_data;
        m_ptr = m_data.empty() ? other.m_ptr : &m_data[0];
        m_rows = other.m_rows;
        m_cols = other.m_cols;
    }
    return *this;
}


template <class T>
void Matrix<T>::resize(size_t rows, size_t cols)
{
    m_rows = rows;
    m_cols = cols;
    m_data.resize(rows*cols);
    m_ptr = &m_data[0];
}


template <class T>
int Matrix<T>::non_none_cnt()
{
    int cnt = 0;
    for (auto ptr = m_ptr; ptr != m_ptr + m_rows*m_cols; ++ptr)
    {
        cnt += (*ptr) == NONE ? 0 : 1;
    }
    return cnt;
}


/*
 * @brief Prints an Matrix<T> object to an output stream.
 */
template <class T>
std::ostream& operator<<(std::ostream &out, Matrix<T> const& matrix)
{
    out << "[";

    for(size_t i = 0; i < matrix.nrows(); ++i)
    {
        if (i > 0)
        {
            out << " ";
        }
        out << "[";
        for(size_t j = 0; j < matrix.ncols(); j++)
        {
            out << matrix(i, j);
            if (j + 1 != matrix.ncols())
            {
                out << ", ";
            }
        }
        out << "]";
        if (i + 1 != matrix.nrows())
        {
            out << ",\n";
        }
    }

    out << "]\n";
    return out;
}


/*
 * @brief A struct for nearst neighbor candidates in a query search.
 */
struct Candidate
{
    /*
     * The identifier of the candidate.
     */
    int idx;

    /*
     * The key/distance of the candidate.
     */
    float key;

    /*
     * Overloaded less-than operator used to store Candidates in a MinHeap.
     */
    bool operator<(const Candidate& other) const
    {
        return key > other.key;
    }
};


/*
 * @brief A template class representing a heap data structure.
 */
template<class T>
class Heap
{
public:
    /*
     * Pushes a new element into the heap.
     *
     * @param value The value to be pushed into the heap.
     */
    void push(const T& value)
    {
        heap.push(value);
    }

    /*
     * Removes and returns the top element from the heap.
     *
     * @return The top element of the heap.
     */
    T pop()
    {
        T top = heap.top();
        heap.pop();
        return top;
    }

    /*
     * Checks if the heap is empty.
     *
     * @return True if the heap is empty, false otherwise.
     */
    bool empty() const
    {
        return heap.empty();
    }

private:
    /*
     * The underlying priority queue used to implement the heap.
     */
    std::priority_queue<T> heap;
};



/**
 * @brief A cache-friendly implementation of a list of maximum heaps.
 *
 * The HeapList class provides a cache-friendly representation of multiple
 * heaps, each containing nodes with associated indices, keys and flags.
 * It supports operations such as pushing nodes into the heaps, sorting
 * the heaps, and retrieving information about the heaps.
 *
 * @tparam KeyType The type of keys associated with the nodes.
 */
template <class KeyType>
class HeapList
{
private:
    /**
     * Number of heaps.
     */
    size_t n_heaps;

    /**
     * Number of nodes.
     */
    size_t n_nodes;

public:
    /**
     * Matrix storing indices of nodes in the heaps.
     */
    Matrix<int> indices;

    /**
     * Matrix storing keys associated with nodes.
     */
    Matrix<KeyType> keys;

    /*
     * Matrix storing flags associated with nodes.
     *
     * As bool leads to problems since std::vector<bool> is special from all
     * other std::vector specializations, char is used instead.
     */
    Matrix<char> flags;

    /**
     * Default constructor. Creates an empty HeapList.
     */
    HeapList() {}

    /**
     * Constructor that initializes the HeapList with specified parameters.
     *
     * @param n_heaps The number of heaps.
     * @param n_nodes The number of nodes in each heap.
     * @param key0 The initial key value for all nodes.
     * @param flag0 The initial flag value for all nodes.
     */
    HeapList(size_t n_heaps, size_t n_nodes, KeyType key0, char flag0)
        : n_heaps(n_heaps)
        , n_nodes(n_nodes)
        , indices(n_heaps, n_nodes, NONE)
        , keys(n_heaps, n_nodes, key0)
        , flags(n_heaps, n_nodes, flag0)
        {}

    /**
     * Constructor that initializes the HeapList with specified parameters,
     * using the same initial key value for all nodes and with no flags.
     *
     * @param n_heaps The number of heaps.
     * @param n_nodes The number of nodes in each heap.
     * @param key0 The initial key value for all nodes.
     */
    HeapList(size_t n_heaps, size_t n_nodes, KeyType key0)
        : n_heaps(n_heaps)
        , n_nodes(n_nodes)
        , indices(n_heaps, n_nodes, NONE)
        , keys(n_heaps, n_nodes, key0)
        , flags(0, 0)
        {}

    /**
     * Retrieves the number of heaps in the HeapList.
     *
     * @return The number of heaps.
     */
    size_t nheaps() const {return n_heaps;}

    /**
     * Retrieves the number of nodes in each heap of the HeapList.
     *
     * @return The number of nodes in each heap.
     */
    size_t nnodes() const {return n_nodes;}

    /**
     * Checks if the HeapList has no flags associated with the nodes.
     *
     * @return True if the HeapList has no flags, false otherwise.
     */
    bool noflags() const { return flags.nrows() == 0; }

    /**
     * Retrieves the maximum key value in the specified heap.
     *
     * @param i The index of the heap.
     * @return The maximum key value in the heap.
     */
    KeyType max(size_t i) const { return keys(i, 0); }

    /**
     * Retrieves the number of non none nodes in the specified heap.
     *
     * @param i The index of the heap.
     * @return The number of non none nodes of the heap.
     */
    size_t size(size_t i) const;

    /**
     * Pushes a node with the specified index, key, and flag into the
     * specified heap if its key is smaller and it is not already in the heap.
     *
     * @param i The index of the heap.
     * @param idx The index of the node.
     * @param key The key associated with the node.
     * @param flag The flag associated with the node.
     * @return 1 if the node was added to the heap, 0 otherwise.
     */
    int checked_push(size_t i, int idx, KeyType key, char flag);

    /**
     * Pushes a node with the specified index, key, and flag into the
     * specified heap if its key is smaller and it is not already in the heap.
     *
     * @param i The index of the heap.
     * @param idx The index of the node.
     * @param key The key associated with the node.
     * @return 1 if the node was added to the heap, 0 otherwise.
     */
    int checked_push(size_t i, int idx, KeyType key);

    /**
     * Performs a "siftdown" operation on the specified heap starting from the
     * given index.
     *
     * The "siftdown" operation descends the top node down the heap by swapping
     * values until the maximum heap criterion is met or "stop" is reached.
     *
     * @param i The index of the heap to perform the siftdown operation on.
     * @param stop The index at which to stop the siftdown operation.
     */
    void siftdown(size_t i, size_t stop);

    /**
     * @brief Sorts all heaps in ascending key order.
     * given index.
     *
     * As the heap criterion is already met only the second part of the
     * "Heapsort" algorithm is executed.
     */
    void heapsort();
};


template <class KeyType>
void HeapList<KeyType>::heapsort()
{
    int tmp_id;
    KeyType tmp_key;

    for (size_t i = 0; i < n_heaps; ++i)
    {
        for (size_t j = n_nodes - 1; j > 0; --j)
        {
            tmp_id = indices(i, 0);
            tmp_key = keys(i, 0);

            indices(i, 0) = indices(i, j);
            keys(i, 0) = keys(i, j);

            indices(i, j) = tmp_id;
            keys(i, j) = tmp_key;

            this->siftdown(i, j);
        }
    }
}


template <class KeyType>
void HeapList<KeyType>::siftdown(size_t i, size_t stop)
{
    KeyType key = keys(i, 0);
    int idx = indices(i, 0);

    size_t current = 0;
    size_t left_child;
    size_t right_child;
    size_t swap;

    while (true)
    {
        left_child = 2*current + 1;
        right_child = left_child + 1;

        if (left_child >= stop)
        {
            break;
        }
        else if (right_child >= stop)
        {
            if (keys(i, left_child) > key)
            {
                swap = left_child;
            }
            else
            {
                break;
            }
        }
        else if (keys(i, left_child) >= keys(i, right_child))
        {
            if (keys(i, left_child) > key)
            {
                swap = left_child;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (keys(i, right_child) > key)
            {
                swap = right_child;
            }
            else
            {
                break;
            }
        }
        indices(i, current) = indices(i, swap);
        keys(i, current) = keys(i, swap);

        current = swap;
    }
    // Insert node at current position.
    indices(i, current) = idx;
    keys(i, current) = key;
}


template <class KeyType>
int HeapList<KeyType>::checked_push(size_t i, int idx, KeyType key, char flag)
{
    if (key >= keys(i, 0))
    {
        return 0;
    }

    // Break if we already have this element.
    for (auto it = indices.begin(i); it != indices.end(i); ++it)
    {
        if (*it == idx)
        {
            return 0;
        }
    }

    // Siftdown: Descend the heap, swapping values until the max heap
    // criterion is met.
    size_t current = 0;
    size_t left_child;
    size_t right_child;
    size_t swap;

    while (true)
    {
        left_child = 2*current + 1;
        right_child = left_child + 1;

        if (left_child >= n_nodes)
        {
            break;
        }
        else if (right_child >= n_nodes)
        {
            if (keys(i, left_child) > key)
            {
                swap = left_child;
            }
            else
            {
                break;
            }
        }
        else if (keys(i, left_child) >= keys(i, right_child))
        {
            if (keys(i, left_child) > key)
            {
                swap = left_child;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (keys(i, right_child) > key)
            {
                swap = right_child;
            }
            else
            {
                break;
            }
        }
        indices(i, current) = indices(i, swap);
        keys(i, current) = keys(i, swap);
        flags(i, current) = flags(i, swap);

        current = swap;
    }

    // Insert node at current position.
    indices(i, current) = idx;
    keys(i, current) = key;
    flags(i, current) = flag;

    return 1;
}


template <class KeyType>
int HeapList<KeyType>::checked_push(size_t i, int idx, KeyType key)
{
    if (key >= keys(i, 0))
    {
        return 0;
    }

    // Break if we already have this element.
    for (auto it = indices.begin(i); it != indices.end(i); ++it)
    {
        if (*it == idx)
        {
            return 0;
        }
    }

    // Siftdown: Descend the heap, swapping values until the max heap
    // criterion is met.
    size_t current = 0;
    size_t left_child;
    size_t right_child;
    size_t swap;

    while (true)
    {
        left_child = 2*current + 1;
        right_child = left_child + 1;

        if (left_child >= n_nodes)
        {
            break;
        }
        else if (right_child >= n_nodes)
        {
            if (keys(i, left_child) > key)
            {
                swap = left_child;
            }
            else
            {
                break;
            }
        }
        else if (keys(i, left_child) >= keys(i, right_child))
        {
            if (keys(i, left_child) > key)
            {
                swap = left_child;
            }
            else
            {
                break;
            }
        }
        else
        {
            if (keys(i, right_child) > key)
            {
                swap = right_child;
            }
            else
            {
                break;
            }
        }
        indices(i, current) = indices(i, swap);
        keys(i, current) = keys(i, swap);

        current = swap;
    }

    // Insert node at current position.
    indices(i, current) = idx;
    keys(i, current) = key;

    return 1;
}


template <class KeyType>
size_t HeapList<KeyType>::size(size_t i) const
{
    size_t count = std::count_if(
        indices.begin(i),
        indices.end(i),
        [&](int const &idx){ return idx != NONE; }
    );
    return count;
}


/**
 * @brief Returns number of non-none matrix elements.
 */
int non_none_cnt(std::vector<std::vector<int>> matrix);


/*
 * Auxiliary function for recursively printing a binary Heap.
 */
template <class KeyType>
void _add_heap_from_to_stream
(
    std::ostream &out,
    std::string prefix,
    HeapList<KeyType> heaplist,
    size_t i,
    size_t from,
    char is_left
)
{
    if (from >= heaplist.nnodes())
    {
        return;
    }

    out << prefix;
    out << (is_left && (from + 1 < heaplist.nnodes()) ? "├──" : "└──");

    // Print current node
    char flag = heaplist.noflags() ? 'x' : heaplist.flags(i, from);
    out << "(idx=" << heaplist.indices(i, from)
        << " key=" << heaplist.keys(i, from)
        << " flag=" << flag
        << ")\n";
    std::string prefix_children = prefix + (is_left ? "│   " : "    ");

    // Add children of current node.
    _add_heap_from_to_stream(out, prefix_children, heaplist, i, from*2 + 1, true);
    _add_heap_from_to_stream(out, prefix_children, heaplist, i, from*2 + 2, false);
}


/*
 * Auxiliary function for printing a binary Heap.
 */
template <class KeyType>
void add_heap_to_stream(std::ostream &out, HeapList<KeyType> heaplist, size_t i)
{
    out << i << " [size=" << heaplist.nnodes() << "]\n";
    _add_heap_from_to_stream(out, "    ", heaplist, i, 0, false);
}


/**
 * @brief Prints a HeapList<KeyType> object to an output stream.
 */
template <class KeyType>
std::ostream& operator<<(std::ostream &out, HeapList<KeyType> &heaplist)
{
    out << "HeapList(n_heaps=" << heaplist.nheaps() << ", n_nodes="
        << heaplist.nnodes() << ", KeyType=" << typeid(KeyType).name()
        << ",\n";
    for (size_t i = 0; i < heaplist.nheaps(); ++i)
    {
        out << "    ";
        add_heap_to_stream(out, heaplist, i);
    }
    out << ")\n";
    return out;
}


/*
 * @brief Debug function to print the data as 2d map.
 */
void print_map(Matrix<float> matrix);


template <class T>
std::ostream& operator<<(std::ostream &out, std::vector<T> &vec)
{
    out << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        out << vec[i];
        if (i + 1 != vec.size())
        {
            out << ", ";
        }
    }
    out << "]";
    return out;
}


/*
 * @brief Prints a vectorized Matrix object to an output stream.
 */
template <class T>
std::ostream& operator<<(std::ostream &out, std::vector<std::vector<T>> &matrix)
{
    out << "[\n";
    for(size_t i = 0; i < matrix.size(); ++i)
    {
        out << "    " << i << ": " <<  matrix[i] << ",\n";
    }
    out << "]";
    return out;
}


/*
 * @brief A struct holding two node identifiers and the key/distance between
 * the nodes.
 */
typedef struct
{
    int idx0;
    int idx1;
    float key;
} NNUpdate;


/*
 * @brief Prints a NNUpdate object to an output stream.
 */
std::ostream& operator<<(std::ostream &out, NNUpdate &update);


/*
 * @brief Prints a std::vector<NNUpdate> object to an output stream.
 */
std::ostream& operator<<(std::ostream &out, std::vector<NNUpdate> &updates);



} // namespace nndescent
