#include <iostream>
#include <vector>

using namespace std;

int k; //블록을 입력한 횟수2
struct info {
	int t;
	int x; 
	int y;
};

vector<info> v;

bool map[10][10];
int score = 0;

void yellow_down(int row_num) {

	int tmp_map[10][10] = { 0, };

	for (int r = 4; r < row_num; r++) {
		for (int j = 0; j < 4; j++) {
			tmp_map[r + 1][j] = map[r][j];
		}
	}

	for (int r = 4; r <= row_num; r++) {
		for (int j = 0; j < 4; j++) {
			map[r][j] = tmp_map[r][j];
		}
	}
}

void red_down(int col_num) {

	int tmp_map[10][10] = { 0, };

	for (int c = 4; c < col_num; c++) {
		for (int i = 0; i < 4; i++) {
			tmp_map[i][c + 1] = map[i][c];
		}
	}

	for (int c = 4; c <= col_num; c++) {
		for (int i = 0; i < 4; i++) {
			map[i][c] = tmp_map[i][c];
		}
	}
}
void jin_check() {

	//노란색이 다 찾는지 확인
	int tmp_score = 0;

	while (true) {
		int yellow_score = 0;
		for (int i = 6; i <= 9; i++) {
			if (map[i][0] && map[i][1] && map[i][2] && map[i][3]) {
				yellow_score++;
				yellow_down(i);
			}
		}

		if (yellow_score == 0) {
			break;
		}
		else {
			tmp_score += yellow_score;
		}
	}
	
	//빨간색이 다 찼는지 확인
	
	while (true) {
		int red_score = 0;
		for (int j = 6; j <= 9; j++) {
			if (map[0][j] && map[1][j] && map[2][j] && map[3][j]) {
				red_score++;
				red_down(j);
			}
		}

		if (red_score == 0) {
			break;
		}
		else {
			tmp_score += red_score;
		}
	}

	score += tmp_score;
	

}
void move(info i) {

	int t = i.t;
	int x = i.x;
	int y = i.y;

	if (t == 1) {
		//오른쪽으로 감
		int nx = x;
		int ny = y;
		for (int j = 4; j <= 9; j++) {
			if (!map[x][j]) { //블록이 없다면
				ny = j;
			}
			else {
				break;
			}
		}
		map[nx][ny] = true;

		nx = x;
		ny = y;
		//아래로 감
		for (int i = 4; i <= 9; i++) {
			if (!map[i][y]) { //블록이 없다면
				nx = i;
			}
			else {
				break;
			}
		}
		map[nx][ny] = true;
	}
	else if (t == 2) {
		//오른쪽으로 감
		int nx = x;
		int ny1 = y;
		int ny2 = y + 1;
		for (int j = 4; j <= 8; j++) {
			if (!map[x][j] && !map[x][j + 1]) { //블록이 없다면
				ny1 = j;
				ny2 = j + 1;
			}
			else {
				break;
			}
		}
		map[nx][ny1] = true;
		map[nx][ny2] = true;

		//아래로 감
		nx = x;
		ny1 = y;
		ny2 = y + 1;

		for (int i = 4; i <= 9; i++) {
			if (!map[i][y] && !map[i][y + 1]) { //블록이 없다면
				nx = i;
			}
			else {
				break;
			}
		}
		map[nx][ny1] = true;
		map[nx][ny2] = true;
	}
	else {
		//오른쪽으로 감
		int nx1 = x;
		int nx2 = x + 1;

		int ny = y;
		for (int j = 4; j <= 9; j++) {
			if (!map[x][j] && !map[x + 1][j]) {
				ny = j;
			}
			else {
				break;
			}
		}
		map[nx1][ny] = true;
		map[nx2][ny] = true;
		//아래로 감
		nx1 = x;
		nx2 = x + 1;
		ny = y;

		for (int i = 4; i <= 8; i++) {
			if (!map[i][y] && !map[i + 1][y]) {
				nx1 = i;
				nx2 = i + 1;
			}
			else {
				break;
			}
		}

		map[nx1][ny] = true;
		map[nx2][ny] = true;
	}
}

void yeon_check() {
	//연한 것들 체크

	for (int i = 4; i <= 5; i++) {
		if (map[i][0] || map[i][1] || map[i][2] || map[i][3]) {
			yellow_down(9);
		}
	}

	for (int j = 4; j <= 5; j++) {
		if (map[0][j] || map[1][j] || map[2][j] || map[3][j]) {
			red_down(9);
		}
	}
}

void solution() {

	for (int i = 0; i < v.size(); i++) {
		move(v[i]);
		jin_check();
		yeon_check();
	}

	int ans2 = 0;

	for (int i = 0; i <= 3; i++) {
		for (int j = 6; j <= 9; j++) {
			ans2 += map[i][j];
		}
	}

	for (int j = 0; j <= 3; j++) {
		for (int i = 6; i <= 9; i++) {
			ans2 += map[i][j];
		}
	}

	cout <<  score << "\n"; 
	cout << ans2 << "\n";
}

void input() {

	cin >> k;

	for (int i = 0; i < k; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		v.push_back({ t,x,y });
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}