#include <stdio.h>
#include <string.h>
#include "food.h"
#include "utils.h"

static Food foods[MAX_FOOD];
static int foodCount = 0;

static int foodIdExists(int id)
{
    int i;

    for (i = 0; i < foodCount; i++) {
        if (foods[i].id == id) {
            return 1;
        }
    }

    return 0;
}

int loadFood(const char *path)
{
    FILE *fp;
    char line[MAX_LINE];
    char *fields[5];
    int lineNumber;
    int fieldCount;
    int id;
    int price;
    int vendorId;
    int valid;

    fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: cannot open %s\n", path);

        return -1;
    }

    foodCount = 0;
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

        fieldCount = splitCsv(line, fields, 5);
        valid = fieldCount == 5;

        if (valid) {
            valid = parsePositiveInt(fields[0], &id)
                && parsePositiveInt(fields[3], &price)
                && parsePositiveInt(fields[4], &vendorId)
                && fields[1][0] != '\0'
                && fields[2][0] != '\0'
                && strlen(fields[1]) < MAX_FOOD_NAME
                && strlen(fields[2]) < MAX_CATEGORY
                && !foodIdExists(id)
                && foodCount < MAX_FOOD;
        }

        if (!valid) {
            printf("Warning: %s line %d skipped (bad row)\n", path, lineNumber);
            continue;
        }

        foods[foodCount].id = id;
        strcpy(foods[foodCount].name, fields[1]);
        strcpy(foods[foodCount].category, fields[2]);
        foods[foodCount].price = price;
        foods[foodCount].vendorId = vendorId;
        foodCount++;
    }

    fclose(fp);

    return foodCount;
}

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

    for (i = 0; i < foodCount; i++) {
        printFoodRow(&foods[i]);
    }
}

int searchFood(const char *query)
{
    int i;
    int count;

    count = 0;

    for (i = 0; i < foodCount; i++) {
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