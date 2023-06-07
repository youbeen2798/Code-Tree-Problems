#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n, m, t;
int map[51][51];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

vector<pair<int, int>> dolpungs;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= m) {
		return true;
	}
	return false;
}

void dust_spread() {
	//먼지가 인접한 4방향의 상하좌우 칸으로 확산된다.

	int plus_dust[51][51];
	memset(plus_dust, 0, sizeof(plus_dust));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			
			if (map[i][j] == -1) {
				continue;
			}

			int cnt = 0;
			int divided_five = map[i][j] / 5;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny) && map[nx][ny] != -1) {
					plus_dust[nx][ny] += divided_five;
					cnt++;
				}
			}

			plus_dust[i][j] -= divided_five * cnt;
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			map[i][j] += plus_dust[i][j];
		}
	}
}

void dust_up_move() {
	//위쪽 먼지 움직인다.

	int dolpung_x = dolpungs[0].first;
	int dolpung_y = dolpungs[0].second;

	for (int i = dolpung_x - 2; i >= 1; i--) {
		map[i + 1][1] = map[i][1];
	}


	for (int j = 1; j < m; j++) {
		map[1][j] = map[1][j + 1];
	}

	for (int i = 1; i < dolpung_x; i++) {
		map[i][m] = map[i + 1][m];
	}

	for (int j = m; j > 2; j--) {
		map[dolpung_x][j] = map[dolpung_x][j - 1];
	}

	map[dolpung_x][2] = 0;

}

void dust_down_move() {
	//먼지 아래쪽이 움직인다.


	int dolpung_x = dolpungs[1].first;
	int dolpung_y = dolpungs[1].second;

	for (int i = dolpung_x + 1; i < n; i++) {
		map[i][1] = map[i + 1][1];
	}

	for (int j = 1; j < m; j++) {
		map[n][j] = map[n][j + 1];
	}

	for (int i = n; i > dolpung_x; i--) {
		map[i][m] = map[i - 1][m];
	}

	for (int j = m; j >= 2; j--) {
		map[dolpung_x][j] = map[dolpung_x][j - 1];
	}
	map[dolpung_x][2] = 0;


}
void dust_move() {
	//먼지가 움직인다.

	dust_up_move();
	dust_down_move();
}
void one_time() {

	dust_spread();
	dust_move();

}
void solution() {

	for (int times = 1; times <= t; times++) {
		one_time();
	}

	int ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans += map[i][j];
		}
	}


	ans += 2;

	cout << ans;
}

void input() {

	cin >> n >> m >> t;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				dolpungs.push_back({ i,j });
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