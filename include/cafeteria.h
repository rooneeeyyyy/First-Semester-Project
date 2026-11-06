#ifndef CAFETERIA_H
#define CAFETERIA_H

#define CAFETERIA_COUNT 3
#define MAX_CAFETERIA_NAME 30
#define MAX_HOURS 20

typedef struct {
    int id;
    char name[MAX_CAFETERIA_NAME];
    int locationId;
    char hours[MAX_HOURS];
} Cafeteria;

void listCafeterias(void);

#endif