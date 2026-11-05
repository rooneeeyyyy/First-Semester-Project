#include <stdio.h>

#define COUNT 8

int main(void)
{
    const char *names[COUNT] = {
        "Test Biryani", "Test Chicken Roll", "Test Samosa", "Test Fries",
        "Test Tea", "Test Cold Drink", "Test Burger", "Test Biryani"
    };
    int prices[COUNT] = {250, 180, 50, 150, 60, 100, 300, 270};
    int budget;
    int result;
    int i;
    int affordable;

    printf("%-4s %-20s %8s\n", "ID", "Name", "Price");

    for (i = 0; i < COUNT; i++) {
        printf("%-4d %-20s %8d\n", i + 1, names[i], prices[i]);
    }

    printf("\nEnter your budget: ");
    result = scanf("%d", &budget);

    if (result != 1 || budget <= 0) {
        printf("Error: budget must be a whole number above 0.\n");

        return 1;
    }

    affordable = 0;

    for (i = 0; i < COUNT; i++) {
        if (prices[i] <= budget) {
            affordable++;
        }
    }

    printf("%d item(s) cost Rs. %d or less.\n", affordable, budget);

    return 0;
}