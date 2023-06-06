#include <iostream>
#include <queue>
#include <cstring>
#include <vector>


using namespace std;

int n; //총 칸의 크기
int l; //계란 이동의 범위의 최솟값
int r; //계란 이동의 범위의 최댓값
int map[51][51];
bool visited[51][51];
bool flag = false;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void bfs(int x, int y) {

	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;

	vector<pair<int, int>> eggs;
	int egg_total_sum = 0;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;

		eggs.push_back({ x,y });
		egg_total_sum += map[x][y];

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny]) {
				int diff = abs(map[nx][ny] - map[x][y]);

				if (l <= diff && diff <= r) {
					q.push({ nx,ny });
					visited[nx][ny] = true;
				}
			}
			
		}
	}


	if (eggs.size() > 1) {
		flag = true;
	}

	int egg_average = egg_total_sum / eggs.size();

	for (int i = 0; i < eggs.size(); i++) {
		int x = eggs[i].first;
		int y = eggs[i].second;

		map[x][y] = egg_average;
	}
}

void check() {

	memset(visited, false, sizeof(visited));

	flag = false;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visited[i][j]) {
				bfs(i, j);
			}
		}
	}

}
void solution() {

	for (int cnt = 0;; cnt++) {
		check();

		if (!flag) {
			cout <<  cnt << "\n";
			break;
		}
	}
	

}

void input() {

	cin >> n >> l >> r;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}