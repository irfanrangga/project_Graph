#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <iostream>
#define firstKota(G) G.firstKota
#define idKota(v) v->idKota
#define nextKota(v) v->nextKota
#define firstDest(v) v->firstDest
#define destKotaID(e) e->destKotaID
#define weight(e) e->weight
#define nextDest(e) e->nextDest
using namespace std;

//Kota = Vertex
typedef struct Kota *adrKota;
//Dest = Edge
typedef struct Dest *adrDest;

struct Kota {
    string idKota;
    adrKota nextKota;
    adrDest firstDest;
};

struct Dest {
    string destKotaID;
    int weight;
    adrDest nextDest;
};

struct Map {
    adrKota firstKota;
};

void createKota(string newKotaId, adrKota &v);
void createDest(string destKotaID, int weight, adrDest &d);
void initMap(Map &G);
void addKota(Map &G, string newKotaID);
void addDest(Map &G, string sourceKotaID, string destKotaID, int weight);
void inputDests(Map &G, string sourceKotaID, string tujuanAkhir);
void buildMap(Map &G);
void printMap(Map &G);
int indegree(Map G, string kotaID);
int outdegree(Map G, string kotaID);
int degree(Map G, string kotaID);
//void findFastestRoute(Map G);
//void findCheapestFare(Map G);
//int caculateRoute(Map G);
#endif
