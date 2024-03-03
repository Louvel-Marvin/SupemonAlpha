#include <stdio.h>
#include "SUPEMON_GAME.h"

void displayItems(Item* items, int numItems, Player* player) {
    printf("Items available in the shop:\n");
    int i;
    for (i = 0; i < numItems; i++) {
        printf("%d. %s - Price: %d, Quantity: %d\n", i + 1, items[i].name, items[i].price, items[i].quantity);
    }
    printf("%d. Exit\n", numItems + 1);

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice > 0 && choice <= numItems) {
        Item selected = items[choice - 1];
        printf("%s: %d Supcoins each. How many would you like to buy? (Available: %d)\n", selected.name, selected.price, selected.quantity);
        int quantityToBuy;
        scanf("%d", &quantityToBuy);
        clearInputBuffer();
        if (quantityToBuy > selected.quantity) {
            printf("There are not enough items in stock.\n");
        } else if (quantityToBuy > 0) {
            // Adjust buyItem to handle item purchase logic, including updating player's inventory and balance
            //buyItem(player, choice, quantityToBuy);
        } else {
            printf("Invalid quantity.\n");
        }
    } else if (choice == numItems + 1) {
        printf("Exiting shop.\n");
    } else {
        printf("Invalid choice. Please enter a number from 1 to %d.\n", numItems + 1);
    }
}

void enterShop(Player* player, Item* items, int numItems) {
    displayItems(items, numItems, player);
    
    printf("You have left the shop.\n");
}

void buyItem(Player* player,Item* items, int itemNumber, int quantity){
    if (player->supcoins < items[itemNumber].price * quantity) {
        printf("You don't have enough Supcoins to buy that item.\n");
        return;
    } else {
        player->supcoins -= items[itemNumber].price * quantity;
        player->items[itemNumber].quantity += quantity;
    }
    printf("You have bought the item.\n");
}
