#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio2.h>
#include "console.h"

int startSDL();

int main(int argc, char **argv) {
    char choice;

    printf("Activer le mode graphique ?\n");
    printf("O = Oui\nN = Non\n");
    scanf("%c", &choice);
    system("cls");

    if(choice == 'O' || choice == 'o'){
        startSDL();
    }
    else{
        consoleMode();
    }

    return 0;
}

#include <SDL.h>
#include "graphic.h"

int startSDL(){
    game vorassic_struct;

    boardSetup(&vorassic_struct);
    graphicMode();

    return 0;
}
