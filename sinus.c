#include <stdio.h>

double fact(int n) {
    if (n == 0) {
        return 1;
    } else {
        double f = n;
        for (int i = n-1; i > 1; i--) {
        f *= i;
        }
        return f;
    }
}

double power(double n, int p) {
    double P = 1;
    for (int i = 1; i <= p; i++) {
        P *= n;
    }
    return P;
}

double sinus(double x, int n) {
    double sum = 0.0;
    for (int k = 0; k < n; k++) {
        int exp = 2 * k + 1;
        double term = power(x, exp) / fact(exp);
        if (k % 2 != 0) {
            term = -term;
        }
        sum += term;
    }
    return sum;
}

int main() {
    double x;
    int n;
    printf("Which sinus should we calculate and with which order?");
    scanf("%lf %d", &x, &n);
    printf("The sinus of %f is %f", x, sinus(x, n));
    return 0;
}