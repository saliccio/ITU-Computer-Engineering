// Author: Yunus Karatepe
// Some of the code is copied from https://www.geeksforgeeks.org/. 
// Code is updated according to recitation 8 slides.
// solution for 0-1 Knapsack problem
#include <bits/stdc++.h>
using namespace std;
 
// A utility function that returns
// maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
 
// Returns the maximum value that
// can be put in a knapsack of capacity W
vector<vector<int>> knapSack(int W, int weights[], int values[], int n)
{
    int i, w;
    vector<vector<int>> M(n + 1, vector<int>(W + 1));

    for (w = 0; w <= W; w++) 
        M[0][w] = 0;
 
    // Build table M[][] in bottom up manner
    for (i = 1; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (weights[i - 1] <= w)
                M[i][w] = max(M[i - 1][w], values[i - 1] + M[i - 1][w - weights[i - 1]]);
            else
                M[i][w] = M[i - 1][w];
        }
    }
    return M;
}

void printSolution(vector<vector<int>> M, int W, int n, int weights[], int values[]) {
    int i = n;
    int k = W;
    int sum = 0;
    while (i > 0 && k > 0){
        if (M[i][k] != M[i - 1][k]) {
            cout << "Item: " << i << "  Value: " << values[i - 1] << "\n";
            sum = sum + values[i - 1];
            k = k - weights[i - 1];
        }
        i = i - 1;
    }
    cout << "Total value: " << sum;
}
 
// Driver Code
int main()
{
    int profits[] = { 6, 5, 10, 4, 10 };
    int weights[] = { 2, 3, 5, 4, 5 };
    int W = 10;
    int n = sizeof(profits) / sizeof(profits[0]);

    vector<vector<int>> M = knapSack(W, weights, profits, n);
    printSolution(M, W, n, weights, profits);

    return 0;
}