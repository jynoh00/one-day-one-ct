#include <iostream>
#include <vector>
#include <algorithm>

#define endl "\n"

using namespace std;

int N;

void input();
int solve();

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    cout << solve();

    return 0;
}

void input() {
    cin >> N;
}

// 5의 개수는 항상 2의 개수와 같거나 보다 작다.
// 반복해서 나누는 방식을 통해 거듭제곱 값의 정수 오버플로우를 피하고 코드가 단순해진다.
int solve() {
    int count = 0;
    while (N) { // N이 0이 될 때까지
        N /= 5;
        count += N;
    }

    return count;
}