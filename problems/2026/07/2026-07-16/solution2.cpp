#include <iostream>
#include <vector>
#include <algorithm>

#define endl "\n"

using namespace std;

int N;
pair<int, int> p = make_pair(0, 0); // p.first -> 2의 개수, p.second -> 5의 개수

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

int solve() {
    if (N == 1) return 0;

    for (int i = 2; i <= N; i++) {
        int tmp_i = i;

        while (true) {
            if (tmp_i % 2 == 0) {
                p.first++;
                tmp_i /= 2;

                continue;
            }
            if (tmp_i % 5 == 0) {
                p.second++;
                tmp_i /= 5;

                continue;
            }
            break;
        }
    }

    return min(p.first, p.second);
}