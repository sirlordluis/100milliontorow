#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_MOVES_LENGTH 2048

typedef struct {
    char event[MAX_LINE_LENGTH];
    char site[MAX_LINE_LENGTH];
    char date[MAX_LINE_LENGTH];
    char white[MAX_LINE_LENGTH];
    char black[MAX_LINE_LENGTH];
    char result[MAX_LINE_LENGTH];
    char whiteElo[MAX_LINE_LENGTH];
    char blackElo[MAX_LINE_LENGTH];
    char termination[MAX_LINE_LENGTH];
} ChessGame;

void extractGameData(FILE *pgnFile, ChessGame *game) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), pgnFile) != NULL) {
        if (strstr(line, "[Event ") != NULL) {
            sscanf(line, "[Event \"%[^\"]\"]", game->event);
        } else if (strstr(line, "[Site ") != NULL) {
            sscanf(line, "[Site \"%[^\"]\"]", game->site);
        } else if (strstr(line, "[Date ") != NULL) {
            sscanf(line, "[Date \"%[^\"]\"]", game->date);
        } else if (strstr(line, "[White ") != NULL) {
            sscanf(line, "[White \"%[^\"]\"]", game->white);
        } else if (strstr(line, "[Black ") != NULL) {
            sscanf(line, "[Black \"%[^\"]\"]", game->black);
        } else if (strstr(line, "[Result ") != NULL) {
            sscanf(line, "[Result \"%[^\"]\"]", game->result);
        } else if (strstr(line, "[WhiteElo ") != NULL) {
            sscanf(line, "[WhiteElo \"%[^\"]\"]", game->whiteElo);
        }else if (strstr(line, "[BlackElo ") != NULL) {
            sscanf(line, "[BlackElo \"%[^\"]\"]", game->blackElo);
        }else if (strstr(line, "[Termination ") != NULL) {
            sscanf(line, "[Termination \"%[^\"]\"]", game->termination);
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.pgn>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *pgnFile = fopen(argv[1], "r");
    FILE *csvFile = fopen("partidas.csv", "w");

    if (pgnFile == NULL || csvFile == NULL) {
        perror("Error al abrir los archivos");
        return EXIT_FAILURE;
    }

    ChessGame game;

    fprintf(csvFile, "Event,Site,Date,White,Black,Result,WhiteElo,BlackElo,Termination\n");

    while (!feof(pgnFile)) {
        memset(&game, 0, sizeof(ChessGame));
        extractGameData(pgnFile, &game);
        fprintf(csvFile, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n",
                game.event, game.site, game.date, game.white, game.black, game.result, game.whiteElo,game.blackElo,game.termination);
    }

    fclose(pgnFile);
    fclose(csvFile);

    return 0;
}
