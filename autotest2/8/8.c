#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *input = fopen("data.txt", "r");
    if (input == NULL) {
        FILE *output = fopen("res.txt", "w");
        if (output) {
            fprintf(output, "ERROR");
            fclose(output);
        }
        return -1;
    }

    int M, N, L, K;
    if (fscanf(input, "%d %d %d %d", &M, &N, &L, &K) != 4) {
        fclose(input);
        FILE *output = fopen("res.txt", "w");
        if (output) {
            fprintf(output, "ERROR");
            fclose(output);
        }
        return -1;
    }

    if (L <= 0 || K <= 0) {
        fclose(input);
        FILE *output = fopen("res.txt", "w");
        if (output) {
            fprintf(output, "ERROR");
            fclose(output);
        }
        return -1;
    }

    int **matrix = (int **)malloc(L * sizeof(int *));
    if (matrix == NULL) {
        fclose(input);
        FILE *output = fopen("res.txt", "w");
        if (output) {
            fprintf(output, "ERROR");
            fclose(output);
        }
        return -1;
    }

    for (int i = 0; i < L; i++) {
        matrix[i] = (int *)malloc(K * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fclose(input);
            FILE *output = fopen("res.txt", "w");
            if (output) {
                fprintf(output, "ERROR");
                fclose(output);
            }
            return -1;
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (fscanf(input, "%d", &matrix[i][j]) != 1) {
                for (int k = 0; k <= i; k++) {
                    free(matrix[k]);
                }
                free(matrix);
                fclose(input);
                FILE *output = fopen("res.txt", "w");
                if (output) {
                    fprintf(output, "ERROR");
                    fclose(output);
                }
                return -1;
            }
        }
    }
    fclose(input);

    int *valid_rows = (int *)calloc(L, sizeof(int));
    int *valid_cols = (int *)calloc(K, sizeof(int));

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (matrix[i][j] >= M && matrix[i][j] <= N) {
                valid_rows[i] = 1;
                break;
            }
        }
    }

    for (int j = 0; j < K; j++) {
        for (int i = 0; i < L; i++) {
            if (matrix[i][j] >= M && matrix[i][j] <= N) {
                valid_cols[j] = 1;
                break;
            }
        }
    }

    int *has_S_before = (int *)calloc(K, sizeof(int));
    int found_S = 0;
    for (int j = 0; j < K; j++) {
        has_S_before[j] = found_S;
        if (valid_cols[j]) {
            found_S = 1;
        }
    }

    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            if (valid_rows[i] && valid_cols[j]) {
                matrix[i][j] = has_S_before[j] ? 1 : 0;
            }
        }
    }

    FILE *output = fopen("res.txt", "w");
    if (output == NULL) {
        free(valid_rows);
        free(valid_cols);
        free(has_S_before);
        for (int i = 0; i < L; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return -1;
    }

    fprintf(output, "%d %d %d %d\n", M, N, L, K);
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < K; j++) {
            fprintf(output, "%d", matrix[i][j]);
            if (j < K - 1) {
                fprintf(output, " ");
            }
        }
        fprintf(output, "\n");
    }
    fclose(output);

    free(valid_rows);
    free(valid_cols);
    free(has_S_before);
    for (int i = 0; i < L; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}