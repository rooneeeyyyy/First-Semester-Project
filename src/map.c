#include <stdio.h>
#include <stddef.h>
#include "map.h"
#include "utils.h"

static const Location locations[LOCATION_COUNT] = {
    {1, "Main Gate"},
    {2, "Parking"},
    {3, "Admin Block"},
    {4, "Cafeteria"},
    {5, "Library"},
    {6, "CS Department"},
    {7, "Mosque"},
    {8, "Sports Ground"}
};

void printLocations(void)
{
    int i;

    printf("\n%-4s %s\n", "ID", "Location");

    for (i = 0; i < LOCATION_COUNT; i++) {
        printf("%-4d %s\n", locations[i].id, locations[i].name);
    }
}

int findLocation(const char *name)
{
    int i;

    for (i = 0; i < LOCATION_COUNT; i++) {
        if (equalsIgnoreCase(locations[i].name, name)) {
            return locations[i].id;
        }
    }

    return -1;
}

const char *getLocationName(int id)
{
    if (id < 1 || id > LOCATION_COUNT) {
        return NULL;
    }

    return locations[id - 1].name;
}