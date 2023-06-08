#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n; //������ ���� ũ��
int k; //���� ����

int map[13][13];

vector<int> horse_map[13][13]; //�� ��ȣ

//1: ������, 2: ����, 3:����, 4: �Ʒ���

struct info {
	int x; //�� ��ġ ��
	int y; //�� ��ġ ��
	int dir; //�� ����
};

info horses[11];
int turns = 1;


void print() {

	cout << "########" << "\n";
	for (int i = 1; i <= k; i++) {
		cout << i << " ��° �� ��ġ: " << horses[i].x << " " << horses[i].y << " ����: " << horses[i].dir << "\n";
	}
}
bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}

void move_white(int horse_num, int next_x, int next_y) {
	//�� ��(x,y)���� ������ ��


	info horse = horses[horse_num];

	int horse_x = horse.x; //�� ��
	int horse_y = horse.y; //�� ��

	vector<int> v = horse_map[horse_x][horse_y];

	//�� �ε���
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
	//���� ��(x,y)���� ������ ��

	info horse = horses[horse_num];

	int horse_x = horse.x; //�� ��
	int horse_y = horse.y; //�� ��

	vector<int> v = horse_map[horse_x][horse_y];

	//�� �ε���
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

	int horse_x = horse.x; //�� ��
	int horse_y = horse.y; //�� ��
	int horse_dir = horse.dir; //�� ����

	int next_horse_x = horse_x; //�� ���� ��
	int next_horse_y = horse_y; //�� ���� ��
	int next_horse_dir = horse_dir; //�� ���� ����

	if (horse_dir == 1) {
		//�� ������ �������̶��
		if (horse_y + 1 <= n && map[horse_x][horse_y + 1] != 2) {
			next_horse_y++;
		}
		else {
			next_horse_y--;
			horses[horse_num].dir = 2; //���� �������� �ٲ�
		}

	}
	else if (horse_dir == 2) {
		//�� ������ �����̶��
		if (horse_y - 1 >= 1 && map[horse_x][horse_y - 1] != 2) {
			next_horse_y--;
		}
		else {
			next_horse_y++;
			horses[horse_num].dir = 1; //���� ���������� �ٲ�
		}
	}
	else if (horse_dir == 3) {
		//�� ������ �����̶��
		if (horse_x - 1 >= 1 && map[horse_x - 1][horse_y] != 2) {
			next_horse_x--;
		}
		else {
			next_horse_x++;
			horses[horse_num].dir = 4; //���� �Ʒ������� �ٲ�
		}
	}
	else {
		//�� ������ �Ʒ����̶��
		if (horse_x + 1 <= n && map[horse_x + 1][horse_y] != 2) {
			next_horse_x++;
		}
		else {
			next_horse_x--;
			horses[horse_num].dir = 3; //���� �������� �ٲ�
		}
	}


	if (map[next_horse_x][next_horse_y] == 2 || !inrange(next_horse_x, next_horse_y)) {
		//���� �ڵ��ƺôµ��� �Ķ����̶��
	}
	else if (map[next_horse_x][next_horse_y] == 0) {
		//������ ���� ����̶��
	//	cout << "���!" << "\n";
		move_white(horse_num, next_horse_x, next_horse_y);
	}
	else if (map[next_horse_x][next_horse_y] == 1) {
		//������ ���� �������̶��

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