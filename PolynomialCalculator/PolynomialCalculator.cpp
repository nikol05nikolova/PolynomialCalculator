/**
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024 / 2025
*
* @author Nikol Nikolova
* @idnumber 1MI0600495
* @compiler VC
*
* <file with all functions and main>
*
*/

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
typedef vector<pair<int, Fraction>> Polynomial;

void printFraction(Fraction x) {
	cout << x.first;
	if (x.second != 1) {
		cout << "/" << x.second;
	}
}

void normalizeMinus(Fraction& coef) {
	if (coef.second < 0) {
		coef.first *= -1;
		coef.second *= -1;
	}
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

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

int charToInt(char ch) {
	if (!isDigit(ch)) {
		return -1;
	}
	return ch - '0';
}

int StrToInt(char* str, size_t beg, size_t end) {
	if (str == nullptr) {
		return -2;
	}

	int result = 0;
	if (beg > end || end - beg > MAX_LENGTH_INT) {
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
	cout << "11) Find k-th derivative" << endl;
	cout << "12) Quit program" << endl;
}

int chooseOption() {
	int option;
	cout << "Enter your option here>> ";
	cin >> option;

	while (cin.fail() || option < 1 || option > 12) {
		clearInputBuffer();
		cout << "Invalid input! Please choose a number between 1 and 11!" << endl << endl;
		cout << "Enter your option here>> ";
		cin >> option;
	}

	clearInputBuffer();
	return option;
}

int chooseDegree() {
	int degree;
	cout << "Enter degree of your polynomial>> ";
	cin >> degree;

	while (cin.fail() || degree < 0) {
		clearInputBuffer();
		cout << "Invalid input! Please choose a positive number or 0!" << endl << endl;
		cout << "Enter degree of your polynomial>> ";
		cin >> degree;
	}

	clearInputBuffer();
	return degree;
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
	normalizeMinus(result);
	return result;
}

void inputPolynomial(Polynomial& polynomial, char PolynomialName) {
	cout << "Enter Polynomial " << PolynomialName << "(x)" << endl;

	int degree = chooseDegree();
	cout << endl;

	polynomial.clear();
	bool nonZeroFound = false;
	for (int i = degree; i >= 0; --i) {
		char input[MAX_LENGTH_COEFFICIENT];
		cout << "Enter coefficient before x^" << i << ">> ";
		cin >> input;

		int num = numerator(input);
		int den = denominator(input);

		while (num < 0 || den <= 0) {
			cout << "Invalid input! Please choose a rational coefficient!" << endl << endl;
			while (cin.get() != '\n');
			cout << "Enter coefficient before x^" << i << ">> ";
			cin >> input;
			num = numerator(input);
			den = denominator(input);
		}

		if (isNegative(input)) {
			num = (-1) * num;
		}

		Fraction fraction = simplifyFraction(num, den);
		if (num != 0) {
			nonZeroFound = true;
		}
		polynomial.push_back({ i, fraction });
	}

	if (!nonZeroFound) {
		cout << "The polynomial is empty! Please enter at least one non-zero coefficient." << endl << endl;
		inputPolynomial(polynomial, PolynomialName);
	}
}

bool isZeroTerm(const pair<int, Fraction>& p1) {
	return p1.second.first == 0;
}

void removeZeroTerms(Polynomial& p1) {
	p1.erase(remove_if(p1.begin(), p1.end(), isZeroTerm), p1.end());
}


void displayPolynomial(Polynomial polynomial) {
	removeZeroTerms(polynomial);

	if (polynomial.empty()) {
		cout << "0" << endl << endl;
		return;
	}

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
	Fraction f = simplifyFraction(numerator, denominator);
	return f;
}

Fraction subtractFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.second - b.first * a.second;
	int denominator = a.second * b.second;
	Fraction f = simplifyFraction(numerator, denominator);
	return f;
}

Fraction multiplyFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.first;
	int denominator = a.second * b.second;
	Fraction f = simplifyFraction(numerator, denominator);
	return f;
}

