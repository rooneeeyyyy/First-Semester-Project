#include <stdio.h>
#include "ui.h"

void showMainMenu(void)
{
    printf("\n==================================\n");
    printf("  FAST Navigator & Cafeteria Hub\n");
    printf("==================================\n");
    printf("1. Food\n");
    printf("2. Cafeterias\n");
    printf("3. Campus Map\n");
    printf("4. Assistant\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
}

int readChoice(void)
{
    int choice;
    int result;
    int c;

    result = scanf("%d", &choice);

    if (result == EOF) {
        return 0;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (result != 1) {
        return -1;
    }

    return choice;
}

void printMessage(const char *text)
{
    printf("%s\n", text);
}