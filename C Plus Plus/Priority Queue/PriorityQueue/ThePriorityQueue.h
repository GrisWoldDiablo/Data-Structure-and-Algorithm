/*
 * Author: Alexandre Lepage
 * Date: February 2020
 */

#ifndef THEPRIORITYQUEUE
#define THEPRIORITYQUEUE
#include <limits>

enum class PriorityType
{
	Min,
	Max
};
 /// <summary>
 /// Custom priority queue class
 /// </summary>
template <class T>
class ThePriorityQueue
{
private: // class variables
	//int _head; // index of the element at the beginning of the queue
	//int _tail; // index of the element at the end of the queue
	int _size; // the size of the queue
	T* _array; // array holding the queue
	int _arraySize; // current size of the array
	const int ARRAY_INITIAL_SIZE = 8; // initial size of the array holding the queue
	PriorityType _priorityType; // If the queue is has priority has minimum or maximum
	T _priorityBound; // Based on the priority type a value limit value is set

public: // user Methods
	ThePriorityQueue(PriorityType minPriority); // Constructor
	~ThePriorityQueue(); // Destructor
	void Enqueue(T key);
	T Dequeue();
	T Peek();

	void Clear();
	T* ToArray();
	bool Empty();

private: // class Method
	void IncreaseSize();
	void MaxHeapify(int i, int heapSize);
	void IncreaseKey(int i, T key);
	void MinHeapify(int i, int heapSize);
	void DecreaseKey(int i, T key);
	int Parent(int i);
	int Left(int i);
	int Right(int i);

public: // Property

	int Count() { return _size; }
	std::string Type() {
		switch (_priorityType)
		{
		case PriorityType::Min:
			return "Min";
			break;
		default: // PriorityType::Max
			return "Max";
			break;
		}
	}
};

/// <summary>
/// Class constructor,
/// initialize size and
/// initinial size of the array is 8.
/// -----PSEUDO CODE-----
/// (Q is the queue)
/// PriorityQueue(Q,type)
///  Q.size = 0
///  Let Q[0..7] be a new array
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
inline ThePriorityQueue<T>::ThePriorityQueue(PriorityType minPriority)
{
	_size = 0;
	_array = new T[ARRAY_INITIAL_SIZE];
	_arraySize = ARRAY_INITIAL_SIZE;
	_priorityType = minPriority;
	switch (_priorityType)
	{
	case PriorityType::Min:
		_priorityBound = std::numeric_limits<T>::max();
		break;
	default: // PriorityType::Max
		_priorityBound = std::numeric_limits<T>::min();
		break;
	}
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
	_size++;
	if (_size == _arraySize)
	{
		IncreaseSize();
	}
	_array[_size - 1] = _priorityBound;
	switch (_priorityType)
	{
	case PriorityType::Min:
		DecreaseKey(_size - 1, key);
		break;
	case PriorityType::Max:
		IncreaseKey(_size - 1, key);
		break;
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
	if (_size == 0)
	{
		throw std::exception("Queue is empty!");
	}
	T key = _array[0];
	_array[0] = _array[_size - 1];
	_size--;
	switch (_priorityType)
	{
	case PriorityType::Min:
		MinHeapify(0, _size + 1);
		break;
	case PriorityType::Max:
		MaxHeapify(0, _size + 1);
		break;
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
		throw std::exception("Queue is empty!");
	}
	return _array[0];
}


template<class T>
inline void ThePriorityQueue<T>::IncreaseKey(int i, T key)
{
	if (key < _array[i])
	{
		throw std::exception("New key is smaller than current key.");
	}
	_array[i] = key;
	while (i > 0 && _array[Parent(i)] < _array[i])
	{
		T temp = _array[Parent(i)];
		_array[Parent(i)] = _array[i];
		_array[i] = temp;
		i = Parent(i);
	}
}

template<class T>
inline void ThePriorityQueue<T>::DecreaseKey(int i, T key)
{
	if (key > _array[i])
	{
		throw std::exception("New key is larger than current key.");
	}
	_array[i] = key;
	while (i > 0 && _array[Parent(i)] > _array[i])
	{
		T temp = _array[Parent(i)];
		_array[Parent(i)] = _array[i];
		_array[i] = temp;
		i = Parent(i);
	}
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
	for (int i = 0; i < _size; i++)
	{
		tempArray[i] = _array[i];
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
	return Count() == 0;
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
	_arraySize *= 2;
	T* tempArray = new T[_arraySize];
	for (int i = 0; i < _size; i++)
	{
		tempArray[i] = _array[i];
	}
	delete[] _array;
	_array = tempArray;
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
inline void ThePriorityQueue<T>::MaxHeapify(int i, int heapSize)
{
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l < heapSize && _array[l] > _array[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r < heapSize && _array[r] > _array[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		T temp = _array[largest];
		_array[largest] = _array[i];
		_array[i] = temp;
		MaxHeapify(largest, heapSize);
	}
}

template<class T>
inline void ThePriorityQueue<T>::MinHeapify(int i, int heapSize)
{
	int l = Left(i);
	int r = Right(i);
	int smallest;
	if (l < heapSize && _array[l] < _array[i])
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}
	if (r < heapSize && _array[r] < _array[smallest])
	{
		smallest = r;
	}
	if (smallest != i)
	{
		T temp = _array[smallest];
		_array[smallest] = _array[i];
		_array[i] = temp;
		MinHeapify(smallest, heapSize);
	}
}

template<class T>
inline int ThePriorityQueue<T>::Parent(int i)
{
	return (i / 2);
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