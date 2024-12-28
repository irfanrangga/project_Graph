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

void inputDest(Map &G, string sourceKotaID, string tujuanAkhir) {
    adrKota kotaAsal = firstKota(G);
    adrDest kotaTujuan = firstDest(kotaAsal);
    string destKotaID;
    int weight;

    cout << "Masukkan destinasi dari kota " << sourceKotaID << " (Format: tujuan bobot), akhiri dengan kota tujuan akhir: " << tujuanAkhir << endl;

    while (kotaAsal != NULL) {
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
    string startKota;
    string kotaTujuan = "Budapest";
    initMap(G);
    cout << "Masukkan jumlah rute: ";
    cin >> jumlahRute;

    for (int i = 1; i <= jumlahRute; i++) {
        cout << "\nRute " << i << endl;
        cout << "Masukkan kota asal: ";
        cin >> startKota;
        addKota(G, startKota);
        inputDest(G, startKota, kotaTujuan);
    }
}

void printMap(Map &G) {
    adrKota city = firstKota(G);
    int routeNumber = 1;
    while (city != NULL) {
        cout << routeNumber << ". Kota " << infoKota(city) << " -> ";
        adrDest dest = firstDest(city);
        while (dest != NULL) {
            cout << infoDest(dest) << "(" << weight(dest) << ")";
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

int costPerKilometer(Map G, adrDest p, int price){
    int totalCost = 0;
    totalCost = weight(p) * price;
    return totalCost;
}

void findCheapestFare(Map G) {
    int i = 1, idxRute = 1;
    adrKota p = firstKota(G);
    int cheapestRoute = -1;
    while(p != NULL){
        cout << "Masukkan biaya perjalanan pada rute ke-" << idxRute << endl;
        int tempPrice = calculateRoutebyCost(G, infoKota(p));
        if(cheapestRoute == -1 || tempPrice < cheapestRoute){
            cheapestRoute = tempPrice;
            i++;
        }
        cout << endl;
        idxRute++;
        p = nextKota(p);
    }
    cout << "Rute Termurah berada di rute ke-" << i << " dengan total biaya " << cheapestRoute << " euro" << endl;
}

void findFastestRoute(Map G) {
    int fastRoute = 9999, i = 1;
    adrKota p = firstKota(G);

    while(p != NULL){
        int tempFast = calculateRoutebyDistance(G, infoKota(p));
        if(tempFast < fastRoute){
            fastRoute = tempFast;
            i++;
        }
        p = nextKota(p);
    }

    cout << "Rute tercepat berada di rute ke-" << i << " dengan total jarak " << fastRoute << " Km" << endl;
}

int calculateRoutebyDistance(Map G, string kotaID) {
    int totalJarak = 0;

    adrKota p = findKota(G, kotaID);
    adrDest q = firstDest(p);

    while(q != NULL){
        totalJarak += weight(q);
        q = nextDest(q);
    }
    return totalJarak;
}

int calculateRoutebyCost(Map G, string kotaAsal) {
    int totalBiaya = 0;

    adrKota p = findKota(G, kotaAsal);
    adrDest q = firstDest(p);
    while(p != NULL && q != NULL){
        int harga, hargaTemp;
        cout << "Masukkan biaya perjalanan menuju kota " << infoDest(q) << ": ";
        cin >> harga;
        hargaTemp = costPerKilometer(G, q, harga);
        totalBiaya += hargaTemp;
        q = nextDest(q);
    }
    return totalBiaya;
}

void showMenu(){
    cout << "===== PILIH LAYANAN XXMAP =====" << endl;
    cout << "1. Buat Rute" << endl;
    cout << "2. Cari Kota Asal" << endl;
    cout << "3. Cari Kota Tujuan" << endl;
    cout << "4. Cari Rute Termurah" << endl;
    cout << "5. Cari Rute Tercepat" << endl;
    cout << "6. Tampilkan Semua Rute" << endl;
    cout << "9. Exit" << endl;
    cout << "Pilih Menu: ";
}
