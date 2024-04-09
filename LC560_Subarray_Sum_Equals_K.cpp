#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;


        // first make sure nums are sorted, for now ASSUME SORTED

        // check subarrays up to where the current element == k

        int index = 0;

        while (nums.at(index) <= k){
            // check if sum of elements left in array == k

            // prep subarray for recursive function

            count += recursiveSum(nums.begin(),nums.begin()+index,k);

            index++;
        }

        return count;
    }

    int recursiveSum(vector<int>::iterator begin,vector<int>::iterator end, int k){
        int sum = 0;

        while (begin != end){
            sum += ;
        }
    }

};

int main(){

    Solution s;

    vector<int> nums = {1,2,3};

    cout << s.subarraySum(nums,3) << endl; // 2

}
