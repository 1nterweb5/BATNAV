#include <iostream>
#include <conio.h>
#include "curcolor.h"
#include <chrono>

#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define SPACE 32
#define SU  72
#define DX  77
#define GIU  80
#define SX 75

#define COLOR_ACQUA 3
#define COLOR_NAVE_ATTIVA 13
#define COLOR_NAVE_FISSA 4
#define RED 12
#define LIGHTBLUE 9

using namespace std;
using Clock = chrono::high_resolution_clock;
using TimePoint = chrono::time_point<Clock>;

const int MAIN_BG = 9;
const int MAIN_FG = 14;
const int MAX_CLASSIFICA = 10;

struct Record {
    char nome[50];
    int punti;
    double tempo;
};

struct Giocatore
{
    char nome[15];
    char scacchiera[10][30];
    int vittorie;
    int punti;
};

void menu(int n6, int n5, int n4, int n3, int n2, int tot, Record storico[], int &vinti);
void scelta(int n6, int n5, int n4, int n3, int n2, int tot, Record storico[], int &vinti);
void gestioneNavi(int n6, int n5, int n4, int n3, int n2, int tot, Record storico[], int &vinti);
void iniziaGioco(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Giocatore &p1, Giocatore &p2, Record storico[], int &vinti);
void classifica(Record lista[], int numRecord);
void salvaInClassifica(Record storico[], int &vinti, Giocatore &vincitore, double tempo);
void esci();
void scacchiere();
void preparaFlotta(int n6, int n5, int n4, int n3, int n2, int tot, Giocatore &ordinePlayer);
void posizionamentoNavi(int nave, Giocatore &player, int &quantitaDisponibile);
void stampoNavi(int nave, int rotazione, int x, int y);
bool eseguiAttacco(Giocatore &attaccante, Giocatore &difensore, int totNavi);
void visualizzaRisultatiFinali(Giocatore p1, Giocatore p2);

TimePoint timer_start() {
    return Clock::now();
}

