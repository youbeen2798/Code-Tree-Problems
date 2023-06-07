#include <iostream>
#include <vector>

using namespace std;

int n, m, k;

struct info {
	int s; //�ӷ�
	int d; //�̵� ����
	int b; //ũ��
};

info map[101][101];

struct after_move_info {
	int x;
	int y;
	int s;
	int d;
	int b; //ũ��
};

int ans = 0;


void print() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j].d == 0) {
				continue;
			}
		}
	}
}

void catch_virus(int column) {
	//column�� �ִ� ���̷����� ��´�.

	for (int i = 1; i <= n; i++) {
		if (map[i][column].d != 0) {
			//���̷����� �����ϸ�
			ans += map[i][column].b;
			map[i][column] = { 0,0,0 }; //���̷����� ���ش�.
			break;
		}
	}
}

after_move_info virus_up_down(int x, int y, int s, int d, int b) {
	//(x,y)�� �ִ� ���̷����� s��� �ӷ����� b��ŭ "�� / �Ʒ�" �����δ�.

	int nx = x;
	int ny = y;

	for (int i = 0; i < s; i++) {

		if (nx == 1) { //���� ������� ������ �Ʒ���
			d = 2;
		}
		else if (nx == n) { //�Ʒ��� ������� ������ ����
			d = 1;
		}

		if (d == 1) { //�������� �����̶��
			nx -= 1; 
		}
		else if (d == 2) { //�Ʒ��� �����̶��
			nx++;
		}

	
	}

	return{ nx, ny, s, d, b };
}

after_move_info virus_right_left(int x, int y, int s, int d, int b) {

	//(x,y)�� �ִ� ���̷����� s��� �ӷ����� b��ŭ "�� / �Ʒ�" �����δ�.

	int nx = x;
	int ny = y;


	for (int i = 0; i < s; i++) {

		if (ny == m) { //�������� ������� ������ ��������
			d = 4;
		}
		else if (ny == 1) { //������ ������� ������ ����������
			d = 3;
		}

		if (d == 3) { //���������� �����̶��
			ny++;
		}
		else if (d == 4) { //�������� �����̶��
			ny--;
		}
	}

	return{ nx, ny, s, d, b };
}
after_move_info virus_move(int x, int y, int s, int d, int b) {
	//(x,y)�� �ִ� ���̷����� s��� �ӷ����� d�������� b��ŭ �����δ�.

	//������ �� ��ġ
	int nx = x;
	int ny = y;

	if (d <= 2) {
		s = s % (2 * n - 2);
	}
	else {
		s = s % (2 * m - 2);
	}

	if (d == 1 || d == 2) {
		//����, �Ʒ�������
		return virus_up_down(x, y, s, d, b);

	}
	else if (d == 3 || d == 4) {
		//������, ��������
		return virus_right_left(x, y, s, d, b);
	}
	
}
void all_virus_move() {
	//��� ���̷����� �����δ�.
	
	info tmp_map[101][101] = { 0,0,0 };
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (map[i][j].d != 0) {
				after_move_info p = virus_move(i,j,map[i][j].s, map[i][j].d, map[i][j].b);

				//��� �ְų� �� ũ�ٸ�
				if (tmp_map[p.x][p.y].b < p.b || tmp_map[p.x][p.y].d == 0) {
					tmp_map[p.x][p.y] = { p.s, p.d, p.b };
				}
			}
			map[i][j] = { 0,0,0 };
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (tmp_map[i][j].d != 0) {
				map[i][j] = tmp_map[i][j];
			}
		}
	}

	

}
void solution() {


	for (int i = 1; i <= m; i++) {
		catch_virus(i);
		all_virus_move();
	}

	cout << ans;

}

void input() {

	cin >> n >> m >> k;

	for (int i = 0; i < k; i++) {
		int x, y, s, d, b;
		cin >> x >> y >> s >> d >> b;
		map[x][y] = { s,d,b };

	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
//	print();
	solution();
}