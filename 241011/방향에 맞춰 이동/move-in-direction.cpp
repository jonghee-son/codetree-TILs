#include <bits/stdc++.h>
using namespace std;

int n, dist;
char dir;
int x = 0, y = 0;

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> dir >> dist;
        if (dir == 'N') {
            x += dx[1] * dist;
            y += dy[1] * dist;
        }
        else if (dir == 'E') {
            x += dx[0] * dist;
            y += dy[0] * dist;
        }
        else if (dir == 'S') {
            x += dx[3] * dist;
            y += dy[3] * dist;
        }
        else if (dir == 'W') {
            x += dx[2] * dist;
            y += dy[2] * dist;
        }
    }

    cout << x << ' ' << y;

    return 0;
}