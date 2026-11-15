#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "assistant.h"
#include "utils.h"
#include "map.h"
#include "route.h"
#include "food.h"
#include "cafeteria.h"

#define CHEAP_LIMIT 100
#define MIN_BUDGET 10
#define PADDED_SIZE (MAX_TEXT + 4)
#define COUNT_OF(list) ((int)(sizeof(list) / sizeof((list)[0])))

typedef struct {
    const char *phrase;
    const char *target;
} Alias;

static const Alias aliases[] = {
    {"library", "Library and Cafe"},
    {"masjid", "Mosque"},
    {"parking", "Parking Area"},
    {"gym", "Sports Room Gymnasium"},
    {"gymnasium", "Sports Room Gymnasium"},
    {"sports room", "Sports Room Gymnasium"},
    {"futsal", "Futsal Ground"},
    {"badminton", "Badminton Court"},
    {"basketball", "Basketball Court"},
    {"volleyball", "Basketball Court"},
    {"throwball", "Basketball Court"},
    {"ee", "Academic Block 2"},
    {"ee building", "Academic Block 2"},
    {"ee block", "Academic Block 2"},
    {"block 1", "Academic Block 1"},
    {"block 2", "Academic Block 2"},
    {"block 3", "Academic Block 3"}
};

#define ALIAS_COUNT COUNT_OF(aliases)

static const char *helpWords[] = {"help", "madad", "examples"};

static const char *routeWords[] = {
    "route", "path", "rasta", "raasta", "directions", "navigate", "reach",
    "how to go", "how to get", "jana", "jaana", "pohanchna"
};

static const char *priceWords[] = {
    "price", "prices", "cost", "rs", "pkr", "rupees", "under", "below",
    "within", "cheap", "cheaper", "cheapest", "sasta", "sasti", "budget",
    "kitne", "kitna", "kam"
};

static const char *cheapWords[] = {"cheap", "cheaper", "cheapest", "sasta", "sasti"};

static const char *cafeWords[] = {
    "cafe", "cafes", "cafeteria", "cafeterias", "canteen", "canteens", "stall", "stalls"
};

static const char *foodWords[] = {"food", "menu", "eat", "hungry", "khana", "khane", "bhook"};

static const char *stopWords[] = {
    "and", "the", "for", "from", "with", "can", "how", "get", "are", "you",
    "all", "any", "hai", "hain", "aur", "kya", "show", "list", "find", "where",
    "near", "kahan", "milegi", "milta", "mujhe", "main", "food", "khana", "menu",
    "cafe", "cafeteria", "canteen", "price", "under", "below", "cheap", "sasta",
    "kitne", "what", "when", "which", "that", "this"
};

static int phrasePosition(const char *query, const char *phrase)
{
    char padded[PADDED_SIZE];
    char pattern[MAX_TEXT];
    char *where;

    snprintf(padded, sizeof(padded), " %s ", query);
    snprintf(pattern, sizeof(pattern), " %s ", phrase);
    where = strstr(padded, pattern);

    if (where == NULL) {
        return -1;
    }

    return (int)(where - padded);
}

static int hasWord(const char *query, const char *word)
{
    return phrasePosition(query, word) >= 0;
}

static int hasAny(const char *query, const char *list[], int count)
{
    int i;

    for (i = 0; i < count; i++) {
        if (hasWord(query, list[i])) {
            return 1;
        }
    }

    return 0;
}

