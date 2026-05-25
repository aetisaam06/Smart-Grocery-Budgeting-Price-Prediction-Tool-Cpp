#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>   

using namespace std;

const int MAX_ITEMS = 50;

// Function prototypes
void inputItems(string names[], int qty[], double price[], int& itemCount);
void calculateCosts(const int itemCount,
    const int qty[], const double price[],
    double currentCost[], double predictedPrice[],
    double predictedCost[],
    double inflationRate,
    double& totalCurrent, double& totalPredicted,
    double& avgUnitPrice);
void showReport(const int itemCount,
    const string names[], const int qty[],
    const double price[], const double currentCost[],
    const double predictedPrice[], const double predictedCost[],
    double totalCurrent, double totalPredicted,
    double monthlyBudget, double avgUnitPrice,
    double inflationRate);

void showInflationTrend(double totalCurrent, double inflationRate, int monthsToShow);

int main() {
    cout << fixed << setprecision(2); // format all money values to 2 decimal places

    double monthlyBudget;
    int itemCount = 0;

    string itemNames[MAX_ITEMS];
    int itemQty[MAX_ITEMS];
    double itemPrice[MAX_ITEMS];
    double currentCost[MAX_ITEMS];
    double predictedPrice[MAX_ITEMS];
    double predictedCost[MAX_ITEMS];

    double inflationPercent;
    double inflationRate;
    double totalCurrentCost = 0.0;
    double totalPredictedCost = 0.0;
    double avgUnitPrice = 0.0;

    cout << "=============================================\n";
    cout << "  Smart Grocery Budgeting & Price Predictor\n";
    cout << "=============================================\n\n";

    // 1. Ask for monthly budget
    cout << "Enter your monthly grocery budget: ";
    cin >> monthlyBudget;

    // 2. Input items
    inputItems(itemNames, itemQty, itemPrice, itemCount);

    if (itemCount == 0) {
        cout << "\nNo items entered. Exiting program.\n";
        return 0;
    }

    // 3. Input expected inflation percentage
    cout << "\nEnter expected percentage increase for next month (e.g., 5 for 5%): ";
    cin >> inflationPercent;
    inflationRate = inflationPercent / 100.0;

    // 4. Calculate costs
    calculateCosts(itemCount,
        itemQty, itemPrice,
        currentCost, predictedPrice, predictedCost,
        inflationRate,
        totalCurrentCost, totalPredictedCost,
        avgUnitPrice);

    // 5. Show full report
    showReport(itemCount,
        itemNames, itemQty,
        itemPrice, currentCost,
        predictedPrice, predictedCost,
        totalCurrentCost, totalPredictedCost,
        monthlyBudget, avgUnitPrice,
        inflationRate);

    cout << "\nThank you for using the Smart Grocery Budgeting Tool. Goodbye!\n";

    return 0;
}

// ---------------------- Function Definitions -------------------------

// Input items from user
void inputItems(string names[], int qty[], double price[], int& itemCount) {
    cout << "How many different grocery items do you want to enter? ";
    cin >> itemCount;

    if (itemCount < 0) {
        itemCount = 0;
    }

    if (itemCount > MAX_ITEMS) {
        cout << "You entered more than " << MAX_ITEMS
            << " items. Limiting to " << MAX_ITEMS << ".\n";
        itemCount = MAX_ITEMS;
    }

    cout << "\n--- Enter item details ---\n";
    for (int i = 0; i < itemCount; i++) {
        cout << "\nItem " << (i + 1) << " name: ";
        cin >> ws; // clear any whitespace
        getline(cin, names[i]);

        cout << "Monthly quantity used for \"" << names[i] << "\": ";
        cin >> qty[i];

        cout << "Current price per unit for \"" << names[i] << "\": ";
        cin >> price[i];

        if (qty[i] < 0) qty[i] = 0;
        if (price[i] < 0) price[i] = 0.0;
    }
}