double timer_stop(TimePoint start) {
    TimePoint end = Clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

int main()
{
    int naviDa6 = 1, naviDa5 = 2, naviDa4 = 2, naviDa3 = 3, naviDa2 = 3, totNavi = 39;
    Record storicoVincitori[MAX_CLASSIFICA];
    int quantiVinti = 0;

    clearScreen(MAIN_BG, MAIN_FG);
    setColor(MAIN_BG, MAIN_FG);

    do
    {
        menu(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, storicoVincitori, quantiVinti);
    }
    while(true);

    return 0;
}

void menu(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Record storicoVincitori[], int &quantiVinti)
{
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
    scelta(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, storicoVincitori, quantiVinti);
}

void scelta(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Record storicoVincitori[], int &quantiVinti)
{
    int selezione, newPos = 7, oldPos = 7;
    Giocatore player1, player2;
    char comando;

    do
    {
        gotoXY(12, oldPos);
        cout << " ";
        gotoXY(12, newPos);
        cout << ">";
        oldPos = newPos;

        comando = _getch();

        if(comando == SU)
        {
            newPos = (newPos == 7) ? 13 : newPos - 2;
        }
        else if(comando == GIU)
        {
            newPos = (newPos == 13) ? 7 : newPos + 2;
        }

        if (comando == ENTER)
        {
            selezione = newPos;
            switch (selezione)
            {
            case 7: // INIZIA GIOCO
                clearScreen(MAIN_BG, MAIN_FG);

                gotoXY(10, 5);
                cout << "Inserisci nome Giocatore 1: ";
                cin >> player1.nome;
                gotoXY(10, 7);
                cout << "Inserisci nome Giocatore 2: ";
                cin >> player2.nome;
                iniziaGioco(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, player1, player2, storicoVincitori, quantiVinti);
                setColor(MAIN_BG, MAIN_FG);
                clearScreen(MAIN_BG, MAIN_FG);
                menu(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, storicoVincitori, quantiVinti);
                break;

            case 9: // GESTIONE NAVI
                clearScreen(MAIN_BG, MAIN_FG);
                gestioneNavi(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, storicoVincitori, quantiVinti);
                break;

            case 11: // CLASSIFICA
                clearScreen(MAIN_BG, MAIN_FG);
                classifica(storicoVincitori, quantiVinti);
                clearScreen(MAIN_BG, MAIN_FG);
                menu(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, totNavi, storicoVincitori, quantiVinti);
                break;

            case 13: // ESCI
                esci();
                break;
            }
        }
    }
    while (comando != ESC);
}

void gestioneNavi(int nNavi6, int nNavi5, int nNavi4, int nNavi3, int nNavi2, int sommaNavi, Record storicoVincitori[], int &quantiVinti)
{
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
    do
    {
        gotoXY(oldPosX,oldPosY);
        cout << " ";
        gotoXY(newPosX,newPosY);
        cout << ">";
        oldPosX = newPosX;
        oldPosY = newPosY;
        comando = _getch();
        if(comando == SU && newPosY != 6)
        {
            newPosY -= 2;
        }
        else if(comando == SU && newPosY == 6)
        {
            newPosY = 14;
        }
        if(comando == GIU && newPosY != 14)
        {
            newPosY += 2;
        }
        else if(comando == GIU && newPosY == 14)
        {
            newPosY = 6;
        }
        if(comando == DX && newPosX != 38)
        {
            newPosX = 38;
        }
        else if(comando == DX && newPosX == 38)
        {
            newPosX = 30;
        }
        if(comando == SX && newPosX != 30)
        {
            newPosX = 30;
        }
        else if(comando == SX && newPosX == 30)
        {
            newPosX = 38;
        }
        if(comando == ENTER)
        {
            selezione = newPosY;
            switch (selezione)
            {
            case 6 :
                if (newPosX == 30)
                {
                    if(nNavi6 > 0)
                    {
                        nNavi6--;
                        sommaNavi = sommaNavi - 6;
                        gotoXY(35,6);
                        cout << nNavi6;
                        if (nNavi6 < 10)
                        {
                            gotoXY(36,6);
                            cout << " ";
                        }
                    }
                }
                else if(newPosX == 38)
                {
                    sommaNavi = sommaNavi + 6;
                    if(sommaNavi < 300)
                    {
                        nNavi6++;
                        gotoXY(35,6);
                        cout << nNavi6;
                    }
                    else
                    {
                        sommaNavi = sommaNavi - 6;
                    }
                }
                break;
            case 8 :
                if (newPosX == 30)
                {
                    if(nNavi5 > 0)
                    {
                        nNavi5--;
                        sommaNavi = sommaNavi - 5;
                        gotoXY(35,8);
                        cout << nNavi5;
                        if (nNavi5 < 10)
                        {
                            gotoXY(36,8);
                            cout << " ";
                        }
                    }
                }
                else if(newPosX == 38)
                {
                    sommaNavi = sommaNavi + 5;
                    if(sommaNavi < 300)
                    {
                        nNavi5++;
                        gotoXY(35,8);
                        cout << nNavi5;
                    }
                    else
                    {
                        sommaNavi = sommaNavi - 5;
                    }
                }
                break;
            case 10 :
                if (newPosX == 30)
                {
                    if(nNavi4 > 0)
                    {
                        nNavi4--;
                        sommaNavi = sommaNavi - 4;
                        gotoXY(35,10);
                        cout << nNavi4;
                        if (nNavi4 < 10)
                        {
                            gotoXY(36,10);
                            cout << " ";
                        }
                    }
                }
                else if(newPosX == 38)
                {
                    sommaNavi = sommaNavi + 4;
                    if(sommaNavi < 300)
                    {
                        nNavi4++;
                        gotoXY(35,10);
                        cout << nNavi4;
                    }
                    else
                    {
                        sommaNavi = sommaNavi - 4;
                    }
                }
                break;
            case 12 :
                if (newPosX == 30)
                {
                    if(nNavi3 > 0)
                    {
                        nNavi3--;
                        sommaNavi = sommaNavi - 3;
                        gotoXY(35,12);
                        cout << nNavi3;
                        if (nNavi3 < 10)
                        {
                            gotoXY(36,12);
                            cout << " ";
                        }
                    }
                }
                else if(newPosX == 38)
                {
                    sommaNavi = sommaNavi + 3;
                    if(sommaNavi < 300)
                    {
                        nNavi3++;
                        gotoXY(35,12);
                        cout << nNavi3;
                    }
                    else
                    {
                        sommaNavi = sommaNavi - 3;
                    }
                }
                break;
            case 14 :
                if (newPosX == 30)
                {
                    if(nNavi2 > 0)
                    {
                        nNavi2--;
                        sommaNavi = sommaNavi - 2;
                        gotoXY(35,14);
                        cout << nNavi2;
                        if (nNavi2 < 100)
                        {
                            gotoXY(37,14);
                            cout << " ";
                        }
                        if (nNavi2 < 10)
                        {
                            gotoXY(36,14);
                            cout << " ";
                        }
                    }
                }
                else if(newPosX == 38)
                {
                    sommaNavi = sommaNavi + 2;
                    if(sommaNavi < 300)
                    {
                        nNavi2++;
                        gotoXY(35,14);
                        cout << nNavi2;
                    }
                    else
                    {
                        sommaNavi = sommaNavi - 2;
                    }
                }
                break;

            }
        }
        if (comando == ESC)
        {
            clearScreen(MAIN_BG, MAIN_FG);
            setColor(MAIN_BG, MAIN_FG);
            menu(nNavi6, nNavi5, nNavi4, nNavi3, nNavi2, sommaNavi, storicoVincitori, quantiVinti);
        }
    }
    while (comando != ESC || comando != ENTER);



}

void classifica(Record lista[], int numRecord)
{
    clearScreen(MAIN_BG, MAIN_FG);
    gotoXY(20, 5);
    cout << "=== CLASSIFICA MIGLIORI GIOCATORI ===";

    if (numRecord == 0) {
        gotoXY(20, 8);
        cout << "Nessun dato salvato";
    } else {
        for (int i = 0; i < numRecord; i++) {
            gotoXY(20, 8 + i);
            cout << i + 1 << ". " << lista[i].nome
                 << " | Punti: " << lista[i].punti
                 << " | Tempo: " << lista[i].tempo << "s";
        }
    }

    gotoXY(20, 22);
    cout << "Premi ESC per tornare al menu";
    while(_getch() != ESC);
}

void esci()
{
    clearScreen(0, 7);
    cout << "Grazie per aver giocato a Battaglia Navale! A presto." << endl;
    exit(0);
}

void scacchiere ()
{
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

void iniziaGioco(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Giocatore &p1, Giocatore &p2, Record storico[], int &vinti) {
    p1.punti = 0;
    p2.punti = 0;
    p1.vittorie = 0;
    p2.vittorie = 0;

    int nNaviEffettive = (naviDa6 + naviDa5 + naviDa4 + naviDa3 + naviDa2);

    clearScreen(MAIN_BG, MAIN_FG);
    gotoXY(10, 10);
    cout << "Turno di " << p1.nome << ". Premi un tasto per posizionare le tue navi...";
    _getch();
    preparaFlotta(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, nNaviEffettive, p1);

    clearScreen(MAIN_BG, MAIN_FG);
    gotoXY(10, 10);
    cout << p1.nome << " ha completato il piazzamento!";
    gotoXY(10, 12);
    cout << "Ora tocca a " << p2.nome << ". Passagli la tastiera e premi un tasto...";
    _getch();

    preparaFlotta(naviDa6, naviDa5, naviDa4, naviDa3, naviDa2, nNaviEffettive, p2);

    bool partitaFinita = false;
    int turno = 1;

    TimePoint t_inizio = timer_start();

    while (!partitaFinita) {
        clearScreen(MAIN_BG, MAIN_FG);
        gotoXY(10, 10);

        if (turno == 1) {
            cout << "TURNO DI ATTACCO: " << p1.nome;
            gotoXY(10, 12);
            cout << "Premi un tasto per mirare...";
            _getch();

            partitaFinita = eseguiAttacco(p1, p2, totNavi);

            if (partitaFinita) break;
            turno = 2;
        }
        else {
            cout << "TURNO DI ATTACCO: " << p2.nome;
            gotoXY(10, 12);
            cout << "Premi un tasto per mirare...";
            _getch();

            partitaFinita = eseguiAttacco(p2, p1, totNavi);

            if (partitaFinita) break;
            turno = 1;
        }

        clearScreen(MAIN_BG, MAIN_FG);
        gotoXY(10, 10);
        cout << "Fine turno. Passa la tastiera all'altro giocatore...";
        _getch();
    }

    double durataSecondi = timer_stop(t_inizio);

    visualizzaRisultatiFinali(p1, p2);

    gotoXY(5, 1);
    setColor(MAIN_BG, 14);
    cout << "========================================" << endl;
    gotoXY(5, 3);

    if (turno == 1) {
        cout << "VITTORIA PER: " << p1.nome << "!!!";
        if (vinti < MAX_CLASSIFICA) {
            for(int i = 0; i < 49; i++) {
                storico[vinti].nome[i] = p1.nome[i];
                if(p1.nome[i] == '\0') break;
            }
            storico[vinti].punti = totNavi;
            storico[vinti].tempo = durataSecondi;
            vinti++;
        }
    }
    else {
        cout << "VITTORIA PER: " << p2.nome << "!!!";
        if (vinti < MAX_CLASSIFICA) {
            for(int i = 0; i < 49; i++) {
                storico[vinti].nome[i] = p2.nome[i];
                if(p2.nome[i] == '\0') break;
            }
            storico[vinti].punti = totNavi;
            storico[vinti].tempo = durataSecondi;
            vinti++;
        }
    }

    gotoXY(5, 5);
    cout << "Tempo totale: " << durataSecondi << " secondi.";
    gotoXY(5, 7);
    cout << "========================================";

    gotoXY(5, 9);
    cout << "Premi un tasto per tornare al menu...";
    _getch();
}

void preparaFlotta(int naviDa6, int naviDa5, int naviDa4, int naviDa3, int naviDa2, int totNavi, Giocatore &ordinePlayer) {
    clearScreen(MAIN_BG, MAIN_FG);

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 30; j++) {
            ordinePlayer.scacchiera[i][j] = '~';
        }
    }

    scacchiere();

    int n6 = naviDa6, n5 = naviDa5, n4 = naviDa4, n3 = naviDa3, n2 = naviDa2;
    int tot = totNavi;

    while (tot > 0) {

        gotoXY(66,3);
        cout << "Navi : " << tot << "    ";
        gotoXY(66,6);
        cout << "Navi da 6:  " << n6 << " ";
        gotoXY(66,8);
        cout << "Navi da 5:  " << n5 << " ";
        gotoXY(66,10);
        cout << "Navi da 4:  " << n4 << " ";
        gotoXY(66,12);
        cout << "Navi da 3:  " << n3 << " ";
        gotoXY(66,14);
        cout << "Navi da 2:  " << n2 << " ";

        if (n6 > 0) {
            posizionamentoNavi(6, ordinePlayer, n6);
        } else if (n5 > 0) {
            posizionamentoNavi(5, ordinePlayer, n5);
        } else if (n4 > 0) {
            posizionamentoNavi(4, ordinePlayer, n4);
        } else if (n3 > 0) {
            posizionamentoNavi(3, ordinePlayer, n3);
        } else if (n2 > 0) {
            posizionamentoNavi(2, ordinePlayer, n2);
        }

        tot--;
    }
    setColor(MAIN_BG, MAIN_FG);
    clearScreen(MAIN_BG, MAIN_FG);
}

