#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *data_file = fopen("data.txt", "r");
    if (data_file == NULL) {
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) fprintf(res_file, "ERROR");
        if (res_file) fclose(res_file);
        return -1;
    }

    int M, N, L, K;
    if (fscanf(data_file, "%d %d %d %d", &M, &N, &L, &K) != 4 || M <= 0 || N < 0 || L <= 0 || K <= 0) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) fprintf(res_file, "ERROR");
        if (res_file) fclose(res_file);
        return -1;
    }

    int **matrix = (int **)malloc(L * sizeof(int *));
    if (matrix == NULL) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) fprintf(res_file, "ERROR");
        if (res_file) fclose(res_file);
        return -1;
    }
    for (int i = 0; i < L; i++) {
        matrix[i] = (int *)malloc(K * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            fclose(data_file);
            FILE *res_file = fopen("res.txt", "w");
            if (res_file) fprintf(res_file, "ERROR");
            if (res_file) fclose(res_file);
            return -1;
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (fscanf(data_file, "%d", &matrix[i][j]) != 1) {
                for (int x = 0; x < L; x++) free(matrix[x]);
                free(matrix);
                fclose(data_file);
                FILE *res_file = fopen("res.txt", "w");
                if (res_file) fprintf(res_file, "ERROR");
                if (res_file) fclose(res_file);
                return -1;
            }
        }
    }
    fclose(data_file);

    int *rows_R = (int *)calloc(L, sizeof(int));
    int *cols_C = (int *)calloc(K, sizeof(int));

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (matrix[i][j] % M == N) {
                rows_R[i] = 1;
                break;
            }
        }
    }

    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (matrix[i][j] % M == N) {
                cols_C[j] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < L; i++) {
        if (!rows_R[i]) continue;
        for (int j = 0; j < K; j++) {
            if (!cols_C[j]) continue;
            int count = 0;
            int current = matrix[i][j];
            for (int x = 0; x < L; x++) {
                if (rows_R[x] && matrix[x][j] == current) {
                    count++;
                }
            }
            if (count >= 2) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }

    free(rows_R);
    free(cols_C);

    FILE *res_file = fopen("res.txt", "w");
    if (res_file == NULL) {
        for (int i = 0; i < L; i++) free(matrix[i]);
        free(matrix);
        FILE *err_file = fopen("res.txt", "w");
        if (err_file) fprintf(err_file, "ERROR");
        if (err_file) fclose(err_file);
        return -1;
    }

    fprintf(res_file, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(res_file, "%d ", matrix[i][j]);
        }
        fprintf(res_file, "\n");
    }
    fclose(res_file);

    for (int i = 0; i < L; i++) free(matrix[i]);
    free(matrix);

    return 0;
}