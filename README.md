# Stock Trading System Simulation

## Overview
This C++ application simulates a stock trading system where multiple traders can buy and sell stocks. The system maintains an order book and matches buy/sell orders in a multi-threaded environment. This project demonstrates the use of object-oriented design, design patterns, multithreading, and STL in C++.

## Features
- Object-oriented design principles applied to entities like Trader, Stock, and OrderBook.
- Utilizes the Factory Method pattern for creating orders of different types (Market Order, Limit Order).
- Implements the Strategy Pattern for matching algorithms.
- Leverages STL containers for efficient data management.
- Multithreaded implementation to simulate multiple traders sending buy/sell orders concurrently.

## Components
### Trader
- Represents a trader participating in the stock trading system.
- Created with an ID, name, and initial balance.
- Can place market and limit orders to buy or sell stocks.

### Order
- Represents an order to buy or sell stocks.
- Contains information such as stock symbol, order type, quantity, and price.

### OrderBook
- Maintains an order book and matches buy/sell orders.
- Uses multithreading to handle orders from multiple traders concurrently.
- Implements market and limit order execution logic.

## Design Patterns
- Factory Method Pattern: Used to create different types of orders (Market and Limit orders).
- Observer Pattern: Traders observe the OrderBook to receive updates.
- Strategy Pattern: Allows flexible matching algorithms for orders.

## Usage
1. Compile the project using a C++ compiler.
2. Run the compiled binary.
3. The application simulates traders placing orders and matching them in a multi-threaded environment.
4. View the console output to see the trading simulation in action.

## Performance Evaluation
- Evaluate the efficiency and performance of the multi-threaded order matching system.
- Measure how the system handles a high number of concurrent orders.
- Analyze the impact on the order book's performance under different scenarios.

