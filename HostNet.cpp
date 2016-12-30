//
// Created by Boran Yildirim on 13.12.2016.
// 21401947
// CS 202-01
//

#include <iomanip>
#include <sstream>
#include "HostNet.h"

/*
 * The default constructor loads a host network from an input file called hName.
 * The first row of this file indicates the number of hosts in the network.
 * Subsequent lines of file include information of host and their num_conn.
 * Connections between hosts are bidirectional,
 * that is, if there is a bus from O to D, then there also exists a bus from D to O.
 * Information in the lines contains host id, host name, number of num_conn,
 * and ids of connected hosts tokens separated by white spaces.
 */

// constructor
HostNet::HostNet(const string &hName) {
    string line;
    ifstream myfile (hName.c_str());
    if ( myfile.is_open() && getline(myfile, line) ) {
        stringstream stoi (line);
        stoi >> HOST_SIZE;
        hosts = new Host[HOST_SIZE];    // hosts array initialized with the first line of the file

        NUM_COMPONENT = 1;    // number of component is 1 by default
        components = new int[NUM_COMPONENT];

        int i = 0;
        while ( myfile >> hosts[i].id >> hosts[i].name >> hosts[i].num_conn ) {
            hosts[i].connected_ids = new int[hosts[i].num_conn];
            for (int j = 0; j < hosts[i].num_conn; ++j) {
                myfile >> hosts[i].connected_ids[j];
            }
            hosts[i].visit = Host::NOTVISITED;
            i++;
        }
    }
    else {  // the file is empty
        NUM_COMPONENT = 0;
        HOST_SIZE  = 0;
        hosts = NULL;
        cout << "File is empty." << endl;
    }
}

// copy constructor
HostNet::HostNet(const HostNet &hNet) {
    if (HOST_SIZE != 0) {
        this->NUM_COMPONENT = hNet.NUM_COMPONENT;
        this->HOST_SIZE = hNet.HOST_SIZE;
        this->hosts = new Host[this->HOST_SIZE];
        for (int i = 0; i < this->HOST_SIZE; ++i) {
            this->hosts[i] = hNet.hosts[i];
        }
    }
}

// destructor
HostNet::~HostNet() {
    for (int i = 0; i < HOST_SIZE; ++i) {
        delete [] hosts[i].connected_ids;
    }
    if (HOST_SIZE != 0)
        delete [] hosts;
    if (NUM_COMPONENT != 0)
        delete [] components;
}

/*
 * It outputs the hosts that are reachable with cost lower than
 * “cost” from host “hname”. If this given host does not take place
 * in the host network, give a warning message. See the output example below for the format.
 * You may assume that the names are unique within the host network.
 */
void HostNet::listCommunicationsLowerThan(const string &hname, const int &cost) {
    if (HOST_SIZE != 0) {
        int index = findIndex(hname);

        if (index == NOTFOUND)     // hname not in the graph
            cout << hname << " does not exist in the host network." << endl;
        else {  // hname is found
            cout << "From " << hname << " these hosts are directly reachable with cost lower than " << cost << ": ";
            BFSListCommunicationsLowerThan(index, cost);
            cout << endl;
        }
    }
}

/*
 * It outputs the routes (<o, d> tuples) for which there exist no direct
 * connection between <o> and <d>,
 * but <d> can be reached from <o> using host “hname” as a hub host.
 * You may consider only first level neighborhood of “hname”.
 * If this given host does not take place in the host network,
 * give a warning message.
 * Similarly, you may assume that the names are unique within the host network.
 */
void HostNet::listCommunicationsOnHubHost(const string &hname) {
    if (HOST_SIZE != 0) {
        int index = findIndex(hname);

        if (index == NOTFOUND)  //hname not in the graph
            cout << hname << " does not exist in the host network." << endl;
        else {
            cout << "If " << hname << " is considered as hub these routes are possible: " << endl;
            BFSListCommunicationsOnHubHost(index);
        }
    }
}

/*
 * This member function determines whether given graph has more than one connected components or not.
 * If graph includes only one connected component than,
 * you should give this as an information message,
 * otherwise you should display number of nodes of connected
 * components.
 */
void HostNet::findConnectedComponents() {
    if (HOST_SIZE != 0) {
        int num;        // number of node in a component

        // first component
        BFSFindConnectedComponents(0, num, NUM_COMPONENT);
        cout << "For component " << NUM_COMPONENT << ": " << num << endl;
        components[0] = num;

        // check for another component exist
        for (int i = 0; i < HOST_SIZE; ++i) {
            if (hosts[i].visit == Host::NOTVISITED) {   // another component exists
                NUM_COMPONENT++;
                BFSFindConnectedComponents(i, num, NUM_COMPONENT);

                cout << "For component " << NUM_COMPONENT << ": " << num << endl;

                // add new item to components
                int *tmp = new int[NUM_COMPONENT];
                for (int j = 0; j < NUM_COMPONENT - 1; ++j) {
                    tmp[j] = components[j];
                }
                tmp[NUM_COMPONENT - 1] = num;
                delete []components;
                components = tmp;
            }
        }
        for (int i = 0; i < HOST_SIZE; ++i) {
            hosts[i].visit = Host::NOTVISITED;
        }
    }
}


/*
 * It should calculate betweenness centrality score of each vertex in graph
 * and it should output the most central host
 * that has the highest betweenness centrality score
 * for each connected component separately.
 */
void HostNet::displayMostCentralHosts() {
    if (HOST_SIZE != 0) {
        int comp = 1;
        cout << "Most central node in component " << comp++ << ": -" << endl;
        if (NUM_COMPONENT > 1) {
            for (int i = comp; i <= NUM_COMPONENT; ++i)
                cout << "Most central node in component " << comp++ << ": -" << endl;
        }
    }
}

