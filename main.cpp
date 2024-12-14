#include "Graph_Header.h"

int main() {
    Map G;
    string tujuanAkhir = "Budapest";

    initMap(G);

    buildMap(G);

    cout << "\nPeta Koneksi Antar Kota: " << endl;
    printMap(G);


    string kotaID;

    // Test indegree, outdegree, and degree for different cities
    cout << "Masukkan nama kota untuk uji indegree, outdegree, dan degree: ";
    cin >> kotaID;

    int indeg = indegree(G, kotaID);
    int outdeg = outdegree(G, kotaID);
    int deg = degree(G, kotaID);

    cout << "Indegree kota " << kotaID << " = " << indeg << endl;
    cout << "Outdegree kota " << kotaID << " = " << outdeg << endl;
    cout << "Degree kota " << kotaID << " = " << deg << endl;

    return 0;
}
