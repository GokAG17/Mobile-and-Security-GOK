#include <bits/stdc++.h>
using namespace std;

int modInverse(int a, int b)
{
    a = a % b;
    for (int i = 1; i < b; i++)
    {
        if ((a * i) % b == 1)
        {
            return i;
        }
    }
    return -1;
}

int chineseremaindertheorem(int a[], int m[], int k)
{
    int M = 1;
    for (int i = 0; i < k; i++)
    {
        M *= m[i];
    }
    int result = 0;
    for (int i = 0; i < k; i++)
    {
        int Mi = M / m[i];
        int inv = modInverse(Mi, m[i]);
        if (inv == -1)
        {
            cout << "Modular Inverse Does not exists for " << m[i] << endl;
            return -1;
        }
        result += a[i] * Mi * inv;
    }
    return result;
}

int main()
{
    int a[] = {2, 3, 2};
    int m[] = {3, 5, 7};
    int k = sizeof(a) / sizeof(a[0]);
    int result = chineseremaindertheorem(a, m, k);
    if (result != -1)
    {
        cout << "The solution of x is : " << result << endl;
    }
    return 0;
}