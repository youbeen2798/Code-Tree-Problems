#include <iostream>
#include <vector>
#include <deque>

using namespace std;

deque<char> map[4];
int n; //ȸ�� Ƚ��

vector<pair<int, int>> v; //ȸ����ų �Ȱ����� ��ȣ, ����

vector<pair<int, int>> rotate_info; //ȸ�����Ѿ� �� ����

void output() {

	int ans = 0;

	if (map[0][0] == '1') {
		ans += 1;
	}
	if (map[1][0] == '1') {
		ans += 2;
	}
	if (map[2][0] == '1') {
		ans += 4;
	}
	if (map[3][0] == '1') {
		ans += 8;
	}

	cout << ans;
}
void rotate(int num, int dir) {
	//�Ȱ����� num�� dir �������� ȸ��

	rotate_info.clear();
	rotate_info.push_back({ num, dir });

	if (num == 0) {
		if (map[0][2] != map[1][6]) {
			dir *= -1;
			rotate_info.push_back({ 1, dir });
		}
		else {
			return;
		}

		if (map[1][2] != map[2][6]) {
			dir *= -1;
			rotate_info.push_back({ 2, dir });
		}
		else {
			return;
		}

		if (map[2][2] != map[3][6]) {
			dir *= -1;
			rotate_info.push_back({ 3, dir });
		}
		else {
			return;
		}
	}
	else if (num == 1) {

		if (map[0][2] != map[1][6]) {
			rotate_info.push_back({ 0, -dir });
		}
		if (map[1][2] != map[2][6]) {
			dir *= -1;
			rotate_info.push_back({ 2, dir });
		}
		else {
			return;
		}
		if (map[2][2] != map[3][6]) {
			dir *= -1;
			rotate_info.push_back({ 3, dir });
		}

	}
	else if (num == 2) {
		if (map[2][2] != map[3][6]) {
			rotate_info.push_back({ 3, -dir });
		}
		if (map[1][2] != map[2][6]) {
			dir *= -1;
			rotate_info.push_back({ 1, dir });
		}
		else {
			return;
		}
		if (map[0][2] != map[1][6]) {
			dir *= -1;
			rotate_info.push_back({ 0, dir });
		}
	}
	else if (num == 3) {
		if (map[2][2] != map[3][6]) {
			dir *= -1;
			rotate_info.push_back({ 2, dir });
		}
		else {
			return;
		}
		if (map[1][2] != map[2][6]) {
			dir *= -1;
			rotate_info.push_back({ 1, dir });
		}
		else {
			return;
		}
		if (map[0][2] != map[1][6]) {
			dir *= -1;
			rotate_info.push_back({ 0, dir });
		}
	}
}

void real_rotate() {

	for (int i = 0; i < rotate_info.size(); i++) {
		int num = rotate_info[i].first; //�Ȱ��� ��ȣ
		int dir = rotate_info[i].second; //�Ȱ��� ����

		if (dir == 1) { //�ð����
			char back = map[num].back();
			map[num].pop_back();
			map[num].push_front(back);
		}
		else if (dir == -1) { //�ݽð����
			char front = map[num].front();
			map[num].pop_front();
			map[num].push_back(front);
		}
	}
}
void solution() {

	for (int i = 0; i < v.size(); i++) {
		int num = v[i].first;
		int dir = v[i].second;
		rotate(num, dir);
		real_rotate();
	}
	output();
	

}
void input() {

	for (int i = 0; i < 4; i++) {
		string st;
		cin >> st;
		for (int j = 0; j < 8; j++) {
			map[i].push_back(st[j]);
		}
	}

	cin >> n;

	for (int i = 0; i < n; i++) {
		int num, dir;
		cin >> num >> dir;
		v.push_back({ num - 1, dir });
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}
