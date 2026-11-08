#ifndef CAFETERIA_H
#define CAFETERIA_H

#define MAX_CAFETERIAS 20
#define MAX_CAFETERIA_NAME 30
#define MAX_HOURS 20

typedef struct {
    int id;
    char name[MAX_CAFETERIA_NAME];
    int locationId;
    char hours[MAX_HOURS];
} Cafeteria;

int loadCafeterias(const char *path);
void listCafeterias(void);

#endif