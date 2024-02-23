#include <iostream>
#include <stack>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<int> s;

        ListNode *tmp = head;

        while (tmp){
            s.push(tmp->val);
            tmp = tmp->next;
        }

        tmp = head;
        while(tmp){
            tmp->val = s.top();
            s.pop();
            tmp = tmp->next;
        }

        return head;
    }
};

int main(){

}