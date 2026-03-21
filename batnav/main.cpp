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

void menu();
void scelta();
void iniziaGioco();
void gestioneNavi();
void classifica();
void esci();

struct Giocatore {
    char username[15];
    scacchiera[]


}

void menu () {
    cout << "	      BATTAGLIA NAVALE                Data : ";
    displayToday();
    cout << endl << "===============================================================" << endl;
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
    cout << "===============================================================" << endl;
    scelta();
}

void scelta() {
    int selezione, newPos = 7, oldPos = 7;
    char comando;
    do {
        gotoXY(12,oldPos);
        cout << " ";
        gotoXY(12,newPos);
        cout << ">";
        oldPos = newPos;
        comando = _getch();
        if(comando == SU && newPos != 7) {
            newPos -= 2;
        }else if(comando == SU && newPos == 7) {
            newPos = 13;
        }
        if(comando == GIU && newPos != 13) {
            newPos += 2;
        }else if(comando == GIU && newPos == 13){
            newPos = 7;
        }
        if (comando == ENTER) {
             selezione = newPos;
             switch (selezione) {
                  case 7 :
                      clearScreen(MAIN_BG, MAIN_FG);
                      setColor(MAIN_BG, MAIN_FG);
                      iniziaGioco();
                      break;
                  case 9 :
                      gestioneNavi();
                      break;
                  case 11 :
                      classifica();
                      break;
                  case 13 :
                      esci();
                      break;
              }
        }
    }while (comando != ENTER && comando != ESC);
}

void scacchiere () {
    cout << "	      BATTAGLIA NAVALE                Data : ";
    displayToday();
    gotoXY(0,1);
    cout << "===============================================================" << endl;
    gotoXY(0,2);
    cout << R"(
    0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3
    1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0

A   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
B   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
C   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
D   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
E   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
F   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
G   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
H   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
I   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
J   O O O O O O O O O O O O O O O O O O O O O O O O O O O O O O
)";
    gotoXY(0,17);
    cout << "===============================================================" << endl;

}

void posizioneNavi () {

}

void iniziaGioco() {

    scacchiere ();
}

void gestioneNavi() {

}

void classifica() {

}


void esci() {

}


/*
    analisi tecnica : funzioni usate

    gestione navi
        numero navi predefinito
        dimensioni predefinite
        vuoi modificare
        per ogni nave scegliere le dimensioni

    controlloPosizionamentoNavi
*/


int main() {
    clearScreen(MAIN_BG, MAIN_FG);
    setColor(MAIN_BG, MAIN_FG);
    do {
        menu();
    } while(3 == 100);
    return 0;
}
