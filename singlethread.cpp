#include <iostream>

using namespace std;

void *csu() // csu helper function
{
    cout << "csu  ";
}

void *sb() // sb helper function
{
    cout << "sb  ";
}

void *csusb() // csusb helper function
{
    cout << "csusb  ";
}

void *number(int input) // number helper function
{
    cout << input << "  ";
}

int main() // main function
{
    int size; // size of array -> to be inputted

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
    int mod1, mod2;  // modulus 1 and 2

    for (int i = 0; i < size; i++)
    {
        array[i] = i + 1; // assign array elements with numbers
    }

    for (int i = 0; i < size; i++)
    {
        mod1 = array[i] % 2;
        mod2 = array[i] % 5;
        if (mod1 == 0 && mod2 == 0) // checks if divisible by 2 AND 5
            csusb();
        else if (mod1 != 0 && mod2 != 0) // neither divisible by 2 or 5
            number(array[i]);
        else if (mod1 == 0 && mod2 != 0) // divisible by 2 but not 5
            csu();
        else if (mod2 == 0 && mod1 != 0) // divisible by 5 but not 2
            sb();
    }

    return 0;
}
