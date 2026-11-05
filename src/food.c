#include <stdio.h>
#include "food.h"

static const char *foodNames[FOOD_COUNT] = {
    "Test Biryani", "Test Chicken Roll", "Test Samosa", "Test Fries",
    "Test Tea", "Test Cold Drink", "Test Burger", "Test Biryani"
};

static const int foodPrices[FOOD_COUNT] = {250, 180, 50, 150, 60, 100, 300, 270};

void displayFood(void)
{
    int i;

    printf("\n%-4s %-20s %8s\n", "ID", "Name", "Price");

    for (i = 0; i < FOOD_COUNT; i++) {
        printf("%-4d %-20s %8d\n", i + 1, foodNames[i], foodPrices[i]);
    }
}