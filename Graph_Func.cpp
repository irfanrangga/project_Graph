#include "Graph_Header.h"

adrKota createKota(string newKotaId, adrKota &v) {
    v = new Kota;
    infoKota(v) = newKotaId;
    nextKota(v) = NULL;
    firstDest(v) = NULL;

    return v;
}

adrDest createDest(string destKotaID, int weight, adrDest &d) {
    d = new Dest;
    infoDest(d) = destKotaID;
    weight(d) = weight;
    nextDest(d) = NULL;

    return d;
}

void initMap(Map &G) {
    firstKota(G) = NULL;
}

adrKota findKota(Map G, string kotaID){
    if(firstKota(G) == NULL){
        return NULL;
    } else {
        adrKota p = firstKota(G);
        while(p != NULL){
            if(infoKota(p) == kotaID){
                return p;
            }
            p = nextKota(p);
        }
    }
    return NULL;
}

adrDest findDest(Map G, string destID){
    adrKota pKota = firstKota(G);
    while(pKota != NULL){
        if(firstKota(G) == NULL || firstDest(pKota) == NULL){
            return NULL;
        } else {
            adrDest p = firstDest(pKota);
            while(p != NULL){
                if(infoDest(p) == destID){
                    return p;
                }
                p = nextDest(p);
            }
        }
        pKota = nextKota(pKota);
    }
    return NULL;
}

