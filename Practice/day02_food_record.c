#include <stdio.h>
#include <string.h>

#define MAX_NAME 50

int main(void)
{
    int price;
    int result;
    char name[MAX_NAME];

    printf("Enter food name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0) {
        printf("Error: name cannot be empty.\n");

        return 1;
    }

    printf("Enter price in PKR (whole number): ");
    result = scanf("%d", &price);

    if (result != 1) {
        printf("Error: price must be a whole number.\n");

        return 1;
    }

    if (price <= 0) {
        printf("Error: price must be greater than 0.\n");

        return 1;
    }

    printf("\n--- Food Record ---\n");
    printf("Name  : %s\n", name);
    printf("Price : Rs. %d\n", price);

    return 0;
}