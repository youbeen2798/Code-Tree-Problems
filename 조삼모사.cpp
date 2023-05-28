#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int work[21][21];
int ans = 999999999;

void math(vector<int> morning_work) {

	vector<int> dining_work; //Àú³á ÀÏ

	bool morning[21];

	memset(morning, false, sizeof(morning));

	for (int i = 0; i < morning_work.size(); i++) {
		morning[morning_work[i]] = true;
	}

	for (int i = 1; i <= n; i++) {
		if (!morning[i]) {
			dining_work.push_back(i);
		}
	}

	int morning_energy = 0;
	int dining_energy = 0;

	for (int i = 0; i < morning_work.size(); i++) {
		for (int j = i + 1; j < morning_work.size(); j++) {
			morning_energy += work[morning_work[i]][morning_work[j]];
			morning_energy += work[morning_work[j]][morning_work[i]];
		}
	}

	for (int i = 0; i < dining_work.size(); i++) {
		for (int j = i + 1; j < dining_work.size(); j++) {
			dining_energy += work[dining_work[i]][dining_work[j]];
			dining_energy += work[dining_work[j]][dining_work[i]];
		}
	}

	int diff = abs(morning_energy - dining_energy);
	ans = min(diff, ans);
}
void combination(vector<int> arr, vector<int> comb, int r, int idx, int depth) {

	if (r == 0) {
		math(comb);
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

	vector<int> arr;

	for (int i = 1; i <= n; i++) {
		arr.push_back(i);
	}

	int r = n / 2;

	vector<int> comb(r);

	combination(arr, comb, r, 0, 0);
}

void input() {

	cin >> n;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> work[i][j];
		}
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
	cout << ans;
}