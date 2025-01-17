// PolynomialCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
// For std::pair
#include <utility> 
#include <cmath>

using namespace std;
const int MAX_LENGTH_INT = 10;
//max lenght - 2 integers, 1 '/', and 2 '-' + '\0'
const int MAX_LENGTH_COEFFICIENT = 2 * MAX_LENGTH_INT + 4;

void clearInputBuffer() {
	cin.clear();
	while (cin.get() != '\n');
}

void displayMenu() {
	cout << "Welcome to Polynomial Calculator - a mini project intended to work with polynomials with rational coefficients" << endl;
	cout << "Choose one of the following functionalities:" << endl;
	cout << "1) Add polynomials" << endl;
	cout << "2) Subtract polynomials" << endl;
	cout << "3) Multiply polynomials" << endl;
	cout << "4) Divide polynomials" << endl;
	cout << "5) Multiply polynomial by scalar" << endl;
	cout << "6) Find value of polinomial ata a given number" << endl;
	cout << "7) Find GCD of two polynomials" << endl;
	cout << "8) Display Vieta's formulas for given polynomial" << endl;
	cout << "9) Represent a polynomial in powers of (x + a)" << endl;
	cout << "10) Factor polynomial and find its rational roots" << endl;
	cout << "11) Quit program" << endl;
}

int chooseOption() {
	int option;
	cout << "Enter your option here>> ";
	cin >> option;

	while (cin.fail() || option < 1 || option > 11)
	{
		if (cin.fail()) {
			clearInputBuffer();
			cout << "Invalid input! Please choose a number between 1 and 11!" << endl << endl;
		}
		else {
			cout << "Invalid option! Please choose a number between 1 and 11!" << endl << endl;
		}
		cout << "Enter your option here>> ";
		cin >> option;
	}
	return option;
}

int chooseDegree() {
	int degree;
	cout << "Enter degree of your polynomial>> ";
	cin >> degree;

	while (cin.fail() || degree < 0)
	{
		if (cin.fail()) {
			clearInputBuffer();
			cout << "Invalid input! Please choose a number that isn't negative!" << endl << endl;
		}
		else {
			cout << "Invalid option! Please choose a number that isn't negative!" << endl << endl;
		}
		cout << "Enter degree of your polynomial>> ";
		cin >> degree;
	}
	return degree;
}

int strLength(const char* str) {
	if (str == nullptr) {
		return -2;
	}

	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

int separatorPosition(const char* str) {
	if (str == nullptr) {
		return -2;
	}

	int length = strLength(str);
	for (size_t i = 0; i < length; i++) {
		if (str[i] == '/' && i != 0 && i != length - 1) {
			return i;
		}
	}
	return -1;
}

int minusPosition(const char* str) {
	if (str == nullptr) {
		return -2;
	}

	int separator = separatorPosition(str);
	if (separator != -1) {
		if (str[separator + 1] == '-' && separator + 1 < strLength(str) - 1) {

			if (str[0] == '-') {

				return 2;
			}
			return 1;
		}
	}

	if (str[0] == '-') {

		return 0;
	}
	return -1;
}

bool isNegative(const char* str) {
	if (str == nullptr) {
		return -2;
	}
	int minus = minusPosition(str);
	if (minus == 2 || minus == -1)
	{
		return false;
	}
	return true;
}

bool isNumber(char ch) {
	return ch >= '0' && ch <= '9';
}

int charToInt(char ch) {
	if (!isNumber(ch)) {
		return -1;
	}
	return ch - '0';
}

int StrToInt(char* str, size_t beg, size_t end) {
	if (str == nullptr) {
		return -2;
	}

	int result = 0;
	if (beg > end) {
		return -1;
	}

	for (size_t i = beg; i < end; i++) {
		result *= 10;

		int digit = charToInt(str[i]);
		if (digit == -1) {
			return -1;
		}

		result += digit;
	}
	return result;
}

int numerator(char* str) {
	if (str == nullptr) {
		return -2;
	}

	int sepatator = separatorPosition(str);
	int minus = minusPosition(str);
	int length = strLength(str);

	if (sepatator == -1) {
		if (minus == 0) {
			return StrToInt(str, 1, length);
		}
		return StrToInt(str, 0, length);
	}

	if (minus == 0 || minus == 2) {
		return StrToInt(str, 1, sepatator);
	}
	return StrToInt(str, 0, sepatator);
}

int denominator(char* str) {
	if (str == nullptr) {
		return -2;
	}

	int sepatator = separatorPosition(str);
	int minus = minusPosition(str);
	int length = strLength(str);

	if (sepatator == -1) {
		return 1;
	}
	if (minus == 1 || minus == 2) {
		return StrToInt(str, sepatator + 2, length);
	}
	return StrToInt(str, sepatator + 1, length);
}

//Euclidean algorithm
int gcdNumbers(int num1, int num2) {
	while (num2 != 0) {
		int temp = num2;
		num2 = num1 % num2;
		num1 = temp;
	}
	return abs(num1);
}

pair<int, int> simplifyFraction(int numerator, int denominator) {
	pair<int, int> result;
	int g = gcdNumbers(abs(numerator), abs(denominator));
	numerator /= g;
	denominator /= g;
	result.first = numerator;
	result.second = denominator;
	return result;
}

void inputPolynomial(vector<pair<int, pair<int, int>>>& polynomial, char PolynomialName) {
	cout << "Enter Polynomial " << PolynomialName << "(x)" << endl;

	int degree = chooseDegree();
	cout << endl;

	polynomial.clear();
	for (int i = degree; i >= 0; --i) {
		char input[MAX_LENGTH_COEFFICIENT];
		cout << "Enter coefficient before x^" << i << ">> ";
		cin >> input;

		while (numerator(input) == -1 || denominator(input) <= 0) {
			cout << "Invalid input! Please choose a rational coefficient!" << endl << endl;
			while (cin.get() != '\n');
			cout << "Enter coefficient before x^" << i << ">> ";
			cin >> input;
		}

		int num = numerator(input);
		int den = denominator(input);

		if (isNegative(input)) {
			num = 0 - num;
		}

		pair<int, int> fraction = simplifyFraction(num, den);
		if (num != 0) {
			polynomial.push_back({ i, fraction });
		}
	}
}

void displayPolynomial(const vector<pair<int, pair<int, int>>>& polynomial, char PolynomialName) {
	if (polynomial.empty()) {
		cout << PolynomialName << "(x) is empty!" << endl;
		return;
	}

	cout << PolynomialName << "(x) = ";
	for (size_t i = 0; i < polynomial.size(); ++i) {
		int numerator = polynomial[i].second.first;
		int denominator = polynomial[i].second.second;
		int degree = polynomial[i].first;

		if (i > 0 && numerator > 0) {
			cout << "+";
		}

		if (denominator == 1) {
			cout << numerator;
		}
		else {
			cout << numerator << "/" << denominator;
		}

		if (degree > 0) {
			cout << "x";
			if (degree > 1) {
				cout << "^" << degree;
			}
		}
	}
	cout << endl;
}

int main()
{
	vector<pair<int, pair<int, int>>> polynomial1, polynomial2, result;
	displayMenu();
	cout << endl;
	int option = chooseOption();
	cout << endl;
	inputPolynomial(polynomial1, 'P');
	displayPolynomial(polynomial1, 'P');
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
