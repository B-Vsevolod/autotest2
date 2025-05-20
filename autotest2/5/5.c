#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *data_file = fopen("data.txt", "r");
    if (data_file == NULL) {
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int M, N, L, K;
    if (fscanf(data_file, "%d %d %d %d", &M, &N, &L, &K) != 4) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int **arr = malloc(L * sizeof(int *));
    if (arr == NULL) {
        fclose(data_file);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int read_error = 0;
    for (int i = 0; i < L; i++) {
        arr[i] = malloc(K * sizeof(int));
        if (arr[i] == NULL) {
            read_error = 1;
            break;
        }
        for (int j = 0; j < K; j++) {
            if (fscanf(data_file, "%d", &arr[i][j]) != 1) {
                read_error = 1;
                break;
            }
        }
        if (read_error) break;
    }

    fclose(data_file);

    if (read_error) {
        for (int i = 0; i < L; i++) {
            if (arr[i]) free(arr[i]);
        }
        free(arr);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    int *rows_R = calloc(L, sizeof(int));
    if (rows_R == NULL) {
        for (int i = 0; i < L; i++) free(arr[i]);
        free(arr);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (arr[i][j] % M == N) {
                rows_R[i] = 1;
                break;
            }
        }
    }

    int *cols_C = calloc(K, sizeof(int));
    if (cols_C == NULL) {
        free(rows_R);
        for (int i = 0; i < L; i++) free(arr[i]);
        free(arr);
        FILE *res_file = fopen("res.txt", "w");
        if (res_file) {
            fprintf(res_file, "ERROR");
            fclose(res_file);
        }
        return -1;
    }

    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (arr[i][j] % M == N) {
                cols_C[j] = 1;
                break;
            }
        }
    }

    int *elements = NULL;
    int *counts = NULL;
    size_t num_elements = 0;

    for (int i = 0; i < L; i++) {
        if (rows_R[i]) {
            for (int j = 0; j < K; j++) {
                int val = arr[i][j];
                int found = 0;
                for (size_t k = 0; k < num_elements; k++) {
                    if (elements[k] == val) {
                        counts[k]++;
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    num_elements++;
                    elements = realloc(elements, num_elements * sizeof(int));
                    counts = realloc(counts, num_elements * sizeof(int));
                    if (!elements || !counts) {
                        free(elements);
                        free(counts);
                        free(rows_R);
                        free(cols_C);
                        for (int i = 0; i < L; i++) free(arr[i]);
                        free(arr);
                        FILE *res_file = fopen("res.txt", "w");
                        if (res_file) {
                            fprintf(res_file, "ERROR");
                            fclose(res_file);
                        }
                        return -1;
                    }
                    elements[num_elements - 1] = val;
                    counts[num_elements - 1] = 1;
                }
            }
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (rows_R[i] && cols_C[j]) {
                int val = arr[i][j];
                int frequency = 0;
                for (size_t k = 0; k < num_elements; k++) {
                    if (elements[k] == val) {
                        frequency = counts[k];
                        break;
                    }
                }
                arr[i][j] = (frequency >= 2) ? 1 : 0;
            }
        }
    }

    free(elements);
    free(counts);
    free(rows_R);
    free(cols_C);

    FILE *res_file = fopen("res.txt", "w");
    if (res_file == NULL) {
        for (int i = 0; i < L; i++) free(arr[i]);
        free(arr);
        return -1;
    }

    fprintf(res_file, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(res_file, "%d", arr[i][j]);
            if (j < K - 1) fprintf(res_file, " ");
        }
        fprintf(res_file, "\n");
    }

    fclose(res_file);

    for (int i = 0; i < L; i++) free(arr[i]);
    free(arr);

    return 0;
}