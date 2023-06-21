#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int n; //격자 크기
int m; //굴리는 횟수

bool visited[21][21]; 
int map[21][21];
int move_dir = 4; //상 하 좌 우
int dice[6] = { 5,4,1,3,2,6 };
int dice_x = 1;
int dice_y = 1;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int score = 0;

void up() {

	dice_x--;
	int new_dice[6] = { dice[2], dice[1], dice[4], dice[3], dice[5], dice[0] };

	for (int i = 0; i < 6; i++) {
		dice[i] = new_dice[i];
	}
}

void down() {

	dice_x++;
	int new_dice[6] = { dice[5], dice[1], dice[0], dice[3], dice[2], dice[4] };

	for (int i = 0; i < 6; i++) {
		dice[i] = new_dice[i];
	}
}

void left() {

	dice_y--;
	int new_dice[6] = { dice[0], dice[2], dice[3], dice[5], dice[4], dice[1] };

	for (int i = 0; i < 6; i++) {
		dice[i] = new_dice[i];
	}

}

void right() {

	dice_y++;
	int new_dice[6] = { dice[0], dice[5], dice[1], dice[2], dice[4], dice[3] };

	for (int i = 0; i < 6; i++) {
		dice[i] = new_dice[i];
	}

}

void dice_rotate() {
	if (move_dir == 1) { //상

		if (dice_x - 1 >= 1) {
			up();
		}
		else {
			move_dir = 2;
			down();
		}
	}
	else if (move_dir == 2) { //하

		if (dice_x + 1 <= n) {
			down();
		}
		else {
			move_dir = 1;
			up();
		}
	}
	else if (move_dir == 3) { //좌

		if (dice_y - 1 >= 1) {
			left();
		}
		else {
			move_dir = 4;
			right();
		}
	}
	else if (move_dir == 4) { //우

		if (dice_y + 1 <= n) {
			right();
		}
		else {
			move_dir = 3;
			left();
		}
	}
}

void change_move_dir() {

	if (dice[5] > map[dice_x][dice_y]) {
		//주사위 아랫면이 보드 숫자보다 크면
		if (move_dir == 1) { //위면
			move_dir = 4;
		}
		else if (move_dir == 2) { //아래면
			move_dir = 3; //왼쪽으로
		}
		else if (move_dir == 3) { //왼쪽이면
			move_dir = 1;
		}
		else {
			move_dir = 2; //왼쪽으로
		}
	}
	else if (dice[5] < map[dice_x][dice_y]) {
		//주사위 아랫면이 보드 숫자보다 작으면
		if (move_dir == 1) {
			move_dir = 3; 
		}
		else if (move_dir == 2) {
			move_dir = 4;
		}
		else if (move_dir == 3) {
			move_dir = 2;
		}
		else {
			move_dir = 1;
		}
	}
}

void move() {

	dice_rotate();
	change_move_dir();
}


bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void get_score() {

	queue<pair<int, int>> q;
	memset(visited, false, sizeof(visited));

	q.push({ dice_x, dice_y });
	visited[dice_x][dice_y] = true;

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		score += map[x][y];

		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			if (inrange(nx, ny) && !visited[nx][ny] && map[nx][ny] == map[dice_x][dice_y]) {
				q.push({ nx,ny });
				visited[nx][ny] = true; 
			}
		}
	}
}
void solution() {

	for (int i = 0; i < m; i++) {
		move();
		get_score();

	}

	cout <<  score << "\n";
}

void input() {

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
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