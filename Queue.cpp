//
// Created by Boran Yildirim on 14.12.2016.
// 21401947
// CS 202-01
//

#include "Queue.h"

Queue::Queue() {
    first = NULL;
    last = NULL;
}

Queue::Queue(Queue &input) {
    if (input.isEmpty()) {
        first = NULL;
        last = NULL;
    }
    else {
        first = new Node;
        first->data = input.first->data;
        first->cost = input.first->cost;
        last = first;
        Node *cur = input.first->next;
        Node *tail = last;
        while (cur != NULL) {
            tail->next = new Node;
            tail = tail->next;
            tail->data = cur->data;
            tail->cost = cur->cost;
            cur = cur->next;
        }
        tail->next = NULL;
    }
}

Queue::~Queue() {
    while (!isEmpty()) {
        if (first == last)
            delete first;
        else {
            Node *tmp = first;
            first = first->next;
            delete tmp;
        }
    }
}

void Queue::dequeue(Host &out, int &depth) {
    if (!isEmpty()) {
        out = first->data; // out the dequeued item
        depth = first->cost;
        if (first == last) {
            delete first;
            first = NULL;
        }
        else {
            Node *tmp = first;
            first = first->next;
            delete tmp;
        }
    }
}

void Queue::enqueue(const Host &data, const int &cost) {
    if (isEmpty()) {
        Node *x = new Node;
        x->data = data;
        x->cost = cost;
        x->next = NULL;
        first = x;
        last = x;

        x->data.visit = Host::VISITED;
    }
    else {
        last->next = new Node;
        last->next->data = data;
        last->next ->cost = cost;
        last->next->next = NULL;
        last = last->next;

        last->data.visit = Host::VISITED;
    }
}

bool Queue::isEmpty() {
    return first == NULL;
}

void Queue::display() {
    Node *cur = first;
    while (cur != NULL) {
        cout << cur->data.name << " ";
        cur = cur->next;
    }
    cout << endl;
}