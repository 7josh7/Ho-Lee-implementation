# README for Black-Scholes Option Pricing Model Implementation

## Overview

This repository hosts a GUI-based application for the Black-Scholes model, essential for pricing European-style options. This implementation allows users to compute the fair values of call and put options using a user-friendly interface that simplifies entering necessary financial parameters such as stock prices, strike prices, volatility, and maturity dates. It also integrates the Nelson-Siegel model parameters to model the term structure of interest rates, enhancing the robustness and accuracy of the pricing model.

## Files

This application is structured as follows:

- **`main.cpp`**: The primary entry of the application, setting up the GUI and handling user interactions.
- **`BlackScholes.h`**: Header file that defines the `BlackScholes`, `CallOption`, and `PutOption` classes essential for option pricing.
- **`date.h` & `date.cpp`**: Manages date inputs, performs date calculations, and supports various day count conventions.
- **`term_structure.h`**: Includes the implementation of the Nelson-Siegel parameters and related interest rate calculations.

## Dependencies

To provide a graphical user interface, this application relies on:

- **Nana C++ Library**: A modern C++ GUI library for building cross-platform graphical applications. It offers simplicity and high performance.
- **Standard C++ Libraries**: Including `<iostream>`, `<sstream>`, `<vector>`, `<string>` for handling input/output operations, string manipulation, and vector data structures.

## Installation and Setup

To run this application, follow these steps to set up your environment:

1. **Install the Nana C++ Library**: Obtain the library from its [official repository on GitHub](https://github.com/cnjinhao/nana). Follow the installation instructions specific to your operating system and development environment.
2. **Compile the Application**: Use a C++ compiler that supports C++14 or later. It's recommended to use an IDE like Microsoft Visual Studio or a similar tool that simplifies C++ development and Nana library integration.

## Usage Instructions

After launching the application, the interface allows you to:

1. **Input Financial Parameters**: Fill in fields for stock price, strike price, volatility, dividend yield, and Nelson-Siegel parameters to model the risk-free interest rate curve dynamically.
2. **Specify Dates**: Enter the starting and expiration dates for the option in the YYYY/MM/DD format.
3. **Choose Day Count Convention**: Select from predefined conventions which affect how interest accrues over time.
4. **Compute Option Prices**: Click the "Calculate Prices" button to display the results, including both call and put option prices and their Greeks (Delta, Gamma, Vega, Theta, and Rho).

Results are displayed in a message box, showing detailed calculations based on user inputs and the integrated pricing models.

## Key Classes and Methods

- **`date Class`**: Handles date validation, conversion, and calculation of time intervals using different day count conventions.
- **`BlackScholes` and its derivatives `CallOption` and `PutOption`**: Perform the calculations using the Black-Scholes formula, adjusted dynamically based on the specified interest rate model.

## Notes

- The application includes error handling to alert users about invalid dates and other input-related issues, ensuring reliable operation.
- Designed for intuitive operation, the GUI caters to users with varying levels of expertise in financial modeling or programming.

## License

This project is released under the MIT License, allowing free use, modification, and distribution.

## Disclaimer

This software is for educational and informational purposes only. It is not intended for making actual trading or investment decisions. Always consult with a qualified financial advisor before making investment decisions.
