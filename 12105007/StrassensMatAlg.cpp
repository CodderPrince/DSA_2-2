#include <iostream>
using namespace std;

int main()
{
    int x[2][2], y[2][2], z[2][2];
    int i, j;
    int m1, m2, m3, m4, m5, m6, m7;

    // Input both matrices
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            cin >> x[i][j];

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            cin >> y[i][j];

    // Strassen’s algorithm calculations
    m1 = (x[0][0] + x[1][1]) * (y[0][0] + y[1][1]);
    m2 = (x[1][0] + x[1][1]) * y[0][0];
    m3 = x[0][0] * (y[0][1] - y[1][1]);
    m4 = x[1][1] * (y[1][0] - y[0][0]);
    m5 = (x[0][0] + x[0][1]) * y[1][1];
    m6 = (x[1][0] - x[0][0]) * (y[0][0] + y[0][1]);
    m7 = (x[0][1] - x[1][1]) * (y[1][0] + y[1][1]);

    z[0][0] = m1 + m4 - m5 + m7;
    z[0][1] = m3 + m5;
    z[1][0] = m2 + m4;
    z[1][1] = m1 - m2 + m3 + m6;

    // Output as single line
    cout << "The first matrix is:\n";
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }

    cout << "The second matrix is:\n";
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            cout << y[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Product achieved using Strassen's algorithm:\n";
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            cout << z[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
1 2
3 4
5 6
7 8

*/