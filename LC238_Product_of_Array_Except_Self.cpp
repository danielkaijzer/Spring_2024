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

        // prefix loop
        int postfix = 1;

        for (int i = nums.size(); i >=0; ++i){
            answer[i] = postfix;
            postfix *= nums[i];
        }
       
    }
};

int main(){

    vector<int> nums = {1,2,3,4}; // [24,12,8,6]

    Solution s;

    vector<int> answer = s.productExceptSelf(nums);

    for (auto a: answer){
        cout << a << endl;
    }


}



/*
 vector<int> answer(nums.size());

        // prefix loop
        int prefix = 1;
        for (int i = 0; i < nums.size(); ++i){
            answer[i] = prefix;
            prefix *= nums[i]; // this staggers so cur index will only have product of what comes before it
        }
        // res: [1,1,2,6]

        // postfix loop
        int postfix = 1;
        for (int i = nums.size()-1; i >=0; --i){
            answer[i] *= postfix;
            postfix *= nums[i]; // again staggers so cur index will have product of what comes after it 
        }
        // res: [ (12*2) , (4*3) , (2*4) , (6*1)]


        return answer;*/