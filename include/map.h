#ifndef MAP_H
#define MAP_H

#define LOCATION_COUNT 8
#define MAX_LOCATION_NAME 30

typedef struct {
    int id;
    char name[MAX_LOCATION_NAME];
} Location;

void printLocations(void);
int findLocation(const char *name);
const char *getLocationName(int id);

#endif