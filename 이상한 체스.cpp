#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int n, m;
int map[10][10];

struct horse {
	int x;
	int y;
	int type;
};

vector<horse> horses;
vector<int> horses_dirs[9]; 
bool visited[9][9];
int ans = 100;

void all_horse_move() {

	memset(visited, false, sizeof(visited));

	for (int i = 0; i < horses.size(); i++) {
		int horse_x = horses[i].x; //행
		int horse_y = horses[i].y; //열
		vector<int> dirs = horses_dirs[i]; //방향

		for (int j = 0; j < dirs.size(); j++) {
			int dir = dirs[j]; //방향

			if (dir == 1) { //위
				for (int x = horse_x - 1; x >= 1; x--) {
					if (map[x][horse_y] == 6) {
						break;
					}
					visited[x][horse_y] = true;
				}
			}
			else if (dir == 2) { //오른쪽
				for (int y = horse_y + 1; y <= m; y++) {
					if (map[horse_x][y] == 6) {
						break;
					}
					visited[horse_x][y] = true;
				}
			}
			else if (dir == 3) { //아래
				for (int x = horse_x + 1; x <= n; x++) {
					if (map[x][horse_y] == 6) {
						break;
					}
					visited[x][horse_y] = true;
				}
			}
			else if (dir == 4) { //왼쪽
				for (int y = horse_y - 1; y >= 1; y--) {
					if (map[horse_x][y] == 6) {
						break;
					}
					visited[horse_x][y] = true;
				}
			}
		}
	}

	int tmp_ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!visited[i][j] && !map[i][j]) {
				tmp_ans++;
			}
		}
	}
	
	ans = min(ans, tmp_ans);
}
void permutation(int pos, int cnt) {
	if (pos == cnt) {
		all_horse_move();
		return;
	}

	if (horses[pos].type == 1) {
		for (int dir = 1; dir <= 4; dir++) {
			horses_dirs[pos].push_back(dir);
			permutation(pos + 1, cnt);
			horses_dirs[pos].clear();
		}
	}
	else if (horses[pos].type == 2) {
		for (int dir = 1; dir <= 2; dir++) {
			horses_dirs[pos].push_back(dir);
			horses_dirs[pos].push_back(dir + 2);
			permutation(pos + 1, cnt);
			horses_dirs[pos].clear();
		}

	}
	else if (horses[pos].type == 3) {
		for (int dir = 1; dir <= 3; dir++) {
			horses_dirs[pos].push_back(dir);
			horses_dirs[pos].push_back(dir + 1);
			permutation(pos + 1, cnt);
			horses_dirs[pos].clear();
		}

		horses_dirs[pos].push_back(4);
		horses_dirs[pos].push_back(1);
		permutation(pos + 1, cnt);
		horses_dirs[pos].clear();
	}
	else if (horses[pos].type == 4) {
		horses_dirs[pos].push_back(1);
		horses_dirs[pos].push_back(2);
		horses_dirs[pos].push_back(3);
		permutation(pos + 1, cnt);
		horses_dirs[pos].clear();

		horses_dirs[pos].push_back(2);
		horses_dirs[pos].push_back(3);
		horses_dirs[pos].push_back(4);
		permutation(pos + 1, cnt);
		horses_dirs[pos].clear();

		horses_dirs[pos].push_back(3);
		horses_dirs[pos].push_back(4);
		horses_dirs[pos].push_back(1);
		permutation(pos + 1, cnt);
		horses_dirs[pos].clear();

		horses_dirs[pos].push_back(4);
		horses_dirs[pos].push_back(1);
		horses_dirs[pos].push_back(2);
		permutation(pos + 1, cnt);
		horses_dirs[pos].clear();
	}
	else if (horses[pos].type == 5) {

		horses_dirs[pos].push_back(1);
		horses_dirs[pos].push_back(2);
		horses_dirs[pos].push_back(3);
		horses_dirs[pos].push_back(4);
		permutation(pos + 1, cnt);
		horses_dirs[pos].clear();

	}
}
void solution() {

	permutation(0, horses.size());
	cout << ans;
}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] != 0 && map[i][j] != 6) {
				horses.push_back({ i,j,map[i][j] });
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