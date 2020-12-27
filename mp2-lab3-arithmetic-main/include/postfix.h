#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

class TPostfix 
{
	string infix;
	string postfix;

	bool Icorrect(string str);
public:
	TPostfix()
	{
		infix = "a+b";
	}
	TPostfix(string t )
	{
		if (!Icorrect(t))
		{
			throw std::logic_error("Incorrect expression");
		}
		infix = t;
		if (infix.length() < 1)
			throw std::logic_error("Error in infix length");
		//infix = str;
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix();
	double Calculate();				//Ввод переменных, вычисление по постфиксной форме
	bool CheckOper(char elem) 
	{		//проверить оператор?
		char operators[7] = { '(',')','+','-','*','/','^' };
		for (int i = 0; i < 7; i++)
			if (elem == operators[i])
				return true;
		return false;
	}
	bool CheckOper2(char elem) 
	{
		char operators2[5] = {'+','-','*','/','^'};
		for (int i = 0; i < 5; i++)
			if (elem == operators2[i])
				return true;
		return false;
	}
	int Priority(char oper) 
	{		//получить приоритет операции
		char operators[5] = { '+','-','*','/','^'};
		char priority[5] = { 1, 1, 2, 2, 3};
		for (int i = 0; i < 5; i++)
			if (oper == operators[i])
				return priority[i];
		return -2;
	}
	
};

#endif