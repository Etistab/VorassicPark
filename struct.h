#define QUIT    0
#define RULES   1
#define SERPENT 2
#define PIEUVRE 3
#define PARAM   4

typedef struct game{
    short n;
    int board[26][26];
    int numberOfPlayers;
    int scoreJ;
    int scoreR;
    int scoreB;
    int scoreV;
    char random;
    int wallLevel;
    int negLevel;
}game;
