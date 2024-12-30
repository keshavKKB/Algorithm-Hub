#include<bits/stdc++.h>
using namespace std;
// dp algorithm(releated to knapsack problem)
// find the maximum sum of time take to make the dishes, 1 dish takes 1 unit of time

//basic Recursive approach
int RecursiveApproach(vector<int>& satisfaction, int index, int time) {
    if(index == satisfaction.size()) {
        return 0;
    }
    
    int include = satisfaction[index]*(time+1) + RecursiveApproach(satisfaction, index+1, time+1); // including dishes
    int exclude = 0 + RecursiveApproach(satisfaction, index+1, time); // excluding dishes

    return max(include, exclude);
}

// Memoisation Approach(using dp arr)(top down approach)
int MemoisationApproach(vector<int>& satisfaction, int index, int time, vector<vector<int>>& dp) {
    if(index == satisfaction.size()) {
        return 0;
    }
    if(dp[index][time] != -1) {
        return dp[index][time];
    }
    
    int include = satisfaction[index]*(time+1) + MemoisationApproach(satisfaction, index+1, time+1, dp);
    int exclude = 0 + MemoisationApproach(satisfaction, index+1, time, dp);

    dp[index][time] = max(include, exclude);
    return dp[index][time];
}

//Tabulation approach(bottom up approach)
int TabulatonApproach(vector<int>& satisfaction) {
    int n = satisfaction.size();
    vector<vector<int>>dp(n+1, vector<int>(n+1, 0));

    for(int index=n-1; index>=0; index--) {
        for(int time=index; time>=0; time--) {
            int include = satisfaction[index]*(time+1) + dp[index+1][time+1];
            int exclude = 0 + dp[index+1][time];
            dp[index][time] = max(include, exclude);
        }
    }
    return dp[0][0];
}

//space optimised Appproach
int SpaceOptimised(vector<int>& satisfaction, int n) {
    vector<int> curr(n+1, 0);
    vector<int> next(n+1, 0);

    for(int index=n-1; index>=0; index--) {
        for(int time=index; time>=0; time--) {
            int include = satisfaction[index]*(time+1) + next[time+1];
            int exclude = 0 + next[time];
            curr[time] = max(include, exclude);
        }
        next = curr;
    }
    return next[0];
    
}

int main() {
    // dishes selected by chef
    vector<int> satisfaction = {-1,-8,0,5,-9};
    int n = satisfaction.size();

    // int ans = RecursiveApproach(satisfaction, 0, 0);
     
    // using MemoisationApproach
    // vector<vector<int>>dp(n+1,vector<int>(n+1, -1));
    // int ans = MemoisationApproach(satisfaction, 0, 0, dp);

    //using TabulationApproach
    // int ans = TabulatonApproach(satisfaction);

    //using Optimisation
    int ans  = SpaceOptimised(satisfaction, n);
    cout<<"Minimum sumTime to prepare dish: "<< ans;

    return 0;
}