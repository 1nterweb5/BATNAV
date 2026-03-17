#include <iostream>
#include <conio.h>
#include "curcolor.h"

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define SU  72
#define DX  77
#define GIU  80
#define SX 75

using namespace std;

const int MAIN_BG = 9;
const int MAIN_FG = 14;
const int INPUT_FG = 15;
const int INFO_FG = 5;
const int ERROR_FG = 4;

void menu (int posizioneScelta) {
    cout << "	      BATTAGLIA NAVALE            Data : ";
    displayToday();
    cout << endl << "===========================================================" << endl;
    gotoXY(12,5);
    cout << "Selezione opzione :";
    gotoXY(12, posizioneScelta);
    cout << "X" << endl;
    gotoXY(14,7);
    cout << "1. Inizia Gioco";
    gotoXY(14,9);
    cout << "2. Gestione Navi";
    gotoXY(14,11);
    cout << "3. Classifica";
    gotoXY(14,13);
    cout << "4. Esci";
    gotoXY(0,17);
    cout << "===========================================================" << endl;

    int scelta(posizioneScelta);
}
    /*
        int selezione;
        do {
            gotoXY(32,5);
            cin >> selezione;
        } while (selezione<0 || selezione>4);
    */

int scelta(int posizioneSceltaVecchia) {
    int comando, posizioneSceltaNuova = posizioneSceltaVecchia;
    comando = _getch();
    do {
        switch(comando) {
            case SU :
                if (posizioneSceltaVecchia == 7) {
                    posizioneSceltaNuova = 13;
                    menu(posizioneSceltaNuova);
                } else {
                    posizioneSceltaNuova = posizioneSceltaNuova + 2;
                    menu(posizioneSceltaNuova);
                }
            case GIU :
                if (posizioneSceltaVecchia == 13) {
                    posizioneSceltaNuova = 7;
                    menu(posizioneSceltaNuova);
                } else {
                    posizioneSceltaNuova = posizioneSceltaNuova - 2;
                    menu(posizioneSceltaNuova);
                }

        }
    }while (comando != ENTER);
}
/*
    } while(comando == ENTER);
    switch (selezione) {
        case 1 :
            //iniziaGioco();
            break;
        case 2 :
            //gestioneNavi();
            break;
        case 3 :
            //classifica();
            break;
        case 4 :
            //esci();
            break;
    }


}

void iniziaGioco() {

}

void gestioneNavi() {

}

classifica() {

}


esci() {
    return 0;
}
*/

/*
    ⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬⚬
    ●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●●
    analisi tecnica : funzioni usate

    menu
        inizio gioco
        gestione navi
        classifica
        esci

    gestione navi
        numero navi predefinito
        dimensioni predefinite
        vuoi modificare
        per orgni nave scegliere le dimensioni

    controlloPosizionamentoNavi
*/


int main() {
    int posizioneIniziale = 7;
    clearScreen(MAIN_BG, MAIN_FG);
    setColor(MAIN_BG, MAIN_FG);
    do {
        menu(posizioneIniziale);
    }while(posizioneIniziale == 100);
    return 0;
}
