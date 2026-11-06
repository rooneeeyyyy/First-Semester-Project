#ifndef UTILS_H
#define UTILS_H

#define MAX_TEXT 100

void trimNewline(char *text);
void trimSpaces(char *text);
void toLowerCase(char *text);
int equalsIgnoreCase(const char *first, const char *second);
int containsIgnoreCase(const char *text, const char *part);
int readLine(const char *prompt, char *buffer, int size);

#endif