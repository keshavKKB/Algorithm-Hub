#include<bits/stdc++.h>
using namespace std;
// Dynamic programming 
// using recursively
int solveRecursively(vector<int>& v, int n, int i, int j) {
    if(i+1 == j) {
        return 0;
    }
    int minAns = INT_MAX;
    for(int k=i+1; k<j; k++) { 
        minAns = min(minAns, v[i]*v[j]*v[k] + solveRecursively(v, n, i, k) + 
                    solveRecursively(v, n, k, j));
    }
    return minAns;

    // Time complexity = Exponential Time complexity O(n!)
    // Space complexity = Exponentioal time complexity (gives TLE).
}

// using the Memoisation approach for space optimisation(top-down Approach)
int MemoisationApproach( vector<int>& v, int n, int i, int j, vector<vector<int>>& dp) {
    if(i+1 == j) {
        return 0;
    }
    if(dp[i][j] != -1) {    // store dp if already called.
        return dp[i][j];
    }
    int minAns = INT_MAX;
    for(int k=i+1; k<j; k++) { 
        minAns = min(minAns, v[i]*v[j]*v[k] + MemoisationApproach(v, n, i, k, dp) + 
                    MemoisationApproach(v, n, k, j, dp));
    }
    dp[i][j] = minAns;      // store in dp vector.
    return dp[i][j];

    // Time complexity = O(number of states × work per state)=O(n*2 × n)=O(n*3)
    // Auxiliary space = O(N*2)(dp) + O(N)(recursive depth ) = O(n*2)
}

// using Tabulation approach for Optimised space(bottom-up approach)
int TabulatonApproach( vector<int>& v, int n) {
    vector<vector<int>> dp(n,vector<int>(n, 0));

    for(int i=n-1; i>=0; i--) {
        for(int j=i+2; j<n; j++) {
            int minAns = INT_MAX;
            for(int k=i+1; k<j; k++) {
                minAns = min(minAns, v[i]*v[j]*v[k] + dp[i][k] + dp[k][j]);
            }
            dp[i][j] = minAns;
        }
    }
    return dp[0][n-1];

    // Time complexity = O(n*3)
    // Auxiliary Space = O(n*2)

}

int main() {
    
    vector<int> values = {1,3,1,4,1,5}; // since vector has 6 vlaues, so its hexagon.
    int n = values.size();              // size of vector.

    // <Way-1> using(calling ) solveRecursively func. 
    // int ans = solveRecursively( values, n, 0, n-1);  // Uncomment for calls

    // <way-2> using(calling ) Memoisation
    // using dp vector for optimised space
    // vector<vector<int>> dp(n, vector<int> (n, -1));  // Uncomment for calls
    // int ans = MemoisationApproach( values, n, 0, n-1, dp);   // Uncomment for calls

    // <way-3> using Tabulation 
    int ans = TabulatonApproach( values, n);
    cout<<"The min Trangulation area: "<< ans ;
    cout<< endl;

    return 0;
}