#include <iostream>

#define MAX 501
#define endl "\n"
#define MOD 1000000007

using namespace std;

int N, M, K;
int r, c;

int map[MAX][MAX];
int dp[MAX][MAX];

void input();
void solve();
void calc(int i, int j);
bool nodeCheck(int x, int y);


int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}

void input() {
    cin >> N >> M >> K;
    for (int i = 0; i < K; i++) {
        cin >> r >> c;
        map[r][c] = 1; // 휴식 공간
    }
}

void solve() {
    dp[1][1] = 1;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            calc(i, j);
        }
    }

    cout << dp[N][M] << endl;
}

void calc(int i, int j) {
    int ans = 0;

    for (int d = 1; d <= 6; d++) {
        if (nodeCheck(i - d, j)) {
            dp[i][j] += (dp[i - d][j]) % MOD;
            dp[i][j] = dp[i][j] % MOD;
        }
    }

    for (int d = 1; d <= 6; d++) {
        if (nodeCheck(i, j - d)) {
            dp[i][j] += (dp[i][j - d]) % MOD;
            dp[i][j] = dp[i][j] % MOD;
        }
    }


}

bool nodeCheck(int x, int y) {
    if (x < 1 || x > N || y < 1 || y > M) return false;
    if (map[x][y] == 1) return false;

    return true;
}