// PolynomialCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

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
    cout << "11) Quit program" << endl << endl;
}

int chooseOption() {
    int option;
    cout << "Enter your option here>> ";
    cin >> option;

    while (option < 1 || option > 11)
    {
        cout << "Invalid option! Please choose a number between 1 and 11!" << endl << endl;
        cout << "Enter your option here>> ";
        cin >> option;
    }

    cout << endl << endl;

    return option;
}

int main()
{
    displayMenu();
    int option = chooseOption();

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
