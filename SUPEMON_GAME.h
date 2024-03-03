#ifndef SUPEMON_GAME_H
#define SUPEMON_GAME_H

#define MAX_MOVES 4
#define MAX_NAME_LENGTH 20
#define MAX_QUANTITY 99
#define MAX_ITEMS 6 

typedef enum {
    poison,
    burn,
    freeze,
    paralyze,
    sleep,
    confusion,
    heal
} effect;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int damage;
} Move;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int level;
    int experience;
    int current_hp;
    int max_hp;
    int attack;
    int baseAttack;
    int defense;
    int baseDefense;
    int evasion;
    int baseEvasion;
    int accuracy;
    int baseAccuracy;
    int speed;
    int numMoves;
    Move moves[MAX_MOVES];
} Supemon;

typedef struct {
    char name[MAX_NAME_LENGTH];
    Supemon supemon; // Utilisation d'un Supemon pour représenter l'ennemi
} Enemy;


typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
    int quantityMax[MAX_QUANTITY];
    int price;
    int amount;
    int maxAmount[MAX_ITEMS];
} Item;   

typedef struct {
    char name[MAX_NAME_LENGTH];
    int supcoins;
    int numSupemons;
    Supemon supemons[5];
    Item items[MAX_ITEMS];
} Player;

// Prototypes des fonctions
void clearInputBuffer();
void displaySeparator(int length);
void displayMoves(Supemon* supemon);
void emptySupemon(Player* player);
void initializeSupemonMoves(Supemon* supemon, int supemonType);
void initializeSupemon(Supemon* supemon, char* name, int level, int experience, int current_hp, int max_hp, int attack, int base_attack, int defense, int base_defense, int evasion, int base_evasion, int accuracy, int base_accuracy, int speed);
void chooseInitialSupemon(Player* player);
void loadGame(Player* player);
void saveGame(Player* player);
void enterShop(Player* player, Item* items, int numItems);
void startCombat(Player* player, Supemon* enemy);
void playerTurn(Player* player, Supemon* enemy, Supemon* supemon, int move_choice);
void enemyTurn(Supemon* playerSupemon, Supemon* enemy);
void launchRandomFight(Player* player);
void mainMenu(Player* player);
void displaySupemonStats(Supemon* supemon);
void displayPlayerStatsInBattle(Player* player);
void initRandom();
void gainExperience(Supemon* supemon, int experience);
void performMove(Supemon *attacker, Supemon *defender, int move);
void usePotion(Player* player, Supemon* supemon);
void useEther(Supemon* supemon);
void startGame(Player* player);
void fight(Player* player, Supemon* enemy);
void buyItem(Player* player,Item* items, int itemNumber, int quantity);
void displayItems(Item* items, int numItems, Player* player);
void displayEnemyStats(Supemon* enemy);
void displayMenuOptions();
void displayMoveOptions();
Item* initializeShopItems();
void displaySeparatorWithSpace(int length, int space);
void displayStatsSideBySide(Player* player, Supemon* enemy);
void printTwoFormattedLines(const char* leftFormat, const char* rightFormat);
void displayCombinedStats(Supemon* enemy, Player* player);
void displaySupemon(Player* player);
void captureSupemon(Player* player, Supemon* enemy);
 
#endif // SUPEMON_GAME_H
