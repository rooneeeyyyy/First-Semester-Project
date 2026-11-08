#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "map.h"
#include "utils.h"

static Location locations[MAX_LOCATIONS];
static Route routes[MAX_ROUTES];
static int locationCount = 0;
static int routeCount = 0;

int loadLocations(const char *path)
{
    FILE *fp;
    char line[MAX_LINE];
    char *fields[2];
    int lineNumber;
    int fieldCount;
    int id;
    int valid;

    fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: cannot open %s\n", path);

        return -1;
    }

    locationCount = 0;
    lineNumber = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        lineNumber++;

        if (lineNumber == 1) {
            continue;
        }

        trimNewline(line);

        if (line[0] == '\0') {
            continue;
        }

        fieldCount = splitCsv(line, fields, 2);
        valid = fieldCount == 2;

        if (valid) {
            valid = parsePositiveInt(fields[0], &id)
                && id == locationCount + 1
                && fields[1][0] != '\0'
                && strlen(fields[1]) < MAX_LOCATION_NAME
                && locationCount < MAX_LOCATIONS;
        }

        if (!valid) {
            printf("Warning: %s line %d skipped (bad row)\n", path, lineNumber);
            continue;
        }

        locations[locationCount].id = id;
        strcpy(locations[locationCount].name, fields[1]);
        locationCount++;
    }

    fclose(fp);

    return locationCount;
}

int loadRoutes(const char *path)
{
    FILE *fp;
    char line[MAX_LINE];
    char *fields[3];
    int lineNumber;
    int fieldCount;
    int from;
    int to;
    int distance;
    int valid;

    fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: cannot open %s\n", path);

        return -1;
    }

    routeCount = 0;
    lineNumber = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        lineNumber++;

        if (lineNumber == 1) {
            continue;
        }

        trimNewline(line);

        if (line[0] == '\0') {
            continue;
        }

        fieldCount = splitCsv(line, fields, 3);
        valid = fieldCount == 3;

        if (valid) {
            valid = parsePositiveInt(fields[0], &from)
                && parsePositiveInt(fields[1], &to)
                && parsePositiveInt(fields[2], &distance)
                && from <= locationCount
                && to <= locationCount
                && from != to
                && routeCount < MAX_ROUTES;
        }

        if (!valid) {
            printf("Warning: %s line %d skipped (bad row)\n", path, lineNumber);
            continue;
        }

        routes[routeCount].from = from;
        routes[routeCount].to = to;
        routes[routeCount].distance = distance;
        routeCount++;
    }

    fclose(fp);

    return routeCount;
}

void printLocations(void)
{
    int i;

    printf("\n%-4s %s\n", "ID", "Location");

    for (i = 0; i < locationCount; i++) {
        printf("%-4d %s\n", locations[i].id, locations[i].name);
    }
}

void printRoutes(void)
{
    int i;

    printf("\n%-16s %-16s %s\n", "From", "To", "Distance (m, estimated)");

    for (i = 0; i < routeCount; i++) {
        printf("%-16s %-16s %d\n", getLocationName(routes[i].from), getLocationName(routes[i].to), routes[i].distance);
    }
}

int findLocation(const char *name)
{
    int i;

    for (i = 0; i < locationCount; i++) {
        if (equalsIgnoreCase(locations[i].name, name)) {
            return locations[i].id;
        }
    }

    return -1;
}

const char *getLocationName(int id)
{
    if (id < 1 || id > locationCount) {
        return NULL;
    }

    return locations[id - 1].name;
}
int getLocationCount(void)
{
    return locationCount;
}

int getDistance(int from, int to)
{
    int i;

    for (i = 0; i < routeCount; i++) {
        if ((routes[i].from == from && routes[i].to == to) || (routes[i].from == to && routes[i].to == from)) {
            return routes[i].distance;
        }
    }

    return 0;
}