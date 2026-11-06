#include <stdio.h>
#include "cafeteria.h"
#include "map.h"

static const Cafeteria cafeterias[CAFETERIA_COUNT] = {
    {1, "Test Cafe One", 4, "09:00-17:00"},
    {2, "Test Cafe Two", 4, "10:00-16:00"},
    {3, "Test Tea Stall", 7, "08:00-18:00"}
};

void listCafeterias(void)
{
    int i;
    const char *place;

    printf("\n%-4s %-16s %-16s %s\n", "ID", "Name", "Location", "Hours (test data)");

    for (i = 0; i < CAFETERIA_COUNT; i++) {
        place = getLocationName(cafeterias[i].locationId);

        if (place == NULL) {
            place = "Unknown";
        }

        printf("%-4d %-16s %-16s %s\n", cafeterias[i].id, cafeterias[i].name, place, cafeterias[i].hours);
    }
}