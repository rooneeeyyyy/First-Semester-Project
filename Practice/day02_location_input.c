#include <stdio.h>
#include <string.h>

#define MAX_NAME 50
#define MIN_ID 1
#define MAX_ID 20

int main(void)
{
    int id;
    int scanResult;
    int c;
    char name[MAX_NAME];

    printf("Enter location ID (%d-%d): ", MIN_ID, MAX_ID);
    scanResult = scanf("%d", &id);

    if (scanResult != 1) {
        printf("Error: ID must be a number.\n");

        return 1;
    }

    if (id < MIN_ID || id > MAX_ID) {
        printf("Error: ID must be between %d and %d.\n", MIN_ID, MAX_ID);

        return 1;
    }

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    printf("Enter location name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    if (strlen(name) == 0) {
        printf("Error: name cannot be empty.\n");

        return 1;
    }
    else {
        printf("Location %d: %s\n", id, name);
    }

    return 0;
}