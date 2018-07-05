#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio2.h>
#include "struct.h"

int menu(){
    short choice;
    printf("\n========== MENU ==========\n");
    printf("Fais ton choix !\n");
    printf("%d_Regles\n", RULES);
    printf("%d_Mode serpent\n", SERPENT);
    printf("%d_Mode pieuvre\n", PIEUVRE);
    printf("%d_Parametres\n", PARAM);
    printf("%d_Quitter\n", QUIT);
    scanf("%hi", &choice);
    system("cls");
    return choice;
}

int rules(){
    short conti ;

    printf("=========== REGLES DU JEU ===========\n\n");
    textcolor(LIGHTBLUE);
    printf("2 a 4 joueurs s'affrontent sur un plateau de 5 a 26 cases\n");
    printf("A tour de role les joueurs doivent capturer des cases qui valent entre -3 et 9 points\n");
    textcolor(YELLOW);
    printf("\n\t>>>> Mode Serpent <<<<\n\n");
    printf("Un serpent ne peut capturer la case que si:\n");
    printf("\t - Elle est libre\n");
    printf("\t - Elle est adjacente a la derniere case capture\n");
    printf("Les mouvements en diagonales sont interdits\n");
    textcolor(LIGHTRED);
    printf("\n\t>>>> Mode Pieuvre <<<<\n\n");
    printf("Une pieuvre ne peut capturer la case que si:\n");
    printf("\t - Elle est libre\n");
    printf("\t - Elle est adjacente a une case deja capture\n");
    printf("Les mouvements en diagonales sont autorises\n");
    textcolor(LIGHTGREEN);
    printf("\n\t>>>> Fin de la partie <<<<\n\n");
    printf("Le but est d\'avoir le maximum de points\n");
    printf("La partie s'arrete lorsque plus aucun joueur ne peut jouer\n");
    textcolor(LIGHTGRAY);
    printf("\nEntrez un chiffre pour retourner au menu ou 0 pour quitter\n");
    scanf("%hi", &conti);

    if(conti == 0){
        return 0;
    }
    else{
        return 9;
    }
}
void param(game* vorassic_struct){
    printf("Remplir la grille aleatoirement ?\n O/N\n");
    fflush(stdin);
    scanf("%c", &vorassic_struct->random);

    printf("Taux d'apparition des murs (plus la valeure est eleve moins il y a de murs)\n");
    printf("Valeur actuelle: %d\n", vorassic_struct->wallLevel);
    scanf("%d", &vorassic_struct->wallLevel);
    while(vorassic_struct->wallLevel<2 || vorassic_struct->wallLevel>100){
        printf("Choisissez une valeur entre 2 et 100\n");
        scanf("%d", &vorassic_struct->wallLevel);
        system("cls");
    }

    printf("Taux d'apparition des cases negatives (plus la valeure est eleve moins il y a de cases negatives)\n");
    printf("Valeur actuelle: %d\n", vorassic_struct->negLevel);
    scanf("%d", &vorassic_struct->negLevel);
    while(vorassic_struct->negLevel<2 || vorassic_struct->negLevel>100){
        printf("Choisissez une valeur entre 2 et 100\n");
        scanf("%d", &vorassic_struct->negLevel);
        system("cls");
    }
}

