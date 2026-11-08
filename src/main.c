#include <stdio.h>
#include "ui.h"
#include "food.h"
#include "map.h"
#include "cafeteria.h"
#include "utils.h"

#define MAX_INPUT 100

static void foodMenu(void)
{
    char query[MAX_INPUT];
    int choice;

    do {
        printf("\n--- Food ---\n");
        printf("1. Show all food\n");
        printf("2. Search by name or category\n");
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
            case 0:
                break;
            default:
                printMessage("Invalid choice. Enter 0, 1 or 2.");
                break;
        }
    } while (choice != 0);
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
            case 0:
                break;
            default:
                printMessage("Invalid choice. Enter 0, 1, 2 or 3.");
                break;
        }
    } while (choice != 0);
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
                listCafeterias();
                break;
            case 3:
                mapMenu();
                break;
            case 4:
                printMessage("Assistant feature coming soon.");
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