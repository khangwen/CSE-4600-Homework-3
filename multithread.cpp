#include <iostream>
#include <pthread.h>
#include <stdio.h>

using namespace std;

// global variables
pthread_cond_t wait1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t wait2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t wait3 = PTHREAD_COND_INITIALIZER;
pthread_cond_t wait4 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int size;        // size of array -> to be inputted
int counter = 1; // counter to allow conditional wait

void *csu(int num) // csu helper function
{
    int mod1, mod2; // modulus 1 and 2

    mod1 = num % 2;
    mod2 = num % 5;

    if (mod1 == 0 && mod2 != 0)
    { // divisible by 2 but not 5
        cout << "csu  ";
        counter++;
    }
}

void *sb(int num) // sb helper function
{
    int mod1, mod2; // modulus 1 and 2

    mod1 = num % 2;
    mod2 = num % 5;

    if (mod2 == 0 && mod1 != 0)
    { // divisible by 5 but not 2
        cout << "sb  ";
        counter++;
    }
}

void *csusb(int num) // csusb helper function
{
    int mod1, mod2; // modulus 1 and 2

    mod1 = num % 2;
    mod2 = num % 5;

    if (mod1 == 0 && mod2 == 0)
    { // checks if divisible by 2 AND 5
        cout << "csusb  ";
        counter++;
    }
}

void *number(int num) // number helper function
{
    int mod1, mod2; // modulus 1 and 2

    mod1 = num % 2;
    mod2 = num % 5;

    if (mod1 != 0 && mod2 != 0)
    { // neither divisible by 2 or 5
        cout << num << "  ";
        counter++;
    }
}

void *thread_1(void *data) // thread 1
{

    int *array = (int *)data;

    for (int i = 0; i < size; i++) // loop through array and check conditions
    {

        pthread_mutex_lock(&mutex);
        while (i == counter)
            pthread_cond_wait(&wait4, &mutex);

        csu(array[i]);
        pthread_cond_signal(&wait3);
        pthread_cond_signal(&wait2);
        pthread_cond_signal(&wait1);

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void *thread_2(void *data) // thread 2
{

    int *array = (int *)data;

    for (int i = 0; i < size; i++) // loop through array and check conditions
    {

        pthread_mutex_lock(&mutex);
        while (i == counter)
            pthread_cond_wait(&wait3, &mutex);

        sb(array[i]);
        pthread_cond_signal(&wait4);
        pthread_cond_signal(&wait2);
        pthread_cond_signal(&wait1);

        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void *thread_3(void *data) // thread 3
{

    int *array = (int *)data;

    for (int i = 0; i < size; i++) // loop through array and check conditions
    {

        pthread_mutex_lock(&mutex);
        while (i == counter)
            pthread_cond_wait(&wait2, &mutex);

        csusb(array[i]);

        pthread_cond_signal(&wait3);
        pthread_cond_signal(&wait4);
        pthread_cond_signal(&wait1);

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

void *thread_4(void *data) // thread 4
{

    int *array = (int *)data;

    for (int i = 0; i < size; i++) // loop through array and check conditions
    {

        pthread_mutex_lock(&mutex);
        while (i == counter)
            pthread_cond_wait(&wait1, &mutex);
        number(array[i]);
        pthread_cond_signal(&wait3);
        pthread_cond_signal(&wait2);
        pthread_cond_signal(&wait4);

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

int main() // main function
{
    try // throw exception if out of bound
    {
        cout << "Please input a number from 1 - 50 for the array size\n";
        cin >> size; // user inputs size
        if (size < 1 || size > 50)
            throw "Number out of bound\n";
    }
    catch (const char *msg)
    {
        cerr << msg << endl; // returns exception message
        return 0;            // exits program
    }

    int array[size]; // array initialized with inputted size

    pthread_t id1, id2, id3, id4; // thread identifiers

    pthread_attr_t attr1, attr2, attr3, attr4; // set of thread attributes

    pthread_mutex_init(&mutex, NULL); // initialize mutex

    // get default attributes
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    pthread_attr_init(&attr4);

    // assign array elements with numbers
    for (int i = 0; i < size; i++)
    {
        array[i] = i + 1;
    }

    // create threads
    pthread_create(&id4, &attr4, thread_4, array);
    pthread_create(&id1, &attr1, thread_1, array);
    pthread_create(&id2, &attr2, thread_2, array);
    pthread_create(&id3, &attr3, thread_3, array);

    // wait for threads to exit
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
    pthread_join(id4, NULL);

    return 0;
}
