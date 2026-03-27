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

struct Giocatore {
    char nome[15];
    char scacchiera[30][10] = {'O'};
    int vittorie;
};

void menu();
void scelta(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi);
void iniziaGioco(int naviDa6 ,int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Giocatore ordinePlayer);
void gestioneNavi(int nNavi6, int nNavi5, int nNavi4, int nNavi3, int nNavi2, int sommaNavi);
void classifica();
void esci();
void posizionamentoNavi(int naveN);

/*
struct Giocatore {
    char username[15];
    scacchiera[]

}
*/

void menu () {
    int naviDa6 = 1, naviDa5 = 2, naviDa4 = 2, naviDa3 = 3, naviDa2 = 3, totNavi = 39;
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
    scelta(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi);
}

void scelta(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi) {
    int selezione, newPos = 7, oldPos = 7;
    Giocatore player1, player2;

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
                      iniziaGioco(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, player1);
                      break;
                  case 9 :
                      clearScreen(MAIN_BG, MAIN_FG);
                      setColor(MAIN_BG, MAIN_FG);
                      gestioneNavi(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi);
                      break;
                  case 11 :
                      clearScreen(MAIN_BG, MAIN_FG);
                      setColor(MAIN_BG, MAIN_FG);
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

void posizionamentoNavi (int naveN) {
    displayMessage(char nave[naveN],)

}

void iniziaGioco(int naviDa6 ,int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Giocatore ordinePlayer) {
    int selezione, newPos = 6, oldPos = 6;
    char comando;

    for(int i = 0; i < 30; i++) {
        for(int j = 0; j < 10; j++) {
            ordinePlayer.scacchiera[i][j] = 'O';
        }
    }
    scacchiere();
    gotoXY(66,3);
    cout << "Inserire navi:";
    gotoXY(66,6);
    cout << "Navi da 6:  " << naviDa6;
    gotoXY(66,8);
    cout << "Navi da 5:  " << naviDa5;
    gotoXY(66,10);
    cout << "Navi da 4:  " << naviDa4;
    gotoXY(66,12);
    cout << "Navi da 3:  " << naviDa4;
    gotoXY(66,14);
    cout << "Navi da 2:  " << naviDa2;

    do {
        gotoXY(65,oldPos);
        cout << " ";
        gotoXY(65,newPos);
        cout << ">";
        oldPos = newPos;
        oldPos = newPos;
        comando = _getch();
        if(comando == SU && newPos != 6) {
            newPos -= 2;
        }else if(comando == SU && newPos == 6) {
            newPos = 14;
        }
        if(comando == GIU && newPos != 14) {
            newPos += 2;
        }else if(comando == GIU && newPos == 14){
            newPos = 6;
        }
        if(comando == ENTER) {
                switch:
                    case 6:
                        posizionamentoNavi(6);
                        break;


        }
    }while (totNavi != 0);



}

void gestioneNavi(int nNavi6, int nNavi5, int nNavi4, int nNavi3, int nNavi2, int sommaNavi) {
    int selezione, newPosX = 30, oldPosX = 30, newPosY = 6, oldPosY = 6;
    char comando;

    cout << "	      BATTAGLIA NAVALE                Data : ";
    displayToday();
    gotoXY(0,1);
    cout << "===============================================================" << endl;
    gotoXY(7,3);
    cout << "NAVI DISPONIBILI:    (Premere ESC per uscire)";
    gotoXY(12,6);
    cout << "Navi da 6 :        -   " << nNavi6 << "   +";
    gotoXY(12,8);
    cout << "Navi da 5 :        -   " << nNavi5 << "   +";
    gotoXY(12,10);
    cout << "Navi da 4 :        -   " << nNavi4 << "   +";
    gotoXY(12,12);
    cout << "Navi da 3 :        -   " << nNavi3 << "   +";
    gotoXY(12,14);
    cout << "Navi da 2 :        -   " << nNavi2 << "   +";


    gotoXY(0,17);
    cout << "===============================================================" << endl;
    do {
        gotoXY(oldPosX,oldPosY);
        cout << " ";
        gotoXY(newPosX,newPosY);
        cout << ">";
        oldPosX = newPosX;
        oldPosY = newPosY;
        comando = _getch();
        if(comando == SU && newPosY != 6) {
            newPosY -= 2;
        }else if(comando == SU && newPosY == 6) {
            newPosY = 14;
        }
        if(comando == GIU && newPosY != 14) {
            newPosY += 2;
        }else if(comando == GIU && newPosY == 14){
            newPosY = 6;
        }
        if(comando == DX && newPosX != 38){
            newPosX = 38;
        }else if(comando == DX && newPosX == 38) {
            newPosX = 30;
        }
        if(comando == SX && newPosX != 30){
            newPosX = 30;
        }else if(comando == SX && newPosX == 30) {
            newPosX = 38;
        }
        if(comando == ENTER) {
            selezione = newPosY;
            switch (selezione) {
                case 6 :
                    if (newPosX == 30) {
                        if(nNavi6 > 0) {
                            nNavi6--;
                            sommaNavi = sommaNavi - 6;
                            gotoXY(35,6);
                            cout << nNavi6;
                            if (nNavi6 < 10) {
                                gotoXY(36,6);
                                cout << " ";
                            }
                        }
                    }else if(newPosX == 38) {
                        sommaNavi = sommaNavi + 6;
                        if(sommaNavi < 300) {
                            nNavi6++;
                            gotoXY(35,6);
                            cout << nNavi6;
                        }else{
                            sommaNavi = sommaNavi - 6;
                        }
                    }
                    break;
                case 8 :
                    if (newPosX == 30) {
                        if(nNavi5 > 0) {
                            nNavi5--;
                            sommaNavi = sommaNavi - 5;
                            gotoXY(35,8);
                            cout << nNavi5;
                            if (nNavi5 < 10) {
                                gotoXY(36,8);
                                cout << " ";
                            }
                        }
                    }else if(newPosX == 38) {
                        sommaNavi = sommaNavi + 5;
                        if(sommaNavi < 300) {
                            nNavi5++;
                            gotoXY(35,8);
                            cout << nNavi5;
                        }else{
                            sommaNavi = sommaNavi - 5;
                        }
                    }
                    break;
                case 10 :
                    if (newPosX == 30) {
                        if(nNavi4 > 0) {
                            nNavi4--;
                            sommaNavi = sommaNavi - 4;
                            gotoXY(35,10);
                            cout << nNavi4;
                            if (nNavi4 < 10) {
                                gotoXY(36,10);
                                cout << " ";
                            }
                        }
                    }else if(newPosX == 38) {
                        sommaNavi = sommaNavi + 4;
                        if(sommaNavi < 300) {
                            nNavi4++;
                            gotoXY(35,10);
                            cout << nNavi4;
                        }else{
                            sommaNavi = sommaNavi - 4;
                        }
                    }
                    break;
                case 12 :
                    if (newPosX == 30) {
                        if(nNavi3 > 0) {
                            nNavi3--;
                            sommaNavi = sommaNavi - 3;
                            gotoXY(35,12);
                            cout << nNavi3;
                            if (nNavi3 < 10) {
                                gotoXY(36,12);
                                cout << " ";
                            }
                        }
                    }else if(newPosX == 38) {
                        sommaNavi = sommaNavi + 3;
                        if(sommaNavi < 300) {
                            nNavi3++;
                            gotoXY(35,12);
                            cout << nNavi3;
                        }else{
                            sommaNavi = sommaNavi - 3;
                        }
                    }
                    break;
                case 14 :
                    if (newPosX == 30) {
                        if(nNavi2 > 0) {
                            nNavi2--;
                            sommaNavi = sommaNavi - 2;
                            gotoXY(35,14);
                            cout << nNavi2;
                            if (nNavi2 < 100) {
                                gotoXY(37,14);
                                cout << " ";
                            }
                            if (nNavi2 < 10) {
                                gotoXY(36,14);
                                cout << " ";
                            }
                        }
                    }else if(newPosX == 38) {
                        sommaNavi = sommaNavi + 2;
                        if(sommaNavi < 300) {
                            nNavi2++;
                            gotoXY(35,14);
                            cout << nNavi2;
                        }else{
                            sommaNavi = sommaNavi - 2;
                        }
                    }
                    break;

            }
        }
        }while (comando != ESC);



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
