#include "Graph_Header.h"
#include <iostream>
using namespace std;

void createKota(string newKotaId, adrKota &v) {
    v = new Kota;
    idKota(v) = newKotaId;
    nextKota(v) = NULL;
    firstDest(v) = NULL;
}

void createDest(string destKotaID, int weight, adrDest &d) {
    d = new Dest;
    destKotaID(d) = destKotaID;
    weight(d) = weight;
    nextDest(d) = NULL;
}

void initMap(Map &G) {
    firstKota(G) = NULL;
}

void addKota(Map &G, string newKotaID) {
    adrKota v;
    createKota(newKotaID, v);

    if (firstKota(G) == NULL) {
        firstKota(G) = v;
    } else {
        adrKota q = firstKota(G);
        while (nextKota(q) != NULL) {
            q = nextKota(q);
        }
        nextKota(q) = v;
    }
}

void addDest(Map &G, string sourceKotaID, string destKotaID, int weight) {
    adrKota sourceKota = firstKota(G);
    while (sourceKota != NULL && idKota(sourceKota) != sourceKotaID) {
        sourceKota = nextKota(sourceKota);
    }

    if (sourceKota == NULL) {
        cout << "Kota " << sourceKotaID << " tidak ditemukan!" << endl;
        return;
    }

    adrDest newDest;
    createDest(destKotaID, weight, newDest);

    if (firstDest(sourceKota) == NULL) {
        firstDest(sourceKota) = newDest;
    } else {
        adrDest temp = firstDest(sourceKota);
        while (nextDest(temp) != NULL) {
            temp = nextDest(temp);
        }
        nextDest(temp) = newDest;
    }
}

void inputDest(Map &G, string sourceKotaID, string tujuanAkhir) {
    string destKotaID;
    int weight;

    cout << "Masukkan destinasi dari kota " << sourceKotaID << " (Format: tujuan bobot), akhiri dengan kota tujuan akhir: " << tujuanAkhir << endl;

    while (true) {
        cout << "Tujuan dan Bobot (contoh: Munich 400): ";
        cin >> destKotaID >> weight;

        addDest(G, sourceKotaID, destKotaID, weight);

        if (destKotaID == tujuanAkhir) {
            cout << "Jalur menuju " << tujuanAkhir << " selesai!" << endl;
            break;
        }
    }
}

void buildMap(Map &G) {
    int jumlahRute;
    string tujuanAkhir;

    cout << "Masukkan tujuan akhir: ";
    cin >> tujuanAkhir;

    cout << "Masukkan jumlah rute: ";
    cin >> jumlahRute;

    for (int i = 1; i <= jumlahRute; i++) {
        string startKota;

        cout << "\nRute " << i << ": Masukkan kota awal: ";
        cin >> startKota;

        addKota(G, startKota);
        inputDest(G, startKota, tujuanAkhir);
    }
}

void printMap(Map &G) {
    adrKota city = firstKota(G);
    int routeNumber = 1;
    while (city != NULL) {
        cout << routeNumber << ". Kota " << idKota(city) << " -> ";
        adrDest dest = firstDest(city);
        while (dest != NULL) {
            cout << destKotaID(dest) << "(" << weight(dest) << ")";
            if (nextDest(dest) != NULL) {
                cout << " -> ";
            }
            dest = nextDest(dest);
        }
        cout << endl;
        city = nextKota(city);
        routeNumber++;
    }
}

int indegree(Map G, string kotaID) {
    int count = 0;
    adrKota kota = G.firstKota;
    while (kota != nullptr) {
        adrDest dest = kota->firstDest;
        while (dest != nullptr) {
            if (dest->destKotaID == kotaID) {
                count++;
            }
            dest = dest->nextDest;
        }
        kota = kota->nextKota;
    }
    return count;
}

int outdegree(Map G, string kotaID) {
    adrKota kota = G.firstKota;
    while (kota != nullptr) {
        if (kota->idKota == kotaID) {
            int count = 0;
            adrDest dest = kota->firstDest;
            while (dest != nullptr) {
                count++;
                dest = dest->nextDest;
            }
            return count;
        }
        kota = kota->nextKota;
    }
    return 0;
}

int degree(Map G, string kotaID) {
    return indegree(G, kotaID) + outdegree(G, kotaID);
}



