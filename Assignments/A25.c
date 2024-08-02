// Program to find the greatest/smallest  of 3 numbers
#include <stdio.h>

int Max(int num1, int num2, int num3) {
    int max = num1;

    if (num2 > max) {
        max = num2;
    }

    if (num3 > max) {
        max = num3;
    }

    return max;
}

int Min(int num1, int num2, int num3) {
    int min = num1;

    if (num2 < min) {
        min = num2;
    }

    if (num3 < min) {
        min = num3;
    }

    return min;
}

int main() {
    int num1, num2, num3;

    printf("Enter three numbers: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    int max = Max(num1, num2, num3);
    int min = Min(num1, num2, num3);

    printf("Maximum number: %d\n", max);
    printf("Minimum number: %d\n", min);

    return 0;
}

