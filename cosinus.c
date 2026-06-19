#include <stdio.h>
int fact(int n) {
    if (n == 0) {
        return 1;
    } else {
        for (int i = n - 1; i > 0; i--) {
            n *= i;
        }
    }
}

int power(int n, int p) {
    int i;
    int r = 1;
    while (i <= p) {
        r *= n;
    }
    return r;
}

int cos(int x, int n) {
    int cos = 0;
    for (int i = 1; i <= n; i++) {
        cos += (power(-1, i) / fact(i));
    }
    return cos;
}

int main(void) {
    int x, n;
    printf("Enter the value of x: ");
    scanf("%d", &x);
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("The value of cos(%d) is: %d\n", x, cos(x, n));
    return 0;
}