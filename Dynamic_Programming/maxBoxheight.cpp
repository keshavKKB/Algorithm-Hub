#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // using largest increasing subsequence(LIS) algorithem. 
    bool check(vector<int> baseCuboid, vector<int> nextCuboid) {
        if(nextCuboid[0] <= baseCuboid[0] && nextCuboid[1] <= baseCuboid[1] &&  nextCuboid[2] <= baseCuboid[2]){
            return true;
        }
        return false;
    }
    int solveTabulation(vector<vector<int>>& a, int n) {
        vector<int> currRow(n+1, 0);
        vector<int> nextRow(n+1, 0);

        for(int curr=n-1; curr>=0; curr--) {
            for(int prev=curr-1; prev>=-1; prev--) {
                int include = 0;
                if(prev == -1 || check(a[curr] , a[prev])) {
                    include = a[curr][2]  + currRow[curr+1];
                }
                int exclude = 0 + nextRow[prev+1];
                currRow[prev+1] = max(include, exclude);

            }
            nextRow = currRow;
        }
        return nextRow[0];
    }
    int maxHeight(vector<vector<int>>& cuboids) {
        int n = cuboids.size();
        for(auto &a : cuboids) {
            sort(a.begin(), a.end());
        }
        sort(cuboids.begin(), cuboids.end());

        return solveTabulation(cuboids, n);
    }
    //creator - keshav kishan baraik.
};