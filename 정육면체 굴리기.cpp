#include <iostream>
#include <vector>

using namespace std; 

int n; //������ ���� ũ��
int m; //������ ���� ũ��
int x, y; //������ü ó�� ��ġ
int k; //������ Ƚ��
int map[21][21];
int dice[6] = { 0,0,0,0,0,0 };
vector<int> move_dirs;

//�� �� �� ��
int dx[5] = { 0,0,0,-1,1 };
int dy[5] = { 0,1,-1,0,0 };

bool inrange(int x, int y) {
	if (0 <= x && x < n && 0 <= y && y < m) {
		return true;
	}
	return false;
}

void change_dice(int move_dir) {
	//�ֻ��� �ٲٱ�

	if (move_dir == 1) {
		int tmp_dice[6] = { dice[0], dice[5], dice[1], dice[2], dice[4], dice[3] };

		for (int i = 0; i < 6; i++) {
			dice[i] = tmp_dice[i];
		}
	}
	else if (move_dir == 2) {
		int tmp_dice[6] = { dice[0], dice[2], dice[3], dice[5], dice[4], dice[1] };

		for (int i = 0; i < 6; i++) {
			dice[i] = tmp_dice[i];
		}
	}
	else if (move_dir == 3) {
		int tmp_dice[6] = { dice[2], dice[1], dice[4], dice[3], dice[5], dice[0] };

		for (int i = 0; i < 6; i++) {
			dice[i] = tmp_dice[i];
		}
	}
	else if (move_dir == 4) {
		int tmp_dice[6] = { dice[5], dice[1], dice[0], dice[3], dice[2], dice[4] };

		for (int i = 0; i < 6; i++) {
			dice[i] = tmp_dice[i];
		}
	}

	
}
void move(int move_dir) {

	//�ֻ��� �̵�
	if (move_dir == 1 && inrange(x, y + 1)) { //��
		y++;
	}
	else if (move_dir == 2 && inrange(x, y-1)) { //��
		y--;
	}
	else if (move_dir == 3 && inrange(x - 1, y)) { //��
		x--;
	}
	else if (move_dir == 4 && inrange(x + 1, y)) { //��
		x++;
	}
	else { //���� ������ ����ٸ�
		return;
	}

	change_dice(move_dir);
	
	//ĭ�� ������ �ִ� ���ڰ� 0�̸�
	if (map[x][y] == 0) {
		map[x][y] = dice[5]; //�ֻ����� �ٴڸ��� ���ڰ� ����ȴ�.
	}
	else { //ĭ�� ������ �ִ� ���ڰ� 0�� �ƴϸ�
		dice[5] = map[x][y]; //ĭ�� ���� �ִ� ���ڰ� ������ü �ٴ����� ����ȴ�.
		map[x][y] = 0; //�ش� ĭ�� ���� 0�� �ȴ�.
	}

	//��ܸ��� ���� ���
	/*
	cout << "#####move_dir: " << move_dir << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << map[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "dice: " << "\n";

	for (int i = 0; i < 6; i++) {
		cout << dice[i] << " ";
	}
	cout << "\n";
	*/
	
	cout << dice[2] << "\n";

}
void solution() {

	for (int i = 0; i < k; i++) {
		int move_dir = move_dirs[i];
		move(move_dir);
	}

}

void input() {

	cin >> n >> m >> x >> y >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int num;
		cin >> num;
		move_dirs.push_back(num);
	}
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}