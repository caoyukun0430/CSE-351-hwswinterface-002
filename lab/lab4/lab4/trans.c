/*
CSE 351 Lab 4, Part 2 - Matrix Transposes
*/

/* 
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
// Yukun refer to
// https://yangtau.me/computer-system/csapp-cache.html
// https://zhuanlan.zhihu.com/p/138881600
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M])
{
    // blocking of 8*8 ints
    // for (int i = 0; i < N; i += 8) {
    //     for (int j = 0; j < M; j += 8) {
    //         for (int k = i; k < i+8; k++) {
    //             for (int s = j; s < j+8; s++) {
    //                 B[s][k] = A[k][s];
    //             }
    //         }
    //     }
    // }

    int a0, a1, a2, a3, a4, a5, a6, a7;
    int i, j, k;
    if (M==32)
    {
        // in the order A[0][0,7]->A[0][24,31]->A[8][0,7]->A[24][24,31]

        for (i = 0; i < M; i += 8)
        {
            for (j = 0; j < N; j += 8)
            {
                for (k = i; k < i + 8; k++)
                {
                    a0 = A[k][j];
                    a1 = A[k][j + 1];
                    a2 = A[k][j + 2];
                    a3 = A[k][j + 3];
                    a4 = A[k][j + 4];
                    a5 = A[k][j + 5];
                    a6 = A[k][j + 6];
                    a7 = A[k][j + 7];
                    B[j][k] = a0;
                    B[j + 1][k] = a1;
                    B[j + 2][k] = a2;
                    B[j + 3][k] = a3;
                    B[j + 4][k] = a4;
                    B[j + 5][k] = a5;
                    B[j + 6][k] = a6;
                    B[j + 7][k] = a7;
                }
            }
        }
    }
    else if (M==64)
    {
        int tmp;
        // k is 4*4 sub-blocks under i,j 8*8 blocks
        for (i = 0; i < M; i += 8)
        {
            for (j = 0; j < N; j += 8)
            {
                for (k = 0; k < 4; k++)
                {
                    // A top left
                    a0 = A[k + i][j];
                    a1 = A[k + i][j + 1];
                    a2 = A[k + i][j + 2];
                    a3 = A[k + i][j + 3];

                    // copy
                    // A top right
                    a4 = A[k + i][j + 4];
                    a5 = A[k + i][j + 5];
                    a6 = A[k + i][j + 6];
                    a7 = A[k + i][j + 7];

                    // B top left
                    B[j][k + i] = a0;
                    B[j + 1][k + i] = a1;
                    B[j + 2][k + i] = a2;
                    B[j + 3][k + i] = a3;

                    // copy
                    // B top right
                    B[j + 0][k + 4 + i] = a4;
                    B[j + 1][k + 4 + i] = a5;
                    B[j + 2][k + 4 + i] = a6;
                    B[j + 3][k + 4 + i] = a7;
                }
                for (k = 0; k < 4; k++)
                {
                    // step 1, 2: copy the A[4,0]-A[7,0] into buf1,A[4,4]-A[7,4] into buf2  
                    a0 = A[i + 4][j + k], a4 = A[i + 4][j + k + 4];
                    a1 = A[i + 5][j + k], a5 = A[i + 5][j + k + 4];
                    a2 = A[i + 6][j + k], a6 = A[i + 6][j + k + 4];
                    a3 = A[i + 7][j + k], a7 = A[i + 7][j + k + 4];
                    // step 3: B[0,4-7](which is A[0-3.4]) is stored and replaced by A[4-7,0]
                    tmp = B[j + k][i + 4], B[j + k][i + 4] = a0, a0 = tmp;
                    tmp = B[j + k][i + 5], B[j + k][i + 5] = a1, a1 = tmp;
                    tmp = B[j + k][i + 6], B[j + k][i + 6] = a2, a2 = tmp;
                    tmp = B[j + k][i + 7], B[j + k][i + 7] = a3, a3 = tmp;
                    // step 4: B[0,4-7] is put in B[4,0-3], A[4-7,4] is put into B[4,4-7]
                    B[j + k + 4][i + 0] = a0, B[j + k + 4][i + 4 + 0] = a4;
                    B[j + k + 4][i + 1] = a1, B[j + k + 4][i + 4 + 1] = a5;
                    B[j + k + 4][i + 2] = a2, B[j + k + 4][i + 4 + 2] = a6;
                    B[j + k + 4][i + 3] = a3, B[j + k + 4][i + 4 + 3] = a7;
                }
            }
        }
    }

    // call before evaluating performance, it increases miss!
    // if (is_transpose(M,N,A,B) == 1) {
    //     printf("CORRECT!");
    // }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */
char transpose_32_noconflict_desc[] = "Transpose submission 32 no conflict";
void transpose_32_noconflict(int M, int N, int A[M][N], int B[N][M])
{
    // a better option to avoid diagnoal conflict is to copy A into B
    // then do the tranpose inside B blocks in each iteration
    int i, j, k, l;
    int a0, a1, a2, a3, a4, a5, a6, a7;
    for (i = 0; i < M; i += 8)
    {
        for (j = 0; j < N; j += 8)
        {
            for (k = i, l = j; k < i + 8; k++, l++)
            {
                a0 = A[k][j];
                a1 = A[k][j + 1];
                a2 = A[k][j + 2];
                a3 = A[k][j + 3];
                a4 = A[k][j + 4];
                a5 = A[k][j + 5];
                a6 = A[k][j + 6];
                a7 = A[k][j + 7];
                // copy the transposed block
                B[l][i] = a0;
                B[l][i + 1] = a1;
                B[l][i + 2] = a2;
                B[l][i + 3] = a3;
                B[l][i + 4] = a4;
                B[l][i + 5] = a5;
                B[l][i + 6] = a6;
                B[l][i + 7] = a7;
            }
            // do the transpose before entering next block!
            for (k = 0; k < 8; k++)
            {
                for (l = k + 1; l < 8; l++)
                {
                    // i is row, j is column
                    a0 = B[k + j][l + i];
                    B[k + j][l + i] = B[l + j][k + i];
                    B[l + j][k + i] = a0;
                }
            }
        }
    }
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M])
{
    int i, j, tmp;

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    registerTransFunction(transpose_32_noconflict, transpose_32_noconflict_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M])
{
    int i, j;

    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}
