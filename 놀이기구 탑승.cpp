#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int n; //격자 크기
set<int> s[401];
vector<int> vt;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

int map[21][21];
int score = 0;
int dscore[5] = { 0,1,10,100,1000 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

pair<int, int> find_place(int no) {

	vector<pair<int, pair<int, int>>> pos;
	int max_cnt = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {

			if (map[i][j] != 0) {
				continue;
			}
			int cnt = 0;
			int empty = 0;

			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny)) {
					int num = map[nx][ny];

					if (s[no].find(num) != s[no].end()) { //좋아하는 친구가 있으면
						cnt++;
					}
					else if (map[nx][ny] == 0) { //빈칸이라면
						empty++;
					}
				}
			}

			if (cnt > max_cnt) {
				max_cnt = max(max_cnt, cnt);
				pos.clear();
				pos.push_back({ empty, { i,j } });
			}
			else if (cnt == max_cnt) {
				pos.push_back({ empty, { i,j } });
			}
		}
	}

	sort(pos.begin(), pos.end());

	int max_empty = pos.back().first;

	pair<int, int> final_p;

	for (int i = pos.size() - 1; i >= 0; i--) {

		int empty = pos[i].first;
		pair<int, int> p = pos[i].second; 

		if (empty == max_empty) {
			final_p = p;
		}
		else {
			break;
		}
	}

	map[final_p.first][final_p.second] = no;
	return final_p;
}

void get_score() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int no = map[i][j];
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (inrange(nx, ny)) {
					int side = map[nx][ny];

					if (s[no].find(side) != s[no].end()) {
						cnt++;
					}
				}
			}

			score += dscore[cnt];
		}
	}
}
void solution() {

	for (int i = 0; i < n * n; i++) {
		int no = vt[i];

		find_place(no);
	}

	get_score();
	cout << score << "\n";
}

void input() {

	cin >> n;

	for (int i = 1; i <= n * n; i++) {
		int a, b, c, d, e;
		cin >> a >> b >> c >> d >> e;
		s[a].insert(b);
		s[a].insert(c);
		s[a].insert(d);
		s[a].insert(e);
		vt.push_back(a);
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
/*

*/