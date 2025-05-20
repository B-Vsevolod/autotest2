#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *data_file = fopen("data.txt", "r");
    if (!data_file) {
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int M, N, L, K;
    if (fscanf(data_file, "%d %d %d %d", &M, &N, &L, &K) != 4 || M <= 0 || N < 0 || L <= 0 || K <= 0) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int **array = (int **)malloc(L * sizeof(int *));
    if (!array) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        array[i] = (int *)malloc(K * sizeof(int));
        if (!array[i]) {
            for (int j = 0; j < i; j++) free(array[j]);
            free(array);
            fclose(data_file);
            FILE *res_file = fopen("res.txt", "w");
            if (res_file) {
                fprintf(res_file, "ERROR");
                fclose(res_file);
            }
            return -1;
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (fscanf(data_file, "%d", &array[i][j]) != 1) {
                for (int x = 0; x < L; x++) free(array[x]);
                free(array);
                fclose(data_file);
                FILE *res_file = fopen("res.txt", "w");
                if (res_file) {
                    fprintf(res_file, "ERROR");
                    fclose(res_file);
                }
                return -1;
            }
        }
    }
    fclose(data_file);

    int *rows_valid = (int *)calloc(L, sizeof(int));
    int *cols_valid = (int *)calloc(K, sizeof(int));
    if (!rows_valid || !cols_valid) {
        for (int i = 0; i < L; i++) free(array[i]);
        free(array);
        free(rows_valid);
        free(cols_valid);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (array[i][j] % M == N) {
                rows_valid[i] = 1;
                break;
            }
        }
    }

    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (array[i][j] % M == N) {
                cols_valid[j] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < L; i++) {
        if (!rows_valid[i]) continue;
        for (int j = 0; j < K; j++) {
            if (!cols_valid[j]) continue;
            int current = array[i][j];
            int found = 0;
            for (int k = 0; k < j; k++) {
                if (cols_valid[k] && array[i][k] == current) {
                    found = 1;
                    break;
                }
            }
            array[i][j] = found ? 1 : 0;
        }
    }

    FILE *res_file = fopen("res.txt", "w");
    if (!res_file) {
        for (int i = 0; i < L; i++) free(array[i]);
        free(array);
        free(rows_valid);
        free(cols_valid);
        return -1;
    }

    fprintf(res_file, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(res_file, "%d", array[i][j]);
            if (j < K - 1) fprintf(res_file, " ");
        }
        if (i < L - 1) fprintf(res_file, "\n");
    }

    fclose(res_file);

    for (int i = 0; i < L; i++) free(array[i]);
    free(array);
    free(rows_valid);
    free(cols_valid);

    return 0;
}