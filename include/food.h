#ifndef FOOD_H
#define FOOD_H

#define MAX_FOOD 100
#define MAX_FOOD_NAME 30
#define MAX_CATEGORY 20

typedef struct {
    int id;
    char name[MAX_FOOD_NAME];
    char category[MAX_CATEGORY];
    int price;
    int vendorId;
} Food;

int loadFood(const char *path);
void displayFood(void);
int searchFood(const char *query);

#endif