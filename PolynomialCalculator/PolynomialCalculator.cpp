// PolynomialCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
// For std::pair
#include <utility> 
#include <cmath>

using namespace std;
const int MAX_LENGTH_INT = 9;
//max lenght - 2 integers, 1 '/', and 2 '-' + '\0'
const int MAX_LENGTH_COEFFICIENT = 2 * MAX_LENGTH_INT + 4;

typedef pair<int, int> Fraction;

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
	cout << "6) Find value of polinomial at a given number" << endl;
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
	for (int i = 0; i < length; i++) {
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

Fraction simplifyFraction(int numerator, int denominator) {
	pair<int, int> result;
	int g = gcdNumbers(abs(numerator), abs(denominator));
	numerator /= g;
	denominator /= g;
	result.first = numerator;
	result.second = denominator;
	return result;
}

void inputPolynomial(vector<pair<int, Fraction>>& polynomial, char PolynomialName) {
	cout << "Enter Polynomial " << PolynomialName << "(x)" << endl;

	int degree = chooseDegree();
	cout << endl;

	polynomial.clear();
	bool nonZeroFound = false;
	for (int i = degree; i >= 0; --i) {
		char input[MAX_LENGTH_COEFFICIENT];
		cout << "Enter coefficient before x^" << i << ">> ";
		cin >> input;

		while (numerator(input) == -1 || denominator(input) <= 0 ||
			separatorPosition(input) > MAX_LENGTH_INT ||
			(separatorPosition(input) > 0 && strLength(input) - 1 - separatorPosition(input) > MAX_LENGTH_INT)) {
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
			nonZeroFound = true;
			polynomial.push_back({ i, fraction });
		}
	}

	if (!nonZeroFound) {
		cout << "The polynomial is empty! Please enter at least one non-zero coefficient." << endl << endl;
		inputPolynomial(polynomial, PolynomialName);
	}
}

bool isZeroTerm(const pair<int, Fraction>& poly) {
	return poly.second.first == 0;
}

void removeZeroTerms(vector<pair<int, Fraction>>& poly) {
	poly.erase(remove_if(poly.begin(), poly.end(), isZeroTerm), poly.end());
}


void displayPolynomial(vector<pair<int, Fraction>>& polynomial) {
	if (polynomial.empty()) {
		cout << "0" << endl << endl;
		return;
	}

	removeZeroTerms(polynomial);

	for (size_t i = 0; i < polynomial.size(); ++i) {
		int numerator = polynomial[i].second.first;

		int denominator = polynomial[i].second.second;
		int degree = polynomial[i].first;

		if (i > 0 && numerator > 0) {
			cout << "+";
		}

		if (denominator == 1) {
			if ((numerator != 1 && numerator != -1) || degree == 0) {
				cout << numerator;
			}
			else if (numerator == -1) {
				cout << "-";
			}
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
	cout << endl << endl;
}

Fraction addFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.second + b.first * a.second;
	int denominator = a.second * b.second;
	return simplifyFraction(numerator, denominator);
}

Fraction subtractFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.second - b.first * a.second;
	int denominator = a.second * b.second;
	return simplifyFraction(numerator, denominator);
}

Fraction multiplyFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.first;
	int denominator = a.second * b.second;
	return simplifyFraction(numerator, denominator);
}

Fraction divideFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.second;
	int denominator = a.second * b.first;
	return simplifyFraction(numerator, denominator);
}

