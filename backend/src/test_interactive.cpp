#include <bits/stdc++.h>

using namespace std;

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    int S = 0;
    for (auto i : arr)
    {
        cout << i << endl;
        int sq;
        cin >> sq;
        cerr << sq << endl;
        S += sq;
    }
    cout << "ans: " << S << endl;
}