#include<bits/stdc++.h>
using namespace std;

//recursive Approach
int SolveRecursively(vector<int>& slices, int index, int endindex,  int n) {
    if(n == 0 || index > endindex) {
        return 0;
    }

    int TakeSlices = slices[index] + SolveRecursively(slices, index+2, endindex, n-1);

    int notTakeSlicex = 0 + SolveRecursively(slices, index+1, endindex, n);

    return max(TakeSlices, notTakeSlicex);
}

//using memoisation
int SolveMemoisation(vector<int>& slices, int index, int endindex, int n, vector<vector<int>>& dp ) {
    //base case
    if(n == 0 || index > endindex) {
        return 0;
    }
    if(dp[index][n] != -1) {
        return dp[index][n];
    }

    int TakeSlices = slices[index] + SolveMemoisation(slices, index+2, endindex, n-1, dp);

    int notTakeSlicex = 0 + SolveMemoisation(slices, index+1, endindex, n, dp);

    return  dp[index][n] = max(TakeSlices, notTakeSlicex);
}

//using Tabulation
int TabulationApproach(vector<int>& slices) {
    int k = slices.size();

    vector<vector<int>>dp1(k+2, vector<int>(k+2, 0));
    vector<vector<int>>dp2(k+2, vector<int>(k+2, 0));

    for(int index=k-2; index>=0; index--) {
        for(int n=1; n<=k/3; n++) {
            int takeSlice = slices[index] + dp1[index+2][n-1];
            int nottakeSlice = 0 + dp1[index+1][n];

            dp1[index][n] = max(takeSlice, nottakeSlice);
        }
    }
    int case1 = dp1[0][k/3];

    for(int index=k-1; index>=1; index--) {
        for(int n=1; n<=k/3; n++) {
            int takeSlice = slices[index] + dp2[index+2][n-1];
            int nottakeSlice = 0 + dp2[index+1][n];

            dp2[index][n] = max(takeSlice, nottakeSlice);
        }
    }
    int case2 = dp2[1][k/3];
    return max(case1, case2);
}

// using space optimisation method
int sPaceOptimmised(vector<int>& slices) {
    int k = slices.size();

    vector<int> prev1(k+2, 0);
    vector<int> curr1(k+2, 0);
    vector<int> next1(k+2, 0);

    vector<int> prev2(k+2, 0);
    vector<int> curr2(k+2, 0);
    vector<int> next2(k+2, 0);

    for(int index=k-2; index>=0; index--) {
        for(int n=1; n<=k/3; n++) {
            int takeSlices = slices[index] + next1[n - 1];
            int notTake = 0 + curr1[n];

            prev1[n] = max(takeSlices, notTake);
        }
        next1 = curr1;
        curr1 = prev1;
        
    }
    int case1 = curr1[k/3];

    for(int index=k-1; index>=1; index--) {
        for(int n=1; n<=k/3; n++) {
            int takeSlices = slices[index] + next2[n - 1];
            int notTake = 0 + curr2[n];

            prev2[n] = max(takeSlices, notTake);
        }
        next2= curr2;
        curr2 = prev2;
    }
    int case2 = curr2[k/3];
    return max(case1, case2);
}
int main() {
    vector<int> slices = {1,2,3,4,5,6};
    int k = slices.size();

    // int ans = max(SolveRecursively(slices, 0, k-2, k/3), SolveRecursively(slices, 1, k-1, k/3));

    //Memoisation Approach
    // vector<vector<int>> dp1(k+2, vector<int>(k+2, -1));
    // vector<vector<int>> dp2(k+2, vector<int>(k+2, -1));
    // int ans = max(SolveMemoisation(slices, 0, k-2, k/3, dp1), SolveMemoisation(slices, 1, k-1, k/3, dp2));   

    // using tabulation Approach
    // int ans = TabulationApproach(slices);

    //space optimised approach
    int ans = sPaceOptimmised(slices);
    cout<<"Maximum slices sum: "<< ans;

    return 0;
}