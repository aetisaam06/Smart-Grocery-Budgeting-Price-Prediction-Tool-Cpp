# Smart Grocery Budgeting & Price Prediction Tool

A C++ console-based Programming Fundamentals project that helps users manage grocery expenses, compare spending with a monthly budget, and predict future costs using a simple inflation-based model.

## Project Overview

The Smart Grocery Budgeting & Price Prediction Tool is designed to help students and beginners manage their monthly grocery budget more effectively. The system takes user input such as monthly budget, grocery item names, quantities, current prices, and expected inflation percentage.

Based on this information, the program calculates current grocery expenses, predicts next month’s grocery cost, compares the predicted cost with the user’s monthly budget, identifies expensive items, and displays a simple inflation trend for the next few months.

This project connects basic programming concepts with a real-life problem and shows how C++ can be used to build a simple, useful, and educational budgeting tool.

## Features

- Monthly grocery budget input
- Grocery item name, quantity, and price input
- Current total grocery cost calculation
- Predicted future cost calculation using inflation rate
- Budget comparison
- Expensive item detection
- Suggestions for cheaper alternatives
- Inflation trend for the next 3 months
- Neat grocery report output
- Offline console-based system

## Technologies Used

- C++
- Console Input/Output
- Arrays
- Loops
- Functions
- Conditional Statements
- Basic Mathematical Modeling
- Flowchart Design
- Microsoft Word for documentation

## Programming Concepts Applied

This project demonstrates important Programming Fundamentals concepts, including:

- Variables and constants
- Arrays for storing grocery item data
- Loops for processing multiple items
- Functions for modular program design
- Conditional statements for budget comparison
- Arithmetic calculations for cost prediction
- Formatted console output

## Project Workflow

The system follows these major steps:

1. Start the program
2. Display welcome message
3. Take monthly grocery budget from the user
4. Take number of grocery items
5. Take item name, quantity, and price for each item
6. Take expected inflation percentage
7. Calculate current cost of each item
8. Predict next month’s price and cost
9. Calculate total current and predicted grocery cost
10. Compare predicted cost with monthly budget
11. Identify expensive items
12. Suggest cheaper alternatives
13. Display inflation trend for the next 3 months
14. End the program

## Mathematical Model

The project uses a simple inflation-based formula:

```cpp
predictedPrice = currentPrice * (1 + inflationRate);
predictedCost = quantity * predictedPrice;
