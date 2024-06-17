#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix* create_matrix(int rows, int cols) {
    Matrix *matrix = (Matrix*)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

void free_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

void print_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* add_matrices(Matrix *a, Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        printf("矩陣尺寸不匹配\n");
        return NULL;
    }
    Matrix *result = create_matrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}

Matrix* multiply_matrices(Matrix *a, Matrix *b) {
    if (a->cols != b->rows) {
        printf("矩陣尺寸不匹配\n");
        return NULL;
    }
    Matrix *result = create_matrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            result->data[i][j] = 0;
            for (int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}

Matrix* transpose_matrix(Matrix *matrix) {
    Matrix *result = create_matrix(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j];
        }
    }
    return result;
}

int main() {

    Matrix *a = create_matrix(2, 2);
    a->data[0][0] = 1; a->data[0][1] = 2;
    a->data[1][0] = 3; a->data[1][1] = 4;

    Matrix *b = create_matrix(2, 2);
    b->data[0][0] = 5; b->data[0][1] = 6;
    b->data[1][0] = 7; b->data[1][1] = 8;

    Matrix *sum = add_matrices(a, b);
    Matrix *product = multiply_matrices(a, b);
    Matrix *transpose = transpose_matrix(a);

    printf("Matrix A:\n");
    print_matrix(a);
    printf("Matrix B:\n");
    print_matrix(b);
    printf("Sum of A and B:\n");
    print_matrix(sum);
    printf("Product of A and B:\n");
    print_matrix(product);
    printf("Transpose of A:\n");
    print_matrix(transpose);

    free_matrix(a);
    free_matrix(b);
    free_matrix(sum);
    free_matrix(product);
    free_matrix(transpose);

    return 0;
    
}

