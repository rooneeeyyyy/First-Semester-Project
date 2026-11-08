#include <stdio.h>
#include <string.h>
#include "cafeteria.h"
#include "map.h"
#include "utils.h"

static Cafeteria cafeterias[MAX_CAFETERIAS];
static int cafeteriaCount = 0;

static int cafeteriaIdExists(int id)
{
    int i;

    for (i = 0; i < cafeteriaCount; i++) {
        if (cafeterias[i].id == id) {
            return 1;
        }
    }

    return 0;
}

int loadCafeterias(const char *path)
{
    FILE *fp;
    char line[MAX_LINE];
    char *fields[4];
    int lineNumber;
    int fieldCount;
    int id;
    int locationId;
    int valid;

    fp = fopen(path, "r");

    if (fp == NULL) {
        printf("Error: cannot open %s\n", path);

        return -1;
    }

    cafeteriaCount = 0;
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

        fieldCount = splitCsv(line, fields, 4);
        valid = fieldCount == 4;

        if (valid) {
            valid = parsePositiveInt(fields[0], &id)
                && parsePositiveInt(fields[2], &locationId)
                && getLocationName(locationId) != NULL
                && fields[1][0] != '\0'
                && fields[3][0] != '\0'
                && strlen(fields[1]) < MAX_CAFETERIA_NAME
                && strlen(fields[3]) < MAX_HOURS
                && !cafeteriaIdExists(id)
                && cafeteriaCount < MAX_CAFETERIAS;
        }

        if (!valid) {
            printf("Warning: %s line %d skipped (bad row)\n", path, lineNumber);
            continue;
        }

        cafeterias[cafeteriaCount].id = id;
        strcpy(cafeterias[cafeteriaCount].name, fields[1]);
        cafeterias[cafeteriaCount].locationId = locationId;
        strcpy(cafeterias[cafeteriaCount].hours, fields[3]);
        cafeteriaCount++;
    }

    fclose(fp);

    return cafeteriaCount;
}

void listCafeterias(void)
{
    int i;
    const char *place;

    printf("\n%-4s %-16s %-16s %s\n", "ID", "Name", "Location", "Hours (test data)");

    for (i = 0; i < cafeteriaCount; i++) {
        place = getLocationName(cafeterias[i].locationId);

        if (place == NULL) {
            place = "Unknown";
        }

        printf("%-4d %-16s %-16s %s\n", cafeterias[i].id, cafeterias[i].name, place, cafeterias[i].hours);
    }
}