#include <iostream>
#include <vector>

using namespace std;

int n; //�Ĵ� ��
vector<int> people_num; //��� ��
int max_team_manager; //�˻� ������ �˻��� �� �ִ� �ִ� �� ��
int max_team_worker; //�˻� ������ �˻��� �� �ִ� �ִ� �� ��

int mini_solution(int people_num) {

	//���� �� ���� ������ �ʿ��ϹǷ�
	people_num -= max_team_manager;

	if (people_num <= 0) {
		return 1;
	}

	if (people_num % max_team_worker == 0) {
		return (people_num / max_team_worker) + 1;
	}
	else {
		return (people_num / max_team_worker) + 2;
	}
}

void solution() {

	long ans = 0;
	
	for (int i = 0; i < people_num.size(); i++) {
		ans += mini_solution(people_num[i]);
	}

	cout << ans;
}

void input() {

	cin >> n;

	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		people_num.push_back(num);
	}

	cin >> max_team_manager >> max_team_worker;
}
int main() {

	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}