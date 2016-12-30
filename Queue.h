//
// Created by Boran Yildirim on 14.12.2016.
// 21401947
// CS 202-01
//

#ifndef INC_5ASSIGNMENT_QUEUE_H
#define INC_5ASSIGNMENT_QUEUE_H

#include <string>
#include <iostream>
#include "Host.h"

using namespace std;

class Queue {
public:
    Queue();
    Queue(Queue &input);
    ~Queue();
    void dequeue(Host &out, int &depth);
    void enqueue(const Host &data, const int &cost);
    bool isEmpty();
    void display();
private:
    struct Node {
        Host data;
        int cost;
        Node *next;
    };
    Node *first;
    Node *last;
};

#endif //INC_5ASSIGNMENT_QUEUE_H