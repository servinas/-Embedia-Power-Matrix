#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int mod = 1e9 + 7, MaxStringLen = 10;

long int FastPower(long int base, long int power, long int mod);

long int StringToInt(char *str);

bool isEmbediaPowerMatrix(char ***matrix, int rows, int cols);

void removeQuotes(char *str);

void main() {
    int rows, cols;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);
    char ***matrix = (char ***) malloc(rows * sizeof(char **));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (char **) malloc(cols * sizeof(char *));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (char *) malloc(MaxStringLen * sizeof(char));
        }
    }
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%s", matrix[i][j]);
            removeQuotes(matrix[i][j]);
        }
    }
    if (isEmbediaPowerMatrix(matrix, rows, cols)) {
        printf("Embedia Power Matrix\n");
    } else {
        printf("Not an Embedia Power Matrix\n");
    }
    return;
}

void removeQuotes(char *str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        for (int i = 0; i < len - 2; i++) {
            str[i] = str[i + 1];
        }
        str[len - 2] = '\0';
    }
}

bool isEmbediaPowerMatrix(char ***matrix, int rows, int cols) {
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            long int base = StringToInt(matrix[i + 1][j]);
            long int power = StringToInt(matrix[i - 1][j]);
            long int CalculatedPower = FastPower(base, power, mod);
            long int CurrentPower = StringToInt(matrix[i][j]);
            if (CalculatedPower != CurrentPower) {
                return false;
            }
        }
    }
    return true;
}

long int StringToInt(char *str) {
    long int ret = 0;
    int sz = strlen(str);
    int rem = 0;
    for (int i = 0; i < sz; i++) {
        ret *= 10;
        ret += (str[i] - '0');
    }
    return ret;
}

long int FastPower(long int base, long int power, long int mod) {
    long int ans = 1;
    while (power > 0) {
        if (power & 1) {
            ans = ((ans % mod) * (base % mod)) % mod;
        }
        base = ((base % mod) * (base % mod)) % mod;
        power /= 2;
    }
    return ans;
}