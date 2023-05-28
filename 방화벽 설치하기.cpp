#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

int n, m;
int map[10][10]; //0: 공백, 1: 방화벽, 2:불
bool visited[10][10];

vector<pair<int, int>> bincan; 

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int tmp_fire_cnt = 0;
int ans = 0;
int banghwa_cnt = 0;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}
	return false;
}

void fire(int x, int y) {

	queue<pair<int, int>> q;
	q.push({ x, y });
	visited[x][y] = true;

	while (!q.empty()) {
		int now_x = q.front().first;
		int now_y = q.front().second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = now_x + dx[i];
			int ny = now_y + dy[i];
			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] != 1) { //불이 퍼질 수 있다면
				visited[nx][ny] = true;
				q.push({ nx, ny });
				tmp_fire_cnt++;
			}
		}
	}

}

void check_fire() {

	memset(visited, false, sizeof(visited));
	tmp_fire_cnt = 0; 

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j] == 2 && !visited[i][j]) {
				fire(i, j); //fire만 개수 새기
				tmp_fire_cnt++;
			}
		}
	}

	int not_spread_fire_cnt = n * m - tmp_fire_cnt - banghwa_cnt - 3; //퍼지지 않은 구역

	ans = max(ans, not_spread_fire_cnt); 
}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {
		for (int i = 0; i < comb.size(); i++) {
			map[comb[i].first][comb[i].second] = 1; //방화벽이라고 가정
		}
		check_fire();
		for (int i = 0; i < comb.size(); i++) {
			map[comb[i].first][comb[i].second] = 0; //빈칸으로 돌려놓기
		}
		return;
	}
	else if (arr.size() == depth) {
		return;
	}
	else {
		comb[idx] = arr[depth];

		combination(arr, comb, r - 1, idx + 1, depth + 1);

		combination(arr, comb, r, idx, depth + 1);
	}
}

void solution() {

	vector<pair<int, int>> comb(3);

	combination(bincan, comb, 3, 0, 0);

}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 0) {
				bincan.push_back({ i,j });
			}
			else if (map[i][j] == 1) { //방화벽 개수
				banghwa_cnt++;
			}
		}
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
	cout << ans << "\n";
}