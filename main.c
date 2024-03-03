#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "SUPEMON_GAME.h"

// Declaration de la fonction clearInputBuffer
void clearInputBuffer();

// Fonction principale
int main() {
    Player player;
    srand(time(NULL)); // Initialiser le generateur de nombres aleatoires
    startGame(&player); // Commencez le jeu en initialisant le joueur et en choisissant un Supemon
    emptySupemon(&player); // Initialiser les Supemons du joueur

    mainMenu(&player); // Affichez le menu principal et permettez au joueur de choisir des actions

    return 0;
}

// Afficher le menu principal
void mainMenu(Player* player) {
    int choice;
    do {
        printf("\nMain Menu\n");
        printf("1. Start a random fight\n");
        printf("2. Enter the shop\n");
        printf("3. Save game\n");
        printf("4. Load game\n");
        printf("5. Quit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1:
                launchRandomFight(player);
                break;
            case 2: {
                Item* items = initializeShopItems(); 
                int numItems = MAX_ITEMS;
                enterShop(player, items, numItems);
                break;
            }
            case 3:
                saveGame(player);
                break;
            case 4:
                loadGame(player);
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }
    } while (choice != 5);
}

// Commencer le jeu en initialisant le joueur et en choisissant un Supemon initial
void startGame(Player* player) {
    printf("Welcome to Supemon!\n");
    printf("Enter your name: ");
    fgets(player->name, 20, stdin);
    printf("\n");
    player->name[strcspn(player->name, "\n")] = 0; // Supprimez le caractere de nouvelle ligne de l'entree

    player->supcoins = 100; // Initialiser le nombre de Supcoins du joueur
    player->numSupemons = 0; // Initialiser le nombre de Supemons du joueur
    chooseInitialSupemon(player); // Permettre au joueur de choisir son Supemon initial

    initRandom(); // Initialiser le generateur de nombres aleatoires
}