#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack{
	T *pMem;
	int size;
	int top;
public:
	TStack(int _size = 1){
		if ((_size < 1) || (_size > MaxStackSize))
			throw _size;
		size = _size;
		top = -1;
		pMem = new T[size];
	}

	TStack(const TStack &tmp){
		size = tmp.size;
		top = tmp.top;
		pMem = new T[size];
		for (int i = 0; i < size; i++)
			pMem[i] = tmp.pMem[i];
	}
	
	~TStack(){
		delete[] pMem;
	}

	bool Full() {							//стек полон?
		return top == size - 1;
	}

	bool Empty() {				 			//стек пуст? 
		return top == -1;
	}

	void Push(T el) {			 			//положить элемент
		if (Full())
			throw ("Нет места");
		/*top++;*/
		pMem[++top] = el;
	}
	T Pop() {								//вытащить элемент
		if (Empty())
			throw ("Пусто");
		top--;
		return pMem[top + 1];
	}

	T Get() {								//считать верхний элемент
		return pMem[top];
	}
};

#endif