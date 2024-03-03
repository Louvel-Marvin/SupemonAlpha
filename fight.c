#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "SUPEMON_GAME.h"

void launchRandomFight(Player* player) {
    if (player->numSupemons == 0) {
        printf("You don't have any Supemons to fight with!\n");
        return;
    }

    int randomIndex = rand() % 3; // Generates a random number between 0 and 2 inclusive
    Supemon enemy;
    switch (randomIndex) {
        case 0:
            initializeSupemon(&enemy, "Supmander", 1, 0, 10, 10, 1, 1, 1, 1, 1, 1, 2, 2, 1);
            initializeSupemonMoves(&enemy, 1); // Assuming 1 corresponds to Supmander
            break;
        case 1:
            initializeSupemon(&enemy, "Supasaur", 1, 0, 9, 9, 1, 1, 1, 1, 3, 3, 2, 2, 2);
            initializeSupemonMoves(&enemy, 2); // Assuming 2 corresponds to Supasaur
            break;
        case 2:
            initializeSupemon(&enemy, "Supirtle", 1, 0, 11, 11, 1, 1, 2, 2, 2, 2, 1, 1, 2);
            initializeSupemonMoves(&enemy, 3); // Assuming 3 corresponds to Supirtle
            break;
        default:
            printf("Error: Invalid random index.\n");
            return;
    }
    
    printf("\nYou encountered a %s!\n", enemy.name);
    fight(player, &enemy);
}
 
void fight(Player* player, Supemon* enemy) {
        int Player_Speed;
        Player_Speed = player->supemons[0].speed;
        int Enemy_Speed = enemy->speed;
        int runChance = Player_Speed * 100 / (Player_Speed + Enemy_Speed);

    while (enemy->current_hp > 0 || player->supemons[0].current_hp > 0) { // Ajout d'une condition pour vérifier également la santé du Supémon du joueur
        /*displayPlayerStatsInBattle(player);
        displayCombinedStats(enemy, player);*/

        displayStatsSideBySide(player, enemy);
        
        displayMenuOptions();

        int choice;
        printf("1, 2, 3, 4 or 5: ");
        if(scanf("%d", &choice) != 1) {
            printf("Error: invalid input.\n");
            while(getchar() != '\n'); // nettoyer le buffer d'entrée
            continue; // retour au début de la boucle while
        }

        switch(choice) {
            case 1:
                displayMoveOptions();
                printf("1, 2 or 3: ");
                int move_choice;
                if(scanf("%d", &move_choice) != 1) {
                    printf("Error: invalid input.\n");
                    while(getchar() != '\n'); // nettoyer le buffer d'entrée
                    continue; // retour au début de la boucle while
                }
                if (move_choice == 1 || move_choice == 2) {
                    playerTurn(player, enemy, &player->supemons[0], move_choice);
                    enemyTurn(enemy, &player->supemons[0]);
                }
                break;
            case 2:
                // Implement logic for changing Supemon
                break;
            case 3:
                // Implement logic for using an item
                break;
            case 4:
                captureSupemon(player, enemy);
                break;
            case 5:
                if (rand() % 100 < runChance * 100 ) {
                    printf("You ran away successfully!\n");
                    return;
                } else {
                    printf("You couldn't run away!\n");
                    enemyTurn(enemy, &player->supemons[0]);
                }
                break;
            default:
                printf("Invalid choice. Please enter a number from 1 to 5.\n");
                while(getchar() != '\n'); // nettoyer le buffer d'entrée
                break;
        }
        

    if (player->supemons[0].current_hp <= 0) {
        printf("Your Supémon has fainted!\n");
    } else if (enemy->current_hp <= 0) {
        printf("Enemy Supémon defeated!\n");
    }
}}


void playerTurn(Player* player, Supemon* enemy, Supemon* supemon, int moveChoice) {
    performMove(supemon, enemy, moveChoice);
}

void performMove(Supemon *attacker, Supemon *defender, int move) {
    if (move >= 1 && move <= attacker->numMoves) {
        if (attacker == defender) {
            printf("Invalid move. Attacker and defender cannot be the same Supemon.\n");
            return;
        }

        Move selectedMove = attacker->moves[move - 1];

        // Chance de base pour une attaque de réussir, par exemple 50%
        int baseHitChance = 80;

        // Ajustez la chance de base avec l'accuracy et l'evasion
        int hitChance = baseHitChance + (attacker->accuracy - defender->evasion);

        // Assurez-vous que hitChance ne dépasse pas 100 et n'est pas inférieur à un minimum, par exemple 10%
        hitChance = hitChance > 100 ? 100 : hitChance < 10 ? 10 : hitChance;

        if (rand() % 100 < hitChance) {
            int damage = selectedMove.damage * attacker->baseAttack / defender->baseDefense;
            defender->current_hp -= damage;
            printf("%s used %s!\n", attacker->name, selectedMove.name);
            printf("It dealt %d damage to %s!\n", damage, defender->name);
        } else {
            printf("%s's attack missed!\n", attacker->name);
            return;
        }
    } else {
        printf("Invalid move. Please enter a number from 1 to %d.\n", attacker->numMoves);
        return;
    }
}


void displayMoves(Supemon* supemon) {
    printf("Moves:\n");
    int i;
    for (i = 0; i < supemon->numMoves; i++) {
        printf("%d. %s\n", i + 1, supemon->moves[i].name);
    }
}

void enemyTurn(Supemon* enemy, Supemon* playerSupemon) {
    if (enemy == NULL || playerSupemon == NULL) {
        printf("Error: Invalid pointers.\n");
        return;
    }

    if (playerSupemon->current_hp <= 0) {
        printf("The player's Supemon is knocked out. Enemy cannot attack.\n");
        return;
    }

    if (enemy->numMoves <= 0) {
        printf("The enemy has no moves available. It cannot attack.\n");
        return;
    }

    int randomMove = rand() % enemy->numMoves + 1;
    performMove(enemy, playerSupemon, randomMove);
}

void displayEnemyStats(Supemon* enemy) {
    displaySeparator(33);
    printf("| %11s (Enemy)         |\n", enemy->name);
    displaySeparator(33);
    printf("| HP: %2d/%-2d  Lvl: %-2d          |\n", enemy->current_hp, enemy->max_hp, enemy->level);
    printf("| Atk: %-2d  Def: %-2d          |\n", enemy->attack, enemy->defense);
    printf("| Acc: %-2d  Eva: %-2d          |\n", enemy->accuracy, enemy->evasion);
    displaySeparator(33);
}

void supemonPassesOut(Enemy* supemon, Player* player) {
    printf("%s has passed out!\n", supemon->name);
        if (supemon->supemon.current_hp <= 0) {
            // Give Supecoins to the player
            player->supcoins += 150;
            printf("You have gained 150 Supecoins!\n");
        } 
}

void displayMenuOptions() {
    displaySeparator(32);
    printf("| What will you do?              |\n");
    printf("| 1 - Move                       |\n");
    printf("| 2 - Change Supemon             |\n");
    printf("| 3 - Use item                   |\n");
    printf("| 4 - Capture                    |\n");
    printf("| 5 - Run away                   |\n");
    displaySeparator(32);
}

void displayMoveOptions() {
    displaySeparator(31);
    printf("| 1 - Scratch                  |\n");
    printf("| 2 - Grawl                    |\n");
    printf("| 3 - Cancel                   |\n");
    displaySeparator(31);
}