Fraction divideFractions(Fraction a, Fraction b) {
	int numerator = a.first * b.second;
	int denominator = a.second * b.first;
	Fraction f = simplifyFraction(numerator, denominator);
	return f;
}

// Addition of two polynomials
Polynomial addPolynomials(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result;
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
Polynomial subtractPolynomials(const Polynomial& p1, const Polynomial& p2) {

	Polynomial result;
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
Polynomial multiplyPolynomials(const Polynomial& p1, const Polynomial& p2) {
	Polynomial result;

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
pair<Polynomial, Polynomial> dividePolynomials(const Polynomial& p1, const Polynomial& p2) {

	Polynomial quotient;
	Polynomial remainder = p1;

	while (!remainder.empty() && remainder[0].first >= p2[0].first) {
		int degreeDiff = remainder[0].first - p2[0].first;
		Fraction leadingCoeffQuotient = divideFractions(remainder[0].second, p2[0].second);

		quotient.push_back(make_pair(degreeDiff, leadingCoeffQuotient));

		Polynomial temp;
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
Polynomial multiplyPolynomialByScalar(const Polynomial& p1, Fraction scalar) {
	Polynomial result = p1;

	for (size_t i = 0; i < p1.size(); ++i) {
		result[i].second = multiplyFractions(p1[i].second, scalar);
	}
	return result;
}

Fraction inputRationalNumber() {
	char input[MAX_LENGTH_COEFFICIENT];
	cout << "Enter rational number>> ";
	cin >> input;

	int num = numerator(input);
	int den = denominator(input);

	while (num < 0 || den <= 0) {
		cout << "Invalid input! Please choose a rational number!" << endl << endl;
		while (cin.get() != '\n');
		cout << "Enter rational number>> ";
		cin >> input;
		num = numerator(input);
		den = denominator(input);
	}

	if (isNegative(input)) {
		num = (-1) * num;
	}

	return simplifyFraction(num, den);
}

// Find value of polinomial at a given number
Fraction findValue(const Polynomial& p1, Fraction x) {
	Fraction result = { 0, 1 };
	for (size_t i = 0; i < p1.size(); ++i) {
		int power = p1[i].first;
		Fraction xPowerFraction = { p1[i].second.first, p1[i].second.second };
		for (int j = 0; j < power; ++j) {
			xPowerFraction = multiplyFractions(xPowerFraction, x);
		}
		result = addFractions(result, xPowerFraction);
	}
	return result;
}

void swapPolynomials(Polynomial& p1, Polynomial& p2) {
	Polynomial temp;
	temp = p1;
	p1 = p2;
	p2 = temp;
}

void normalize(Polynomial& p1) {
	removeZeroTerms(p1);
	if (!p1.empty()) {
		Fraction leadingCoeff = p1[0].second;
		for (size_t i = 0; i < p1.size(); i++)
		{
			p1[i].second = divideFractions(p1[i].second, leadingCoeff);
		}
	}
}

// Find GCD of two polynomials
Polynomial gcdPolynomials(const Polynomial& p1, const Polynomial& p2) {
	Polynomial poly1 = p1;
	Polynomial poly2 = p2;

	if (poly1.size() == 1 && poly1[0].first == 0
		&& poly2.size() == 1 && poly2[0].first == 0) {

		if (poly1[0].second.second == 1 && poly2[0].second.second == 1) {
			poly1[0].second.first = gcdNumbers(poly1[0].second.first, poly2[0].second.first);
			return poly1;
		}
		poly1[0].second.first = 0;
		return poly1;
	}

	if (poly1.size() < poly2.size()) {
		swapPolynomials(poly1, poly2);
	}

	pair<Polynomial, Polynomial> quotientRemainder;
	while (!poly2.empty()) {
		quotientRemainder = dividePolynomials(poly1, poly2);
		poly1 = poly2;
		poly2 = quotientRemainder.second;
	}

	normalize(poly1);

	return poly1;
}

//Vieta's formulas for given polynomial
vector<Fraction> vietasFormulas(const Polynomial& p1) {
	vector<Fraction> viet;

	int degree = p1[0].first;
	Fraction leadingCoefficient = p1[0].second;

	for (int i = 1; i < p1.size(); i++) {
		Fraction sigma = divideFractions(p1[i].second, leadingCoefficient);

		if (i % 2 != 0) {
			sigma.first *= -1;
		}

		viet.push_back(sigma);
	}
	return viet;
}

//Display Vieta's formulas
void displayVietasFormulas(const Polynomial& p1) {
	vector<Fraction> viet;

	cout << "Vieta's Formulas for this polynomial:" << endl;
	viet = vietasFormulas(p1);
	for (size_t i = 0; i < viet.size(); i++) {
		cout << "Sigma" << i + 1 << " = ";
		printFraction(viet[i]);
		cout << endl;
	}
	cout << endl;
}

int inputK() {
	int k;
	cout << "Enter a number k >> ";
	cin >> k;

	while (cin.fail() || k < 1) {
		clearInputBuffer();
		cout << "Invalid input! Please choose a positive number!" << endl << endl;
		cout << "Enter degree of your polynomial>> ";
		cin >> k;
	}
	clearInputBuffer();
	return k;
}


Polynomial Derivative(const Polynomial& p1) {
	Polynomial result;
	result.resize(p1.size());

	for (size_t i = 0; i < p1.size(); i++) {
		int degree = p1[i].first;
		if (degree == 0) {
			break;
		}
		result[i].first = degree - 1;
		result[i].second = p1[i].second;
		result[i].second.first *= degree;
		result[i].second = simplifyFraction(result[i].second.first, result[i].second.second);
	}

	return result;
}

//Find kth derivative
Polynomial kthDerivative(const Polynomial& p1, int k) {
	Polynomial result = Derivative(p1);
	for (size_t i = 1; i < k; i++) {
		result = Derivative(result);
	}
	return result;
}

//Find dividers of a number
vector<int> dividers(int a) {
	vector<int> result;

	int abs_a = abs(a);
	for (int i = 1; i <= abs_a; ++i) {
		if (a % i == 0) {
			result.push_back(i);
			result.push_back(i * (-1));
		}
	}

	return result;
}

//Bring to a common denumerator
vector<pair<int, int>> commonDenumerator(const Polynomial& p1) {
	vector<pair<int, int>> result;
	result.resize(p1.size());

	int comDen = p1[0].second.second;
	int gcd = 1;
	int commonGcd = p1[0].second.second;

	for (size_t i = 1; i < p1.size(); i++) {
		int den = p1[i].second.second;
		commonGcd = gcdNumbers(commonGcd, den);
		gcd = gcdNumbers(comDen, den);
		comDen *= den / gcd;
	}

	for (size_t i = 0; i < p1.size(); i++) {
		result[i].first = p1[i].first;
		result[i].second = p1[i].second.first * comDen / commonGcd / p1[i].second.second;
	}
	return result;
}

//Find posible roots of polynomial(Horner first and last coefficient)
vector<Fraction> posibleRoots(const Polynomial& p1) {
	vector<Fraction> posibRoots;
	vector<pair<int, int>> comDenPoly = commonDenumerator(p1);
	int first = comDenPoly[0].second;
	int last = comDenPoly[comDenPoly.size() - 1].second;

	vector<int> dividersFirst = dividers(first);
	vector<int> dividersLast = dividers(last);

	for (size_t i = 0; i < dividersFirst.size(); i++)
	{
		for (size_t j = 0; j < dividersLast.size(); j++)
		{
			Fraction root = simplifyFraction(dividersLast[j], dividersFirst[i]);
			bool found = false;
			for (size_t k = 0; k < posibRoots.size(); k++)
			{
				if (posibRoots[k] == root)
				{
					found = true;
				}
			}
			if (!found)
			{
				posibRoots.push_back(root);
			}
		}
	}
	return posibRoots;
}

//Find rational roots of polynomial
Polynomial rationalRoots(const Polynomial& p1) {
	vector<Fraction> posibRoots = posibleRoots(p1);
	Polynomial ratRoots;

	for (size_t i = 0; i < posibRoots.size(); i++) {
		if (findValue(p1, posibRoots[i]).first == 0) {
			int k = 1;
			Polynomial divider, poly;
			divider.resize(2);
			divider[0] = { 1, {1,1} };
			divider[1] = { 0, posibRoots[i] };
			divider[1].second.first *= -1;
			poly = dividePolynomials(p1, divider).first;
			while (findValue(poly, posibRoots[i]).first == 0) {
				k++;
				poly = dividePolynomials(poly, divider).first;
			}
			
			ratRoots.push_back({ k, posibRoots[i] });
		}
	}

	return ratRoots;
}

void displayRationalRoots(const Polynomial& p1) {
	Polynomial ratRoots = rationalRoots(p1);

	if (ratRoots.empty()) {
		cout << "No rational roots" << endl << endl;
		return;
	}

	for (size_t i = 0; i < ratRoots.size(); i++) {
		ratRoots[i].second.first *= -1;
		cout << "(x";
		if (ratRoots[i].second.first > 0)
		{
			cout << "+";
		}
		printFraction(ratRoots[i].second);
		cout << ")";
		int k = ratRoots[i].first;
		if (ratRoots[i].first > 1)
		{
			cout << "^"<< ratRoots[i].first;
		}
	}
	cout << "=0" << endl << endl;

	cout << "RATIONAL ROOTS:" << endl;
	for (size_t i = 0; i < ratRoots.size(); i++) {
		cout << "x = ";
		printFraction(ratRoots[i].second);
		cout << " -> " << ratRoots[i].first << "-fold root" << endl;
	}
	cout << endl;
}

int main()
{
	Polynomial polynomial1, polynomial2, result;
	pair<Polynomial, Polynomial> quotientRemainder;
	Fraction scalar, x, valueResult;
	int k;

	int option;

	while (true) {
		displayMenu();
		cout << endl;

		option = chooseOption();
		cout << endl;

		if (option == 12) {
			cout << "Exiting program..." << endl;
			break;
		}

		if (option != 4) {
			inputPolynomial(polynomial1, 'P');
			if (option != 8)
			{
				removeZeroTerms(polynomial1);
			}
			cout << "P(x) = ";
			displayPolynomial(polynomial1);
		}

		if (option < 4 || option == 7) {
			inputPolynomial(polynomial2, 'Q');
			removeZeroTerms(polynomial2);
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
			removeZeroTerms(polynomial1);
			cout << "A(x) = ";
			displayPolynomial(polynomial1);
			inputPolynomial(polynomial2, 'B');
			removeZeroTerms(polynomial2);
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
			result = gcdPolynomials(polynomial1, polynomial2);
			if (!(result.size() == 1 && result[0].second.first == 0)) {
				cout << "gcd(P(x), Q(x)) = ";
				displayPolynomial(result);
			}
			else {
				cout << "There isn't GCD!" << endl << endl;
			}
			break;
		case 8:
			if (polynomial1[0].first == 0) {
				cout << "There aren't Vieta's Formulas!" << endl << endl;
				break;
			}
			displayVietasFormulas(polynomial1);
			break;
		case 9:
			cout << "Undergoing development process!!!";
			break;
		case 10:
			displayRationalRoots(polynomial1);
			break;
		case 11:
			k = inputK();
			result = kthDerivative(polynomial1, k);
			cout << k << "-th derivative is: ";
			displayPolynomial(result);
			break;
		}
	}
}