void disegnaNave(int lungh, int rot, int x, int y, Giocatore &p, bool attiva) {
    for (int i = 0; i < lungh; i++) {
        int curX = (rot == 0) ? x + (i * 2) : x;
        int curY = (rot == 0) ? y : y + i;
        int riga = curY - 6;
        int col = (curX - 4) / 2;

        gotoXY(curX, curY);

        if (attiva) {
            setColor(COLOR_NAVE_ATTIVA, 0);
        } else {
            if (p.scacchiera[riga][col] == 'X') {
                setColor(COLOR_NAVE_FISSA, 0);
            } else {
                setColor(COLOR_ACQUA, 15);
            }
        }
        cout << 'O';
    }
    setColor(COLOR_ACQUA, 15);
}

void posizionamentoNavi(int nave, Giocatore &player, int &quantitaDisponibile) {
    if (quantitaDisponibile <= 0) return;
    int x = 4, y = 6;
    int rotazione = 0;
    bool posizionata = false;
    int comando;

    do {
        setColor(9, 13);

        for (int i = 0; i < nave; i++) {
            int curX = (rotazione == 0) ? x + (i * 2) : x;
            int curY = (rotazione == 0) ? y : y + i;
            gotoXY(curX, curY);
            cout << 'O';
        }

        comando = _getch();
        if (comando == 0 || comando == 224) comando = _getch();

        for (int i = 0; i < nave; i++) {
            int curX = (rotazione == 0) ? x + (i * 2) : x;
            int curY = (rotazione == 0) ? y : y + i;
            int r = curY - 6;
            int c = (curX - 4) / 2;

            gotoXY(curX, curY);
            if (player.scacchiera[r][c] == 'X') {
                setColor(MAIN_BG, 12);
                cout << 'O';
            } else {
                setColor(MAIN_BG, 15);
                cout << 'O';
            }
        }

        if (comando == SX && x > 4) x -= 2;
        if (comando == DX) {
            if (rotazione == 0 && x < 4 + (29 - nave + 1) * 2) x += 2;
            else if (rotazione == 1 && x < 62) x += 2;
        }
        if (comando == SU && y > 6) y--;
        if (comando == GIU) {
            if (rotazione == 0 && y < 15) y++;
            else if (rotazione == 1 && y < 6 + (10 - nave)) y++;
        }
        if (comando == 'r' || comando == 'R' || comando == SPACE) {
            if (rotazione == 0 && y <= 6 + (10 - nave)) rotazione = 1;
            else if (rotazione == 1 && x <= 4 + (30 - nave) * 2) rotazione = 0;
        }

        if (comando == 13) {
            int riga = y - 6;
            int col = (x - 4) / 2;
            bool collisione = false;

            for (int i = 0; i < nave; i++) {
                int r = (rotazione == 0) ? riga : riga + i;
                int c = (rotazione == 0) ? col + i : col;
                if (player.scacchiera[r][c] == 'X') collisione = true;
            }

            if (!collisione) {
                for (int i = 0; i < nave; i++) {
                    int r = (rotazione == 0) ? riga : riga + i;
                    int c = (rotazione == 0) ? col + i : col;
                    player.scacchiera[r][c] = 'X';


                    gotoXY((rotazione == 0) ? x + (i * 2) : x, (rotazione == 0) ? y : y + i);
                    setColor(9, 12);
                    cout << 'O';
                }
                quantitaDisponibile--;
                posizionata = true;
            }
        }

    } while (!posizionata);
}

