#include <bits/stdc++.h>
using namespace std;
int R, C, K, ans;

int dy[4] = { 1,-1,0,0 };
int dx[4] = { 0,0,1,-1 };

int Map[73][73];
bool golem_exit[73][73];

struct golem_info {
	int c, d;
};

vector<golem_info> golem;

void input() {
	cin >> R >> C >> K;
	for (int i = 0; i < K; i++) {
		int c, d;
		cin >> c >> d;
		golem.push_back({ c,d });
	}
}

bool isValid(int y, int x) {
	return Map[y][x] == 0 && Map[y - 1][x] == 0 && Map[y + 1][x] == 0 && Map[y][x - 1] == 0 && Map[y][x + 1] == 0 && y <= R + 1 && x >= 2 && x <= C-1;
}

bool isValid2(int y, int x) {
	return y <= R + 2 && x >= 1 && x <= C && Map[y][x] != 0;
}

bool isValid3(int y, int x,int num) {
	return y <= R + 2 && x >= 1 && x <= C && Map[y][x]==num;
}

void mapRemove() {
    memset(Map, 0, sizeof(Map));
    memset(golem_exit, false, sizeof(golem_exit));
}

void bfs(int y,int x,int num) {
	queue<pair<int, int>> q;
	int max_y = y;
	bool visited[73][73] = { false };
	visited[y][x] = true;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		visited[ny][nx] = true;
		q.push({ ny,nx });
	}

	while (!q.empty()) {
		pair<int, int> now = q.front();
		q.pop();
		visited[now.first][now.second] = true;

		max_y = max(max_y, now.first);
		if (golem_exit[now.first][now.second]) {
			for (int i = 0; i < 4; i++) {
				int ny = now.first + dy[i];
				int nx = now.second + dx[i];
				if (visited[ny][nx]) continue;
				if (!isValid2(ny, nx)) continue;
				visited[ny][nx] = true;
				q.push({ ny,nx });
			}
		}
		else if (Map[now.first][now.second] >= 1) {
			for (int i = 0; i < 4; i++) {
				int ny = now.first + dy[i];
				int nx = now.second + dx[i];
				if (visited[ny][nx])continue;
				if (!isValid3(ny, nx,Map[now.first][now.second]))continue;
				visited[ny][nx] = true;
				q.push({ny, nx});
			}
		}
	}
	ans += max_y - 2;
}

void moveGolem(golem_info a, int num) {
	int sR = 0;
	int sC = a.c;
	int sD = a.d;
	
	while (1) {
		sR++;
		if (isValid(sR,sC)) {
			continue;
		}
		sR--;
		sC--;
		if (isValid(sR, sC)) {
			sR++;
			if (isValid(sR, sC)) {
				if (sD == 0) {
                    sD = 3;
                }
				else {
                    sD--;
                }
				continue;
			}
			else {
				sR--;
			}
		}
		sC++;
		sC++;
		if (isValid(sR,sC)) {
			sR++;
			if (isValid(sR, sC)) {
				sD = (sD + 1) % 4;
				continue;
			}
			else {
				sR--;
			}
		}
		sC--;
		break;
	}

	if (sR <= 3) {
		mapRemove();
		return;
	}
	else {
		Map[sR][sC] = num;
		Map[sR - 1][sC] = num;
		Map[sR + 1][sC] = num;
		Map[sR][sC - 1] = num;
		Map[sR][sC + 1] = num;
		if (sD == 0) {
			golem_exit[sR - 1][sC] = true;
		}
		else if (sD == 1) {
			golem_exit[sR][sC + 1] = true;
		}
		else if (sD == 2) {
			golem_exit[sR + 1][sC] = true;
		}
		else if (sD == 3) {
			golem_exit[sR][sC - 1] = true;
		}

		bfs(sR,sC,num);
	}

}

void func() {
	for (int i = 0; i < K; i++) {
		moveGolem(golem[i], i + 1);
	}
	cout << ans;
}

int main() {
	input();
	func();
	return 0;
}