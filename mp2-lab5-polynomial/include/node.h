#pragma once

template <typename T>
class List;

template <typename T>
class Node
{
private:
	Node<T>* pNext;   //указатель на следующее звено
	T data;
public:
	Node();
	Node(T val);

	T GetData();
	Node<T>* GetNext();

	Node<T>& operator += (const Node<T>& q);   // сложение двух идущих друг за другом звеньев
											   // сложение data, перестановка указателя

	friend class List<T>;
	friend class Polinom;
};

template <typename T>
Node<T>::Node()
{
	pNext = nullptr;
}

template <typename T>
Node<T>::Node(T val)
{
	pNext = nullptr;
	data = val;
}

template <typename T>
T Node<T>::GetData()
{
	return data;
}

template <typename T>
Node<T>* Node<T>::GetNext()
{
	return pNext;
}

template <typename T>
Node<T>& Node<T>::operator += (const Node<T>& q)
{
	(*this).data += q.data;
	(*this).pNext = q.pNext;
	return *this;
}
