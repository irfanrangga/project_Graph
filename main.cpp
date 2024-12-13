#include "Graph_Header.h"

int main()
{
    Map G;
    buildMap(G);

    adrKota v = firstKota(G);
    cout << endl;
    while(v != nullptr){
        cout << idKota(v) << " " << endl;
        v = nextKota(v);
    }

    cout << endl;
    return 0;
}
