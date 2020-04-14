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
	void MinHeapify(int i, int heapSize);
	void IncreaseKey(int i, T key);
	void DecreaseKey(int i, T key);
	int Parent(int i);
	int Right(int i);
	int Left(int i);

public: // Property
	int Count() { return _size; }
	PriorityType Type() { return _priorityType; }
};

/// <summary>
/// Class constructor,
/// initialize size and priority type.
/// initial size of the array is 8.
/// -----PSEUDO CODE-----
/// (Q is the queue, t is the type of priority)
/// PriorityQueue(Q,t)
///  Q.size = 0
///  Q.priotityType = t
///  Let Q[0..7] be a new array
///  if type == Min
///		Q.priorityBound = +infinity
///  else
///		Q.pritotyBound = -infinity
/// -----PSEUDO CODE-----
/// </summary>
/// <param name = "priorityType">Type of priority of the queue, min or max</param>
template<class T>
ThePriorityQueue<T>::ThePriorityQueue(PriorityType priorityType)
{
	_size = 0;
	_array = new T[ARRAY_INITIAL_SIZE];
	_arraySize = ARRAY_INITIAL_SIZE;
	_priorityType = priorityType;
	switch (_priorityType)
	{
	case PriorityType::Min:
		_priorityBound = std::numeric_limits<T>::max();
		break;
	default: // PriorityType::Max
		_priorityBound = -std::numeric_limits<T>::max();
		break;
	}
}

/// <summary>
/// Class destructor,
/// delete the array holding the queue from memory
/// </summary>
template<class T>
ThePriorityQueue<T>::~ThePriorityQueue()
{
	delete[] _array;
}

/// <summary>
/// Add an element in the queue and call the appropriate
/// function to place the element at the right place in the
/// queue based on the priority type.
/// -----PSEUDO CODE-----
/// (Q is the Queue, k is the elements to be added)
/// Enqueue(Q,k)
///  Q.size = Q.size + 1
///  if Q.size == Q.arraySize
///		IncreaseSize(Q)
///  Q.array[Q.size - 1] =  Q.priorityBound
///  if Q.pritorityType == Min
///		DecreaseKey(Q,Q.size - 1, key)
///  else
///		IncreaseKey(Q,Q.size - 1, key)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="key">the element to be added</param>
template<class T>
void ThePriorityQueue<T>::Enqueue(T key)
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
/// Remove an element priority element and reorganize the heap
/// to bring the next element in line at the front of the queue.
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// Dequeue(Q)
///  if Q.size == 0
///		Throw Error
///  else
///		k = Q[0]
///		Q[0] = Q[Q.size - 1]
///		Q.size = Q.size - 1
///		if Q.pritorityType == Min
///			MinHeapify(Q,Q.size - 1, key)
///		else
///			MaxHeapify(Q,Q.size - 1, key)
///		return k
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>the element at the beginning of the queue</returns>
template<class T>
T ThePriorityQueue<T>::Dequeue()
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
///		return Q[0]
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>the element at the beginning of the queue</returns>
template<class T>
T ThePriorityQueue<T>::Peek()
{
	if (_size == 0)
	{
		throw std::exception("Queue is empty!");
	}
	return _array[0];
}

/// <summary>
/// Delete the queue and reinitialize it,
/// initial size of the array is 8.
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// Clear(Q)
///  Q.size = 0
///  Let Q[0..7] be a new array
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
void ThePriorityQueue<T>::Clear()
{
	_size = 0;
	_arraySize = ARRAY_INITIAL_SIZE;
	delete[] _array;
	_array = new T[ARRAY_INITIAL_SIZE];
}

/// <summary>
/// Return an array of all the element in the queue, 
/// in the current order of the heap
/// -----PSEUDO CODE-----
/// (Q is the Queue)
/// ToArray(Q)
///  Let T[0..length of Q] be a new array
///  for i = 0 up to length of Q
///		T[i] = Q[i]
///	 return T
/// -----PSEUDO CODE-----
/// </summary>
/// <returns>the queue in an array form</returns>
template<class T>
T* ThePriorityQueue<T>::ToArray()
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
bool ThePriorityQueue<T>::Empty()
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
///  for i = 0 up to Q.size
///		T[i] = Q[i]
///  Q = T
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
void ThePriorityQueue<T>::IncreaseSize()
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
/// Makes sure that the node is the biggest one out of its children
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
void ThePriorityQueue<T>::MaxHeapify(int i, int heapSize)
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

/// <summary>
/// Makes sure that the node is the smallest one out of its children
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (i is the index of the node to MinHeapify)
/// (heapSize is the size of the heap to MinHeapify)
/// MinHeapify(A,i,heapSize)
///  l = Left(i)
///  r = Right(i)
///  if l < heapSize and A[l] < A[i]
///     smallest = l
///  else
///     smallest = i
///  if r < heapSize and A[r] < A[smallest]
///     smallest = r
///  if smallest =/= i
///     swap A[i] and A[smallest]
///     MinHeapify(A,smallest,heapSize)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array of the element to be heapified</param>
/// <param name="i">sub tree root index of the heap</param>
/// <param name="heapSize">the size of the heap</param>
template<class T> // can be of any type, custom types needs to implement LessThan operator '<'
void ThePriorityQueue<T>::MinHeapify(int i, int heapSize)
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

/// <summary>
///	This increase the value of the element at position i with the new element
/// Throws an error if the new element is smaller than the current one.
/// -----PSEUDO CODE-----
/// (Q is the Queue, i is the index, k is the key)
/// IncreaseKey(Q,i,k)
///  if	key < Q[i]
///		Throw Error
///  else
///		Q[i] = key
///		while i > 0 and Q[Parent(i)] < Q[i]
///			swap Q[Parent(i)] and Q[i]
///			i = Parent(i)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="i">the index of the element to increase</param>
/// <param name="key">the new element</param>
template<class T> // can be of any type, custom types needs to implement LessThan operator '<'
void ThePriorityQueue<T>::IncreaseKey(int i, T key)
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

/// <summary>
///	This increase the value of the element at position i with the new element
/// Throws an error if the new element is smaller than the current one.
/// -----PSEUDO CODE-----
/// (Q is the Queue, i is the index, k is the key)
/// DecreaseKey(Q,i,k)
///  if	key < Q[i]
///		Throw Error
///  else
///		Q[i] = key
///		while i > 0 and Q[Parent(i)] > Q[i]
///			swap Q[Parent(i)] and Q[i]
///			i = Parent(i)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="i">the index of the element to decrease</param>
/// <param name="key">the new element</param>
template<class T> // can be of any type, custom types needs to implement GreaterThan operator '>'
void ThePriorityQueue<T>::DecreaseKey(int i, T key)
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
/// Return the Parent element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Left parent's index of requested element</returns>
template<class T>
int ThePriorityQueue<T>::Parent(int i)
{
	return (i / 2);
}

/// <summary>
/// Return the Left child element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Left child's index of requested element</returns>
template<class T>
int ThePriorityQueue<T>::Left(int i)
{
	return (i * 2) + 1;
}

/// <summary>
/// Return the Right child element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Right child's index of requested element</returns>
template<class T> 
int ThePriorityQueue<T>::Right(int i)
{
	return (i * 2) + 2;
}

#endif // !THEPRIORITYQUEUE
