#include <stdio.h>
#include <string.h>

#define COUNT 8
#define MAX_INPUT 50

int main(void)
{
    const char *names[COUNT] = {
        "Main Gate", "Parking", "Admin Block", "Cafeteria",
        "Library", "CS Department", "Mosque", "Sports Ground"
    };
    char input[MAX_INPUT];
    int i;
    int found;

    printf("Locations:\n");

    for (i = 0; i < COUNT; i++) {
        printf("%d. %s\n", i + 1, names[i]);
    }

    printf("\nEnter a location name to search: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    found = -1;
    i = 0;

    while (i < COUNT && found == -1) {
        if (strcmp(names[i], input) == 0) {
            found = i + 1;
        }

        i++;
    }

    if (found == -1) {
        printf("Not found.\n");
    }
    else {
        printf("Found: %s has ID %d\n", input, found);
    }

    return 0;
}