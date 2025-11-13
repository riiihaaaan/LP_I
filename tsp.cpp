#include <iostream>
using namespace std;

#define INF 999
#define MAX 10

int n;
int cost[MAX][MAX];
int bestCost = INF;
int bestPath[MAX+1];

void copyPath(int path[]) {
    for(int i = 0; i < n; i++)
        bestPath[i] = path[i];
    bestPath[n] = path[0];
}

// Performs Row + Column Reduction and returns the reduction cost
int reduceMatrix(int mat[MAX][MAX]) {
    int reduction = 0;

    // Row reduction
    for(int i = 0; i < n; i++) {
        int rowMin = INF;
        for(int j = 0; j < n; j++)
            rowMin = min(rowMin, mat[i][j]);

        if(rowMin != INF && rowMin > 0) {
            reduction += rowMin;
            for(int j = 0; j < n; j++)
                mat[i][j] -= rowMin;
        }
    }

    // Column reduction
    for(int j = 0; j < n; j++) {
        int colMin = INF;
        for(int i = 0; i < n; i++)
            colMin = min(colMin, mat[i][j]);

        if(colMin != INF && colMin > 0) {
            reduction += colMin;
            for(int i = 0; i < n; i++)
                mat[i][j] -= colMin;
        }
    }

    return reduction;
}

// Branch & Bound Recursive Search (LC Method)
void LC_TSP(int currentCity, int count, int currentCost, int path[], bool visited[]) {
    if(count == n) { // all cities visited
        if(cost[currentCity][path[0]] != INF) {
            int totalCost = currentCost + cost[currentCity][path[0]];
            if(totalCost < bestCost) {
                bestCost = totalCost;
                copyPath(path);
            }
        }
        return;
    }

    for(int next = 0; next < n; next++) {
        if(!visited[next] && cost[currentCity][next] != INF) {

            visited[next] = true;
            path[count] = next;

            LC_TSP(next, count + 1, currentCost + cost[currentCity][next], path, visited);

            visited[next] = false;
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter cost matrix (use 0 for same city or no direct path):\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if(i == j) cost[i][j] = INF;     // self edge = Infinity
            else if(cost[i][j] == 0) cost[i][j] = INF; // no path = Infinity
        }
    }

    // Apply initial row + column reduction
    int reducedCost = reduceMatrix(cost);
    cout << "\nInitial Reduction Cost (Lower Bound) = " << reducedCost << endl;

    int path[MAX];
    bool visited[MAX] = {false};

    visited[0] = true;
    path[0] = 0;

    LC_TSP(0, 1, 0, path, visited);

    cout << "\nOptimal Path: ";
    for(int i = 0; i <= n; i++)
        cout << bestPath[i] + 1 << " ";

    cout << "\nMinimum Cost = " << bestCost << endl;

    return 0;
}