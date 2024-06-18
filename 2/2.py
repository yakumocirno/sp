#include <stdio.h>
#include <stdlib.h>

// 定義矩陣結構
typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

// 初始化矩陣
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

// 釋放矩陣內存
void free_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// 打印矩陣
void print_matrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%lf ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

// 矩陣加法
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

// 矩陣乘法
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

// 矩陣轉置
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

    Matrix *sum = NULL;
    Matrix *product = NULL;
    Matrix *transpose = NULL;

    int choice;
    do {
        printf("Choose an operation:\n");
        printf("1. Add matrices\n");
        printf("2. Multiply matrices\n");
        printf("3. Transpose matrix A\n");
        printf("4. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sum = add_matrices(a, b);
                printf("Sum of A and B:\n");
                print_matrix(sum);
                free_matrix(sum);
                break;
            case 2:
                product = multiply_matrices(a, b);
                printf("Product of A and B:\n");
                print_matrix(product);
                free_matrix(product);
                break;
            case 3:
                transpose = transpose_matrix(a);
                printf("Transpose of A:\n");
                print_matrix(transpose);
                free_matrix(transpose);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // 釋放內存
    free_matrix(a);
    free_matrix(b);

    return 0;
}
