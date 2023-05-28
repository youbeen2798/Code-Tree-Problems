#include <iostream>

using namespace std;

int n, m;
int map[51][51]; //도로: 0, 인도: 1
bool visited[51][51];

int start_x, start_y, start_dir;

//0: 북, 1: 동, 2: 남, 3: 서
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int ans = 0;

int to_left(int dir) {
	if (dir == 0) {
		return 3;
	}
	return dir - 1;
}

bool inrange(int x, int y) {
	if (0 <= x && x < n && 1 <= y && y < m) {
		return true;
	}
	return false;
}
void move(int x, int y, int dir) {

	visited[x][y] = true;

	int next_dir = dir;  //다음 방향

	for (int i = 0; i < 4; i++) {
		next_dir = to_left(next_dir); //왼쪽으로
		int nx = x + dx[next_dir];
		int ny = y + dy[next_dir];

		if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] == 0) {
			move(nx, ny, next_dir);
			return; 
		}
	}

	//후진
	int back_dir;
	if (dir <= 1) {
		back_dir = dir + 2;
	}
	else {
		back_dir = dir - 2;
	}
	int nx = x + dx[back_dir];
	int ny = y + dy[back_dir];

	if (inrange(nx, ny) && map[nx][ny] == 0) {
		move(nx, ny, dir);
	}

}

void solution() {

	move(start_x, start_y, start_dir);

	ans = 0; 
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j]) {
				ans++;
			}
		}
	}
	cout << ans;
}

void input() {

	cin >> n >> m;
	cin >> start_x >> start_y >> start_dir;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
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