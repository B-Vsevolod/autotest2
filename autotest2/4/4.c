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
    if (fscanf(data_file, "%d %d %d %d", &M, &N, &L, &K) != 4) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    if (L <= 0 || K <= 0) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int **array = (int **)malloc(L * sizeof(int *));
    if (array == NULL) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }
    for (int i = 0; i < L; i++) {
        array[i] = (int *)malloc(K * sizeof(int));
        if (array[i] == NULL) {
            for (int j = 0; j < i; j++) free(array[j]);
            free(array);
            fclose(data_file);
            FILE *res_file = fopen("res.txt", "w");
            if (res_file != NULL) {
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
                if (res_file != NULL) {
                    fprintf(res_file, "ERROR");
                    fclose(res_file);
                }
                return -1;
            }
        }
    }
    fclose(data_file);

    int **original = (int **)malloc(L * sizeof(int *));
    if (original == NULL) {
        for (int i = 0; i < L; i++) free(array[i]);
        free(array);
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
            for (int x = 0; x < L; x++) free(array[x]);
            free(array);
            FILE *res_file = fopen("res.txt", "w");
            if (res_file != NULL) {
                fprintf(res_file, "ERROR");
                fclose(res_file);
            }
            return -1;
        }
        for (int j = 0; j < K; j++) original[i][j] = array[i][j];
    }

    int *row_valid = (int *)calloc(L, sizeof(int));
    int *col_valid = (int *)calloc(K, sizeof(int));
    if (row_valid == NULL || col_valid == NULL) {
        free(row_valid);
        free(col_valid);
        for (int i = 0; i < L; i++) {
            free(original[i]);
            free(array[i]);
        }
        free(original);
        free(array);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file != NULL) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (original[i][j] >= M && original[i][j] <= N) {
                row_valid[i] = 1;
                break;
            }
        }
    }

    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (original[i][j] >= M && original[i][j] <= N) {
                col_valid[j] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < L; i++) {
        if (!row_valid[i]) continue;
        for (int j = 0; j < K; j++) {
            if (!col_valid[j]) continue;
            int current = original[i][j];
            int found = 0;
            for (int c = 0; c < j; c++) {
                if (col_valid[c] && original[i][c] == current) {
                    found = 1;
                    break;
                }
            }
            array[i][j] = found ? 1 : 0;
        }
    }

    FILE *res_file = fopen("res.txt", "w");
    if (res_file == NULL) {
        free(row_valid);
        free(col_valid);
        for (int i = 0; i < L; i++) {
            free(original[i]);
            free(array[i]);
        }
        free(original);
        free(array);
        return -1;
    }

    fprintf(res_file, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(res_file, "%d", array[i][j]);
            if (j < K - 1) fprintf(res_file, " ");
        }
        fprintf(res_file, "\n");
    }

    fclose(res_file);
    free(row_valid);
    free(col_valid);
    for (int i = 0; i < L; i++) {
        free(original[i]);
        free(array[i]);
    }
    free(original);
    free(array);

    return 0;
}