#include <iostream>

using namespace std;

pair<int, int> info[16];

int n;
int ans = 0;
int cnt = 0;

void dfs(int now_day, int now_cost) {
	//now_day���� now_cost ��ŭ ������.

	ans = max(now_cost, ans);
	int next_day = now_day + 1;
	
	if (next_day > n) {
		return;
	}
	

	//���� ��
	int spend_cost = info[next_day].second; //1
	int total_cost = now_cost + spend_cost; //2
	int spend_day = info[next_day].first; //3
	int total_day = next_day + spend_day - 1; //1 + 

	if (total_day <= n) {
		dfs(total_day, total_cost);
	}
	//������ ��
	dfs(next_day, now_cost);

}
void solution() {

	int first_day = info[1].first;
	int first_cost = info[1].second;

	//���� ��
	int next_day = first_day;
	int next_cost = first_cost;

	if (next_day <= n) {
		dfs(next_day, next_cost);
	}

	//������ ��
	dfs(1, 0);

	cout << ans;
}

void input() {
	
	cin >> n;

	for (int i = 1; i <= n; i++) {
		int t, p;
		cin >> t >> p;
		//�Ѵٰ� ����
		//���Ѵٰ� ����
		info[i] = { t, p };
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}