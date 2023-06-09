#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

int n; //격자 크기
int m; //승객 수
int c; //초기 배터리 충전량

int map[21][21];
bool visited[21][21];

int car_x;
int car_y;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

struct info {
	pair<int, int> starts;
	pair<int, int> ends;
};


info people[405];

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y & y <= n) {
		return true;
	}
	return false;
}
void find_closet_people() {

	queue < pair < int, pair<int, int>>> q;

	memset(visited, false, sizeof(visited));


	int people_dist;
	int people_x;
	int people_y;
	int people_num;

	q.push({ 0, {car_x, car_y} });
	visited[car_x][car_y] = true;


	vector<pair<int, pair<int, int>>> v;

	while (!q.empty()) {
		int dist = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;

		if (map[x][y] >= 2) {
			v.push_back({ dist,{x,y,} });

		}
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			//벽이 아니라면
			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] != 1) {
				int next_dist = dist + 1;
				q.push({ next_dist, { nx,ny } });
				visited[nx][ny] = true;
			}
		}
	}

	//태울 승객이 없다면
	if (v.size() == 0) {
		cout << -1;
		exit(0);
	}
	sort(v.begin(), v.end());

	//거리가 가장 가까운 사람 위치
	people_dist = v[0].first;
	people_x = v[0].second.first;
	people_y = v[0].second.second;
	people_num = map[people_x][people_y];

	map[people_x][people_y] = -1; //사람 태우고 -1로...

	//배터리 소모
	if (c >= people_dist) {
		c -= people_dist;
	}
	else {
		cout << -1;
		exit(0);
	}

	//자동차 위치: 사람 태운 위치
	car_x = people_x;
	car_y = people_y;

	memset(visited, false, sizeof(visited));
	q.push({ 0, { car_x, car_y } });
	visited[car_x][car_y] = true;

	//사람 도착지까지 거리
	int end_dist = 0;
	int end_x = people[people_num].ends.first;
	int end_y = people[people_num].ends.second;

	while (!q.empty()) {
		int dist = q.front().first;
		int x = q.front().second.first;
		int y = q.front().second.second;

		//사람을 모신다면
		if (end_x == x && end_y == y) {
			end_dist = dist;
			car_x = x;
			car_y = y;
			break;
		}
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_dist = dist + 1;
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] != 1) {
				visited[nx][ny] = true;
				q.push({ next_dist, {nx,ny} });
			}
		}
	}

	if (end_dist <= c && end_dist != 0) {
		//승객을 도착시킬 수 있다면
		c += end_dist; //연료에 배터리를 채운다.
	}
	else {
		cout << -1;
		exit(0);
	}

}
void solution() {

	for (int i = 0; i < m; i++) {
		find_closet_people();

	}

	cout << c << "\n";

}

void input() {
	cin >> n >> m >> c;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	cin >> car_x >> car_y;

	int people_num = 2;

	for (int i = 0; i < m; i++) {
		int x_s, y_s, x_e, y_e;
		cin >> x_s >> y_s >> x_e >> y_e;
		map[x_s][y_s] = people_num;
		people[people_num].starts = { x_s, y_s };
		people[people_num].ends = { x_e, y_e };
		people_num++;
	}

}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}