#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int n; //격자판의 크기
int map[21][21];
bool visited[21][21];
int dist[21][21];
//1 ~ 6 : 몬스터 레벨
//9 : 전투 로봇

int robot_x; //로봇 행
int robot_y; //로봇 열
int robot_level = 2; //로봇 레벨
int eaten_monster_cnt = 0; //로봇이 먹은 몬스터 개수(level up하면 0)

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int ans = 0; //일을 끝내기 전까지 걸린 시간

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void find_monster() {

	memset(visited, false, sizeof(visited));
	memset(dist, 0, sizeof(dist));

	queue<pair<int, pair<int, int>>> q; //현재 위치

	//먹을 수 있는 몬스터
	vector < pair<int, pair<int, int>>> can_eat_monsters;

	q.push({ 0, { robot_x, robot_y } });
	dist[robot_x][robot_y] = 0;

	visited[robot_x][robot_y] = true;

	while (!q.empty()) {

		int now_dist = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] <= robot_level) {

				int next_dist = now_dist + 1;
				visited[nx][ny] = true;
				q.push({ next_dist, { nx,ny } });

				if (map[nx][ny] < robot_level && map[nx][ny] >= 1 && map[nx][ny] <= 6) {
					can_eat_monsters.push_back({ next_dist, {nx,ny} });
				}
			}
		}
	}

	sort(can_eat_monsters.begin(), can_eat_monsters.end());

	if (can_eat_monsters.size() == 0) {
		cout << ans;
		exit(0);
	}

	int running_time = can_eat_monsters[0].first;
	int monster_x = can_eat_monsters[0].second.first;
	int monster_y = can_eat_monsters[0].second.second;

	ans += running_time;
	map[monster_x][monster_y] = 9; //로봇이 채움
	map[robot_x][robot_y] = 0; //로봇 있던 자리 제자리로

	robot_x = monster_x;
	robot_y = monster_y;
	eaten_monster_cnt++;

	if (eaten_monster_cnt == robot_level) {
		robot_level++;
		eaten_monster_cnt = 0;
	}
}

void solution() {

	for (int times = 0;; times++) {
		find_monster();
	}

}

void input() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				robot_x = i;
				robot_y = j;
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