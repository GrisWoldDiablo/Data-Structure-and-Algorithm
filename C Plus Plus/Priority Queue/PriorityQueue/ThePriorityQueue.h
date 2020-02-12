/*
 * Author: Alexandre Lepage
 * Date: February 2020
 */

#ifndef THEPRIORITYQUEUE
#define THEPRIORITYQUEUE

/// <summary>
/// Custom priority queue class
/// </summary>
template <class T>
class ThePriorityQueue
{
private: // class variables
	int _head; // index of the element at the beginning of the queue
	int _tail; // index of the element at the end of the queue
	int _size; // the size of the queue
	T* _array; // array holding the queue
	int _arraySize; // current size of the array
	const int ARRAY_INITIAL_SIZE = 8; // initial size of the array holding the queue
	bool _minPriority;

public: // user Methods
	//ThePriorityQueue(); // Constructor
	ThePriorityQueue(bool minPriority); // Constructor
	~ThePriorityQueue(); // Destructor
	void Enqueue(T key);
	T Dequeue();
	T Peek();
	void Clear();
	T* ToArray();
	bool Empty();

private: // class Method
	void IncreaseSize();
	void HeapSort();
	void BuildMaxHeap();
	void MaxHeapify(T A[], int i, int heapSize);

public: // Property
	int Count() { return _size; }
	int Left(int i);
	int Right(int i);
};

/// <summary>
/// Class constructor,
/// initialize head, tail, size and
/// initinial size of the array is 8.
/// -----PSEUDO CODE-----
/// (Q is the queue)
/// PriorityQueue(Q)
///  Q.head = 0
///  Q.tail = 0
///  Q.size = 0
///  Let Q[0..7] be a new array
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
inline ThePriorityQueue<T>::ThePriorityQueue(bool minPriority)
{
	_head = 0;
	_tail = 0;
	_size = 0;
	_array = new T[ARRAY_INITIAL_SIZE];
	_arraySize = ARRAY_INITIAL_SIZE;
	_minPriority = minPriority;

}

/// <summary>
/// Class destructor,
/// delete the array holding the queue from memory
/// </summary>
template<class T>
inline ThePriorityQueue<T>::~ThePriorityQueue()
{
	delete[] _array;
}

/// <summary>
/// Add an element at the tail of the queue
/// -----PSEUDO CODE-----
/// (Q is the Queue, k is the elements to be added)
/// Enqueue(Q,k)
///  Q[Q.tail] = k
///  Q.tail = Q.tail + 1
///  Q.size = Q.size + 1
///  if Q.tail == length of Q
///		Q.tail = 0
///  if Q.tail == Q.head
///		IncreaseSize(Q)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="key">the element to be added</param>
template<class T>
inline void ThePriorityQueue<T>::Enqueue(T key)
{
	_array[_tail++] = key;
	_size++;
	if (_tail == _arraySize)
	{
		_tail = 0;
	}
	if (_tail == _head)
	{
		IncreaseSize();
	}
}

/// <summary>
/// Remove an element from the head of the queue
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// Dequeue(Q)
///  if Q.size == 0
///		Throw Error
///  else
///		Q.size = Q.size - 1
///		k = Q[Q.head]
///		Q.head = Q.head + 1
///		if Q.head == lenght of Q
///			Q.head = 0
///		return k
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>the element at the beginning of the queue</returns>
template<class T>
inline T ThePriorityQueue<T>::Dequeue()
{
	HeapSort();
	if (_size == 0)
	{
		throw std::exception("Cannot dequeue: Queue is empty!");
	}
	_size--;
	T key = _array[_head++];
	if (_head == _arraySize)
	{
		_head = 0;
	}
	return key;
}

/// <summary>
/// Look at what is the element in pole position in the queue
/// without removing it.
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// Peek(Q)
///  if	Q.size == 0
///		Throw Error
///  else
///		return Q[Q.head]
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>the element at the beginning of the queue</returns>
template<class T>
inline T ThePriorityQueue<T>::Peek()
{
	if (_size == 0)
	{
		throw std::exception("Cannot peek: Queue is empty!");
	}
	return _array[_head];
}

/// <summary>
/// Delete the queue and reinitialize it,
/// initinial size of the array is 8.
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// Clear(Q)
///  Q.head = 0
///  Q.tail = 0
///  Q.size = 0
///  Let Q[0..7] be a new array
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
inline void ThePriorityQueue<T>::Clear()
{
	_head = 0;
	_tail = 0;
	_size = 0;
	_arraySize = ARRAY_INITIAL_SIZE;
	delete[] _array;
	_array = new T[ARRAY_INITIAL_SIZE];
}