static int isStopWord(const char *word)
{
    int i;

    for (i = 0; i < COUNT_OF(stopWords); i++) {
        if (strcmp(word, stopWords[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

static int findNumber(const char *query, int *value)
{
    char copy[MAX_TEXT];
    char *token;
    int number;

    strncpy(copy, query, MAX_TEXT - 1);
    copy[MAX_TEXT - 1] = '\0';
    token = strtok(copy, " ");

    while (token != NULL) {
        if (parsePositiveInt(token, &number) && number >= MIN_BUDGET) {
            *value = number;

            return 1;
        }

        token = strtok(NULL, " ");
    }

    return 0;
}

static int findFoodTerm(const char *query, char *term, int size)
{
    char copy[MAX_TEXT];
    char *token;

    strncpy(copy, query, MAX_TEXT - 1);
    copy[MAX_TEXT - 1] = '\0';
    token = strtok(copy, " ");

    while (token != NULL) {
        if (strlen(token) >= 3 && !isStopWord(token) && countFoodMatches(token) > 0) {
            strncpy(term, token, (size_t)(size - 1));
            term[size - 1] = '\0';

            return 1;
        }

        token = strtok(NULL, " ");
    }

    return 0;
}

static void addFound(int id, int pos, int ids[], int positions[], int *count)
{
    int i;

    for (i = 0; i < *count; i++) {
        if (ids[i] == id) {
            if (pos < positions[i]) {
                positions[i] = pos;
            }

            return;
        }
    }

    ids[*count] = id;
    positions[*count] = pos;
    (*count)++;
}

static void sortFound(int ids[], int positions[], int count)
{
    int i;
    int j;
    int temp;

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - 1 - i; j++) {
            if (positions[j] > positions[j + 1]) {
                temp = positions[j];
                positions[j] = positions[j + 1];
                positions[j + 1] = temp;
                temp = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = temp;
            }
        }
    }
}

static int collectLocations(const char *query, int ids[], int positions[])
{
    char lower[MAX_TEXT];
    const char *name;
    int count;
    int total;
    int id;
    int pos;
    int i;

    count = 0;
    total = getLocationCount();

    for (id = 1; id <= total; id++) {
        name = getLocationName(id);
        strncpy(lower, name, MAX_TEXT - 1);
        lower[MAX_TEXT - 1] = '\0';
        toLowerCase(lower);
        pos = phrasePosition(query, lower);

        if (pos >= 0) {
            addFound(id, pos, ids, positions, &count);
        }
    }

    for (i = 0; i < ALIAS_COUNT; i++) {
        id = findLocation(aliases[i].target);
        pos = phrasePosition(query, aliases[i].phrase);

        if (id != -1 && pos >= 0) {
            addFound(id, pos, ids, positions, &count);
        }
    }

    sortFound(ids, positions, count);

    return count;
}

static void printNeighbors(int id)
{
    int total;
    int other;
    int first;

    total = getLocationCount();
    first = 1;
    printf("Directly connected to: ");

    for (other = 1; other <= total; other++) {
        if (other != id && getDistance(id, other) > 0) {
            if (!first) {
                printf(", ");
            }

            printf("%s", getLocationName(other));
            first = 0;
        }
    }

    if (first) {
        printf("no connections listed");
    }

    printf("\n");
}

static void handleHelp(void)
{
    printf("You can ask me things like:\n");
    printf("  biryani price      where can I find biryani\n");
    printf("  food under 150     cheap food\n");
    printf("  show cafeterias    badr canteen menu\n");
    printf("  where is the library\n");
    printf("  route from Main Gate to Mosque\n");
    printf("Roman Urdu words I know:\n");
    printf("  kahan (where), khana (food), sasta (cheap), qareeb (near), kitne (price)\n");
    printf("  biryani kahan milegi, sasta khana, main gate se library tak\n");
}

static void handleRoute(const char *query)
{
    int ids[MAX_LOCATIONS];
    int positions[MAX_LOCATIONS];
    int count;
    int start;
    int end;
    int fromPos;

    count = collectLocations(query, ids, positions);

    if (count < 2) {
        printf("I need two places. Try: route from Main Gate to Library\n");

        return;
    }

    start = ids[0];
    end = ids[1];
    fromPos = phrasePosition(query, "from");

    if (fromPos >= 0 && positions[0] < fromPos) {
        start = ids[1];
        end = ids[0];
    }

    printRoute(start, end);
}

static void handlePrice(const char *query)
{
    char term[MAX_TEXT];
    int budget;
    int hasBudget;
    int hasTerm;
    int shown;

    budget = 0;
    hasBudget = findNumber(query, &budget);
    hasTerm = findFoodTerm(query, term, (int)sizeof(term));

    if (!hasBudget && hasAny(query, cheapWords, COUNT_OF(cheapWords))) {
        budget = CHEAP_LIMIT;
        hasBudget = 1;
        printf("Cheap means Rs. %d or less.\n", CHEAP_LIMIT);
    }

    if (!hasTerm) {
        term[0] = '\0';
    }

    if (hasBudget) {
        shown = searchByBudget(budget, term);
    }
    else if (hasTerm) {
        shown = searchFood(term);
    }
    else {
        printf("Tell me an item or a budget, for example: food under 150\n");

        return;
    }

    if (shown == 0) {
        printf("No matching items found.\n");
    }
}

static void handleCafeteria(const char *query)
{
    char lower[MAX_TEXT];
    const char *name;
    int id;
    int found;

    found = 0;

    for (id = 1; id <= MAX_CAFETERIAS; id++) {
        name = getCafeteriaName(id);

        if (name != NULL) {
            strncpy(lower, name, MAX_TEXT - 1);
            lower[MAX_TEXT - 1] = '\0';
            toLowerCase(lower);

            if (phrasePosition(query, lower) >= 0) {
                viewCafeteria(id);
                found = 1;
            }
        }
    }

    if (!found) {
        listCafeterias();
    }
}

static void handleLocation(const char *query)
{
    int ids[MAX_LOCATIONS];
    int positions[MAX_LOCATIONS];
    int count;

    count = collectLocations(query, ids, positions);

    if (count == 0) {
        printf("I could not find that place. Try: Mosque, Library, Gate 2, Academic Block 1.\n");

        return;
    }

    printf("Found: ID %d - %s\n", ids[0], getLocationName(ids[0]));
    printNeighbors(ids[0]);
}

static void handleFood(const char *query)
{
    char term[MAX_TEXT];

    if (findFoodTerm(query, term, (int)sizeof(term))) {
        if (searchFood(term) == 0) {
            printf("No matching food found.\n");
        }
    }
    else {
        displayFood();
    }
}

static const char *intentName(int intent)
{
    switch (intent) {
        case INTENT_FOOD_SEARCH:
            return "food search";
        case INTENT_PRICE_SEARCH:
            return "price search";
        case INTENT_LOCATION_SEARCH:
            return "location search";
        case INTENT_ROUTE_HELP:
            return "route help";
        case INTENT_CAFETERIA_SEARCH:
            return "cafeteria search";
        case INTENT_HELP:
            return "help";
        default:
            return "unknown request";
    }
}

void normalizeQuery(char *text)
{
    int i;
    int j;
    int lastSpace;

    j = 0;
    lastSpace = 1;

    for (i = 0; text[i] != '\0'; i++) {
        if (isalnum((unsigned char)text[i])) {
            text[j] = (char)tolower((unsigned char)text[i]);
            j++;
            lastSpace = 0;
        }
        else if (!lastSpace) {
            text[j] = ' ';
            j++;
            lastSpace = 1;
        }
    }

    if (j > 0 && text[j - 1] == ' ') {
        j--;
    }

    text[j] = '\0';
}

int detectIntent(const char *query)
{
    char term[MAX_TEXT];
    int ids[MAX_LOCATIONS];
    int positions[MAX_LOCATIONS];
    int budget;
    int locationTotal;

    if (query[0] == '\0') {
        return INTENT_UNKNOWN;
    }

    if (hasAny(query, helpWords, COUNT_OF(helpWords))) {
        return INTENT_HELP;
    }

    if (hasAny(query, routeWords, COUNT_OF(routeWords))
        || (hasWord(query, "from") && hasWord(query, "to"))
        || (hasWord(query, "se") && hasWord(query, "tak"))) {
        return INTENT_ROUTE_HELP;
    }

    locationTotal = collectLocations(query, ids, positions);

    if (hasAny(query, priceWords, COUNT_OF(priceWords))
        || (findNumber(query, &budget) && locationTotal == 0)) {
        return INTENT_PRICE_SEARCH;
    }

    if (hasAny(query, cafeWords, COUNT_OF(cafeWords))) {
        return INTENT_CAFETERIA_SEARCH;
    }

    if (locationTotal > 0) {
        return INTENT_LOCATION_SEARCH;
    }

    if (findFoodTerm(query, term, (int)sizeof(term)) || hasAny(query, foodWords, COUNT_OF(foodWords))) {
        return INTENT_FOOD_SEARCH;
    }

    return INTENT_UNKNOWN;
}

void processQuery(const char *input)
{
    char query[MAX_TEXT];
    int intent;

    strncpy(query, input, MAX_TEXT - 1);
    query[MAX_TEXT - 1] = '\0';
    normalizeQuery(query);

    if (query[0] == '\0') {
        printf("Please type a question. Type 'help' for examples.\n");

        return;
    }

    intent = detectIntent(query);
    printf("Understood: %s\n", intentName(intent));

    switch (intent) {
        case INTENT_HELP:
            handleHelp();
            break;
        case INTENT_ROUTE_HELP:
            handleRoute(query);
            break;
        case INTENT_PRICE_SEARCH:
            handlePrice(query);
            break;
        case INTENT_CAFETERIA_SEARCH:
            handleCafeteria(query);
            break;
        case INTENT_LOCATION_SEARCH:
            handleLocation(query);
            break;
        case INTENT_FOOD_SEARCH:
            handleFood(query);
            break;
        default:
            printf("Sorry, I did not understand that.\n");
            printf("I only know a small set of English and Roman Urdu phrases.\n");
            printf("Type 'help' to see examples.\n");
            break;
    }
}
