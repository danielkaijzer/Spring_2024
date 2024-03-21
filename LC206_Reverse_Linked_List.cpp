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

// nullptr L1->L2->L3->nullptr

// O(2n) solution
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode * cur = head;
        ListNode * prev = nullptr;

        while(cur){
            ListNode*tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }

        return prev;

    }
};

int main(){

}

/*

        ListNode* prev = nullptr;
        ListNode* cur = head;

        while(cur){
            ListNode* tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }

        return prev;

*/