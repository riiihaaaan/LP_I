#include <iostream>
using namespace std;

int main() {
    int n; // number of items
    cout << "Enter number of items: ";
    cin >> n;

    int value[n], weight[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter value and weight of item " << i + 1 << ": ";
        cin >> value[i] >> weight[i];
    }

    int W; // capacity of knapsack
    cout << "Enter capacity of knapsack: ";
    cin >> W;

    // Create DP table
    int dp[n + 1][W + 1];

    // Initialize table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i - 1] <= w)
                dp[i][w] = max(value[i - 1] + dp[i - 1][w - weight[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    cout << "Maximum value in Knapsack (0/1): " << dp[n][W] << endl;

    return 0;
}