#include "struct.h"

int menu();

int rules();
void param(game* vorassic_struct);

void setPlayers(game* vorassic_struct);
void boardSetup(game* vorassic_struct);
void createBoard(game* vorassic_struct);

void colorize(char player);
void interLine(game* vorassic_struct);
void printBoard(game* vorassic_struct);
void printScores(game* vorassic_struct);

void choosePosition(game* vorassic_struct, char* x, int* y);
bool isPlayable(game* vorassic_struct, int x, int y, char player, bool pieuvre);
void savePosition(game* vorassic_struct, int x, int y, char player, bool pieuvre);
void play(game* vorassic_struct, char player, bool pieuvre);

bool verifyCasesAround(game* vorassic_struct, int xPos, int yPos, char player, bool pieuvre);
bool canPlay(game* vorassic_struct, char player, bool pieuvre);

int max(int* tab, int length, bool value);
void printWinner(game* vorassic_struct);

void gameStart(game* vorassic_struct, bool pieuvre);

void consoleMode();
