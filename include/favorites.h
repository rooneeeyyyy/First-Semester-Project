#ifndef FAVORITES_H
#define FAVORITES_H

#define MAX_FAVORITES 50
#define FAV_FOOD 1
#define FAV_CAFETERIA 2
#define FAV_LOCATION 3

int loadFavorites(const char *path);
int saveFavorites(const char *path);
int addFavorite(int type, int id);
int removeFavorite(int type, int id);
void listFavorites(void);

#endif
