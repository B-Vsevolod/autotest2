#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *file = fopen("data.txt", "r");
    if (!file) {
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }

    int M, N, L, K;
    if (fscanf(file, "%d %d %d %d", &M, &N, &L, &K) != 4) {
        fclose(file);
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }

    if (L <= 0 || K <= 0) {
        fclose(file);
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }

    int **a = malloc(L * sizeof(int *));
    if (!a) {
        fclose(file);
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        a[i] = malloc(K * sizeof(int));
        if (!a[i]) {
            for (int j = 0; j < i; j++) free(a[j]);
            free(a);
            fclose(file);
            FILE *res = fopen("res.txt", "w");
            if (res) {
                fprintf(res, "ERROR");
                fclose(res);
            }
            return -1;
        }
        for (int j = 0; j < K; j++) {
            if (fscanf(file, "%d", &a[i][j]) != 1) {
                for (int k = 0; k <= i; k++) free(a[k]);
                free(a);
                fclose(file);
                FILE *res = fopen("res.txt", "w");
                if (res) {
                    fprintf(res, "ERROR");
                    fclose(res);
                }
                return -1;
            }
        }
    }
    fclose(file);

    // Создание временной копии массива
    int **tmp = malloc(L * sizeof(int *));
    if (!tmp) {
        for (int i = 0; i < L; i++) free(a[i]);
        free(a);
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }
    for (int i = 0; i < L; i++) {
        tmp[i] = malloc(K * sizeof(int));
        if (!tmp[i]) {
            for (int j = 0; j < i; j++) free(tmp[j]);
            free(tmp);
            for (int k = 0; k < L; k++) free(a[k]);
            free(a);
            FILE *res = fopen("res.txt", "w");
            if (res) {
                fprintf(res, "ERROR");
                fclose(res);
            }
            return -1;
        }
        memcpy(tmp[i], a[i], K * sizeof(int));
    }

    // Определение строк с условием
    int *rows = calloc(L, sizeof(int));
    if (!rows) {
        for (int i = 0; i < L; i++) free(tmp[i]);
        free(tmp);
        for (int i = 0; i < L; i++) free(a[i]);
        free(a);
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (tmp[i][j] % M == N) {
                rows[i] = 1;
                break;
            }
        }
    }

    // Определение столбцов с условием
    int *cols = calloc(K, sizeof(int));
    if (!cols) {
        free(rows);
        for (int i = 0; i < L; i++) free(tmp[i]);
        free(tmp);
        for (int i = 0; i < L; i++) free(a[i]);
        free(a);
        FILE *res = fopen("res.txt", "w");
        if (res) {
            fprintf(res, "ERROR");
            fclose(res);
        }
        return -1;
    }
    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (tmp[i][j] % M == N) {
                cols[j] = 1;
                break;
            }
        }
    }

    // Обработка элементов множества X
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (rows[i] && cols[j]) {
                int val = tmp[i][j];
                int found = 0;
                for (int s = 0; s < j; s++) {
                    if (cols[s]) {
                        for (int row = 0; row < L; row++) {
                            if (tmp[row][s] == val) {
                                found = 1;
                                break;
                            }
                        }
                        if (found) break;
                    }
                }
                a[i][j] = found ? 1 : 0;
            }
        }
    }

    // Запись результата
    FILE *res = fopen("res.txt", "w");
    if (!res) {
        free(rows);
        free(cols);
        for (int i = 0; i < L; i++) free(tmp[i]);
        free(tmp);
        for (int i = 0; i < L; i++) free(a[i]);
        free(a);
        return -1;
    }
    fprintf(res, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(res, "%d", a[i][j]);
            if (j < K - 1) fprintf(res, " ");
        }
        fprintf(res, "\n");
    }

    // Освобождение памяти
    free(rows);
    free(cols);
    for (int i = 0; i < L; i++) {
        free(tmp[i]);
        free(a[i]);
    }
    free(tmp);
    free(a);
    fclose(res);

    return 0;
}