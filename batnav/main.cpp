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

/*
    int selezione;
    do {
        gotoXY(32,5);
        cin >> selezione;
    } while (selezione<0 || selezione>4);
*/

void scelta(int posizioneSceltaVecchia) {
    int posizioneSceltaNuova = posizioneSceltaVecchia;
    char comando;
    int i = 7;
    int z = 7;
    do {
        gotoXY(12,z);
        cout << " ";
        gotoXY(12,i);
        cout << "x";
        z = i;
        comando = _getch();
        if(comando == SU && i != 7) {
            i -= 2;
        }else if(comando == SU && i == 7) {
            i = 13;
        }
        if(comando == GIU && i != 13) {
            i += 2;
        }else if(comando == GIU && i == 13){
            i = 7;
        }
    }while (comando != ENTER && comando != ESC);
}
void menu (int posizioneScelta) {
    cout << "	      BATTAGLIA NAVALE            Data : ";
    displayToday();
    cout << endl << "===========================================================" << endl;
    gotoXY(12,5);
    cout << "Selezione opzione :";
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
    scelta(posizioneScelta);
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
    } while(posizioneIniziale == 100);
    return 0;
}
