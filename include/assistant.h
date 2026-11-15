#ifndef ASSISTANT_H
#define ASSISTANT_H

#define INTENT_UNKNOWN 0
#define INTENT_FOOD_SEARCH 1
#define INTENT_PRICE_SEARCH 2
#define INTENT_LOCATION_SEARCH 3
#define INTENT_ROUTE_HELP 4
#define INTENT_CAFETERIA_SEARCH 5
#define INTENT_HELP 6

void normalizeQuery(char *text);
int detectIntent(const char *query);
void processQuery(const char *input);

#endif
