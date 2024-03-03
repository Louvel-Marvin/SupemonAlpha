#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "SUPEMON_GAME.h"

// Initialiser le generateur de nombres aleatoires
void initRandom() {
    srand(time(NULL));
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void displaySeparator(int length) {
    int i;
    printf("+");
    for (i = 0; i < length; i++) printf("-");
    printf("+");
    printf("\n");
}

void displaySeparatorWithSpace(int length, int space) {
    int i;
    int j;
    for (i = 0; i < length; i++) {
        printf("-");
    }
    for (j = 0; j < space; j++) {
        printf(" ");
    }
    for (i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}
void printTwoFormattedLines(const char* leftBuffer, const char* rightBuffer) {
    int totalLength = 40; // Assurez-vous que cette longueur est suffisante pour vos données.
    int i;
    int j;

    // Imprimez la partie gauche.
    printf("| %s", leftBuffer);
    for ( i = strlen(leftBuffer); i < totalLength; i++) {
        putchar(' ');
    }
    printf("|"); // Bordure de fin pour la partie gauche.

    // Espace entre la gauche et la droite.
    printf("           ");

    // Imprimez la partie droite.
    printf("| %s", rightBuffer);
    for ( j = strlen(rightBuffer); j < totalLength; j++) {
        putchar(' ');
    }
    printf("|\n"); // Bordure de fin pour la partie droite.
}

void displayStatsSideBySide(Player* player, Supemon* enemy) {
    int separatorLength = 34;
    char separator[separatorLength + 1];
    memset(separator, '-', separatorLength);
    separator[separatorLength] = '\0';

    char leftBuffer[100], rightBuffer[100]; // Assurez-vous que ces buffers sont suffisamment grands.

    // Header
    printf("%s     %s\n", separator, separator);

    // Nom du joueur et de l'ennemi
    snprintf(leftBuffer, sizeof(leftBuffer), "%s's %s", player->name, player->supemons[0].name);
    snprintf(rightBuffer, sizeof(rightBuffer), "%s (Enemy)", enemy->name);
    printf("| %-31s|     | %-31s|\n", leftBuffer, rightBuffer);
    displaySeparatorWithSpace(34, 5);

    // HP
    snprintf(leftBuffer, sizeof(leftBuffer), "HP: %2d/%-2d  Lvl: %d", 
             player->supemons[0].current_hp, player->supemons[0].max_hp, player->supemons[0].level);
    snprintf(rightBuffer, sizeof(rightBuffer), "HP: %2d/%-2d  Lvl: %d", 
             enemy->current_hp, enemy->max_hp, enemy->level);
    printf("| %-31s|     | %-31s|\n", leftBuffer, rightBuffer);

    // Atk et Def
    snprintf(leftBuffer, sizeof(leftBuffer), "Atk: %d  Def: %d", 
             player->supemons[0].attack, player->supemons[0].defense);
    snprintf(rightBuffer, sizeof(rightBuffer), "Atk: %d  Def: %d", 
             enemy->attack, enemy->defense);
    printf("| %-31s|     | %-31s|\n", leftBuffer, rightBuffer);

    // Acc et Eva
    snprintf(leftBuffer, sizeof(leftBuffer), "Acc: %d  Eva: %d", 
             player->supemons[0].accuracy, player->supemons[0].evasion);
    snprintf(rightBuffer, sizeof(rightBuffer), "Acc: %d  Eva: %d", 
             enemy->accuracy, enemy->evasion);
    printf("| %-31s|     | %-31s|\n", leftBuffer, rightBuffer);

    // Footer
    printf("%s     %s\n", separator, separator);
}
