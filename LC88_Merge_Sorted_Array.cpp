#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m-1;
        int p2 = n-1;
        int k = m+n-1;

        while (p2 >= 0){ // loop until all values from p2 have been added to p1

            // if tail of nums1 is greater value than tail of p2
            // then make tail the tail of the updated nums1 (larger vector)
            if(p1 >= 0 && nums1[p1] > nums2[p2]){
                nums1[k] = nums1[p1];
                p1--;
            }
            // if tail of nums1 is less than or equal to tail of p2
            // then make tail of p2 the tail of updated nums1 (larger vector)
            else{ 
                nums1[k] = nums2[p2];
                p2--;
            }
            k--;
        }
    }
};

int main(){

    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};

    Solution s;
    s.merge(nums1,3,nums2,3);

    for (auto n : nums1){
        cout << n << " ";
    }

    cout << endl;
}
