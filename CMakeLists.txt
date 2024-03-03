cmake_minimum_required(VERSION 3.10)
project(SupemonAlpha)

# Ajoutez tous vos fichiers source
set(SOURCES
    main.c
    fight.c
    supemon.c
    load_and_save.c
    player.c
    shop.c
    item.c
    utils.c
)

# Déclarez l'exécutable
add_executable(SupemonAlpha ${SOURCES})