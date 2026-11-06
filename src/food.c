#include <stdio.h>
#include "food.h"
#include "utils.h"

static const Food foods[FOOD_COUNT] = {
    {1, "Test Biryani", "Rice", 250, 1},
    {2, "Test Chicken Roll", "Snacks", 180, 1},
    {3, "Test Samosa", "Snacks", 50, 2},
    {4, "Test Fries", "Snacks", 150, 2},
    {5, "Test Tea", "Drinks", 60, 3},
    {6, "Test Cold Drink", "Drinks", 100, 3},
    {7, "Test Burger", "Fast Food", 300, 1},
    {8, "Test Biryani", "Rice", 270, 2}
};

static void printFoodHeader(void)
{
    printf("\n%-4s %-20s %-10s %6s %7s\n", "ID", "Name", "Category", "Price", "Vendor");
}

static void printFoodRow(const Food *item)
{
    printf("%-4d %-20s %-10s %6d %7d\n", item->id, item->name, item->category, item->price, item->vendorId);
}

void displayFood(void)
{
    int i;

    printFoodHeader();

    for (i = 0; i < FOOD_COUNT; i++) {
        printFoodRow(&foods[i]);
    }
}

int searchFood(const char *query)
{
    int i;
    int count;

    count = 0;

    for (i = 0; i < FOOD_COUNT; i++) {
        if (containsIgnoreCase(foods[i].name, query) || containsIgnoreCase(foods[i].category, query)) {
            if (count == 0) {
                printFoodHeader();
            }

            printFoodRow(&foods[i]);
            count++;
        }
    }

    return count;
}