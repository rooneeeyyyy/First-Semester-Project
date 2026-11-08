#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void trimNewline(char *text)
{
    text[strcspn(text, "\r\n")] = '\0';
}

void trimSpaces(char *text)
{
    int start;
    int end;

    start = 0;

    while (text[start] == ' ' || text[start] == '\t') {
        start++;
    }

    end = (int)strlen(text);

    while (end > start && (text[end - 1] == ' ' || text[end - 1] == '\t')) {
        end--;
    }

    memmove(text, text + start, (size_t)(end - start));
    text[end - start] = '\0';
}

void toLowerCase(char *text)
{
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        text[i] = (char)tolower((unsigned char)text[i]);
    }
}

int equalsIgnoreCase(const char *first, const char *second)
{
    int i;

    for (i = 0; first[i] != '\0' && second[i] != '\0'; i++) {
        if (tolower((unsigned char)first[i]) != tolower((unsigned char)second[i])) {
            return 0;
        }
    }

    return first[i] == second[i];
}

int containsIgnoreCase(const char *text, const char *part)
{
    char textCopy[MAX_TEXT];
    char partCopy[MAX_TEXT];

    strncpy(textCopy, text, MAX_TEXT - 1);
    textCopy[MAX_TEXT - 1] = '\0';
    strncpy(partCopy, part, MAX_TEXT - 1);
    partCopy[MAX_TEXT - 1] = '\0';

    toLowerCase(textCopy);
    toLowerCase(partCopy);

    return strstr(textCopy, partCopy) != NULL;
}

int readLine(const char *prompt, char *buffer, int size)
{
    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';

        return 0;
    }

    trimNewline(buffer);
    trimSpaces(buffer);

    return 1;
}

int splitCsv(char *line, char *fields[], int maxFields)
{
    int count;
    char *p;

    count = 1;
    fields[0] = line;

    for (p = line; *p != '\0'; p++) {
        if (*p == ',') {
            *p = '\0';

            if (count < maxFields) {
                fields[count] = p + 1;
            }

            count++;
        }
    }

    return count;
}

int parsePositiveInt(const char *text, int *value)
{
    char *end;
    long number;

    if (text[0] == '\0') {
        return 0;
    }

    number = strtol(text, &end, 10);

    if (*end != '\0' || number <= 0 || number > 1000000) {
        return 0;
    }

    *value = (int)number;

    return 1;
}