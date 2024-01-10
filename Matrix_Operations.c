#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int** create_matrix(int n, int m){
    int** A= (int**)malloc(sizeof(int*)*n); // pointers to the rows
    for(int i=0; i<n;i++){
        A[i] = (int*)malloc(sizeof(int)*m); // initialize the elements in the rows
    }
    return A;
}

int** matrix_sum(int**A, int**B,int n, int m){
    int **sum = create_matrix(n,m);
    for(int i=0; i<n;i++){
        for(int j=0; j<m;j++){
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
    return sum;
}

int** matrix_multiplication(int**A, int**B, int n_a, int m_a, int n_b, int m_b){
    if(m_a != n_b){
        printf("Dimesions of matrix A and B don't match");
        exit(1);
    }
    int** prod = create_matrix(n_a,m_b);
    for(int i = 0; i<n_a;i++){
        for(int j = 0; j<m_b;j++){
            prod[i][j] = 0;
        }
    }

    for(int i=0; i<n_a;i++){
        for(int p=0; p<m_b;p++){
            for(int j=0; j<m_a;j++){
                prod[i][p] += A[i][j]*B[j][p];
            }
        }
    }
    return prod;
}

void print_matrix(int**A, int n, int m){
    for(int i=0; i<n;i++){
        for(int j=0; j<m;j++){
            printf("%d, ", A[i][j]);
        }
        printf("\n");
    }
}

int **matrix_transpose(int ** A,int n, int m){
    int** A_T = create_matrix(m,n);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            A_T[j][i] = A[i][j];
        }
    }
    return A_T;
}


int main(void){
    int n=2; int m = 2;
    int** A = create_matrix(n,m);
    A[0][0] = 1; A[0][1] = 1;
    A[1][0] = 3; A[1][1] = 2;
    int** B = create_matrix(n,m);
    B[0][0] = 1; B[0][1] = 1;
    B[1][0] = 3; B[1][1] = 2;

    int n_c = 2; int m_c = 3;
    int**C = create_matrix(n_c,m_c);
    C[0] = (int[]){0,1,2};
    C[1] = (int[]){2,3,4};
    int**C_T = matrix_transpose(C,n_c,m_c);
    int **D = matrix_multiplication(C,C_T,n_c,m_c,m_c,n_c);


    int**sum = matrix_sum(A,B,n,m);
    int**prod = matrix_multiplication(A,B,n,m,n,m);

    printf("A =\n");
    print_matrix(A,n,m);
    printf("\n");
    printf("B = \n");
    print_matrix(B,n,m);
    printf("\n");
    printf("A + B = \n");
    print_matrix(sum,n,m);
    printf("\n");
    printf("A * B = \n");
    print_matrix(prod,n,m);
    printf("\n");
    printf("C = \n");
    print_matrix(C,n_c,m_c);
    printf("\n");
    printf("C^T = \n");
    print_matrix(C_T,m_c,n_c);
    printf("\nMatrix C * C^T:\n");
    print_matrix(D,n_c,n_c);


    return 0;
}