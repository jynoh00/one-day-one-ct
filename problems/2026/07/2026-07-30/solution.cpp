#include <string>
#include <vector>

#define MAX 2001

using namespace std;

long long dp[2001];

long long solution(int n) {
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i-2] % 1234567) + (dp[i-1] % 1234567);
    }
    
    return dp[n] % 1234567;
}