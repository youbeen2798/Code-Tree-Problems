#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n; //격자 크기
int m; //리브로수를 키우는 총 년 수
int map[16][16];
int plus_map[16][16];

vector<pair<int,int>> dirs;
vector<pair<int, int>> nutrients;
bool is_nutrient[16][16];

int dx[9] = { 0,  0, -1, -1, -1, 0,   1,  1, 1 };
int dy[9] = { 0,  1,  1,  0, -1, -1, -1,  0, 1 };

pair<int, int> after_move(int x, int y, int dir, int p) {

	int nx = x + dx[dir] * p;
	int ny = y + dy[dir] * p;

	if (nx <= 0) {
		nx = n - abs(nx) % n;
	}
	else if (n < nx) {
		if (nx % n == 0) {
			nx = n;
		}
		else {
			nx = nx % n;
		}
	}

	if (ny <= 0) {
		ny = n - abs(ny) % n;
	}
	else if (n < ny) {
		if (ny % n == 0) {
			ny = n;
		}
		else {
			ny = ny % n;
		}
	}

	return { nx,ny };
}

void all_nutrients_move(int dir, int p) {
	//특수 영양제를 이동 규칙에 따라 이동시킨다.

	int size = nutrients.size();

	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;

		nutrients[i] = after_move(x, y, dir, p);
	}
}

void all_nutrients_increase() {
	//높이가 1만큼 증가한다.

	int size = nutrients.size();
	memset(plus_map, 0, sizeof(plus_map));
	memset(is_nutrient, false, sizeof(is_nutrient));

	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;
		is_nutrient[x][y] = true;
		map[x][y]++;
	}

	for (int i = 0; i < size; i++) {
		int x = nutrients[i].first;
		int y = nutrients[i].second;

		int cnt = 0;

		for (int j = 1; j <= 4; j++) {
			int nx = x + dx[j * 2];
			int ny = y + dy[j * 2];

			if (1 <= nx && nx <= n && 1 <= ny && ny <= n && map[nx][ny] >= 1) {
				cnt++;
			}
		}
		plus_map[x][y] += cnt;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += plus_map[i][j];
		}
	}
	
}


void all_nutrients_over_two() {
	// 특수 영양제를 맞은 땅을 제외하고 
	// 높이가 2이상인 리브로수를 높이 2만큼 잘라내고
	// 해당 땅 위에 특수 영양제를 올려준다.
	nutrients.clear();

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!is_nutrient[i][j] && map[i][j] >= 2) {
				map[i][j] -= 2; //높이 2만큼 자르기
				nutrients.push_back({ i,j }); 
			}
		}
	}
}
void one_year(int year) {
	//1년동안
	int d = dirs[year].first;
	int p = dirs[year].second;

	all_nutrients_move(d, p);
	all_nutrients_increase();
	all_nutrients_over_two();

}

void output() {

	int answer = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			answer += map[i][j];
		}
	}

	cout << answer << "\n";
}
void solution() {

	nutrients.push_back({n - 1, 1});
	nutrients.push_back({ n - 1, 2 });
	nutrients.push_back({ n, 1 });
	nutrients.push_back({ n, 2 });


	for (int i = 0; i < m; i++) {
		one_year(i);
	}

	output();
}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int d, p;
		cin >> d >> p;
		dirs.push_back({d, p});
	}
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}