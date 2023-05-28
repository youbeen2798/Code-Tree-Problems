#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nums;

int n;
int plus_cnt;
int minus_cnt;
int multiply_cnt;
int min_ans = 1000000000;
int max_ans = -1000000000;

void math(vector<int> operators) {
	//계산하기
	int result = nums[0];

	for (int i = 1; i < nums.size(); i++) {
		if (operators[i - 1] == 0) { //더하기
			result += nums[i];
		}
		else if (operators[i - 1] == 1) { //빼기
			result -= nums[i];
		}
		else if (operators[i - 1] == 2) { //곱하기
			result *= nums[i];
		}
	}

	min_ans = min(min_ans, result);
	max_ans = max(max_ans, result);
}
void solution() {

	vector<int> operators;

	for (int i = 0; i < plus_cnt; i++) {
		operators.push_back(0);
	}

	for (int i = 0; i < minus_cnt; i++) {
		operators.push_back(1);
	}

	for (int i = 0; i < multiply_cnt; i++) {
		operators.push_back(2);
	}

	do {
		math(operators);
	} while (next_permutation(operators.begin(), operators.end()));

}

void input() {

	cin >> n;

	for (int i = 0; i < n; i++) {
		int num;
		cin >> num;
		nums.push_back(num);
	}
	cin >> plus_cnt >> minus_cnt >> multiply_cnt;

}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
	cout << min_ans << " " << max_ans;
}