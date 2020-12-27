#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");

	string expression;
	double res;
	
	cout << "Введите арифметическое выражение: ";
	cin >> expression;
	cout << expression << endl;
	try
	{
		TPostfix postfix(expression);
		cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
		postfix.ToPostfix();
		cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;

		res = postfix.Calculate();
		cout <<"Результат вычисления:"<< res << endl;
	}
	catch (const char* s)
	{
		cout << s;
	}
	return 0;
}