#include <stdio.h>
#include <string.h>
#include "SUPEMON_GAME.h"

void displayPlayerStatsInBattle(Player* player) {
    displaySeparator(33);
    printf("| %s's %1s       |\n",player->name, player->supemons[0].name);
    displaySeparator(33);
    printf("| HP: %2d/%-2d  Lvl: %-2d          |\n", player->supemons[0].current_hp, player->supemons[0].max_hp, player->supemons[0].level);
    printf("| Atk: %-2d  Def: %-2d          |\n", player->supemons[0].attack, player->supemons[0].defense);
    printf("| Acc: %-2d  Eva: %-2d          |\n", player->supemons[0].accuracy, player->supemons[0].evasion);
    displaySeparator(33);
}

void playerInventory(Player* player, Item* items) {
    Item* inventory = &player->items[0];
    printf("You have %d Supecoins.\n", player->supcoins);
}