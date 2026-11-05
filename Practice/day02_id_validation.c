#include <stdio.h>

#define MIN_ID 1
#define MAX_ID 20
#define ATTEMPTS 3

int main(void)
{
    int id;
    int result;
    int c;
    int i;

    for (i = 1; i <= ATTEMPTS; i++) {
        printf("Attempt %d - enter location ID (%d-%d): ", i, MIN_ID, MAX_ID);
        result = scanf("%d", &id);

        while ((c = getchar()) != '\n' && c != EOF) {
        }

        if (result != 1) {
            printf("Invalid: not a number.\n");
        }
        else if (id < MIN_ID) {
            printf("Invalid: %d is below %d.\n", id, MIN_ID);
        }
        else if (id > MAX_ID) {
            printf("Invalid: %d is above %d.\n", id, MAX_ID);
        }
        else {
            printf("Valid: location ID %d accepted.\n", id);
        }

        printf("\n");
    }

    return 0;
}