// Addition of two polynomials
vector<pair<int, Fraction>> addPolynomials(const vector<pair<int, Fraction>>& p1, const vector<pair<int, Fraction>>& p2) {
	vector<pair<int, Fraction>> result;
	size_t i = 0, j = 0;

	while (i < p1.size() || j < p2.size()) {
		int degree1, degree2;
		if (i >= p1.size()) {
			degree1 = -1;
		}
		else {
			degree1 = p1[i].first;
		}

		if (i >= p1.size()) {
			degree2 = -1;
		}
		else {
			degree2 = p2[j].first;
		}

		if (i < p1.size() && (j >= p2.size() || degree1 > degree2)) {
			result.push_back(p1[i]);
			++i;
		}
		else if (j < p2.size() && (i >= p1.size() || degree1 < degree2)) {
			result.push_back(p2[j]);
			++j;
		}
		else {
			if (addFractions(p1[i].second, p2[j].second).first != 0)
			{
				result.push_back({ degree1, addFractions(p1[i].second, p2[j].second) });
			}
			++i;
			++j;
		}
	}

	return result;
}

// Subtraction of two polynomials
vector<pair<int, Fraction>> subtractPolynomials(const vector<pair<int, Fraction>>& p1, const vector<pair<int, Fraction>>& p2) {

	vector<pair<int, Fraction>> result;
	size_t i = 0, j = 0;

	while (i < p1.size() || j < p2.size()) {
		int degree1, degree2;
		if (i >= p1.size()) {
			degree1 = -1;
		}
		else {
			degree1 = p1[i].first;
		}

		if (j >= p2.size()) {
			degree2 = -1;
		}
		else {
			degree2 = p2[j].first;
		}

		if (i < p1.size() && (j >= p2.size() || degree1 > degree2)) {
			result.push_back(p1[i]);
			++i;
		}
		else if (j < p2.size() && (i >= p1.size() || degree1 < degree2)) {
			result.push_back({ p2[j].first, {-p2[j].second.first, p2[j].second.second} });
			++j;
		}
		else {
			if (subtractFractions(p1[i].second, p2[j].second).first != 0)
			{
				result.push_back({ degree1, subtractFractions(p1[i].second, p2[j].second) });
			}
			++i;
			++j;
		}
	}

	return result;
}

// Multiplication of two polynomials
vector<pair<int, Fraction>> multiplyPolynomials(const vector<pair<int, Fraction>>& p1, const vector<pair<int, Fraction>>& p2) {
	vector<pair<int, Fraction>> result;

	for (size_t i = 0; i < p1.size(); ++i) {
		for (size_t j = 0; j < p2.size(); ++j) {
			bool found = false;
			for (size_t k = 0; k < result.size(); ++k) {
				if (result[k].first == p1[i].first + p2[j].first) {
					result[k].second = addFractions(result[k].second, multiplyFractions(p1[i].second, p2[j].second));
					found = true;
					break;
				}
			}
			if (!found) {
				result.push_back({ p1[i].first + p2[j].first, multiplyFractions(p1[i].second, p2[j].second) });
			}
		}
	}
	return result;
}

// Division of two polynomials
pair<vector<pair<int, Fraction>>, vector<pair<int, Fraction>>> dividePolynomials(const vector<pair<int, Fraction>>& p1, 
	const vector<pair<int, Fraction>>& p2) {

	vector<pair<int, Fraction>> quotient;
	vector<pair<int, Fraction>> remainder = p1;

	while (!remainder.empty() && remainder[0].first >= p2[0].first) {
		int degreeDiff = remainder[0].first - p2[0].first;
		Fraction leadingCoeffQuotient = divideFractions(remainder[0].second, p2[0].second);

		quotient.push_back(make_pair(degreeDiff, leadingCoeffQuotient));

		vector<pair<int, Fraction>> temp;
		for (size_t i = 0; i < p2.size(); ++i) {
			Fraction scaledFraction = multiplyFractions(p2[i].second, leadingCoeffQuotient);
			temp.push_back(make_pair(p2[i].first + degreeDiff, scaledFraction));
		}

		remainder = subtractPolynomials(remainder, temp);
		removeZeroTerms(remainder);
	}
	return { quotient, remainder };
}

// Multiplication of polynomial and scalar
vector<pair<int, Fraction>> multiplyPolynomialByScalar(const vector<pair<int, Fraction>>& p1, Fraction scalar) {
	vector<pair<int, Fraction>> result = p1;

	for (size_t i = 0; i < p1.size(); ++i) {
		result[i].second = multiplyFractions(p1[i].second, scalar);
	}
	return result;
}