// Calculate current and predicted costs and averages
void calculateCosts(const int itemCount,
    const int qty[], const double price[],
    double currentCost[], double predictedPrice[],
    double predictedCost[],
    double inflationRate,
    double& totalCurrent, double& totalPredicted,
    double& avgUnitPrice) {
    totalCurrent = 0.0;
    totalPredicted = 0.0;
    double sumUnitPrices = 0.0;

    for (int i = 0; i < itemCount; i++) {
        currentCost[i] = qty[i] * price[i];
        predictedPrice[i] = price[i] * (1.0 + inflationRate);
        predictedCost[i] = qty[i] * predictedPrice[i];

        totalCurrent += currentCost[i];
        totalPredicted += predictedCost[i];
        sumUnitPrices += price[i];
    }

    if (itemCount > 0) {
        avgUnitPrice = sumUnitPrices / itemCount;
    }
    else {
        avgUnitPrice = 0.0;
    }
}

// Show full report including suggestions and inflation trend
void showReport(const int itemCount,
    const string names[], const int qty[],
    const double price[], const double currentCost[],
    const double predictedPrice[], const double predictedCost[],
    double totalCurrent, double totalPredicted,
    double monthlyBudget, double avgUnitPrice,
    double inflationRate) {
    cout << "\n=============================================\n";
    cout << "                GROCERY REPORT               \n";
    cout << "=============================================\n";

    cout << "\nItems summary:\n";
    cout << left << setw(3) << "#"
        << setw(18) << "Item"
        << right << setw(8) << "Qty"
        << setw(12) << "Cur Price"
        << setw(12) << "Cur Cost"
        << setw(14) << "Next Price"
        << setw(14) << "Next Cost"
        << "\n";

    cout << string(73, '-') << "\n";

    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(3) << (i + 1)
            << setw(18) << names[i]
            << right << setw(8) << qty[i]
            << setw(12) << price[i]
            << setw(12) << currentCost[i]
            << setw(14) << predictedPrice[i]
            << setw(14) << predictedCost[i]
            << "\n";
    }

    cout << string(73, '-') << "\n";
    cout << setw(41) << "Total current cost:" << setw(12) << totalCurrent << "\n";
    cout << setw(41) << "Total predicted cost:" << setw(12) << totalPredicted << "\n";

    cout << "\nYour monthly budget: " << monthlyBudget << "\n";

    if (totalPredicted <= monthlyBudget) {
        double remaining = monthlyBudget - totalPredicted;
        cout << "Good news! Your predicted grocery cost is within budget.\n";
        cout << "You may have approximately " << remaining
            << " left after groceries next month.\n";
    }
    else {
        double over = totalPredicted - monthlyBudget;
        cout << "Warning: Your predicted grocery cost is above your budget.\n";
        cout << "You need to save about " << over
            << " or cut down on some items.\n";
    }

    // Suggestions for cheaper alternatives
    cout << "\n---------------------------------------------\n";
    cout << "Items to consider for cheaper alternatives:\n";
    cout << "Average unit price across all items: " << avgUnitPrice << "\n";

    bool anyExpensive = false;
    for (int i = 0; i < itemCount; i++) {
        if (price[i] > avgUnitPrice) {
            anyExpensive = true;
            double targetPrice = price[i] * 0.90; // 10% cheaper target
            cout << "\n* " << names[i] << ":\n";
            cout << "  Current unit price: " << price[i] << "\n";
            cout << "  Suggested target price (10% lower): " << targetPrice << "\n";
            cout << "  Tip: Look for store brands, discounts, or cheaper alternatives.\n";
        }
    }

    if (!anyExpensive) {
        cout << "\nYour items are fairly priced compared to each other.\n";
    }

    // Inflation trend
    cout << "\n---------------------------------------------\n";
    cout << "Inflation trend (assuming same percentage continues):\n";
    showInflationTrend(totalCurrent, inflationRate, 3);
}

// Show predicted total cost for next few months
void showInflationTrend(double totalCurrent, double inflationRate, int monthsToShow) {
    cout << left << setw(10) << "Month" << setw(20) << "Predicted Total Cost\n";
    cout << string(30, '-') << "\n";

    for (int m = 1; m <= monthsToShow; m++) {
        double factor = pow(1.0 + inflationRate, m);
        double predictedTotal = totalCurrent * factor;
        cout << left << setw(10) << m << setw(20) << predictedTotal << "\n";
    }
}
