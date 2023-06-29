#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int n; //������ ũ��
int m; //���̷��� ����
int k; //����Ŭ ��

int plus_map[11][11]; //�������� �߰��Ǵ� ����� ��
int map[11][11];
deque<int> virus[11][11];

int dx[8] = { -1,-1,-1,0,0,1,1,1 };
int dy[8] = { -1,0,1,-1,1,-1,0,1 };

bool inrange(int x, int y) {

	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void one_virus_eat_nutrient(int x, int y) {
	
	sort(virus[x][y].begin(), virus[x][y].end());

	int size = virus[x][y].size();

	for (int i = 0; i < size; i++) {
		int virus_age = virus[x][y][i]; //���̷��� ����

		if (map[x][y] >=  virus_age) {
			//���̷��� ���̺��� ����� �� ũ�ٸ�
			map[x][y] -= virus_age;
			virus[x][y][i]++;
		}
		else {
			//����� �����Ͽ� ����� ������ �� ���ٸ�
			virus[x][y][i] *= -1;
		}
	}
}

void dead_virus_change_to_nutrient(int x, int y) {
	//��� ���̷����� ���븦 ���� ��
	//���� ���̷����� ������� ���Ѵ�.

	int size = virus[x][y].size();

	for (int i = size - 1; i >= 0; i--) {
		if (virus[x][y][i] < 0) { //���� ���̷����̸�
			int plus_nutrient = ( -1 * virus[x][y][i] ) / 2;
			virus[x][y].pop_back();
			map[x][y] += plus_nutrient;
		}
		else {
			break;
		}
	}
}

void have_baby(int x, int y) {
	//���̷����� ������ �����Ѵ�.

	int size = virus[x][y].size();

	for (int i = 0; i < size; i++) {
		if (virus[x][y][i] % 5 == 0) {
			for (int j = 0; j < 8; j++) {
				int nx = x + dx[j];
				int ny = y + dy[j];

				if (inrange(nx, ny)) {
					virus[nx][ny].push_front(1);
				}
			}
		}
	}
}
void all_virus_eat_nutrient() {
	//������ ���̷����� ����� �����Ѵ�.

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus[i][j].size() > 0) {
				one_virus_eat_nutrient(i, j);
			}
		}
	}
}

void all_dead_virus_change_to_nutrinet() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus[i][j].size() > 0) {
				dead_virus_change_to_nutrient(i, j);
			}
		}
	}
}

void all_virus_have_baby() {
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (virus[i][j].size() > 0) {
				have_baby(i, j);
			}
		}
	}
}

void plus_nutrient() {

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] += plus_map[i][j];
		}
	}

}
void one_cycle() {
	//����Ŭ �� ��

	all_virus_eat_nutrient();	
	all_dead_virus_change_to_nutrinet();
	all_virus_have_baby();

	plus_nutrient();

}
void solution() {

	//�ʱ� ���: 5
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			map[i][j] = 5;
		}
	}

	for (int i = 0; i < k; i++) {
		one_cycle();
	}

	int ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += virus[i][j].size();
		}
	}

	cout <<  ans;
}
void input() {

	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> plus_map[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		int r, c, age;
		cin >> r >> c >> age;
		virus[r][c].push_back(age);
	}
}

int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}