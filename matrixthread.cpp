// To perform matrix multiplication on other matrices,
// please change the values M, L, N
// and initialize your matrices

#include <iostream>
#include <pthread.h>
#include <stdio.h>

#define M 4
#define L 3
#define N 4

using namespace std;

// create matrices globally
int A[M][L] = {{5, 2, 3}, {4, 5, 7}, {6, 3, 7}, {1, 3, 4}};
int B[L][N] = {{4, 5, 6, 1}, {3, 2, 3, 5}, {2, 8, 7, 7}};
int C[M][N];         // multiplied matrix
int elementID[M][N]; // ID for each element

void *thread(void *data) // threads to do dot products
{
    int *in = (int *)data; // thread id
    int check = 0;         // check if loop matches id

    // loop through and do matrix multiplication
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        {
            if (*in == check)
            {
                int mult = 0;
                int k = 0;
                int l = 0;
                while (k < L)
                {
                    mult = mult + A[i][k] * B[l][j];
                    k++;
                    l++;
                }
                C[i][j] = mult;
            }

            else
                check++;
        }
    pthread_exit(0);
}

int main() // main function
{
    pthread_t id[M][N]; // thread identifiers

    // create ID for each element of array to be made
    int counter = 0;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
        {
            elementID[i][j] = counter;
            counter++;
        }

    // create threads
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            pthread_create(&id[i][j], NULL, thread, &elementID[i][j]);

    // wait for threads to exit
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            pthread_join(id[i][j], NULL);

    // print final matrix
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    return 0;
}
