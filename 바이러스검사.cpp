#include <iostream>
#include <vector>

using namespace std;

int n; //식당 수
vector<int> people_num; //사람 수
int max_team_manager; //검사 팀장이 검사할 수 있는 최대 고객 수
int max_team_worker; //검사 팀원이 검사할 수 있는 최대 고객 수

int mini_solution(int people_num) {

	//팀장 한 명은 무조건 필요하므로
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