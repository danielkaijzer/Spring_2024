#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> answer(nums.size());

        // prefix loop
        int prefix = 1;
        for (int i = 0; i < nums.size(); ++i){
            answer[i] = prefix;
            prefix *= nums[i];
        }

        // postfix loop
        int postfix = 1;
        for (int i = nums.size()-1; i >=0; --i){
            answer[i] *= postfix;
            postfix *= nums[i];
        }

        return answer;
    }
};

int main(){

    vector<int> nums = {1,2,3,4};

    Solution s;

    vector<int> answer = s.productExceptSelf(nums);

    for (auto a: answer){
        cout << a << endl;
    }


}