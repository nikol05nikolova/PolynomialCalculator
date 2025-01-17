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
			cout << "Invalid input! Please choose an integer that isn't negative!" << endl << endl;
		}
		else {
			cout << "Invalid option! Please choose an integer that isn't negative!" << endl << endl;
		}
		cout << "Enter degree of your polynomial>> ";
		cin >> degree;
	}
	return degree;
}

void inputPolynomial(vector<pair<int, double>>& polynomial, char PolynomialName) {
	cout << "Enter Polynomial " << PolynomialName << "(x)" << endl;

	int degree = chooseDegree();
	cout << endl;

	polynomial.clear();
	for (int i = degree; i >= 0; --i) {
		double coefficient;
		cout << "Enter coefficient before x^" << i << ">> ";
		cin >> coefficient;
		if (coefficient != 0) {
			polynomial.push_back({ i, coefficient });
		}
	}
}

void displayPolynomial(const vector<pair<int, double>> polynomial, char PolynomialName) {
	cout << PolynomialName << "(x) = ";
	for (size_t i = 0; i < polynomial.size(); ++i) {
		if (i != 0 && polynomial[i].second > 0) {
			cout << "+";
		}
		cout << polynomial[i].second;
		if (polynomial[i].first != 0) {
			cout << "x^" << polynomial[i].first;
		}
	}
	cout << endl;
}

int main()
{
	vector<pair<int, double>> polynomial1, polynomial2, result;
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
