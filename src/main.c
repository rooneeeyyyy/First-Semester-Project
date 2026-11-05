#include <stdio.h>
#include "ui.h"
#include "food.h"
#include "map.h"

int main(void)
{
    int choice;

    do {
        showMainMenu();
        choice = readChoice();

        switch (choice) {
            case 1:
                displayFood();
                break;
            case 2:
                printMessage("Cafeterias feature coming soon.");
                break;
            case 3:
                printLocations();
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