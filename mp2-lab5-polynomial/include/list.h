#pragma once

#include "node.h"


template <typename T>
class List
{
protected:
	Node<T>* pHead;          //указатель на фиктивную голову списка
public:
	List();
	List(const List<T>& q);

	bool IsEmpty() const;    //проверка на пустоту
	bool IsSort();           //проверка на упорядоченность

	int GetLength() const;
	Node<T>* GetHead() const;
	Node<T>* GetFirst() const;
	Node<T>* GetLast() const;

	virtual void Insert(const T& val);   //вставка на нужное место по убыванию
	void Delete(Node<T>* pl);            //удаление звена

	void Join(const List<T>& q);         //слияние двух списков
};

template <typename T>
List<T>::List()
{
	Node<T>* ph = new Node<T>();   //выделяем память под фиктивную голову
	pHead = ph;
	pHead->pNext = pHead;          //замыкаем список на фиктивной голове
}

template <typename T>
List<T>::List(const List<T>& q)
{
	Node<T>* ph = new Node<T>();
	pHead = ph;
	ph->pNext = pHead;
	Node<T>* pq = q.pHead->pNext; 

	while (pq != q.pHead) {

		Node<T>* pc = new Node<T>(pq->data);  
		ph->pNext = pc;                      
		pc->pNext = pHead;                   //замыкаем список на фиктивной голове

		ph = pc;
		pq = pq->pNext;
	}

}

template<typename T>
bool List<T>::IsEmpty() const
{
	return (pHead->pNext == pHead);
}

template<typename T>
bool List<T>::IsSort()
{
	Node<T>* pc = pHead->pNext;
	while (pc->pNext != pHead) {
		if ((pc->pNext)->data > pc->data) {
			return false;
		}
		pc = pc->pNext;
	}
	return true;
}

template <typename T>
int List<T>::GetLength() const
{
	int length = 0;
	Node<T>* pc = pHead->pNext;
	while (pc != pHead) {
		length++;
		pc = pc->pNext;
	}
	return length;
}

template <typename T>
Node<T>* List<T>::GetHead() const
{
	return pHead;
}

template <typename T>
Node<T>* List<T>::GetFirst() const
{
	if (pHead->pNext == pHead) {
		throw "error";
	}
	return pHead->pNext;
}

template <typename T>
Node<T>* List<T>::GetLast() const
{
	if (pHead->pNext == pHead) {
		throw "error";
	}
	Node<T>* curr = pHead->pNext;
	while (curr->pNext != pHead) {
		curr = curr->pNext;
	}
	return curr;
}

template <typename T>
void List<T>::Insert(const T & val)
{
	Node<T>* ins = new Node<T>(val);  //создаем звено для вставки
	Node<T>* prev = pHead;
	Node<T>* curr = pHead->pNext;

	if (prev == curr) {              //список пустой
		pHead->pNext = ins;
		ins->pNext = pHead;
	}
	else {
		while ((curr->data > ins->data) && (curr != pHead)) {
			curr = curr->pNext;
			prev = prev->pNext;
		}
		prev->pNext = ins;
		ins->pNext = curr;
	}
}

template <typename T>
void List<T>::Delete(Node<T> * pl)
{
	Node<T>* prev = pHead;
	Node<T>* curr = pHead->pNext;
	while (curr != pHead) {
		if (curr == pl) {
			prev->pNext = curr->pNext;
			return;
		}
		curr = curr->pNext;
		prev = prev->pNext;
	}
}

template <typename T>
void List<T>::Join(const List<T> & q)
{
	Node<T>* pCurr = pHead;   //указатель на текущий в результирующем списке 

	Node<T>* pPrev1 = pHead;
	Node<T>* pPrev2 = q.pHead;
	Node<T>* pCurr1 = pHead->pNext;     //указатель, которым идём по первому списку
	Node<T>* pCurr2 = (q.pHead)->pNext; //указатель, которым идём по второму списку

	while ((pCurr1 != pHead) && (pCurr2 != q.pHead)) {

		if ((pCurr1->data) > (pCurr2->data)) {

			pCurr->pNext = pCurr1;
			pCurr = pCurr1;

			pPrev1 = pCurr1;
			pCurr1 = pCurr1->pNext;
		}
		else {

			pCurr->pNext = pCurr2;
			pCurr = pCurr2;

 			pPrev2 = pCurr2;
			pCurr2 = pCurr2->pNext;

		}
	}
	//присоединяем "хвосты"
	if (pCurr1 == pHead) { //первый список закончился
		
		pPrev1->pNext = pCurr2;
		while (pCurr2 != q.pHead) {
			pPrev2 = pCurr2;
			pCurr2 = pCurr2->pNext;
		}
		pPrev2->pNext = pHead;
	}
	else if (pCurr2 == q.pHead) {  //второй список закончился

		pPrev2->pNext = pCurr1;
	}

}