/// <summary>
/// Return an array of all the element in the queue, 
/// in the same order dequeue would have returned it.
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// ToArray(Q)
///  Let T[0..length of Q * 2] be a new array
///  i = 0
///  j = Q.head
///  while i < Q.size
///		T[i] = Q[j]
///		i = i + 1
///		j = j + 1
///		if j == length of Q
///			j = j - length of Q
///  return T
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>the queue in an array form</returns>
template<class T>
inline T* ThePriorityQueue<T>::ToArray()
{
	T* tempArray = new T[_size];
	int i = 0;
	int j = _head;
	while (i < _size)
	{
		tempArray[i] = _array[j];
		i++;
		j++;
		if (j == _arraySize)
		{
			j -= _arraySize;
		}
	}
	return tempArray;
}

/// <summary>
/// Check if the queue is empty
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// Empty(Q)
///  if Q.size == 0
///		return True
///  else
///		return False
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>True if queue size at 0</returns>
template<class T>
inline bool ThePriorityQueue<T>::Empty()
{
	return _size == 0;
}

/// <summary>
/// Double the size of the array holding the queue,
/// called when the array is full.
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// IncreaseSize(Q)
///  Let T[0..length of Q * 2] be a new array
///  i = 0
///  j = Q.head
///  while i < Q.size
///		T[i] = Q[j]
///		i = i + 1
///		j = j + 1
///		if j == length of Q
///			j = j - length of Q
///  Q.head = 0
///  Q.tail = Q.size
///  Q = T
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
inline void ThePriorityQueue<T>::IncreaseSize()
{
	int previousArraySize = _arraySize;
	_arraySize *= 2;
	T* tempArray = new T[_arraySize];
	int i = 0;
	int j = _head;
	while (i < _size)
	{
		tempArray[i] = _array[j];
		i++;
		j++;
		if (j == previousArraySize)
		{
			j -= previousArraySize;
		}
	}

	delete[] _array;
	_head = 0;
	_tail = _size;
	_array = tempArray;
}

/// <summary>
/// Sort the array using heap sort algorithm
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// Heapsort(A)
///  BuildMaxHeap(A)
///  heapSize = lenght of A
///  for i = lenght of A - 1 to 1
///      swap A[0] and A[i]
///      heapSize = heapSize - 1
///      MaxHeapify(A,0,heapSize)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
template<class T> // can be of any type, custom types needs to implement GreaterThan operator '>'
void ThePriorityQueue<T>::HeapSort()
{
	BuildMaxHeap();
	int heapSize = _size;
	for (int i = _tail - 1; i >= _head + 1; i--)
	{
		T temp = _array[_head];
		_array[_head] = _array[i];
		_array[i] = temp;
		heapSize--;
		MaxHeapify(_array, _head, heapSize);
	}
}

/// <summary>
/// Place the max element as the root of the heap
/// run heapify on each nodes.
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// BuildMaxHeap(A)
///  for i = FLOOR[(length of A) / 2] down to 0
///     MaxHeapify(A,i,length of A)   
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
template<class T> // can be of any type, custom types needs to implement GreaterThan operator '>'
inline void ThePriorityQueue<T>::BuildMaxHeap()
{
	for (int i = (_size / 2) + _head ; i >= _head; i--)
	{
		MaxHeapify(_array, i, _size);
	}
}

/// <summary>
/// Makes sure that the node is the biggest one out of its childrens
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (i is the index of the node to MaxHeapify)
/// (heapSize is the size of the heap to MaxHeapify)
/// MaxHeapify(A,i,heapSize)
///  l = Left(i)
///  r = Right(i)
///  if l < heapSize and A[l] > A[i]
///     largest = l
///  else
///     largest = i
///  if r < heapSize and A[r] > A[largest]
///     largest = r
///  if largest =/= i
///     swap A[i] and A[largest]
///     MaxHeapify(A,largest,heapSize)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array of the element to be heapified</param>
/// <param name="i">sub tree root index of the heap</param>
/// <param name="heapSize">the size of the heap</param>
template<class T> // can be of any type, custom types needs to implement GreaterThan operator '>'
inline void ThePriorityQueue<T>::MaxHeapify(T A[], int i, int heapSize)
{
	i += _head;
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l < heapSize && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r < heapSize && A[r] > A[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		T temp = A[largest];
		A[largest] = A[i];
		A[i] = temp;
		MaxHeapify(A, largest, heapSize);
	}
}

/// <summary>
/// Return the Left child element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Left child's index of requested element</returns>
template<class T> // can be of any type, custom types needs to implement GreaterThan operator '>'
inline int ThePriorityQueue<T>::Left(int i)
{
	return (i * 2);
}

/// <summary>
/// Return the Right child element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Right child's index of requested element</returns>
template<class T> // can be of any type, custom types needs to implement GreaterThan operator '>'
inline int ThePriorityQueue<T>::Right(int i)
{
	return ((i * 2) + 1);
}

#endif // !THEPRIORITYQUEUE