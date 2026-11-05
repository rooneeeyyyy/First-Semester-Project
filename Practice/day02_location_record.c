#include <stdio.h>
#include <string.h>

#define MAX_NAME 50

int main(void)
{
    int id;
    int result;
    int c;
    float distance;
    char type;
    char name[MAX_NAME];

    printf("Location ID: ");
    result = scanf("%d", &id);

    if (result != 1) {
        printf("Error: ID must be a number.\n");

        return 1;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    printf("Location name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Type (B = building, F = food, O = open area): ");
    result = scanf(" %c", &type);

    if (result != 1) {
        printf("Error: type must be one letter.\n");

        return 1;
    }

    printf("Distance from Main Gate in metres: ");
    result = scanf("%f", &distance);

    if (result != 1 || distance < 0) {
        printf("Error: distance must be a number, 0 or more.\n");

        return 1;
    }

    printf("\n--- Location Record ---\n");
    printf("ID       : %d\n", id);
    printf("Name     : %s\n", name);
    printf("Type     : %c\n", type);
    printf("Distance : %.1f m\n", distance);

    return 0;
}