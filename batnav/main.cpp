#include <iostream>
#include <conio.h>
#include "curcolor.h"

using namespace std;

const int MAIN_BG = 9;
const int MAIN_FG = 14;
const int INPUT_FG = 15;
const int INFO_FG = 5;
const int ERROR_FG = 4;

int menu() {
    cout << "================================================================================";
    switch

    cout << "================================================================================";


}

void stampaRighe() {
    for (int i=0; i<10; i++) {
        for (int j=0; j<30; j++) {
            cout << "\t" << colonne << endl;
            colonne ++;
        }

    }
}

void displayMainLayout() {
    int righe [30] = {001, 002, 003} ;
    char colonne = 'A';
    clearScreen(MAIN_BG, MAIN_FG);
    setColor(MAIN_BG, MAIN_FG);
    gotoXY(16,0);
    // 16 = COLONNA DALLA QUALE PARTE LA LETTERA C -1
    cout << "Battaglia Navale                    - Data: ";
    displayToday();
    gotoXY(0,1);
    cout << "================================================================================";
    gotoXY(0,3);
    cout << "  ";
    for (int j=0; j<10; j++) {

    }
    /*for (int i=0; i<10; i++) {
        for (int j=0; j<30; j++) {
            cout << "\t" << colonne << endl;
            colonne ++;
        }
    }
    */
    gotoXY(18,7);
    cout << "1. Gestione navi: ";
    gotoXY(19,10);
    cout << ": ";
    gotoXY(0,21);
    cout << "================================================================================";
}


/*
    analisi tecnica : funzioni usate

    menu
        gestione navi
        inizio gioco
        classifica
        esci

    gestione navi
        numero navi predefinito
        dimensioni predefinite
        vuoi modificare
        per orgni nave scegliere le dimensioni

    controlloPosizionamentoNavi



*/

int main()
{
    displayMainLayout();
    return 0;
}
