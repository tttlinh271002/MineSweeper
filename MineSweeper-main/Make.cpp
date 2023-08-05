#include <bits/stdc++.h>
using namespace std;

long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}

const int maxn = 16;
int a[20][20], bomb = 40;
int dong[] = {-1, -1, -1, 0, 1, 1, 1, 0}, cot[] = {-1, 0, 1, 1, 1, 0, -1, -1};

int main()
{
    for(int i = 1; i <= bomb; i++)
    {
        int d = Rand(1, maxn), c = Rand(1, 16);
        while(1)
        {
            if(a[d][c] != -1)
            {
                a[d][c] = -1;
                break;
            }
            else
            {
                d = Rand(1, maxn);
                c = Rand(1, 16);
            }
        }
    }
    for(int d = 1; d <= maxn; d++)
        for(int c = 1; c <= maxn; c++)
            if(a[d][c] != -1)
            {
                for(int k = 0; k < 8; k++)
                {
                    int dm = d + dong[k], cm = c + cot[k];
                    if(dm > 0 && dm <= maxn && cm > 0 && cm <= maxn)
                        a[d][c] += (a[dm][cm] == -1);
                }
            }
    for(int i = 1; i <= maxn; i++)
    {
        for(int j = 1; j <= maxn; j++)
            cout << a[i][j] << ' ';
        cout << '\n';
    }
}
