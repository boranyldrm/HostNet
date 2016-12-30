//
// Created by Boran Yildirim on 15.12.2016.
// 21401947
// CS 202-01
//

#ifndef INC_5ASSIGNMENT_HOST_H
#define INC_5ASSIGNMENT_HOST_H

#include <string>

using namespace std;

class Host {
public:

    void swap (Host& left, Host& right) {
        using std::swap;
        swap(left.id, right.id);
        swap(left.name, right.name);
        swap(left.visit, right.visit);
        swap(left.comp, right.comp);

        swap(left.num_conn, right.num_conn);
        swap(left.connected_ids, right.connected_ids);
    }

    Host& operator=(Host right){
        swap(*this, right);
        return *this;
    }

private:

    friend class HostNet;
    friend class Queue;

    // when traversing the graph whether visited or not for all Hosts
    enum Visit {
        VISITED,
        NOTVISITED
    };

    int id;         // id of the host
    string name;    // name of the host
    int num_conn;   // number of connections
    int *connected_ids;     // ids of connected hosts [array]
    int comp;       // belong to which component
    Visit visit;    // visited or not in traversing
};

#endif //INC_5ASSIGNMENT_HOST_H