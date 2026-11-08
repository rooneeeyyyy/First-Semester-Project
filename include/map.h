#ifndef MAP_H
#define MAP_H

#define MAX_LOCATIONS 50
#define MAX_ROUTES 200
#define MAX_LOCATION_NAME 30

typedef struct {
    int id;
    char name[MAX_LOCATION_NAME];
} Location;

typedef struct {
    int from;
    int to;
    int distance;
} Route;

int loadLocations(const char *path);
int loadRoutes(const char *path);
void printLocations(void);
void printRoutes(void);
int findLocation(const char *name);
const char *getLocationName(int id);

#endif