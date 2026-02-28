#include <iostream>

using namespace std;

/*
    analisi tecnica : funzioni usate

    menu
        gestione navi
        inizio gioco
        classifica
        esci

    gestione navi
        numero navi predefinito      5 navi
        dimensioni predefinite
        vuoi modificare
        per orgni nave scegliere le dimensioni

    controlloPosizionamentoNavi



*/

int main()
{
    cout << "..." << endl;
    int nNaviPred = 3, lungN1Predef = 2, lungN2Predef = 3, lungN3Predef = 4;
    cout << "Il numero di navi predefiniuto e' : " << nNaviPred << endl;
    cout << "Vuoi modificare il numero delle navi, la loro lunghezza o entrambe le cose ? " << endl;
    cout << "1. Numero navi" << endl << "2. Lunghezza navi " << endl << "3. Entrambe" << endl << "4. Vanno bene le impostazioni predefinite" << endl;

    return 0;
}
