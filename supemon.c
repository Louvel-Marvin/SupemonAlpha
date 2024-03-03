#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "SUPEMON_GAME.h"

void initializeSupemon(Supemon* supemon, char* name, int level, int experience, int current_hp, int max_hp, int attack, int base_attack, int defense, int base_defense, int evasion, int base_evasion, int accuracy, int base_accuracy, int speed) {
    if (supemon == NULL || name == NULL) {
        printf("Error: Invalid pointers provided to initializeSupemon.\n");
        return;
    }

    strncpy(supemon->name, name, sizeof(supemon->name) - 1);
    supemon->name[sizeof(supemon->name) - 1] = '\0'; // Ensure null termination

    supemon->level = level;
    supemon->experience = experience;
    supemon->current_hp = current_hp;
    supemon->max_hp = max_hp;
    supemon->attack = attack;
    supemon->baseAttack = base_attack;
    supemon->defense = defense;
    supemon->baseDefense = base_defense;
    supemon->evasion = evasion;
    supemon->baseEvasion = base_evasion;
    supemon->accuracy = accuracy;
    supemon->baseAccuracy = base_accuracy;
    supemon->speed = speed;
}

void chooseInitialSupemon(Player* player) {
    printf("Choose your initial Supemon:\n");
    printf("1. Supmander\n2. Supasaur\n3. Supirtle\n\n");
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    switch (choice) {
        case 1:
        case 2:
        case 3:
            initializeSupemon(&player->supemons[0], choice == 1 ? "Supmander" : choice == 2 ? "Supasaur" : "Supirtle", 1, 0, choice == 1 ? 10 : choice == 2 ? 9 : 11, choice == 1 ? 10 : choice == 2 ? 9 : 11, 1, 1, 1, 1, 1, 1, 2, 2, 1);
            break;
        default:
            printf("Invalid choice. Choosing Supmander by default.\n");
            choice = 1; // Default to Supmander
            initializeSupemon(&player->supemons[0], "Supmander", 1, 0, 10, 10, 1, 1, 1, 1, 1, 1, 2, 2, 1);
    }

    initializeSupemonMoves(&player->supemons[0], choice);
    printf("\nYou have chosen: %s\n", player->supemons[0].name);
}

void initializeSupemonMoves(Supemon* supemon, int supemonType) {
    if (supemon == NULL) {
        printf("Error: Supemon pointer is NULL.\n");
        return;
    }

    Move* moves = NULL;
    int numMoves = 0;

    switch (supemonType) {
        case 1: { // Supmander
            static Move supmanderMoves[] = {{"Scratch", 3}, {"Grawl", 1}};
            moves = supmanderMoves;
            numMoves = sizeof(supmanderMoves) / sizeof(Move);
            break;
        }
        case 2: { // Supasaur
            static Move supasaurMoves[] = {{"Pound", 2}, {"Foliage", 1}};
            moves = supasaurMoves;
            numMoves = sizeof(supasaurMoves) / sizeof(Move);
            break;
        }
        case 3: { // Supirtle
            static Move supirtleMoves[] = {{"Pound", 2}, {"Shell", 1}};
            moves = supirtleMoves;
            numMoves = sizeof(supirtleMoves) / sizeof(Move);
            break;
        }
        default:
            printf("Invalid Supemon type. No moves initialized.\n");
            return;
    }

    supemon->numMoves = numMoves;
    int i;
    for ( i = 0; i < numMoves; ++i) {
        supemon->moves[i] = moves[i]; // Direct assignment of Move structure
    }
}
void displaySupemon(Player* player){
    int i;

    for (i = 0; i < player->numSupemons & 6 > i ; i++){
        printf("Supemon: %s\n", player->supemons[i].name);
    }
}
void captureSupemon(Player* player, Supemon* enemy) {
    float captureChance = ((float)(enemy->max_hp - enemy->current_hp) / enemy->max_hp) * 1000; // Ajustez selon la logique de votre jeu
    if (rand() % 100 < captureChance) { // Supposons que captureChance est un pourcentage
        int i;
        for (i = 0; i < 5; i++) {
            if (player->supemons[i].name[0] == '\0') { // Vérifie si l'emplacement est libre
                player->supemons[i] = *enemy;
                printf("You captured %s\n", enemy->name);
                player->numSupemons += 1;
                displaySupemon(player); // Assurez-vous que cette fonction affiche les informations correctes
                return; // Capture réussie, sortie de la fonction
            }
        }
        printf("Your team is full. You cannot capture %s\n", enemy->name);
    } else {                
        displaySupemon(player); // Assurez-vous que cette fonction affiche les informations correctes
        enemyTurn(enemy, &player->supemons[0]);
        printf("You failed to capture the enemy Supemon!\n");
    }
}
void emptySupemon(Player* player){
    int i;
    for (i = 1; i < 5; i++){
        player->supemons[i].name[0] = '\0';
    }
}