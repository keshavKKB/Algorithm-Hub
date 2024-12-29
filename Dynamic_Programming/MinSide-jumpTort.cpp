#include<bits/stdc++.h>
using namespace std; 
// Dynamic programming
int RecursiveApproach(vector<int>& obstacles, int currLane, int currFrog_pos, int n) {
    if(currFrog_pos == n) {
        return 0;
    }
    if(obstacles[currFrog_pos+1] != currLane) {
        return RecursiveApproach(obstacles, currLane, currFrog_pos + 1, n);
    }
    else{
        int ans= INT_MAX;
        for(int i=1; i<=3; i++) {
            if(currLane != i && obstacles[currFrog_pos] != i) {
                ans = min(ans , 1+RecursiveApproach(obstacles, i, currFrog_pos, n));
            } 
        } 
        return ans;
    }    
}

//using memoisation
int MemoisationApproach(vector<int>& obstacles, int currLane, int currFrog_pos, int n, vector<vector<int>>& dp) {
    if(currFrog_pos == n) {
        return 0;
    }
    if(dp[currLane][currFrog_pos] != -1) {
        return dp[currLane][currFrog_pos];
    }
    if(obstacles[currFrog_pos+1] != currLane) {
        return MemoisationApproach(obstacles, currLane, currFrog_pos + 1, n, dp);
    }
    else{
        int ans= INT_MAX;
        for(int i=1; i<=3; i++) {
            if(currLane != i && obstacles[currFrog_pos] != i) {
                ans = min(ans , 1+MemoisationApproach(obstacles, i, currFrog_pos, n, dp));
            } 
        } 
        dp[currLane][currFrog_pos] = ans;
        return ans;
    }    
}

//using Tabulation approach
int TablationApproach(vector<int>& obstacles, int n) {
    vector<vector<int>> dp(4, vector<int>(obstacles.size(), INT_MAX));
    dp[0][n] = 0;
    dp[1][n] = 0;
    dp[2][n] = 0;
    dp[3][n] = 0;

    for(int currFrog_pos=n-1; currFrog_pos>=0; currFrog_pos--) {
        for(int currLane=1; currLane<=3; currLane++) {
            if(obstacles[currFrog_pos+1] != currLane) { // obstacles not present in nest position.
                dp[currLane][currFrog_pos] = dp[currLane][currFrog_pos+1];
            }
            else {
                int ans= INT_MAX;
                for(int i=1; i<=3; i++) {
                    if(currLane != i && obstacles[currFrog_pos] != i) { // condition to take sideway jump.
                        ans = min(ans , 1+dp[i][currFrog_pos+1]);
                    } 
                } 
                dp[currLane][currFrog_pos] = ans;   
            }
        }
    }
    return min(dp[2][0], min(1+dp[1][0], 1+dp[3][0]));
}

//most optimised Approach
int OptimisedApproach(vector<int>& obstacles) {
    vector<int> curr(4, INT_MAX);
    vector<int> next(4, INT_MAX);
    int n = obstacles.size();
    next[0]= 0;
    next[1]= 0;
    next[2]= 0;
    next[3] = 0;

    for(int currFrog_pos=n-1; currFrog_pos>=0; currFrog_pos--) {
        for(int currLane=1; currLane<=3; currLane++) {
            if(obstacles[currFrog_pos+1] != currLane) { // obstacles not present in nest position.
                curr[currLane] = next[currLane];
            }
            else {
                int ans= INT_MAX;
                for(int i=1; i<=3; i++) {
                    if(currLane != i && obstacles[currFrog_pos] != i) { // condition to take sideway jump.
                        ans = min(ans , 1+next[i]);
                    } 
                } 
                curr[currLane] = ans;   
            }
        }
        next = curr;
    }
    return min(next[2], min(1+next[1], 1+next[3]));
}

int main() {
    //vector for the obstacles in lane. In total 3 lane 
    vector<int> obstacles = {0,1,2,3,0}; // 0-> No obstacles, 1->obstacles in lane 1, same way as number.
    int n = obstacles.size()-1;

    // Regular recursive apprach
    // 2-> currLane
    // 0-> turtle position
    // int ans = RecursiveApproach(obstacles, 2, 0, n); // uncomment to call func

    //Memoapproach
    // vector<vector<int>> dp(4, vector<int>(n, -1));
    // int ans = MemoisationApproach(obstacles, 2, 0, n, dp); // uncomment to call func

    // int ans = TablationApproach(obstacles, n); // uncomment to call func.

    //optimised func call
    int ans = OptimisedApproach(obstacles);
    cout<<"The minimum Sideway jump: "<< ans;
    return 0;
}