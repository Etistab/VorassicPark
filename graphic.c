#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include "struct.h"
#define WIDTH 700
#define HEIGHT 700

void createBoardSDL(SDL_Surface* screen, int size){
    int i, j;
    SDL_Surface* boardBackground;
    SDL_Rect position;

    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            boardBackground = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);
            position.x = (WIDTH / 2) - (size * 10) + j*20;
            position.y = (HEIGHT / 2) - (size * 10) + i*20;

            if(i%2 == 0){
                if(j%2 == 0)SDL_FillRect(boardBackground, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
                else SDL_FillRect(boardBackground, NULL, SDL_MapRGB(screen->format, 0, 127, 0));
            }
            else{
                if(j%2 != 0)SDL_FillRect(boardBackground, NULL, SDL_MapRGB(screen->format, 0, 255, 0));
                else SDL_FillRect(boardBackground, NULL, SDL_MapRGB(screen->format, 0, 127, 0));
            }
            SDL_BlitSurface(boardBackground, NULL, screen, &position);
        }
    }

    SDL_Flip(screen);
    SDL_FreeSurface(boardBackground);
}

void SDL_Start(){
    if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL
            fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
            exit(EXIT_FAILURE);
    }
}

void loadScreen(SDL_Surface* screen){
    SDL_Surface* background = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_Rect position;
    position.x = 0;
    position.y = 0;

    if (screen == NULL) {
        fprintf(stderr, "Erreur de chargement du mode video: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(background, NULL, SDL_MapRGB(screen->format, 35, 35, 35));
    SDL_BlitSurface(background, NULL, screen, &position);
    SDL_Flip(screen);
}

void pause(){
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void graphicMode(game* vorassic_struct){
    SDL_Start();
    SDL_Surface *screen = NULL;

    SDL_WM_SetIcon(SDL_LoadBMP("img/logo.bmp"), NULL);
    SDL_WM_SetCaption("Vorassic Park", NULL);

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    loadScreen(screen);

    createBoardSDL(screen, vorassic_struct->n);

    pause();
    SDL_Quit();
}
