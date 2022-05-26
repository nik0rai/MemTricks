#pragma once
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

template<class T>
class List
{
public:
    struct Node
    {
        T data;
        Node* next;


        bool isAvailable = true;
    };
    Node* head = NULL;


    void Push(Node* newNode)
    {
        newNode->next = head;
        newNode->isAvailable = true;
        head = newNode;
    }


    Node* Pop()
    {
        Node* top = head;
        if (top == NULL) {
            return NULL;
        }
        head = head->next;
        return top;
    }

    void ShowSegments(Node* startNode) {
        Node* curr = startNode;

        int i = 0;
        while (curr->next != NULL) {
            cout << "Segment [" << i << "] -> " << curr << " Key: " << curr->isAvailable << endl;
            i++;
            curr = curr->next;
        }
    }
};
