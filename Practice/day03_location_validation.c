#include <stdio.h>

#define MIN_ID 1
#define MAX_ID 8

int isValidLocationId(int id)
{
    if (id >= MIN_ID && id <= MAX_ID) {
        return 1;
    }
    else {
        return 0;
    }
}

int main(void)
{
    int testIds[] = {1, 5, 8, 0, 9, -3};
    int count = 6;
    int i;

    for (i = 0; i < count; i++) {
        if (isValidLocationId(testIds[i])) {
            printf("ID %d: valid location\n", testIds[i]);
        }
        else {
            printf("ID %d: invalid location\n", testIds[i]);
        }
    }

    return 0;
}