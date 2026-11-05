#include <stdio.h>

int main(void)
{
    int choice;
    int result;

    printf("==================================\n");
    printf("  FAST Navigator & Cafeteria Hub\n");
    printf("==================================\n");
    printf("1. Food\n");
    printf("2. Cafeterias\n");
    printf("3. Campus Map\n");
    printf("4. Assistant\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    result = scanf("%d", &choice);

    if (result != 1) {
        printf("Error: please enter a number.\n");

        return 1;
    }

    if (choice < 0 || choice > 4) {
        printf("Error: invalid choice. Enter a number from 0 to 4.\n");

        return 1;
    }

    printf("You selected option %d.\n", choice);

    return 0;
}