// task 1

#include <iostream>

using namespace std;

void *csu()
{
    cout << "csu  ";
}

void *sb()
{
    cout << "sb  ";
}

void *csusb()
{
    cout << "csusb  ";
}

void *number(int size)
{
    cout << size << "  ";
}

int main()
{
    int size;

    try
    {
        cout << "Please input a number from 1 - 50 for the array size\n";
        cin >> size;
        if (size < 1 || size > 50)
            throw "Number out of bound\n";
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
        return 0;
    }

    int array[size];
    int mod1, mod2;

    for (int i = 0; i < size; i++)
    {
        array[i] = i + 1;
    }

    for (int i = 0; i < size; i++)
    {
        mod1 = array[i] % 2;
        mod2 = array[i] % 5;
        if (mod1 == 0 && mod2 == 0)
            csusb();
        else if (mod1 != 0 && mod2 != 0)
            number(array[i]);
        else if (mod1 == 0 && mod2 != 0)
            csu();
        else if (mod2 == 0 && mod1 != 0)
            sb();
    }

    return 0;
}

// task 2
/*
#include <iostream>

using namespace std;

string csu(int *size)
{
    return "helo world\n";
}

string sb(int *size)
{
    return "helo world\n";
}

string csusb(int *size)
{
    return "helo world\n";
}

string number(int *size)
{
    return "helo world\n";
}

int main()
{
    int size;

    try
    {
        cout << "Please input a number from 1 - 50 for the array size\n";
        cin >> size;
        if (size < 1 || size > 50)
            throw "Number out of bound\n";
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
        return 0;
    }

    int *array[size];

    for (int i = 0; i < sizeof(array); i++){

    }


    return 0;
}
*/