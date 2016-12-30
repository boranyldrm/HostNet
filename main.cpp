#include "HostNet.h"

using namespace std;

int main(){
    HostNet HN("hName");


    ///*
    HN.listCommunicationsLowerThan("m3", 2);
    HN.listCommunicationsLowerThan("m23", 2); cout << endl;

    HN. listCommunicationsOnHubHost("m7"); cout << endl;
    HN.findConnectedComponents();

    cout << endl;
    HN. displayMostCentralHosts(); cout << endl;
    HN. displayAverageClusteringCoefficients(); cout << endl;

     //*/
    return 0;
}

/* OUTPUT:
From “m3” 3 hosts are directly reachable with cost lower than 2: m1, m4, m5, m6.
“m23” does not exist in the host network.
If m1 is considered as hub these routes are possible:
<m0, m3>
<m2, m3>
There are two connected components:
For component 1: 11 nodes
For component 2: 5 nodes
Most central node in component 1: m3
Most central node in component 2: m13
Average clustering coefficient for component 1: 2.24
Average clustering coefficient for component 2: 0.78
 */