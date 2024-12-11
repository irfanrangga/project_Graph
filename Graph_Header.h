#define GRAPH_H_INCLUDED
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
using namespace std;

typedef struct Kota *adrKota;
typedef struct Destination *adrDestination;

struct Destination {
    string destKotaID;
    int weight;
    Destination* nextDestination;
};

struct Kota {
    string idKota;
    Kota* nextKota;
    Destination* firstDestination;
};

struct Map {
    Kota* firstKota;
};

void createKota(string newKotaID, Kota*& v);
void initMap(Map &G);
void addKota(Map &G, string newKotaID);
void buildMap(Map &G);
void printMap(Map &G);
void findFastestRoute(Map G);
void findCheapestFare(Map G);
int caculateRoute(Map G);
#endif