void stampoNavi (int nave, int rotazione, int x, int y) {
    if (rotazione == 0) {
        for (int i = 0; i < nave; i++) {
            gotoXY(x, y);
            cout << 'O';
            x++;
            cout << ' ';
            x++;
        }
    }else if (rotazione == 1) {
        for (int i = 0; i < nave; i++) {
            gotoXY(x, y);
            cout << 'O';
            y++;
        }
    }
}

bool eseguiAttacco(Giocatore &attaccante, Giocatore &difensore, int totNavi) {
    int x = 4, y = 6;
    char comando;
    bool colpoEffettuato = false;

    setColor(MAIN_BG, MAIN_FG);
    clearScreen(MAIN_BG, MAIN_FG);
    scacchiere();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 30; j++) {
            if (difensore.scacchiera[i][j] == 'H') {
                gotoXY(4 + (j * 2), 6 + i);
                setColor(MAIN_BG, 12); cout << "X";
            } else if (difensore.scacchiera[i][j] == 'M') {
                gotoXY(4 + (j * 2), 6 + i);
                setColor(MAIN_BG, 11); cout << ".";
            }
        }
    }

    gotoXY(20, 0);
    setColor(MAIN_BG, MAIN_FG);
    cout << "Turno di: " << attaccante.nome;

    do {
        gotoXY(x, y);
        setColor(MAIN_BG, COLOR_NAVE_ATTIVA);
        cout << "+";

        comando = _getch();
        if (comando == 0 || comando == 224) comando = _getch();

        gotoXY(x, y);
        int r_temp = y - 6;
        int c_temp = (x - 4) / 2;

        if(difensore.scacchiera[r_temp][c_temp] == 'H') {
            setColor(MAIN_BG, 12); cout << "X";
        } else if (difensore.scacchiera[r_temp][c_temp] == 'M') {
            setColor(MAIN_BG, 11); cout << ".";
        } else {
            setColor(MAIN_BG, MAIN_FG); cout << "O";
        }

        if (comando == SX && x > 4) x -= 2;
        if (comando == DX && x < 62) x += 2;
        if (comando == SU && y > 6) y--;
        if (comando == GIU && y < 15) y++;

        if (comando == ENTER) {
            int r = y - 6;
            int c = (x - 4) / 2;

            if (difensore.scacchiera[r][c] == 'H' || difensore.scacchiera[r][c] == 'M') {
                gotoXY(10, 18); cout << "Hai gia' sparato qui! Riprova.";
                _getch();
                gotoXY(10, 18); cout << "                             ";
            } else {
                gotoXY(x, y);
                if (difensore.scacchiera[r][c] == 'X') {
                    setColor(MAIN_BG, 12); cout << "X";
                    difensore.scacchiera[r][c] = 'H';
                    attaccante.vittorie++;
                    gotoXY(10, 18); cout << "COLPITO! Premi un tasto...";
                } else {
                    setColor(MAIN_BG, 11); cout << ".";
                    difensore.scacchiera[r][c] = 'M';
                    gotoXY(10, 18); cout << "ACQUA... Premi un tasto...";
                }
                colpoEffettuato = true;
                _getch();
            }
        }
    } while (!colpoEffettuato);

    return (attaccante.vittorie == totNavi);
}

