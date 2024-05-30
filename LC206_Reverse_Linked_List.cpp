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

        while(cur != nullptr){ // until you reach tail
            ListNode* next = cur->next; // track next node 

            // reverse the links (swap left and right pointers)
            cur->next = prev; // the right/next pointer will now point to left/prev node

            // move to the next node in list, to prepare to swap links there
            prev = cur; 
            cur = next;
        }

        // return the last node in chain (which is now the new first node in reversed list)
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