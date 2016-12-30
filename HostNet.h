//
// Created by Boran Yildirim on 13.12.2016.
// 21401947
// CS 202-01
//

#ifndef INC_5ASSIGNMENT_HOSTNET_H
#define INC_5ASSIGNMENT_HOSTNET_H

#include "Queue.h"
#include "Host.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class HostNet{

public:
    HostNet(const string &hName);
    HostNet(const HostNet& hNet); // copy constructor

    ~HostNet(); // destructor

    void listCommunicationsLowerThan(const string &hname, const int &cost);
    void listCommunicationsOnHubHost(const string &hname);
    void findConnectedComponents();
    void displayMostCentralHosts();
    void displayAverageClusteringCoefficients();

    void print();

private:
    // traverse for public listCommunicationsLowerThan
    void BFSListCommunicationsLowerThan (const int &index, const int &cost);

    // traverse for public listCommunicationsOnHubHost
    void BFSListCommunicationsOnHubHost (const int &index);

    // traverse for public findConnectedComponents
    void BFSFindConnectedComponents (const int &index, int &num, const int &comp);

    // traverse for public displayMostCentralHosts
    void BFSDisplayMostCentralHosts ();

    // traverse for public displayAverageClusteringCoefficients
    void BFSDisplayAverageClusteringCoefficients(const int &index, double &cc);


#define NOTFOUND -1
    int findIndex (const string &hname);

    // properties
    Host *hosts;
    int HOST_SIZE;
    int NUM_COMPONENT;
    int *components;
};


#endif //INC_5ASSIGNMENT_HOSTNET_H
