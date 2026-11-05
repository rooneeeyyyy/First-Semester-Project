#include <stdio.h>

int main(void)
{
    int choice;
    int result;
    int c;
    int running;
    int validCount;

    running = 1;
    validCount = 0;

    while (running) {
        printf("\n1. Food\n2. Cafeterias\n3. Campus Map\n4. Assistant\n0. Exit\n");
        printf("Enter your choice: ");
        result = scanf("%d", &choice);

        if (result == EOF) {
            return 1;
        }

        while ((c = getchar()) != '\n' && c != EOF) {
        }

        if (result != 1) {
            printf("Invalid input. Enter a number.\n");
        }
        else if (choice == 0) {
            running = 0;
        }
        else if (choice >= 1 && choice <= 4) {
            validCount++;
            printf("You selected option %d.\n", choice);
        }
        else {
            printf("Invalid choice. Enter a number from 0 to 4.\n");
        }
    }

    printf("Goodbye! You made %d valid selection(s).\n", validCount);

    return 0;
}