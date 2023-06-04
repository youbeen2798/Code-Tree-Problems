#include <iostream>
#include <set>
#include <vector>

using namespace std;

int n; //고객 수
int m; //메모리 유실 선의 수
int h; //취약 지점의 개수

set<pair<int, int>> tmp_s;
set<pair<int, int>> s;

bool move_customer(int customer_num, int x, int y) {

	if (x > h) {
		if (customer_num == y) {
			return true;
		}
		else {
			return false;
		}
	}
	if (tmp_s.find({ x, y - 1 }) != tmp_s.end()) { //왼쪽 선이 있으면
		move_customer(customer_num, x + 1, y - 1);
	}
	else if (tmp_s.find({ x, y }) != tmp_s.end()) { //오른쪽 선이 있으면
		move_customer(customer_num, x + 1, y + 1);
	}
	else { //선이 아예 없으면
		move_customer(customer_num, x + 1, y);
	}
}
void check(vector<pair<int,int>> comb) {
	tmp_s = s;

	for (int i = 0; i < comb.size(); i++) {
		tmp_s.insert({ comb[i] });
	}

	bool all_customer_possible = true; 
	for (int customer = 1; customer <= n; customer++) {
		bool one_customer_possible = move_customer(customer, 1, customer);
		if (!one_customer_possible) {
			all_customer_possible = false;
			break;
		}
	}

	if (all_customer_possible) {
		cout << comb.size();
		exit(0);
	}
}
void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {

	if (r == 0) {
		check(comb);
		
	}
	else if (arr.size() == depth) {
		return;
	}
	else {
		comb[idx] = arr[depth];

		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}
void solution() {

	vector<pair<int, int>> plus_line; //추가된 유실선 수

	for (int j = 1; j <= h; j++) {
		for (int customer = 1; customer < n; customer++) {
			if (s.find({ j, customer }) != s.end()) { //이미 있는 유실선이라면
				continue;
			}
			//옆에 유실선이 없다면
			if (s.find({ j, customer - 1}) == s.end() && s.find({ j, customer + 1}) == s.end()) {
				plus_line.push_back({ j, customer });
			}
		}
	}

	for (int i = 0; i <= 3; i++) {
		vector<pair<int, int>> comb(i);

		combination(plus_line, comb, i, 0, 0);
	}

	cout << -1;
}

void input() {
	cin >> n >> m >> h;

	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		s.insert({ x,y });
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}