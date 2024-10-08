#include <bits/stdc++.h>
using namespace std;

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };
int r = 0, c = 0, k = 0, d = 0;
int** arr;
int res = 0;
pair<int, int> coord;

int move_south(pair<int, int> p, int dir, int** map, int num) {
    int x = p.first, y = p.second;
    if (y + 2 > r) {
        return -1;
    }

    map[x + 1][y] = 0; map[x - 1][y] = 0; map[x][y - 1] = 0; map[x][y + 1] = 0; map[x][y] = 0;

    if (map[x][y + 2] == 0 && map[x - 1][y + 1] == 0 && map[x + 1][y + 1] == 0) {
        y++;
        p.second = y;
    }

    map[x + 1][y] = num; map[x - 1][y] = num; map[x][y - 1] = num; map[x][y + 1] = num; map[x][y] = num;

    return 0;
}

int move_west(pair<int, int> p, int dir, int** map, int num) {
    int x = p.first, y = p.second;
    if (x - 2 < 1 || y + 2 > r) {
        return -1;
    }

    map[x + 1][y] = 0; map[x - 1][y] = 0; map[x][y - 1] = 0; map[x][y + 1] = 0; map[x][y] = 0;

    if (map[x - 2][y] == 0 && map[x - 1][y + 1] == 0 && map[x - 1][y - 1] == 0 && map[x - 1][y + 2] == 0 && map[x - 2][y + 1] == 0) {
        x--; y++;
        if (dir == 0) {
            dir = 3;
        }
        else {
            dir--;
        }

        p.first = x;
        p.second = y;
    }

    map[x + 1][y] = num; map[x - 1][y] = num; map[x][y - 1] = num; map[x][y + 1] = num; map[x][y] = num;

    return 0;
}

int move_east(pair<int, int> p, int dir, int** map, int num) {
    int x = p.first, y = p.second;
    if (x + 2 > c || y + 2 > r) {
        return -1;
    }

    map[x + 1][y] = 0; map[x - 1][y] = 0; map[x][y - 1] = 0; map[x][y + 1] = 0; map[x][y] = 0;

    if (map[x + 2][y] == 0 && map[x + 1][y + 1] == 0 && map[x + 1][y - 1] == 0 && map[x + 1][y + 2] == 0 && map[x + 2][y + 1] == 0) {
        x++; y++;
        if (dir == 3) {
            dir = 0;
        }
        else {
            dir++;
        }

        p.first = x;
        p.second = y;
    }

    map[x + 1][y] = num; map[x - 1][y] = num; map[x][y - 1] = num; map[x][y + 1] = num; map[x][y] = num;

    return 0;
}

void movement(pair<int, int> p, int dir, int** map, int num) {
    int x = p.first, y = p.second;
    while (1) {
        if (move_south(p, dir, map, num) != -1) {
            continue;
        }
        else if (move_west(p, dir, map, num) != -1) {
            continue;
        }
        else if (move_east(p, dir, map, num) != -1) {
            continue;
        }
        else {
            if (y - 1 <= 0) {
                memset(map, 0, sizeof(map));
                return;
            }

            switch (dir) {
                case 0:
                    y--;
                    map[x][y] = 1001;
                    break;
                case 1:
                    x++;
                    map[x][y] = 1001;
                    break;
                case 2:
                    y++;
                    map[x][y] = 1001;
                    break;
                case 3:
                    x--;
                    map[x][y] = 1001;
                    break;
            }
            return;
        }
    }
}

void check(pair<int, int> p, int dir, int** map) {
    queue<pair<int, int>> q;
    int max_y = p.second;
    bool visited[71][71] = {false,};
    visited[p.first][p.second] = true;

    for (int i = 0; i < 4; i++) {
		int nx = p.first + dx[i];
        int ny = p.second + dy[i];
		visited[nx][ny] = true;
		q.push({nx, ny});
	}

    while (!q.empty()) {
        pair<int, int> now = q.front();
        int comp = map[now.first][now.second];
        q.pop();
        visited[now.first][now.second] = true;

        max_y = max(max_y, now.second);

        if (map[now.first][now.second] == 1001) {
            for (int i = 0; i < 4; i++) {
				int nx = now.first + dx[i];
				int ny = now.second + dy[i];
				if (visited[nx][ny]) continue;
				if (map[nx][ny] == 0) continue;
				visited[nx][ny] = true;
				q.push({nx, ny});
			}
        }
        else if (map[now.first][now.second] > 0) {
            for (int i = 0; i < 4; i++) {
				int nx = now.first + dx[i];
				int ny = now.second + dy[i];
				if (visited[nx][ny]) continue;
				if (map[nx][ny] != comp && map[nx][ny] != 1001) continue;
				visited[nx][ny] = true;
				q.push({nx, ny});
			}
        }
    }

    res += max_y;
}

int main() {
    cin >> r >> c >> k;

    arr = new int*[r + 1];
    for (int i = 1; i <= c; i++) {
        arr[i] = new int[c];
    }

    memset(arr, 0, sizeof(arr));

    for (int i = 1; i <= k; i++) {
        cin >> coord.first >> d;
        coord.second = 1;
        movement(coord, d, arr, i);
        check(coord, d, arr);
    }

    return 0;
}