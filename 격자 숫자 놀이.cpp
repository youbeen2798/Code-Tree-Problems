#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int r;
int c;
int k;
int arr[101][101];
int row_size = 3;
int col_size = 3;

void mini_solution() {

	int tmp_arr[101][101] = { 0, };

	if (row_size >= col_size) {
		//행의 개수가 열의 개수보다 크거나 같은 경우

		for (int i = 1; i <= row_size; i++) {
			map<int, int> m;

			for (int j = 1; j <= col_size; j ++) {
				if (arr[i][j] == 0) {
					continue;
				}
				if (m.find(arr[i][j]) == m.end()) {
					m.insert({ arr[i][j], 1 });
				}
				else {
					m[arr[i][j]]++;
				}
			}

			vector<pair<int, int>> v;

			for (auto tmp : m) {
				int num = tmp.first;
				int cnt = tmp.second;
				v.push_back({ cnt, num });
			}

			sort(v.begin(), v.end());

			int col = 1;
			for (int j = 0; j < v.size(); j++) {

				if (col >= 100) {
					break;
				}
				tmp_arr[i][col++] = v[j].second;
				tmp_arr[i][col] = v[j].first;
				
				col_size = max(col_size, col);
				col++;
			}
		}
	}
	else {
		//열의 개수가 행의 개수보다 크거나 같은 경우

		for (int j = 1; j <= col_size; j++) {
			map<int, int> m;

			for (int i = 1; i <= row_size; i ++) {
				if (arr[i][j] == 0) {
					continue;
				}
				if (m.find(arr[i][j]) == m.end()) {
					m.insert({ arr[i][j], 1 });
				}
				else {
					m[arr[i][j]]++;
				}
			}

			vector<pair<int, int>> v;

			for (auto tmp : m) {
				int num = tmp.first;
				int cnt = tmp.second;

				v.push_back({ cnt, num });
			}

			sort(v.begin(), v.end());

			int row = 1;
			for (int i = 0; i < v.size(); i++) {

				if (row >= 100) {
					break;
				}
				tmp_arr[row++][j] = v[i].second;
				tmp_arr[row][j] = v[i].first;

				row_size = max(row_size, row);
				row++;
			}
		}
	}

	memset(arr, 0, sizeof(arr));

	for (int i = 1; i <= row_size; i++) {
		for (int j = 1; j <= col_size; j++) {
			arr[i][j] = tmp_arr[i][j];
		}
	}
	
}

void solution() {

	if (arr[r][c] == k) {
		cout << 0;
		exit(0);
	}

	for (int times = 1; times <= 100; times++) {

		mini_solution();

		if (arr[r][c] == k) {
			cout << times;
			exit(0);
		}
	}

	cout << -1;
}

void input() {

	cin >> r >> c >> k;

	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arr[i][j];
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