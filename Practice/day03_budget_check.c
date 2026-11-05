#include <stdio.h>

int main(void)
{
    int price;
    int budget;
    int result;

    printf("Enter item price: ");
    result = scanf("%d", &price);

    if (result != 1 || price <= 0) {
        printf("Error: price must be a whole number above 0.\n");

        return 1;
    }

    printf("Enter your budget: ");
    result = scanf("%d", &budget);

    if (result != 1 || budget <= 0) {
        printf("Error: budget must be a whole number above 0.\n");

        return 1;
    }

    if (price <= budget) {
        printf("Within budget. You have Rs. %d left.\n", budget - price);
    }
    else {
        printf("Over budget by Rs. %d.\n", price - budget);
    }

    return 0;
}