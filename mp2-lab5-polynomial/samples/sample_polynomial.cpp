#include <iostream>
#include <fstream>
#include <locale>
#include "polynomial.h"

int main()
{
	Polinom f, g;

	cout << "Enter the first polynomial" << endl;
	cout << "Enter the number of monoms and their values (coefficient, degree)" << endl;
	cin >> f;
	cout << "Enter the second polynomial" << endl;
	cout << "Enter the number of monoms and their values(coefficient, degree)" << endl;
	cin >> g;
	cout << "You entered: " << endl << "f: " << endl << f << "g: " << endl << g << endl;

	cout << "Choose an operation on polynomials" << endl;
	while (true) {
		cout << "1. Subtract f and g" << endl;
		cout << "2. Multiply f and g" << endl;
		cout << "3. Find the value of f in a point" << endl;
		cout << "4. Add f and g" << endl;

		int menu;
		cin >> menu;

		if (menu == 4) {
			cout << endl << "f + g: " << endl << (f + g) << endl;
		}
 		else if (menu == 1) {
			cout << endl << "f - g: " << endl << (f - g) << endl;
		}
		else if (menu == 2) {
			cout << endl << "f * g: " << endl << (f * g) << endl;
		}
		else if (menu == 3) {
			double a, b, c;
			cout << "Enter point" << endl;
			cin >> a >> b >> c;
			cout << endl << "f (" << a << "," << b << "," << c << "): " << f.ValueinPoint(a, b, c) << endl;
		}
		else {
			cout << "Please choose one of the suggested options" << endl;
			continue;
		}

		while (true) {
			
			cout << "Do you want to shoose another action?" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No" << endl;
			cin >> menu;
			if ((menu == 1) || (menu == 2)) {
				break;
			}
			cout << "Please choose one of the suggested options" << endl;
		}

		if (menu == 1) {
			continue;
		}
		else {
			break;
		}
	}
	return 0;
}