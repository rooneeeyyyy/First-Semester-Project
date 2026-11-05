#include <stdio.h>
#include <string.h>
#include "map.h"

static const char *locationNames[LOCATION_COUNT] = {
    "Main Gate", "Parking", "Admin Block", "Cafeteria",
    "Library", "CS Department", "Mosque", "Sports Ground"
};

void printLocations(void)
{
    int i;

    printf("\n%-4s %s\n", "ID", "Location");

    for (i = 0; i < LOCATION_COUNT; i++) {
        printf("%-4d %s\n", i + 1, locationNames[i]);
    }
}

int findLocation(const char *name)
{
    int i;

    for (i = 0; i < LOCATION_COUNT; i++) {
        if (strcmp(locationNames[i], name) == 0) {
            return i + 1;
        }
    }

    return -1;
}