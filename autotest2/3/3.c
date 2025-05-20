#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *data_file = fopen("data.txt", "r");
    if (data_file == NULL) {
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int M, N, L, K;
    if (fscanf(data_file, "%d %d %d %d", &M, &N, &L, &K) != 4 || M <= 0 || N <= 0 || L <= 0 || K <= 0) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int **matrix = (int **)malloc(L * sizeof(int *));
    if (matrix == NULL) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        matrix[i] = (int *)malloc(K * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            fclose(data_file);
            FILE *res_file = fopen("res.txt", "w");
            if (res_file != NULL) {
                fprintf(res_file, "ERROR");
                fclose(res_file);
            }
            return -1;
        }
        for (int j = 0; j < K; j++) {
            if (fscanf(data_file, "%d", &matrix[i][j]) != 1) {
                for (int x = 0; x <= i; x++) free(matrix[x]);
                free(matrix);
                fclose(data_file);
                FILE *res_file = fopen("res.txt", "w");
                if (res_file != NULL) {
                    fprintf(res_file, "ERROR");
                    fclose(res_file);
                }
                return -1;
            }
        }
    }
    fclose(data_file);

    // Create copy of original matrix
    int **original = (int **)malloc(L * sizeof(int *));
    if (original == NULL) {
        for (int i = 0; i < L; i++) free(matrix[i]);
        free(matrix);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }
    for (int i = 0; i < L; i++) {
        original[i] = (int *)malloc(K * sizeof(int));
        if (original[i] == NULL) {
            for (int j = 0; j < i; j++) free(original[j]);
            free(original);
            for (int x = 0; x < L; x++) free(matrix[x]);
            free(matrix);
            FILE *res_file = fopen("res.txt", "w");
            if (res_file != NULL) {
                fprintf(res_file, "ERROR");
                fclose(res_file);
            }
            return -1;
        }
        for (int j = 0; j < K; j++) {
            original[i][j] = matrix[i][j];
        }
    }

    // Determine R rows
    int *rows_R = (int *)calloc(L, sizeof(int));
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (original[i][j] >= M && original[i][j] <= N) {
                rows_R[i] = 1;
                break;
            }
        }
    }

    // Determine C columns
    int *cols_C = (int *)calloc(K, sizeof(int));
    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (original[i][j] >= M && original[i][j] <= N) {
                cols_C[j] = 1;
                break;
            }
        }
    }

    // Process elements in X
    for (int i = 0; i < L; i++) {
        if (!rows_R[i]) continue;
        for (int j = 0; j < K; j++) {
            if (!cols_C[j]) continue;

            int count = 0;
            for (int x = 0; x < L; x++) {
                if (rows_R[x] && original[x][j] == original[i][j]) {
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

    // Write to res.txt
    FILE *res_file = fopen("res.txt", "w");
    if (res_file == NULL) {
        for (int i = 0; i < L; i++) {
            free(matrix[i]);
            free(original[i]);
        }
        free(matrix);
        free(original);
        free(rows_R);
        free(cols_C);
        return -1;
    }

    fprintf(res_file, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(res_file, "%d", matrix[i][j]);
            if (j != K - 1) fprintf(res_file, " ");
        }
        fprintf(res_file, "\n");
    }

    // Cleanup
    fclose(res_file);
    for (int i = 0; i < L; i++) {
        free(matrix[i]);
        free(original[i]);
    }
    free(matrix);
    free(original);
    free(rows_R);
    free(cols_C);

    return 0;
}