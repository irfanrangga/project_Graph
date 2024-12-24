#include "Graph_Header.h"

int main() {
    Map G;
    int harga;
    string tujuanAkhir = "Budapest";

    buildMap(G);

    cout << "= = = = = = = = = = = Graph Test = = = = = = = = = = =" << endl;
    cout << "\nPeta Koneksi Antar Kota: " << endl;
    printMap(G);

    cout << "\n= = = = = = = = = = = Cari Kota = = = = = = = = = = =" << endl;
    string kotaID, destID, cariHarga;
    cout << "Masukkan nama kota asal: ";
    cin >> kotaID;
    cout << "Masukkan nama kota tujuan: ";
    cin >> destID;
    cout << findKota(G, kotaID) << endl;
    cout << findDest(G, destID) << endl;
    cout << calculateRoutebyRange(G) << endl;
    cout << calculateRoutebyCost(G) << endl;
/*
    int indeg = indegree(G, kotaID);
    int outdeg = outdegree(G, kotaID);
    int deg = degree(G, kotaID);

    cout << "Indegree kota " << kotaID << " = " << indeg << endl;
    cout << "Outdegree kota " << kotaID << " = " << outdeg << endl;
    cout << "Degree kota " << kotaID << " = " << deg << endl;
*/
    return 0;
}
