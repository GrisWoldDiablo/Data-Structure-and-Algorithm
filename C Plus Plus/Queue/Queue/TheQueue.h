/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */

#ifndef THEQUEUE
#define THEQUEUE

 /// <summary>
 /// Custom queue class
 /// </summary>
template<class T>
class TheQueue
{
private: // class variables
	int _head; // index of the element at the beginning of the queue
	int _tail; // index of the element at the end of the queue
	int _size; // the size of the queue
	T* _array; // array holding the queue
	int _arraySize; // current size of the array
	const int ARRAY_INITIAL_SIZE = 8; // initial size of the array holding the queue

public: // user Methods
	TheQueue(); // Constructor
	~TheQueue(); // Destructor
	void Enqueue(T key);
	T Dequeue();
	T Peek();
	void Clear();
	T* ToArray();
	bool Empty();

private: // class Method
	void IncreaseSize();

public: // Property
	int Count() { return _size; }
};

/// <summary>
/// Class constructor,
/// initialize head, tail, size and
/// initinial size of the array is 8.
/// -----PSEUDO CODE-----
/// Queue()
///  Q.head = 0
///  Q.tail = 0
///  Q.size = 0
///  Let Q[0..7] be a new array
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
inline TheQueue<T>::TheQueue()
{
	_head = 0;
	_tail = 0;
	_size = 0;
	_array = new T[ARRAY_INITIAL_SIZE];
	_arraySize = ARRAY_INITIAL_SIZE;
}

/// <summary>
/// Class destructor,
/// delete the array holding the queue from memory
/// </summary>
template<class T>
inline TheQueue<T>::~TheQueue()
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
inline void TheQueue<T>::Enqueue(T key)
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
inline T TheQueue<T>::Dequeue()
{
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
inline bool TheQueue<T>::Empty()
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
///  Q.tail = 0
///  Q = T
/// -----PSEUDO CODE-----
/// </summary>
template<class T>
inline void TheQueue<T>::IncreaseSize()
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
inline T* TheQueue<T>::ToArray()
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
inline T TheQueue<T>::Peek()
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
inline void TheQueue<T>::Clear()
{
	_head = 0;
	_tail = 0;
	_size = 0;
	_arraySize = ARRAY_INITIAL_SIZE;
	delete[] _array;
	_array = new T[ARRAY_INITIAL_SIZE];
}
#endif // !THEQUEUE
