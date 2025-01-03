#include<bits/stdc++.h>
using namespace std;
int solveRecursively(int faces, int dice, int targetSum) {

    if(targetSum < 0) {
        return 0;
    }
    if(dice == 0 && targetSum != 0) {
        return 0;
    }
    if(targetSum == 0 && dice != 0) {
        return 0;
    }
    if(targetSum == 0 && dice == 0) {
        return 1;
    }
    int ans = 0;
    for(int i=1; i<=faces; i++){
        ans = ans + solveRecursively(faces, dice-1, targetSum - i);
    }
    return ans;
}
//using memoisation
int solveMemoisation(int dice, int faces, int targetSum, vector<vector<int>>& dp) {
    if(targetSum < 0) {
        return 0;
    }
    if(dice == 0 && targetSum != 0) {
        return 0;
    }
    if(targetSum == 0 && dice != 0) {
        return 0;
    }
    if(targetSum == 0 && dice == 0) {
        return 1;
    }
    if(dp[dice][targetSum] != -1) {
        return dp[dice][targetSum];
    }
    int ans = 0;
    for(int i=1; i<=faces; i++){
        ans = ans + solveMemoisation(dice-1, faces, targetSum - i, dp);
    }
    return dp[dice][targetSum] = ans;
}

//solve Tabulation 
int TabulationApproach(int dice, int faces, int targetSum) {
    vector<vector<int>> dp(dice+1, vector<int>(targetSum+1, 0));
    dp[0][0] = 1;
    for(int d=1; d<=dice; d++) {
        for(int t=1; t<=targetSum; t++) {
            int ans = 0;
            for(int i=1; i<=faces; i++){
                if(t-i >= 0){
                    ans = ans + dp[d-1][t - i];
                }
            }
            dp[d][t] = ans;
        }
    }
    return dp[dice][targetSum];
}

//using spaceoptimisation
int spaceOptimised(int dice, int faces, int targetSum){
    vector<int>prev(targetSum+1, 0);
    vector<int>curr(targetSum+1, 0);
    prev[0] = 1;
    for(int d=1; d<=dice; d++) {
        for(int t=1; t<=targetSum; t++) {
            int ans = 0;
            for(int i=1; i<=faces; i++){
                if(t-i >= 0){
                    ans = ans + prev[t - i];
                }
            }
            curr[t] = ans;
        }
        prev = curr;
    }
    return prev[targetSum];

}
int main() {
    int dice = 3;
    int faces = 6;
    int target = 12;
    int n = dice ;

    // int ans = solveRecursively(faces, dice, target);
    // vector<vector<int>> dp(dice+1, vector<int> (target+1, -1));
    // int ans = solveMemoisation(dice, faces, target, dp);

    // int ans = TabulationApproach(dice, faces, target);
    int ans = spaceOptimised(dice, faces, target);
    cout<<"Max way to find the targetsum: "<< ans;
    return 0;
}