void setPlayers(game* vorassic_struct){
    printf("Combien y a t-il de joueurs ? (de 2 a 4 joueurs)\n");
    scanf("%d", &vorassic_struct->numberOfPlayers);
    system("cls");

    while(vorassic_struct->numberOfPlayers<2 || vorassic_struct->numberOfPlayers>4){
        printf("Il peut y avoir que de 2 a 4 joueurs\n");
        scanf("%d", &vorassic_struct->numberOfPlayers);
        system("cls");
    }

}
void boardSetup(game* vorassic_struct){
    printf("Choissisez la taille de la grille (entre 5 et 26 cases)\n");
    scanf("%hu", &vorassic_struct->n);
    system("cls");

    while(vorassic_struct->n<5 || vorassic_struct->n>26){
        printf("Entrez une taille entre 5 et 26\n");
        scanf("%hu", &vorassic_struct->n);
        system("cls");
    }
}
void createBoard(game* vorassic_struct){
    short i, j, wall, neg;
    boardSetup(vorassic_struct);
    setPlayers(vorassic_struct);
    srand(time(NULL));

    for(i = 0; i < vorassic_struct->n; i++){
        for(j = 0; j < vorassic_struct->n; j++){
            wall = rand()%vorassic_struct->wallLevel;
            neg = rand()%vorassic_struct->negLevel;
            if(vorassic_struct->random == 'O' || vorassic_struct->random == 'o'){
                vorassic_struct->board[i][j]= rand()%9;
            }
            else{
                vorassic_struct->board[i][j]=j+i;
                if(vorassic_struct->board[i][j] > vorassic_struct->n - 1){
                    vorassic_struct->board[i][j] -= 2*(vorassic_struct->board[i][j] - vorassic_struct->n+1);
                }
                if(vorassic_struct->board[i][j] > 9){
                    vorassic_struct->board[i][j] = 9;
                }
            }
            if(neg == 1)
                vorassic_struct->board[i][j] = -rand()%3;
            if(wall == 1)
                vorassic_struct->board[i][j] = 'W';
        }
    }
    vorassic_struct->board[0][0] = 'J';
    vorassic_struct->board[vorassic_struct->n - 1][vorassic_struct->n - 1] = 'R';
    if(vorassic_struct->numberOfPlayers >= 3)
        vorassic_struct->board[0][vorassic_struct->n-1] = 'B';
    if(vorassic_struct->numberOfPlayers == 4)
        vorassic_struct->board[vorassic_struct->n-1][0] = 'V';
}

void colorize(char player){
    switch (player){
        case 'J':
            textcolor(YELLOW);
            break;
        case 'j':
            textcolor(YELLOW);
            break;
        case 'R':
            textcolor(LIGHTRED);
            break;
        case 'r':
            textcolor(LIGHTRED);
            break;
        case 'B':
            textcolor(LIGHTBLUE);
            break;
        case 'b':
            textcolor(LIGHTBLUE);
            break;
        case 'V':
            textcolor(LIGHTGREEN);
            break;
        case 'v':
            textcolor(LIGHTGREEN);
            break;
        case 'W':
            textcolor(BLACK);
            break;
    }
}
void interLine(game* vorassic_struct){
    short i;

    printf("\n   ");
    for(i = 0; i<(vorassic_struct->n)*4; i++){
        printf("--");
    }
}
void printBoard(game* vorassic_struct){
    short i = 0, j = 0;

    printf("  ||  ");
    for(i = 65; i < 65+vorassic_struct->n; i++){
        printf("%c\t ||  ", i);
    }
    interLine(vorassic_struct);
    printf("\n");
    for(i = 0; i<vorassic_struct->n; i++){
        if(i < 10){
            printf("%d ||  ", i);
        }
        else{
            printf("%d||  ", i);
        }
        for(j = 0; j<vorassic_struct->n; j++){
            if(vorassic_struct->board[i][j] > 26){
                colorize(vorassic_struct->board[i][j]);
                printf("%c   ", vorassic_struct->board[i][j]);
                textcolor(LIGHTGRAY);
                printf("||  ");
            }
            else if(vorassic_struct->board[i][j] < 0){
                textcolor(DARKGRAY);
                printf("%d  ", vorassic_struct->board[i][j]);
                textcolor(LIGHTGRAY);
                printf("||  ");
            }
            else
                printf("%d   ||  ", vorassic_struct->board[i][j]);
        }
        interLine(vorassic_struct);
        printf("\n");
    }
}
void printScores(game* vorassic_struct){
    printf("Score de J: %d \t\t\t\t Score de R: %d\n", vorassic_struct->scoreJ, vorassic_struct->scoreR);
    if(vorassic_struct->numberOfPlayers >= 3){
        printf("Score de B: %d ", vorassic_struct->scoreB);
        if(vorassic_struct->numberOfPlayers == 4)
            printf("\t\t\t\t Score de V: %d", vorassic_struct->scoreV);
        printf("\n");
    }
    printf("\n");
}

