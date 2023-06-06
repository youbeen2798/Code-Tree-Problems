#include <iostream>
#include <vector>
#include <deque>
#include <cstring>
#include <algorithm>

using namespace std;

int n; //배지의 크기
int m; //바이러스 개수
int k; //총 사이클 개수

struct info {
	int r; //행
	int c; //열
	int age; //나이
};

int plus_map[11][11];
int map[11][11];
deque<int> virus_map[11][11];

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void virus_eat_nutrients(int x, int y) {
	//(x,y)에 있는 바이러스가 양분을 먹는다.

	sort(virus_map[x][y].begin(), virus_map[x][y].end());

	deque<int> tmp;
	int size = virus_map[x][y].size();

	for (int i = 0; i < size; i++) {
		int age = virus_map[x][y][i];

		if (age <=  map[x][y]) {
			//나이가 더 적다면
			map[x][y] -= age;
			tmp.push_back(age + 1);
		}
		else { //양분이 부족하여 나이만큼 양분을 섭취할 수 없다면
			tmp.push_back(-1 * age);
		}
	}

	virus_map[x][y] = tmp;
}
void all_virus_eat_nutrients() {
	//각각의 바이러스는 본인이 속한 1*1 크기의 칸에 있는 양분을 섭취한다.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus_map[i][j].size() > 0) {
				virus_eat_nutrients(i, j);
			}
		}
	}
}

void dead_virus_change_to_nutrients(int x, int y) {

	int size = virus_map[x][y].size();

	for (int i = size - 1; i >= 0; i--) {
		if (virus_map[x][y][i] < 0) {
			//바이러스가 죽었으면
			map[x][y] += abs(virus_map[x][y][i]) / 2;
			virus_map[x][y].pop_back();
		}
	}
}
void all_dead_virus_change_to_nutrients() {
	//죽은 바이러스가 양분으로 변한다.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus_map[i][j].size() > 0) {
				dead_virus_change_to_nutrients(i, j);
			}
		}
	}
}

void virus_have_baby(int x, int y){

	int size = virus_map[x][y].size();

	for (int i = 0; i < size; i++) {

		if (virus_map[x][y][i] % 5 != 0) {
			continue;
		}

		for (int j = 0; j < 8; j++) {
			int nx = x + dx[j];
			int ny = y + dy[j];

			if (inrange(nx, ny)) {
				//나이가 1인 바이러스가 생긴다.
				virus_map[nx][ny].push_front(1);
			}
		}
	}
	
}
void all_virus_have_babies() {
	//바이러스가 번식을 진행한다.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus_map[i][j].size() > 0) {
				virus_have_baby(i, j);
			}
		}
	}
}


void plus_nutrients() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += plus_map[i][j];
		}
	}
}
void solution() {

	for (int i = 1; i <= k; i++) {

		all_virus_eat_nutrients();
		all_dead_virus_change_to_nutrients();
		all_virus_have_babies();
		plus_nutrients();
	}


	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += virus_map[i][j].size();
		}
	}
	cout  << ans << "\n";

}

void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> plus_map[i][j];
			map[i][j] = 5;
		}
	}

	for (int i = 0; i < m; i++) {
		int r, c, age;
		cin >> r >> c >> age;
		virus_map[r][c].push_back(age);
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}