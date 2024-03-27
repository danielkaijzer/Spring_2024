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

// L1->L2->L3->null

// O(2n) solution
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* prev = nullptr;

        while(cur){
            ListNode* tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }

    void Print(ListNode* tmp){
        while(tmp){
            cout << tmp->val << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

};

// null<-L1<-L2<-L3

int main(){
    ListNode* L3 = new ListNode(3,nullptr);
    ListNode* L2 = new ListNode(2,L3);
    ListNode* L1 = new ListNode(1,L2);

    ListNode* tmp = L1;

    Solution s;

    s.Print(tmp);

    s.reverseList(L1);

    tmp = L3;

    s.Print(L3);

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