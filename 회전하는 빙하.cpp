#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int n; //회전 가능 레벨
int num; //한 칸
int q; //회전 횟수

int map[70][70];
vector<int> levels;
bool visited[70][70];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void mini_rotate(int x, int y, int k) {

	//k : 한 변 길이
	//num : 4등분 길이
	int num = k / 2;
	int tmp_map[70][70];

	for (int i = x; i < x + k; i++) {
		for (int j = y; j < y + k; j++) {
			tmp_map[i][j] = map[i][j];
		}
	}

	//첫 번째(x,y)
	for (int i = x; i < x + num; i++) {
		for (int j = y; j < y + num; j++) {
			map[i][j] = tmp_map[i + num][j];
		}
	}

	//두 번째(x, y + num)
	for (int i = x ; i < x + num; i++) {
		for (int j = y + num; j < y + 2 * num; j++) {
			map[i][j] = tmp_map[i][j - num];
		}
	}
	
	//세 번째(x + num, y)

	for (int i = x + num; i < x + 2 * num; i++) {
		for (int j = y; j < y + num; j++) {
			map[i][j] = tmp_map[i][j + num];
		}
	}

	//네 번째(x + num, y + num)

	for (int i = x + num; i < x + 2 * num; i++) {
		for (int j = y + num; j < y + 2 * num; j++) {
			map[i][j] = tmp_map[i - num][j];
		}
	}

}


void melt() {

	int minus_map[70][70] = { 0, };

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			if (map[i][j] == 0) {
				continue;
			}

			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (inrange(nx,ny) && map[nx][ny] > 0) {
					cnt++;
				}
			}

			if (cnt >= 3) {
				//녹지 않는다.
			}
			else {
				minus_map[i][j]--;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += minus_map[i][j];
		}
	}
}
void rotate(int level) {
	
	//한 변 길이
	int k = pow(2, level);

	for (int i = 1; i <= n; i += k) {
		for (int j = 1; j <= n; j += k) {
			mini_rotate(i, j, k);
		}
	}
}

int bfs(int x, int y) {

	int cnt = 0;
	queue<pair<int, int>> q;
	q.push({ x,y });
	visited[x][y] = true;
	

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		cnt++;

		q.pop();

		for (int k = 0; k < 4; k++) {
			int nx = x + dx[k];
			int ny = y + dy[k];

			if (inrange(nx, ny) && !visited[nx][ny]&& map[nx][ny] > 0) {
				visited[nx][ny] = true;
				q.push({ nx,ny });
			}
		}
	}

	return cnt;
}
void solution() {

	for (int i = 0; i < q; i++) {
		int level = levels[i];
		rotate(level);
		melt();
	}



	int ans1 = 0;
	int ans2 = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] > 0) {
				ans1 += map[i][j];
			}
			if (!visited[i][j] && map[i][j] > 0) {
				int amount = bfs(i, j);
				ans2 = max(amount, ans2);
			}
		}
	}
	
	cout << ans1 << "\n";
	cout <<  ans2;
}

void input() {

	cin >> n >> q;

	n = pow(2, n);

	for (int i = 1; i <= n;  i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < q; i++) {
		int num;
		cin >> num;
		levels.push_back(num);
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}