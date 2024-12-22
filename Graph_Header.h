#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#define firstKota(G) G.firstKota
#define infoKota(v) v->infoKota
#define nextKota(v) v->nextKota
#define firstDest(v) v->firstDest
#define infoDest(e) e->infoDest
#define weight(e) e->weight
#define nextDest(e) e->nextDest
using namespace std;

//Kota = Vertex
typedef struct Kota *adrKota;
//Dest = Edge
typedef struct Dest *adrDest;

struct Kota {
    string infoKota;
    adrKota nextKota;
    adrDest firstDest;
};

struct Dest {
    string infoDest;
    int weight;
    adrDest nextDest;
};

struct Map {
    adrKota firstKota;
};

adrKota createKota(string newKotaId, adrKota &v);
adrDest createDest(string destKotaID, int weight, adrDest &d);
void initMap(Map &G);
adrKota findKota(Map G, string kotaID);
adrDest findDest(Map G, string destID);
void addKota(Map &G, string newKotaID);
void addDest(Map &G, string sourceKotaID, string destKotaID, int weight);
void inputDests(Map &G, string sourceKotaID, string tujuanAkhir);
void buildMap(Map &G);
void printMap(Map &G);
int indegree(Map G, string kotaID);
int outdegree(Map G, string kotaID);
int degree(Map G, string kotaID);
int costPerKilometer(Map G, string kotaID, int price);
//void findFastestRoute(Map G);
void findCheapestFare(Map G);
//int caculateRoute(Map G);
#endif