void visualizzaRisultatiFinali(Giocatore p1, Giocatore p2) {
    setColor(MAIN_BG, MAIN_FG);
    clearScreen(MAIN_BG, MAIN_FG);

    gotoXY(25, 1);
    setColor(MAIN_BG, 14);
    cout << "--- RIEPILOGO BATTAGLIA FINALE ---";

    gotoXY(5, 3);
    setColor(MAIN_BG, MAIN_FG);
    cout << "Difesa di " << p1.nome << " (Cosa ha colpito l'avversario):";

    for (int i = 0; i < 10; i++) {
        gotoXY(5, 5 + i);
        for (int j = 0; j < 30; j++) {
            char cella = p1.scacchiera[i][j];
            if (cella == 'H') {
                setColor(MAIN_BG, RED);
                cout << "X ";
            } else if (cella == 'M') {
                setColor(MAIN_BG, 11);
                cout << ". ";
            } else if (cella == 'X') {
                setColor(MAIN_BG, 10);
                cout << "O ";
            } else {
                setColor(MAIN_BG, 3);
                cout << "~ ";
            }
        }
    }

    _getch();
    clearScreen(MAIN_BG, MAIN_FG);

    gotoXY(5, 3);
    setColor(MAIN_BG, MAIN_FG);
    cout << "Difesa di " << p2.nome << " (Cosa ha colpito l'avversario):";

    for (int i = 0; i < 10; i++) {
        gotoXY(5, 5 + i);
        for (int j = 0; j < 30; j++) {
            char cella = p2.scacchiera[i][j];
            if (cella == 'H') {
                setColor(MAIN_BG, RED);
                cout << "X ";
            } else if (cella == 'M') {
                setColor(MAIN_BG, 11);
                cout << ". ";
            } else if (cella == 'X') {
                setColor(MAIN_BG, 10);
                cout << "O ";
            } else {
                setColor(MAIN_BG, 3);
                cout << "~ ";
            }
        }
    }
    setColor(MAIN_BG, MAIN_FG);
    _getch();
    clearScreen(MAIN_BG, MAIN_FG);
}

void salvaInClassifica(Giocatore &vincitore, int punteggio) {
    clearScreen(MAIN_BG, MAIN_FG);
    setColor(MAIN_BG, 14);

    gotoXY(10, 10);
    cout << "COMPLIMENTI " << vincitore.nome << "!";
    gotoXY(10, 12);
    cout << "Hai vinto la partita e sei stato salvato in classifica.";
    _getch();
}
