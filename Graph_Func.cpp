#include "Graph_Header.h"

void createKota(string newKotaId, adrKota &v)
{
    v = new Kota;
    idKota(v) = newKotaId;
    nextKota(v) = NULL;
    firstDestination(v) = NULL;
}

void initMap(Map &G)
{
    firstKota(G) = NULL;
}

void addKota(Map &G, string newKotaID)
{
    adrKota v;
    createKota(newKotaID, v);

    if(firstKota(G) == NULL){
        firstKota(G) = v;
    } else {
        adrKota q = firstKota(G);
        while(nextKota(q) != NULL){
            q = nextKota(q);
        }
        nextKota(q) = v;
    }
}

void buildMap(Map &G)
{
    string inputKota;
    initMap(G);

    cin >> inputKota;
    while(inputKota != "-"){
        addKota(G, inputKota);
        cin >> inputKota;
    }
}
