#include <stdio.h>

int main(void)
{
    int choice;
    int result;
    int c;

    do {
        printf("\n==================================\n");
        printf("  FAST Navigator & Cafeteria Hub\n");
        printf("==================================\n");
        printf("1. Food\n");
        printf("2. Cafeterias\n");
        printf("3. Campus Map\n");
        printf("4. Assistant\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        result = scanf("%d", &choice);

        if (result == EOF) {
            return 1;
        }

        while ((c = getchar()) != '\n' && c != EOF) {
        }

        if (result != 1) {
            choice = -1;
        }

        switch (choice) {
            case 1:
                printf("Food feature coming soon.\n");
                break;
            case 2:
                printf("Cafeterias feature coming soon.\n");
                break;
            case 3:
                printf("Campus Map feature coming soon.\n");
                break;
            case 4:
                printf("Assistant feature coming soon.\n");
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Enter a number from 0 to 4.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}