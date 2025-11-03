#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure for storing relief item information
struct ReliefItem {
    string itemName;
    double weight;
    double value;
    bool isDivisible; // true if can take fractional amount
};

// Function to calculate optimal loading using fractional knapsack
void optimizeLoading(vector<ReliefItem>& cargo, double maxWeight) {
    // Sort by value-to-weight ratio (descending)
    sort(cargo.begin(), cargo.end(),
         [](const ReliefItem& a, const ReliefItem& b) {
             return (a.value / a.weight) > (b.value / b.weight);
         });

    double currentLoad = 0.0;
    double totalValue = 0.0;

    cout << "\n=== Relief Cargo Optimization Summary ===\n";
    cout << left << setw(15) << "Item"
         << setw(12) << "Weight(kg)"
         << setw(12) << "Value"
         << setw(12) << "Taken(kg)" << endl;
    cout << "------------------------------------------------------\n";

    for (auto& item : cargo) {
        if (currentLoad >= maxWeight)
            break; // Boat full

        if (currentLoad + item.weight <= maxWeight) {
            // Take the full item
            currentLoad += item.weight;
            totalValue += item.value;
            cout << left << setw(15) << item.itemName
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << item.weight << endl;
        } 
        else if (item.isDivisible) {
            // Take fraction of item
            double remaining = maxWeight - currentLoad;
            double fraction = remaining / item.weight;
            totalValue += item.value * fraction;
            currentLoad += remaining;

            cout << left << setw(15) << item.itemName
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << fixed << setprecision(2) << remaining << endl;
        }
        // skip if indivisible and too heavy
    }

    cout << "------------------------------------------------------\n";
    cout << "Total Weight Loaded: " << fixed << setprecision(2) << currentLoad << " kg\n";
    cout << "Total Utility Value: " << fixed << setprecision(2) << totalValue << "\n";
}

int main() {
    int count;
    double capacity;

    cout << "Enter total number of relief items: ";
    cin >> count;

    vector<ReliefItem> cargo(count);

    for (int i = 0; i < count; ++i) {
        cout << "\nEnter details for item " << i + 1 << ":\n";
        cout << "Name: ";
        cin >> cargo[i].itemName;
        cout << "Weight (kg): ";
        cin >> cargo[i].weight;
        cout << "Utility Value: ";
        cin >> cargo[i].value;
        cout << "Divisible (1 = Yes, 0 = No): ";
        cin >> cargo[i].isDivisible;
    }

    cout << "\nEnter total weight capacity of the boat (kg): ";
    cin >> capacity;

    optimizeLoading(cargo, capacity);

    return 0;
}