void choosePosition(game* vorassic_struct, char* x, int* y){
    fflush(stdin);
    printf("Entrez la colonne a jouer en x:");
    scanf("%c", x);
    while(*x < 65 || *x >= 65+vorassic_struct->n){
        fflush(stdin);
        printf("Entrez une valeur correcte de x (lettre majuscule attendue): ");
        scanf("%c", x);
        printf("\n");
    }
    *x -= 65;

    printf("Entrez la ligne a jouer en y:");
    scanf("%d", y);
    while(*y < 0 || *y >= vorassic_struct->n){
        fflush(stdin);
        printf("Entrez une valeur correcte de y (nombre attendu): ");
        scanf("%d", y);
        printf("\n");
    }
}
bool isPlayable(game* vorassic_struct, int x, int y, int player, bool pieuvre){
    int i, j, xPos, yPos;
    if(vorassic_struct->board[y][x] > 26){ // Si la case n'est pas libre
        printf("La case est deja prise :(\n");
        return false;
    }
    for(i = 0; i<vorassic_struct->n; i++){
        for(j = 0; j<vorassic_struct->n; j++){
            if(vorassic_struct->board[i][j] == player){
                yPos = i;
                xPos = j;
                if(pieuvre &&
                   (x == xPos+1 || x == xPos-1 || x == xPos) &&
                   (y == yPos+1 || y == yPos-1 || y == yPos)){
                    return true;
                }
            }
        }
    }
    if((x == xPos+1 || x == xPos-1 || x == xPos) &&
       (y == yPos+1 || y == yPos-1 || y == yPos)){
        if((x == xPos + 1 || x == xPos - 1) &&
           (y == yPos + 1 || y == yPos -1)){ // Si c'est un mouvement en diagonale
            printf("Interdit de jouer en diagonale !\n");
            return false;
        }
        return true;
    }
    return false;
}
void savePosition(game* vorassic_struct, int x, int y, char player, bool pieuvre){
    int i, j;
    if(!pieuvre){
        for(i = 0; i<vorassic_struct->n; i++){
            for(j = 0; j<vorassic_struct->n; j++){
                if(vorassic_struct->board[i][j] == player){
                    vorassic_struct->board[i][j] += 32;
                }
            }
        }
    }
    if(player == 'J')
        vorassic_struct->scoreJ += vorassic_struct->board[y][x];
    else if(player == 'R')
        vorassic_struct->scoreR += vorassic_struct->board[y][x];
    else if(player == 'B')
        vorassic_struct->scoreB += vorassic_struct->board[y][x];
    else if(player == 'V')
        vorassic_struct->scoreV += vorassic_struct->board[y][x];

    vorassic_struct->board[y][x] = player;
}
void play(game* vorassic_struct, char player, bool pieuvre){
    char x;
    int y;

    colorize(player);
    printf("\n>>> Au tour de %c ! <<<\n\n", player);
    choosePosition(vorassic_struct, &x, &y);
    while(isPlayable(vorassic_struct, x, y, player, pieuvre) == false){
        printf("Reessaye !\n");
        choosePosition(vorassic_struct, &x, &y);
    }
    savePosition(vorassic_struct, x, y, player, pieuvre);
}