void addKota(Map &G, string kotaID) {
    adrKota v;
    createKota(kotaID, v);

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
    while (sourceKota != NULL && infoKota(sourceKota) != sourceKotaID) {
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

void buildMap(Map &G) {
    initMap(G);

    addKota(G, "Paris");
    addKota(G, "Strasbourg");
    addKota(G, "Basel");
    addKota(G, "Luxembourg City");
    addKota(G, "Frankfurt");
    addKota(G, "Munich");
    addKota(G, "Innsbruck");
    addKota(G, "Vienna");
    addKota(G, "Budapest");

    addDest(G, "Paris", "Basel", 500);
    addDest(G, "Paris", "Strasbourg", 500);
    addDest(G, "Paris", "Luxembourg City", 370);
    addDest(G, "Luxembourg City", "Frankfurt", 200);
    addDest(G, "Strasbourg", "Munich", 350);
    addDest(G, "Basel", "Innsbruck", 400);
    addDest(G, "Frankfurt", "Vienna", 700);
    addDest(G, "Munich", "Vienna", 400);
    addDest(G, "Innsbruck", "Vienna", 400);
    addDest(G, "Vienna", "Budapest", 240);
}

void findRoutes(Map &G, adrKota currentCity, string end, string path, int totalDistance) {
    if (currentCity == NULL) return;

    path += infoKota(currentCity);
    if (infoKota(currentCity) == end) {
        cout << "Rute: " << path << " | Total Jarak: " << totalDistance << " KM" << endl;
        return;
    }

    adrDest dest = firstDest(currentCity);
    while (dest != NULL) {
        adrKota nextCity = findKota(G, infoDest(dest));
        findRoutes(G, nextCity, end, path + " -> ", totalDistance + weight(dest));
        dest = nextDest(dest);
    }
}

void printMap(Map &G, string start, string end) {
    adrKota startCity = findKota(G, start);
    if (startCity == NULL) {
        cout << "Kota " << start << " tidak ditemukan!" << endl;
        return;
    }

    cout << "Menampilkan semua rute dari " << start << " ke " << end << ":" << endl;
    findRoutes(G, startCity, end, "", 0);
}

int indegree(Map G, string kotaID) {
    int count = 0;
    adrKota kota = G.firstKota;
    while (kota != nullptr) {
        adrDest dest = firstDest(kota);
        while (dest != nullptr) {
            if (infoDest(dest) == kotaID) {
                count++;
            }
            dest = nextDest(dest);
        }
        kota = nextKota(kota);
    }
    return count;
}

int outdegree(Map G, string kotaID) {
    adrKota kota = G.firstKota;
    while (kota != nullptr) {
        if (infoKota(kota) == kotaID) {
            int count = 0;
            adrDest dest = firstDest(kota);
            while (dest != nullptr) {
                count++;
                dest = nextDest(dest);
            }
            return count;
        }
        kota = nextKota(kota);
    }
    return 0;
}

int degree(Map G, string kotaID) {
    return indegree(G, kotaID) + outdegree(G, kotaID);
}

int costPerKilometer(int totalDistance) {
    return (totalDistance / 10) * 22;
}

void calculateRoutebyCost(Map G, adrKota currentCity, string endCity, string path, int totalCost, int &minCost, string &bestPath) {
    if (currentCity == NULL) return;

    path += infoKota(currentCity);

    if (infoKota(currentCity) == endCity) {
        if (totalCost < minCost) {
            minCost = totalCost;
            bestPath = path;
        }
        return;
    }

    adrDest dest = firstDest(currentCity);
    while (dest != NULL) {
        adrKota nextCity = findKota(G, infoDest(dest));
        calculateRoutebyCost(G, nextCity, endCity, path + " -> ", totalCost + costPerKilometer(weight(dest)), minCost, bestPath);
        dest = nextDest(dest);
    }
}

void findCheapestFare(Map G, string startCity, string endCity) {
    adrKota start = findKota(G, startCity);
    if (start == NULL) {
        cout << "Kota " << startCity << " tidak ditemukan!" << endl;
        return;
    }

    adrKota end = findKota(G, endCity);
    if (end == NULL) {
        cout << "Kota " << endCity << " tidak ditemukan!" << endl;
        return;
    }

    int minCost = INT_MAX;
    string bestPath = "";

    cout << "==========================================" << endl;
    cout << "       Pencarian Rute Termurah            " << endl;
    cout << "==========================================" << endl;

    calculateRoutebyCost(G, start, endCity, "", 0, minCost, bestPath);

    if (minCost == INT_MAX) {
        cout << "Tidak ada rute yang tersedia dari " << startCity << " ke " << endCity << "!" << endl;
    } else {
        cout << "Rute termurah ditemukan!" << endl;
        cout << "Rute: " << bestPath << endl;
        cout << "Total biaya: " << minCost << " euro" << endl;
        cout << "==========================================" << endl;
    }
}


void calculateRoutebyDistance(Map G, adrKota currentCity, string endCity, int totalDistance, int &minDistance, string path, string &bestPath) {
    if (currentCity == NULL) return;

    path += infoKota(currentCity);

    if (infoKota(currentCity) == endCity) {
        if (totalDistance < minDistance) {
            minDistance = totalDistance;
            bestPath = path;
        }
        return;
    }

    adrDest dest = firstDest(currentCity);
    while (dest != NULL) {
        adrKota nextCity = findKota(G, infoDest(dest));
        calculateRoutebyDistance(G, nextCity, endCity, totalDistance + weight(dest), minDistance, path + " -> ", bestPath);
        dest = nextDest(dest);
    }
}

void findFastestRoute(Map G, string startCity, string endCity) {
    adrKota start = findKota(G, startCity);
    if (start == NULL) {
        cout << "Kota " << startCity << " tidak ditemukan!" << endl;
        return;
    }

    adrKota end = findKota(G, endCity);
    if (end == NULL) {
        cout << "Kota " << endCity << " tidak ditemukan!" << endl;
        return;
    }

    int minDistance = INT_MAX;
    string bestPath = "";

    cout << "==========================================" << endl;
    cout << "       Pencarian Rute Tercepat            " << endl;
    cout << "==========================================" << endl;

    calculateRoutebyDistance(G, start, endCity, 0, minDistance, "", bestPath);

    if (minDistance == INT_MAX) {
        cout << "Tidak ada rute yang tersedia dari " << startCity << " ke " << endCity << "!" << endl;
    } else {
        cout << "Rute tercepat ditemukan!" << endl;
        cout << "Rute: " << bestPath << endl;
        cout << "Total jarak: " << minDistance << " KM" << endl;
        cout << "==========================================" << endl;
    }
}




void showMenu(){
    cout << "===== PILIH LAYANAN =====" << endl;
    cout << "1. Buat Rute" << endl;
    cout << "2. Cari Kota Asal" << endl;
    cout << "3. Cari Kota Tujuan" << endl;
    cout << "4. Cari Rute Termurah" << endl;
    cout << "5. Cari Rute Tercepat" << endl;
    cout << "6. Tampilkan Semua Rute" << endl;
    cout << "9. Exit" << endl;
    cout << "Pilih Menu: ";
}
