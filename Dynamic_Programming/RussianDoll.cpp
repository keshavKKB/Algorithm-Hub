#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool compare(const vector<int>& a, const vector<int>& b) {
        if(a[0] == b[0]) {
            return a[1] > b[1]; // sort in descending order if row has same number.
        }
        return a[0] < b[0]; // sort traditionally
    }
    int solve(vector<vector<int>>& envelopes, int n) {
        if(n == 0) {
            return 0;
        }
        vector<int> ans;
        ans.push_back(envelopes[0][1]);

        for(int i=1; i<envelopes.size(); i++) {
            if(envelopes[i][1] > ans.back()) {  // if gets smaller envelope height/width
                ans.push_back(envelopes[i][1]);
            }
            else {
                int index = lower_bound(ans.begin(), ans.end(), envelopes[i][1]) - ans.begin(); // find the lower_bound index to push into ans arr
                ans[index] = envelopes[i][1];
            }
        }
        return ans.size();
    }
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), compare); // sort using comparator
        int ans = solve(envelopes, envelopes.size());
        return ans;
    }
    // creator- keshav kishav baraik
};