bool verifyCasesAround(game* vorassic_struct, int xPos, int yPos, char player, bool pieuvre){
    int i, j;
    for(i = xPos-1; i <= xPos + 1; i++){
        for(j = yPos-1; j <= yPos + 1; j++){
            if(vorassic_struct->board[i][j] <= 26){
                if(!pieuvre && (i == xPos + 1 || i == xPos - 1) &&
                   (j == yPos + 1 || j == yPos -1)){
                    continue;
                }
                return true;
            }
        }
    }
    return false;
}
bool canPlay(game* vorassic_struct, char player, bool pieuvre){
    int i, j, xPos, yPos;
    for(i = 0; i < vorassic_struct->n; i ++){
        for(j = 0; j < vorassic_struct->n; j++){
            if(vorassic_struct->board[i][j] == player){
                xPos = i;
                yPos = j;
                if(verifyCasesAround(vorassic_struct, xPos, yPos, player, pieuvre))
                    return true;
            }
        }
    }
    printf("%c ne peut plus jouer !\n", player);
    return false;
}

int max(int* tab, int length, bool value){
    int max = tab[0];
    int iMemo = 0;
    int i;

    for(i = 1; i < length; i++){
        if(tab[i] > max){
            max = tab[i];
            iMemo = i;
        }
    }

    if(value)
        return max;
    return iMemo;
}
void printWinner(game* vorassic_struct){
    char winner;
    int scores[4] = {vorassic_struct->scoreJ, vorassic_struct->scoreR, vorassic_struct->scoreB, vorassic_struct->scoreV};

    winner = max(scores, 4, false);

    switch(winner){
        case 0:
            winner = 'J';
            break;
        case 1:
            winner = 'R';
            break;
        case 2:
            winner = 'B';
            break;
        case 3:
            winner = 'V';
            break;
    }
    printf("%c gagne la partie !!!\n", winner);
}

void gameStart(game* vorassic_struct, bool pieuvre){
    int i;
    createBoard(vorassic_struct);
    for(i = 0; canPlay(vorassic_struct, 'J', pieuvre) || canPlay(vorassic_struct, 'R', pieuvre) ||
    canPlay(vorassic_struct, 'B', pieuvre) || canPlay(vorassic_struct, 'V', pieuvre); i++){
        system("cls");
        textcolor(LIGHTGRAY);
        if(pieuvre)
            printf("===== MODE PIEUVRE =====\n\n");
        else
            printf("===== MODE SERPENT =====\n\n");
        printScores(vorassic_struct);
        printBoard(vorassic_struct);
        if(i == 0 && canPlay(vorassic_struct, 'J', pieuvre))
            play(vorassic_struct, 'J', pieuvre);
        else if(i == 1 && canPlay(vorassic_struct, 'R', pieuvre)){
            play(vorassic_struct, 'R', pieuvre);
            if(vorassic_struct->numberOfPlayers == 2)
                i = -1;
        }
        else if(i == 2 && canPlay(vorassic_struct, 'B', pieuvre)){
            play(vorassic_struct, 'B', pieuvre);
            if(vorassic_struct->numberOfPlayers == 3)
                i = -1;
        }
        else if(i == 3 && canPlay(vorassic_struct, 'V', pieuvre)){
            play(vorassic_struct, 'V', pieuvre);
            if(vorassic_struct->numberOfPlayers == 4)
                i = -1;
        }
        if(i>3)
            i = -1;
    }
    system("cls");
    if(pieuvre)
        printf("===== MODE PIEUVRE =====\n\n");
    else
        printf("===== MODE SERPENT =====\n\n");
    printScores(vorassic_struct);
    printBoard(vorassic_struct);
    printWinner(vorassic_struct);
}

void consoleMode(){
    short choice;
    game vorassic_struct;
    vorassic_struct.negLevel = 6;
    vorassic_struct.wallLevel = 6;

    do{
        vorassic_struct.scoreJ = 0;
        vorassic_struct.scoreR = 0;
        vorassic_struct.scoreB = 0;
        vorassic_struct.scoreV = 0;
        choice = menu();

        switch (choice) {
            case RULES:
                choice = rules();
                system("cls");
                break;
            case SERPENT:
                gameStart(&vorassic_struct, false);
                break;
            case PIEUVRE:
                gameStart(&vorassic_struct, true);
                break;
            case PARAM:
                param(&vorassic_struct);
                break;
        }
    }while(choice != 0);
}
