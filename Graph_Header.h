#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#define firstKota(G) G.firstKota
#define idKota(v) v->idKota
#define nextKota(v) v->nextKota
#define firstDestination(v) v->firstDestination
#define destKotaID(e) e->destKotaID
#define weight(e) e->weight
#define nextDestination(e) e->nextDestination
using namespace std;

//Kota = Vertex
typedef struct Kota *adrKota;
//Destination = Edge
typedef struct Destination *adrDestination;

struct Kota {
    string idKota;
    adrKota nextKota;
    adrDestination firstDestination;
};

struct Destination {
    string destKotaID;
    int weight;
    adrDestination nextDestination;
};

struct Map {
    adrKota firstKota;
};

void createKota(string newKotaID, adrKota &v);
void initMap(Map &G);
void addKota(Map &G, string newKotaID);
void buildMap(Map &G);
//void printMap(Map &G);
//void findFastestRoute(Map G);
//void findCheapestFare(Map G);
//int caculateRoute(Map G);
#endif
