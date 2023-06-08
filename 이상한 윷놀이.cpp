#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n; //윷놀이 판의 크기
int k; //말의 개수

int map[13][13];

vector<int> horse_map[13][13]; //말 번호

//1: 오른쪽, 2: 왼쪽, 3:윗쪽, 4: 아랫쪽

struct info {
	int x; //말 위치 행
	int y; //말 위치 열
	int dir; //말 방향
};

info horses[11];
int turns = 1;


void print() {

	cout << "########" << "\n";
	for (int i = 1; i <= k; i++) {
		cout << i << " 번째 말 위치: " << horses[i].x << " " << horses[i].y << " 방향: " << horses[i].dir << "\n";
	}
}
bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void move_white(int horse_num, int next_x, int next_y) {
	//흰 색(x,y)으로 가려는 말


	info horse = horses[horse_num];

	int horse_x = horse.x; //말 행
	int horse_y = horse.y; //말 열

	vector<int> v = horse_map[horse_x][horse_y];

	//말 인덱스
	int horse_idx = find(v.begin(), v.end(), horse_num) - v.begin();

	for (int i = horse_idx; i < v.size(); i++) {
		horse_map[next_x][next_y].push_back(v[i]);
		horse_map[horse_x][horse_y].pop_back();
		int this_horse_num = v[i];
		//	cout << "this_horse_num: " << this_horse_num << "\n";
		horses[this_horse_num].x = next_x;
		horses[this_horse_num].y = next_y;
	}

	if (horse_map[next_x][next_y].size() >= 4) {
		cout << turns << "\n";
		exit(0);
	}
}

void move_red(int horse_num, int next_x, int next_y) {
	//빨간 색(x,y)으로 가려는 말

	info horse = horses[horse_num];

	int horse_x = horse.x; //말 행
	int horse_y = horse.y; //말 열

	vector<int> v = horse_map[horse_x][horse_y];

	//말 인덱스
	int horse_idx = find(v.begin(), v.end(), horse_num) - v.begin();

	for (int i = v.size() - 1; i >= horse_idx; i--) {
		horse_map[next_x][next_y].push_back(v[i]);
		horse_map[horse_x][horse_y].pop_back();
		int this_horse_num = v[i];
		horses[this_horse_num].x = next_x;
		horses[this_horse_num].y = next_y;
	}

	if (horse_map[next_x][next_y].size() >= 4) {
		cout << turns;
		//	cout << "turns: " << turns << "\n";
		exit(0);
	}

}

void horse_move(int horse_num) {

	info horse = horses[horse_num];

	int horse_x = horse.x; //말 행
	int horse_y = horse.y; //말 열
	int horse_dir = horse.dir; //말 방향

	int next_horse_x = horse_x; //말 나중 행
	int next_horse_y = horse_y; //말 나중 열
	int next_horse_dir = horse_dir; //말 나중 방향

	if (horse_dir == 1) {
		//말 방향이 오른쪽이라면
		if (horse_y + 1 <= n && map[horse_x][horse_y + 1] != 2) {
			next_horse_y++;
		}
		else {
			next_horse_y--;
			horses[horse_num].dir = 2; //방향 왼쪽으로 바꿈
		}

	}
	else if (horse_dir == 2) {
		//말 방향이 왼쪽이라면
		if (horse_y - 1 >= 1 && map[horse_x][horse_y - 1] != 2) {
			next_horse_y--;
		}
		else {
			next_horse_y++;
			horses[horse_num].dir = 1; //방향 오른쪽으로 바꿈
		}
	}
	else if (horse_dir == 3) {
		//말 방향이 윗쪽이라면
		if (horse_x - 1 >= 1 && map[horse_x - 1][horse_y] != 2) {
			next_horse_x--;
		}
		else {
			next_horse_x++;
			horses[horse_num].dir = 4; //방향 아래쪽으로 바꿈
		}
	}
	else {
		//말 방향이 아랫쪽이라면
		if (horse_x + 1 <= n && map[horse_x + 1][horse_y] != 2) {
			next_horse_x++;
		}
		else {
			next_horse_x--;
			horses[horse_num].dir = 3; //방향 위쪽으로 바꿈
		}
	}


	if (map[next_horse_x][next_horse_y] == 2 || !inrange(next_horse_x, next_horse_y)) {
		//만약 뒤돌아봤는데도 파란색이라면
	}
	else if (map[next_horse_x][next_horse_y] == 0) {
		//가려는 곳이 흰색이라면
	//	cout << "흰색!" << "\n";
		move_white(horse_num, next_horse_x, next_horse_y);
	}
	else if (map[next_horse_x][next_horse_y] == 1) {
		//가려는 곳이 빨간색이라면

		move_red(horse_num, next_horse_x, next_horse_y);
	}

}

void one_turn() {

	for (int i = 1; i <= k; i++) {
		horse_move(i);
	}
}
void solution() {

	for (turns = 1; turns <= 1000; turns++) {
		one_turn();
	}
	cout << -1;

}

void input() {

	cin >> n >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 1; i <= k; i++) {
		int x, y, d;
		cin >> x >> y >> d;
		horse_map[x][y].push_back(i);
		horses[i] = { x, y, d };
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}