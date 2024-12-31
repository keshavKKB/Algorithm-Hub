#include<bits/stdc++.h>
using namespace std;
// Dynamic programming (gfg).
// burte to better approach
class Solution {
  public:
    // Function to find length of longest increasing subsequence.
    int solveRecursively(vector<int>& arr, int n, int curr, int prev) {
        if(curr == n) {
           return 0;
        }
        //include 
        int include = 0;
        if(prev == -1 || arr[curr] > arr[prev]) {
            include = 1 + solveRecursively(arr, n, curr+1, curr);
        }
        //exclude
        int exclude = 0 + solveRecursively(arr, n, curr+1, prev);
        
        return max(include, exclude);
        
    }
    
    //using memoisationapproach
    int MemoisationApproach(vector<int>& arr, int n, int curr, int prev, vector<vector<int>>& dp) {
        if (curr == n ) {
            return 0;
        }
        if(dp[curr][prev+1] != -1) {
            return dp[curr][prev+1];
        }
        int include = 0;
        if(prev == -1 || arr[curr] > arr[prev]) {
            include = 1 + MemoisationApproach(arr, n, curr+1, curr, dp);
        }
        int exclude = 0 + MemoisationApproach(arr, n, curr+1, prev, dp);
        
        return dp[curr][prev+1] = max(include, exclude);
        
        
    }
    //usig Tabulation(use bottom- up approach)
    int TabualtionApproach(vector<int>& arr, int n) {
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        
        for(int curr=n-1; curr>=0; curr--) {
           
            for(int prev=curr-1; prev>=-1; prev--) {
                int include = 0;
                if(prev == -1 || arr[curr] > arr[prev]) {
                    include = 1 + dp[curr+1][curr+1];
                }
                int exclude = 0 + dp[curr+1][prev+1];
                dp[curr][prev+1] = max(include, exclude);
            }
        }
        return dp[0][0];
        
    }
    //using Space optimisation
    int SpaceoptimisedApproach(vector<int>& arr, int n) {
        vector<int> currRow(n+1, 0);
        vector<int> nextRow(n+1, 0);
        
        for(int curr=n-1; curr>=0; curr--) {
           
            for(int prev=curr-1; prev>=-1; prev--) {
                int include = 0;
                if(prev == -1 || arr[curr] > arr[prev]) {
                    include = 1 + nextRow[curr+1];
                }
                int exclude = 0 +   nextRow[prev+1];
                currRow[prev+1] = max(include, exclude);
            }
            nextRow = currRow;
        }
        return nextRow[0];
    }
    
    //int most optimised approach with binary search and 
    int mostOptimised(vector<int>& arr, int n) {
        if(n == 0) {
            return 0;
        }
        vector<int> ans;
        ans.push_back(arr[0]); // mandatory to push first element in ans vector.
        
        for(int i=1; i<n; i++){
            if(ans.back() < arr[i] ) {
                ans.push_back(arr[i]);
            }
            //find index of just greater than that element
            else {
                int index = lower_bound(ans.begin(), ans.end(), arr[i])- ans.begin();
                ans[index]=arr[i];
            }
        }
        return ans.size();

        // time complexity (nlogn)
        // space complexity(o(n));
        
    }
    int longestSubsequence(vector<int>& arr) {
        int n = arr.size();
        // return solveRecursively(arr, n, 0, -1);
        
        //using memoisation make 2d dp vector bcz curr and prev both changes
        // vector<vector<int>> dp(n,vector<int>(n+1, -1));
        // return MemoisationApproach(arr, n, 0, -1, dp);
        
        // return TabualtionApproach(arr, n);
        // return SpaceoptimisedApproach(arr, n);
        
        return mostOptimised(arr, n);
        
        //creator - keshav kishav baraik
    }
};    