Fraction inputRationalNumber() {
	char input[MAX_LENGTH_COEFFICIENT];
	cout << "Enter rational number>> ";
	cin >> input;

	while (numerator(input) == -1 || denominator(input) <= 0 ||
		separatorPosition(input) > MAX_LENGTH_INT ||
		(separatorPosition(input) > 0 && strLength(input) - 1 - separatorPosition(input) > MAX_LENGTH_INT)) {
		cout << "Invalid input! Please choose a rational number!" << endl << endl;
		while (cin.get() != '\n');
		cout << "Enter rational number>> ";
		cin >> input;
	}

	int num = numerator(input);
	int den = denominator(input);

	if (isNegative(input)) {
		num = 0 - num;
	}

	return simplifyFraction(num, den);
}

// Find value of polinomial at a given number
Fraction findValue(const vector<pair<int, Fraction>>& p1, Fraction x) {
	Fraction result = { 0, 1 };
	for (size_t i = 0; i < p1.size(); ++i) {
		int power = p1[i].first;
		Fraction xPowerFraction = { p1[i].second.first, p1[i].second.second };
		for (int j = 0; j < power; ++j) {
			xPowerFraction = multiplyFractions(xPowerFraction,x);
		}
		result = addFractions(result, xPowerFraction);
	}
	return result;
}

void printFraction(Fraction x) {
	cout << x.first;
	if (x.second != 1) {
		cout << "/" << x.second;
	}
}

int main()
{
	vector<pair<int, Fraction>> polynomial1, polynomial2, result;
	pair<vector<pair<int, Fraction>>, vector<pair<int, Fraction>>> quotientRemainder;
	Fraction scalar, x, valueResult;
	int option;

	while (true) {
		displayMenu();
		cout << endl;

		option = chooseOption();
		cout << endl;

		if (option == 11) {
			cout << "Quiting program..." << endl;
			break;
		}

		if (option != 4) {
			inputPolynomial(polynomial1, 'P');
			cout << "P(x) = ";
			displayPolynomial(polynomial1);
		}

		if (option < 4 || option == 7) {
			inputPolynomial(polynomial2, 'Q');
			cout << "Q(x) = ";
			displayPolynomial(polynomial2);
		}

		switch (option) {
		case 1:
			result = addPolynomials(polynomial1, polynomial2);
			cout << "P(x) + Q(x) = ";
			displayPolynomial(result);
			break;
		case 2:
			result = subtractPolynomials(polynomial1, polynomial2);
			cout << "P(x) - Q(x) = ";
			displayPolynomial(result);
			break;
		case 3:
			result = multiplyPolynomials(polynomial1, polynomial2);
			cout << "P(x) * Q(x) = ";
			displayPolynomial(result);
			break;
		case 4:
			inputPolynomial(polynomial1, 'A');
			cout << "A(x) = ";
			displayPolynomial(polynomial1);
			inputPolynomial(polynomial2, 'B');
			cout << "B(x) = ";
			displayPolynomial(polynomial2);
			quotientRemainder = dividePolynomials(polynomial1, polynomial2);
			cout << "Quotient Q(x) = ";
			displayPolynomial(quotientRemainder.first);
			cout << "Remainder R(x) = ";
			displayPolynomial(quotientRemainder.second);
			break;
		case 5:
			scalar = inputRationalNumber();
			result = multiplyPolynomialByScalar(polynomial1, scalar);
			cout << "Result: ";
			displayPolynomial(result);
			break;
		case 6:
			x = inputRationalNumber();
			valueResult = findValue(polynomial1, x);
			cout << "P(";
			printFraction(x);
			cout << ") = ";
			printFraction(valueResult);
			cout << endl << endl;
			break;
		case 7:
			break;
		}
	}
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
