#include <stdio.h>
#include <string.h>
#include "favorites.h"
#include "food.h"
#include "cafeteria.h"
#include "map.h"
#include "utils.h"

typedef struct {
    int type;
    int id;
} Favorite;

static Favorite favorites[MAX_FAVORITES];
static int favoriteTotal = 0;
static char favoritesPath[MAX_LINE] = "";

static const char *typeKey(int type)
{
    switch (type) {
        case FAV_FOOD:
            return "food";
        case FAV_CAFETERIA:
            return "cafeteria";
        default:
            return "location";
    }
}

static const char *typeLabel(int type)
{
    switch (type) {
        case FAV_FOOD:
            return "Food";
        case FAV_CAFETERIA:
            return "Cafeteria";
        default:
            return "Location";
    }
}

static int typeFromKey(const char *key)
{
    if (equalsIgnoreCase(key, "food")) {
        return FAV_FOOD;
    }

    if (equalsIgnoreCase(key, "cafeteria")) {
        return FAV_CAFETERIA;
    }

    if (equalsIgnoreCase(key, "location")) {
        return FAV_LOCATION;
    }

    return 0;
}

static int itemExists(int type, int id)
{
    if (type == FAV_FOOD) {
        return getFoodName(id) != NULL;
    }

    if (type == FAV_CAFETERIA) {
        return getCafeteriaName(id) != NULL;
    }

    if (type == FAV_LOCATION) {
        return getLocationName(id) != NULL;
    }

    return 0;
}

static int findFavorite(int type, int id)
{
    int i;

    for (i = 0; i < favoriteTotal; i++) {
        if (favorites[i].type == type && favorites[i].id == id) {
            return i;
        }
    }

    return -1;
}

int saveFavorites(const char *path)
{
    FILE *fp;
    int i;

    fp = fopen(path, "w");

    if (fp == NULL) {
        printf("Error: cannot save favorites to %s\n", path);

        return -1;
    }

    fprintf(fp, "type,id\n");

    for (i = 0; i < favoriteTotal; i++) {
        fprintf(fp, "%s,%d\n", typeKey(favorites[i].type), favorites[i].id);
    }

    fclose(fp);

    return favoriteTotal;
}

int loadFavorites(const char *path)
{
    FILE *fp;
    char line[MAX_LINE];
    char *fields[2];
    int lineNumber;
    int fieldCount;
    int type;
    int id;
    int valid;

    strncpy(favoritesPath, path, MAX_LINE - 1);
    favoritesPath[MAX_LINE - 1] = '\0';
    favoriteTotal = 0;
    fp = fopen(path, "r");

    if (fp == NULL) {
        return 0;
    }

    lineNumber = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        lineNumber++;

        if (lineNumber == 1) {
            continue;
        }

        trimNewline(line);

        if (line[0] == '\0') {
            continue;
        }

        fieldCount = splitCsv(line, fields, 2);
        valid = fieldCount == 2;
        type = 0;
        id = 0;

        if (valid) {
            type = typeFromKey(fields[0]);
            valid = type != 0
                && parsePositiveInt(fields[1], &id)
                && itemExists(type, id)
                && findFavorite(type, id) == -1
                && favoriteTotal < MAX_FAVORITES;
        }

        if (!valid) {
            printf("Warning: %s line %d skipped (bad row or item no longer exists)\n", path, lineNumber);
            continue;
        }

        favorites[favoriteTotal].type = type;
        favorites[favoriteTotal].id = id;
        favoriteTotal++;
    }

    fclose(fp);

    return favoriteTotal;
}

int addFavorite(int type, int id)
{
    if (type < FAV_FOOD || type > FAV_LOCATION || !itemExists(type, id)) {
        return -1;
    }

    if (findFavorite(type, id) != -1) {
        return 0;
    }

    if (favoriteTotal >= MAX_FAVORITES) {
        return -2;
    }

    favorites[favoriteTotal].type = type;
    favorites[favoriteTotal].id = id;
    favoriteTotal++;

    if (favoritesPath[0] != '\0') {
        saveFavorites(favoritesPath);
    }

    return 1;
}

int removeFavorite(int type, int id)
{
    int index;
    int i;

    index = findFavorite(type, id);

    if (index == -1) {
        return 0;
    }

    for (i = index; i < favoriteTotal - 1; i++) {
        favorites[i] = favorites[i + 1];
    }

    favoriteTotal--;

    if (favoritesPath[0] != '\0') {
        saveFavorites(favoritesPath);
    }

    return 1;
}

void listFavorites(void)
{
    int i;
    int type;
    int id;

    if (favoriteTotal == 0) {
        printf("You have no favorites yet.\n");

        return;
    }

    printf("\n%-10s %-4s %s\n", "Type", "ID", "Name");

    for (i = 0; i < favoriteTotal; i++) {
        type = favorites[i].type;
        id = favorites[i].id;

        if (type == FAV_FOOD) {
            printf("%-10s %-4d %s (Rs. %d)\n", typeLabel(type), id, getFoodName(id), getFoodPrice(id));
        }
        else if (type == FAV_CAFETERIA) {
            printf("%-10s %-4d %s\n", typeLabel(type), id, getCafeteriaName(id));
        }
        else {
            printf("%-10s %-4d %s\n", typeLabel(type), id, getLocationName(id));
        }
    }
}
