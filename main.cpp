#include "Graph_Header.h"
#include <cstdlib>

int main() {
    Map G;
    int harga, opsi;
    string kotaAsal, kotaTujuan;
    opsi = 0;

    while(opsi != 9){
        showMenu();
        cin >> opsi;
        switch(opsi){
        case 1:
            system("cls");
            cout << "===== MENU BUAT RUTE =====" << endl;
            buildMap(G);
            cout << "Berhasil membuat rute!" << endl;
            cout << endl;
            break;
        case 2:
            system("cls");
            cout << "===== CARI KOTA ASAL =====" << endl;
            cout << "Masukkan nama kota asal yang ingin dicari: ";
            cin >> kotaAsal;
            if(findKota(G, kotaAsal) == NULL){
                cout << "Kota " << kotaAsal << " tidak ditemukan pada kota asal" << endl;
            } else {
                cout << "Kota " << kotaAsal << " ditemukan pada alamat: " << findKota(G, kotaAsal) << endl;
            }
            break;
        case 3:
            system("cls");
            cout << "===== CARI KOTA TUJUAN =====" << endl;
            cout << "Masukkan nama kota tujuan yang ingin dicari: ";
            cin >> kotaTujuan;
            if(findDest(G, kotaTujuan) == NULL){
                cout << "Kota " << kotaTujuan << " tidak ditemukan pada kota tujuan" << endl;
            } else {
                cout << "Kota " << kotaTujuan << " ditemukan pada alamat: " << findDest(G, kotaTujuan) << endl;
            }
            break;
        case 4:
            system("cls");
            cout << "===== CARI RUTE TERMURAH =====" << endl;
            printMap(G);
            cout << endl;
            findCheapestFare(G);
            cout << endl;
            break;
        case 5:
            system("cls");
            cout << "===== CARI RUTE TERCEPAT =====" << endl;
            printMap(G);
            cout << endl;
            findFastestRoute(G);
            cout << endl;
            break;

        case 6:
            system("cls");
            cout << "========== RUTE YANG TERSEDIA ==========" << endl;
            printMap(G);
            cout << endl;
            break;
        }
    }
    cout << "Selamat Tinggal!" << endl;

    return 0;
}
