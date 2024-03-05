// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "date.h"
#include <iostream>

int main() {
    date d1(29, 2, 2021); // Create a date: December 25, 2021
    date d2(29, 2, 2024);   // Create another date: January 1, 2022

    // Check if dates are valid
    std::cout << "Date d1 is " << (d1.valid() ? "valid" : "invalid") << std::endl;
    std::cout << "Date d2 is " << (d2.valid() ? "valid" : "invalid") << std::endl;

    // Compare dates
    if (d1 < d2) {
        std::cout << "d1 is before d2." << std::endl;
    }
    else {
        std::cout << "d1 is after d2." << std::endl;
    }

    // Increment d1 (postfix)
    date d1Tomorrow = d1++;
    std::cout << "d1 (after increment): " << d1.day() << "/" << d1.month() << "/" << d1.year() << std::endl;
    std::cout << "d1Tomorrow: " << d1Tomorrow.day() << "/" << d1Tomorrow.month() << "/" << d1Tomorrow.year() << std::endl;

    // Decrement d2 (prefix)
    date d2Yesterday = --d2;
    std::cout << "d2 (after decrement): " << d2.day() << "/" << d2.month() << "/" << d2.year() << std::endl;
    std::cout << "d2Yesterday: " << d2Yesterday.day() << "/" << d2Yesterday.month() << "/" << d2Yesterday.year() << std::endl;

    return 0;
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