/*
 * It calculates and displays the average
 * clustering coefficient of each connected component within the network.
 */
void HostNet::displayAverageClusteringCoefficients() {
    if (HOST_SIZE != 0) {
        double cc = 0;  //clustering coefficient
        int comp = 1;

        for (int i = 0, j = 0; i < components[0] && j < HOST_SIZE; ++j) {
            if (hosts[i].comp == comp) {
                BFSDisplayAverageClusteringCoefficients(i, cc);
                i++;
            }
        }
        cout << "Average clustering coefficient for component " << comp++ << ": " << setprecision (2) << fixed << cc << endl;
        if (NUM_COMPONENT > 1) {
            cc = 0;
            for (int i = comp; i <= NUM_COMPONENT; ++i) {
                for (int j = 0, k = 0; j < components[i - 1] && k < HOST_SIZE; ++k) {
                    if (hosts[k].comp == comp) {
                        BFSDisplayAverageClusteringCoefficients(k, cc);
                        j++;
                    }
                }
                cout << "Average clustering coefficient for component " << comp++ << ": " << setprecision(2) << fixed << cc << endl;
            }
        }
    }
}

void HostNet::print() {
    cout << HOST_SIZE << endl;
    for (int i = 0; i < HOST_SIZE; ++i) {
        cout << hosts[i].id <<  " " << hosts[i].name << " " << hosts[i].num_conn << " ";
        for (int j = 0; j < hosts[i].num_conn; ++j) {
            cout << hosts[i].connected_ids[j] << "-";
        }
        cout << endl;
    }
    for (int k = 0; k < HOST_SIZE; ++k) {
        cout << hosts[k].comp << " ";
    }
    cout << endl;
    for (int l = 0; l < NUM_COMPONENT; ++l) {
        cout << components[l] << " ";
    }
}


void HostNet::BFSListCommunicationsLowerThan(const int &index, const int &cost) {
    Queue q;
    int depth = 1;  // depth must be less than cost
    hosts[index].visit = Host::VISITED;
    q.enqueue(hosts[index], depth);
    while (!q.isEmpty()) {
        Host tmp;
        q.dequeue(tmp, depth);
        if (tmp.name != hosts[index].name)  // don't print the name of the input host
            cout << tmp.name << "-";
        for (int i = 0; i < tmp.num_conn; i++) {
            int it = hosts[tmp.id].connected_ids[i];
            if (depth < cost && hosts[it].visit == Host::NOTVISITED) {
                q.enqueue(hosts[it], depth + 1);
                hosts[it].visit = Host::VISITED;
            }
        }
    }
    for (int i = 0; i < HOST_SIZE; ++i) {
        hosts[i].visit = Host::NOTVISITED;
    }
}

void HostNet::BFSListCommunicationsOnHubHost(const int &index) {
    Host hub = hosts[index];
    for (int i = 0; i < hub.num_conn; ++i) {
        Host cur = hosts[hub.connected_ids[i]];
        for (int j = 0; j < hub.num_conn; ++j) {
            bool flag = false;
            for (int k = 0; k < cur.num_conn; ++k) {
                if (hub.name != hosts[cur.connected_ids[k]].name)
                    if (hosts[hub.connected_ids[j]].name == hosts[cur.connected_ids[k]].name)
                        flag = true;
            }
            // cur.id < hosts[hub.connected_ids[j]].id prevent the repetition of same hosts
            // if <m3, m7> has communication then <m7, m3> also, so it prevents the repetition.
            if (!flag && cur.name != hosts[hub.connected_ids[j]].name
                && cur.id < hosts[hub.connected_ids[j]].id)
                cout << "<" << cur.name << ", " << hosts[hub.connected_ids[j]].name << ">" << endl;
        }
    }
}


void HostNet::BFSFindConnectedComponents(const int &index, int &num, const int &comp) {
    int cost = 0;   // not has usage, just for enqueue and dequeue helper parameter

    Queue q;
    num = 0;
    hosts[index].visit = Host::VISITED;
    hosts[index].comp = comp;
    q.enqueue(hosts[index], cost);
    while (!q.isEmpty()) {
        Host tmp;
        q.dequeue(tmp, cost);
        for (int i = 0; i < tmp.num_conn; ++i) {
            int it = hosts[tmp.id].connected_ids[i];
            if (hosts[it].visit == Host::NOTVISITED) {
                q.enqueue(hosts[it], cost);
                hosts[it].visit = Host::VISITED;
                hosts[it].comp = comp;
            }
        }
        num++;
    }
}

void HostNet::BFSDisplayAverageClusteringCoefficients(const int &index, double &cc) {
    Host hub = hosts[index];
    int edge = 0;
    for (int i = 0; i < hub.num_conn; ++i) {
        Host cur = hosts[hub.connected_ids[i]];
        for (int j = 0; j < hub.num_conn; ++j) {
            for (int k = 0; k < cur.num_conn; ++k) {
                if (hub.id != hosts[cur.connected_ids[k]].id &&
                    hosts[hub.connected_ids[j]].id == hosts[cur.connected_ids[k]].id ) {
                    edge++;
                }
            }
        }
    }
    edge /= 2;
    if (hub.num_conn > 1)
        cc += (2 * edge) / ((hub.num_conn) * (hub.num_conn - 1));
}

void HostNet::BFSDisplayMostCentralHosts() {

}

int HostNet::findIndex(const string &hname) {
    int name_index = NOTFOUND;
    for (int i = 0; i < HOST_SIZE && name_index == NOTFOUND; i++) {
        if (hosts[i].name == hname)
            name_index = i;     // hname is found in graph and index updated
    }
    return name_index;
}