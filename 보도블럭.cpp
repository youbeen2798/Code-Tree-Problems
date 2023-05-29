#include <iostream>
#include <cstring>

using namespace std;

int n, l;
int map[101][101];
int ans = 0;

void column() {

	bool saro[101][101];

	memset(saro, false, sizeof(saro));

	for (int j = 1; j <= n; j++) {
		bool possible = true; //���θ� ���� �� ����
		//		cout << "#####" << "\n";
		for (int i = 1; i < n; i++) {
			int diff = map[i][j] - map[i + 1][j];
			if (abs(diff) > 1) { //���� ���̰� 1�̻��̶��
				possible = false;
				break;
			}
			else if (diff == 0) { //���� ���̰� 1�̶��
				continue;
			}
			else if (diff == 1) { //���� ���ٸ�
				int now_height = map[i + 1][j];
				for (int k = i + 1; k <= i + l; k++) {
					if (k <= n && now_height == map[k][j] && !saro[k][j]) {
						continue;
					}
					else {
						possible = false;
						break;
					}
				}
				if (!possible) {
					break;
				}
				else {
					for (int k = i + 1; k <= i + l; k++) {
						saro[k][j] = true;
					}
					//		i += l;
				}
			}
			else if (diff == -1) { //�ö󰣴ٸ�
				int now_height = map[i][j];
				for (int k = i; k >= i - l + 1; k--) {
					if (k >= 1 && now_height == map[k][j] && !saro[k][j]) {
						continue;
					}
					else {
						possible = false;
						break;
					}
				}
				if (!possible) {
					break;
				}
			}
		}
		if (possible) {
			//			cout << "������ ��: " << j << "\n";
			ans++;
		}
	}
}

void row() {

	bool saro[101][101];

	memset(saro, false, sizeof(saro));

	for (int i = 1; i <= n; i++) {
		bool possible = true; //���θ� ���� �� ����
		//		cout << "#####��: " << i << "\n";
		for (int j = 1; j < n; j++) {
			int diff = map[i][j] - map[i][j + 1];
			if (abs(diff) > 1) { //���� ���̰� 1�̻��̶��
				possible = false;
				break;
			}
			else if (diff == 0) { //���� ���̰� 1�̶��
				continue;
			}
			else if (diff == 1) { //���� ���ٸ�
				int now_height = map[i][j + 1];
				for (int k = j + 1; k <= j + l; k++) {
					if (k <= n && now_height == map[i][k] && !saro[i][k]) {
						continue;
					}
					else {
						possible = false;
						break;
					}
				}
				if (!possible) {
					break;
				}
				else {
					for (int k = j + 1; k <= j + l; k++) {
						saro[i][k] = true;
					}
				}
			}
			else if (diff == -1) { //�ö󰣴ٸ�
				int now_height = map[i][j];
				for (int k = j; k >= j - l + 1; k--) {
					if (k >= 1 && now_height == map[i][k] && !saro[i][k]) {
						continue;
					}
					else {
						possible = false;
						break;
					}
				}
				if (!possible) {
					break;
				}
			}
		}
		if (possible) {
			//			cout << "������ ��: " << i << "\n";
			ans++;
		}
	}

}

void solution() {

	column();
	row();
	cout << ans;

}

void input() {

	cin >> n >> l;

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