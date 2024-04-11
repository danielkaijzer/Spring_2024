#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        int current_sum = 0;

        unordered_map<int,int> hmp;

        for (auto num: nums){
            current_sum+= num;

            if (current_sum == k){
                count++;
            }

            // check if any previous sums
            // can be summed with current sum to get k
            if(hmp.count(current_sum-k) > 0){
                // if complement + current sum exists and equals k, increment count
                // add num of occurences of previous sums
                // we need to factor in that non-negative numbers
                // can be in our array
                count += hmp[current_sum-k];

            }

            hmp[current_sum]++; // add current sum to hashmap
        }
        return count;
    }   

};

int main(){

    Solution s;

    vector<int> nums = {1,2,3};
    vector<int> nums2 = {1,2,1,2,1};

    // cout << endl;
    cout << s.subarraySum(nums,3) << endl; // 2

    cout << s.subarraySum(nums2,3) << endl; // 4

}

/*
     int count =0;
        int current_sum = 0;

        unordered_map<int,int> seen; // store seen sums and their frequencies

        for (int num : nums){
            current_sum += num;

            // see if current sum is target
            if (current_sum == k){
                count++;
            }

            // else see if any previous sums can be summed with current sum to get k
            // Increment count for all previous sums (current_sum - k)
            if (seen.count(current_sum-k)){
                count += seen[current_sum-k];
            }
            seen[current_sum]++;
        }
        
        return count;

*/



/* MY RECURSIVE SOLUTION O(N^2)


    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        
        // std::sort(nums.begin(), nums.end());
        // first make sure nums are sorted, for now ASSUME SORTED
        // check subarrays up to where the current element == k
        recursiveSum(nums.begin(),nums.end(),k,count);
        // cout << endl << "RESULT: " << count << endl; 
        return count;
    }


    // a recursive function that takes the sum of current subarray 
    // and iterates count whenever that sum is equal to k
    void recursiveSum(vector<int>::iterator begin,vector<int>::iterator end, int& k, int& count){
        if (begin == end){ // if vector empty, return
            return;
        }

        // check sum of current subarray
        int sum = 0;

        auto current = begin;
        // cout << *current << endl;

        while (current != end){
            sum += *current;
            ++current;
            // cout << "rolling sum: " << sum << endl;
            if (sum == k){
                count++;
            }
        }
        recursiveSum(++begin, end, k, count); // recursively check subarrays
    }





*/
