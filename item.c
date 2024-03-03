#include <stdio.h>
#include "SUPEMON_GAME.h"

Item* initializeShopItems() {
    static Item items[MAX_ITEMS] = {
        {"Health Potion", 1, 50}, // name, quantity, price
        {"Mana Potion", 1, 75},
        {"Phenix Tail", 1, 100},
        {"Supeball", 1, 100},
        {"Super Supeball", 1, 150},
    };
    return items;
}

void usePotion(Player* player, Supemon* supemon) {
    if (player->items == 0) {
        printf("You don't have any items to use!\n");
        return;
    }

    if (player->items[0].quantity == 0) {
        printf("You don't have any Potions to use!\n");
        return;
    }

    if (supemon->current_hp == supemon->max_hp) {
        printf("%s is already at full health!\n", supemon->name);
        return;
    }

    supemon->current_hp += 20;
    if (supemon->current_hp > supemon->max_hp) {
        supemon->current_hp = supemon->max_hp;
    }

    player->items[0].quantity--;
    if (player->items[0].quantity == 0) {
        player->items[0].quantity--;
    }

    printf("%s used a Potion on %s. %s's HP is now %d/%d.\n", player->name, supemon->name, supemon->name, supemon->current_hp, supemon->max_hp);
}

Item* initializeItems(Item* item, char name, int quantity, int price) {
    if (item == NULL) {
        printf("Error: Invalid pointers provided to initializeItems.\n");
        return;
    }

    strncpy(item->name, name, sizeof(item->name) - 1);
    item->name[sizeof(item->name) - 1] = '\0'; // Ensure null termination
    
    item->quantity = quantity;
    item->price = price;
}