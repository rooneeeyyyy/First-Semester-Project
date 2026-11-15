#include <stdio.h>
#include "ui.h"
#include "food.h"
#include "map.h"
#include "route.h"
#include "cafeteria.h"
#include "utils.h"
#include "assistant.h"

#define MAX_INPUT 100

static void foodMenu(void)
{
    char query[MAX_INPUT];
    char budgetText[MAX_INPUT];
    char category[MAX_INPUT];
    int choice;
    int budget;

    do {
        printf("\n--- Food ---\n");
        printf("1. Show all food\n");
        printf("2. Search by name or category\n");
        printf("3. Filter by budget\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        choice = readChoice();

        switch (choice) {
            case 1:
                displayFood();
                break;
            case 2:
                readLine("Enter food name or category: ", query, sizeof(query));

                if (query[0] == '\0') {
                    printMessage("Search cannot be empty.");
                }
                else if (searchFood(query) == 0) {
                    printMessage("No matching food found.");
                }

                break;
            case 3:
                readLine("Enter maximum budget in PKR: ", budgetText, sizeof(budgetText));

                if (!parsePositiveInt(budgetText, &budget)) {
                    printMessage("Budget must be a whole number above 0.");
                }
                else {
                    readLine("Enter category (or press Enter for all): ", category, sizeof(category));

                    if (searchByBudget(budget, category) == 0) {
                        printMessage("No items found within this budget.");
                    }
                }

                break;
            case 0:
                break;
            default:
                printMessage("Invalid choice. Enter 0, 1, 2 or 3.");
                break;
        }
    } while (choice != 0);
}

static void compareMenu(void)
{
    char line[MAX_INPUT];
    int ids[4];
    int count;
    int i;
    int j;

    readLine("Enter 2 or 3 cafeteria IDs separated by spaces: ", line, sizeof(line));
    count = sscanf(line, "%d %d %d %d", &ids[0], &ids[1], &ids[2], &ids[3]);

    if (count < 2) {
        printMessage("Enter at least two cafeteria IDs.");

        return;
    }

    if (count > 3) {
        printMessage("You can compare at most three cafeterias.");

        return;
    }

    for (i = 0; i < count; i++) {
        if (getCafeteriaName(ids[i]) == NULL) {
            printf("Cafeteria %d not found.\n", ids[i]);

            return;
        }

        for (j = i + 1; j < count; j++) {
            if (ids[i] == ids[j]) {
                printMessage("Each cafeteria can be chosen only once.");

                return;
            }
        }
    }

    compareMenus(ids, count);
}

static void cafeteriaMenu(void)
{
    char idText[MAX_INPUT];
    int choice;
    int id;

    do {
        printf("\n--- Cafeterias ---\n");
        printf("1. List cafeterias\n");
        printf("2. View a cafeteria and its menu\n");
        printf("3. Compare cafeterias\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        choice = readChoice();

        switch (choice) {
            case 1:
                listCafeterias();
                break;
            case 2:
                readLine("Enter cafeteria ID: ", idText, sizeof(idText));

                if (!parsePositiveInt(idText, &id)) {
                    printMessage("Invalid cafeteria ID.");
                }
                else if (!viewCafeteria(id)) {
                    printMessage("Cafeteria not found.");
                }

                break;
            case 3:
                compareMenu();
                break;
            case 0:
                break;
            default:
                printMessage("Invalid choice. Enter 0, 1, 2 or 3.");
                break;
        }
    } while (choice != 0);
}

static void routeMenu(void)
{
    char startName[MAX_INPUT];
    char endName[MAX_INPUT];
    int start;
    int end;

    readLine("Enter start location: ", startName, sizeof(startName));
    start = findLocation(startName);

    if (start == -1) {
        printMessage("Start location not found.");

        return;
    }

    readLine("Enter destination: ", endName, sizeof(endName));
    end = findLocation(endName);

    if (end == -1) {
        printMessage("Destination not found.");

        return;
    }

    printf("From: %s\n", getLocationName(start));
    printf("To: %s\n", getLocationName(end));
    printRoute(start, end);
}

static void mapMenu(void)
{
    char query[MAX_INPUT];
    int choice;
    int id;

    do {
        printf("\n--- Campus Map ---\n");
        printf("1. Show all locations\n");
        printf("2. Search for a location\n");
        printf("3. Show connections\n");
        printf("4. Find a route\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        choice = readChoice();

        switch (choice) {
            case 1:
                printLocations();
                break;
            case 2:
                readLine("Enter location name: ", query, sizeof(query));

                if (query[0] == '\0') {
                    printMessage("Search cannot be empty.");
                }
                else {
                    id = findLocation(query);

                    if (id == -1) {
                        printMessage("Location not found.");
                    }
                    else {
                        printf("Found: ID %d - %s\n", id, getLocationName(id));
                    }
                }

                break;
            case 3:
                printRoutes();
                break;
            case 4:
                routeMenu();
                break;
            case 0:
                break;
            default:
                printMessage("Invalid choice. Enter 0, 1, 2, 3 or 4.");
                break;
        }
    } while (choice != 0);
}

static void assistantMenu(void)
{
    char line[MAX_INPUT];
    int running;

    printMessage("\nAssistant: ask about food, prices, cafeterias, locations or routes.");
    printMessage("Type 'help' for examples or 'back' to return.");
    running = 1;

    while (running) {
        if (!readLine("\nYou: ", line, sizeof(line))) {
            running = 0;
        }
        else if (equalsIgnoreCase(line, "back") || equalsIgnoreCase(line, "0")) {
            running = 0;
        }
        else {
            processQuery(line);
        }
    }
}

int main(void)
{
    int choice;
    int locationTotal;
    int routeTotal;
    int foodTotal;
    int cafeteriaTotal;

    locationTotal = loadLocations("data/locations.csv");
    routeTotal = loadRoutes("data/routes.csv");
    foodTotal = loadFood("data/food.csv");
    cafeteriaTotal = loadCafeterias("data/cafeterias.csv");

    if (locationTotal <= 0 || routeTotal <= 0 || foodTotal <= 0 || cafeteriaTotal <= 0) {
        printMessage("Error: required data could not be loaded.");
        printMessage("Run the program from the project root folder.");

        return 1;
    }

    printf("Loaded: %d locations, %d routes, %d food items, %d cafeterias\n", locationTotal, routeTotal, foodTotal, cafeteriaTotal);

    do {
        showMainMenu();
        choice = readChoice();

        switch (choice) {
            case 1:
                foodMenu();
                break;
            case 2:
                cafeteriaMenu();
                break;
            case 3:
                mapMenu();
                break;
            case 4:
                assistantMenu();
                break;
            case 0:
                printMessage("Goodbye!");
                break;
            default:
                printMessage("Invalid choice. Enter a number from 0 to 4.");
                break;
        }
    } while (choice != 0);

    return 0;
}
