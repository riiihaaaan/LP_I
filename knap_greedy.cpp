#include <iostream>
#include <algorithm>   // for sort()
using namespace std;

// Structure to store item details
struct Item {
    int value;
    int weight;
};

// Function to compare value/weight ratios of two items
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2; // sort in descending order
}

int main() {
    int n; // number of items
    cout << "Enter number of items: ";
    cin >> n;

    Item arr[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> arr[i].value >> arr[i].weight;
    }

    int W; // capacity of knapsack
    cout << "Enter capacity of knapsack: ";
    cin >> W;

    // Sort items by ratio of value/weight
    sort(arr, arr + n, compare);

    double totalValue = 0.0; // final value in knapsack

    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= W) {
            // Take full item
            W -= arr[i].weight;
            totalValue += arr[i].value;
        } else {
            // Take fractional part of the item
            totalValue += arr[i].value * ((double)W / arr[i].weight);
            break; // bag is full now
        }
    }

    cout << "Maximum value in Knapsack (Fractional): " << totalValue << endl;

    return 0;
}