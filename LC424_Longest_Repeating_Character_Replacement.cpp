#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int characterReplacement(string s, int k) {

        unordered_map<char,int> mp;

        int l =0, r=0, maxval = 0, ans = -1;

        for (;r < s.size(); ++r){
            mp[s[r]]++; // iterate char in hashmap
            maxval = std::max(maxval,mp[s[r]]); // update the most common value in string (so far)

            // check num of replacements needed
            // length of window - count of most frequent character
            while((r-l+1)-maxval > k){
                mp[s[l]]--; // before we move pointer, decriment char count at left
                l++; // move left pointer
            }
            ans = std::max(ans,r-l+1);
        }
        return ans;
    }
};

int main(){

}