#include <stdio.h>
#include "route.h"
#include "map.h"

int findRoute(int start, int end, int path[], int *pathLength, int *totalDistance)
{
    int count;
    int queue[MAX_LOCATIONS];
    int visited[MAX_LOCATIONS + 1];
    int parent[MAX_LOCATIONS + 1];
    int reversed[MAX_LOCATIONS];
    int head;
    int tail;
    int current;
    int next;
    int steps;
    int i;

    count = getLocationCount();

    if (start < 1 || start > count || end < 1 || end > count) {
        return -1;
    }

    for (i = 0; i <= count; i++) {
        visited[i] = 0;
        parent[i] = 0;
    }

    head = 0;
    tail = 0;
    queue[tail] = start;
    tail++;
    visited[start] = 1;

    while (head < tail && !visited[end]) {
        current = queue[head];
        head++;

        for (next = 1; next <= count; next++) {
            if (!visited[next] && getDistance(current, next) > 0) {
                visited[next] = 1;
                parent[next] = current;
                queue[tail] = next;
                tail++;
            }
        }
    }

    if (!visited[end]) {
        return 0;
    }

    steps = 0;
    current = end;

    while (current != start) {
        reversed[steps] = current;
        steps++;
        current = parent[current];
    }

    reversed[steps] = start;
    steps++;

    for (i = 0; i < steps; i++) {
        path[i] = reversed[steps - 1 - i];
    }

    *pathLength = steps;
    *totalDistance = 0;

    for (i = 0; i < steps - 1; i++) {
        *totalDistance += getDistance(path[i], path[i + 1]);
    }

    return 1;
}

void printRoute(int start, int end)
{
    int path[MAX_LOCATIONS];
    int pathLength;
    int totalDistance;
    int result;
    int i;

    result = findRoute(start, end, path, &pathLength, &totalDistance);

    if (result == -1) {
        printf("Invalid location.\n");
    }
    else if (result == 0) {
        printf("No route found between %s and %s.\n", getLocationName(start), getLocationName(end));
    }
    else if (pathLength == 1) {
        printf("You are already at %s.\n", getLocationName(start));
    }
    else {
        printf("\nRoute from %s to %s:\n", getLocationName(start), getLocationName(end));

        for (i = 0; i < pathLength; i++) {
            printf("%d. %s\n", i + 1, getLocationName(path[i]));
        }

        printf("Connections: %d, estimated distance: %d m\n", pathLength - 1, totalDistance);
    }
}