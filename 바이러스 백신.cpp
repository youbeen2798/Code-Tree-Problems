#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int n, m;
int map[51][51];
bool visited[51][51];
//0은 바이러스, 1은 벽, 2는 병원

vector<pair<int, int>> hospitals;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 99999;

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void check(vector<pair<int, int>> comb) {

	memset(visited, false, sizeof(visited));

	queue < pair<int, pair<int, int>>> q;

	int maxi_dist = 0;

	for (int i = 0; i < comb.size(); i++) {
		q.push({ 0, {comb[i].first, comb[i].second} });
		visited[comb[i].first][comb[i].second] = true;
	}

	while (!q.empty()) {

		int now_dist = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] != 1) {
				visited[nx][ny] = true;
				q.push({ now_dist + 1, {nx,ny} });

				//바이러스라면
				if (map[nx][ny] == 0) {
					maxi_dist = max(now_dist + 1, maxi_dist);
				}
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0 && !visited[i][j]) {
				//바이러스를 다 청소하지 못 했으면
				return;
			}
		}
	}


	ans = min(ans, maxi_dist);
	
}

void combination(vector<pair<int, int>> hospitals, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {
		check(comb);
		return;
	}
	else if (hospitals.size() == depth) {
		return;
	}
	else {
		comb[idx] = hospitals[depth];

		combination(hospitals, comb, r - 1, idx + 1, depth + 1);
		combination(hospitals, comb, r, idx, depth + 1);
	}
}

void solution() {

	vector<pair<int, int>> comb(m);

	combination(hospitals, comb, m, 0, 0);

	if (ans == 99999) {
		cout << -1;
	}
	else {
		cout << ans;
	}

}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				hospitals.push_back({ i,j });
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

}