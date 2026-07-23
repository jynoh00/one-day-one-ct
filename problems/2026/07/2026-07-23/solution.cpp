#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

int N, K;
map<int, map<int, vector<int>>> m;
int answer = -1;

void solve(int k, vector<bool> isInfection);

int solution(int n, int infection, vector<vector<int>> edges, int k) {
    // init
    N = n; K = k;
    
    for (vector<int> vec : edges) {
        int node_a = vec[0];
        int node_b = vec[1];
        int pipe_num = vec[2];
        
        m[node_a][pipe_num].emplace_back(node_b);
        m[node_b][pipe_num].emplace_back(node_a);
    }
    
    vector<bool> isInfection(n + 1, false);
    isInfection[infection] = true;
    
    // solve
    solve(0, isInfection);
    
    return answer;
}

void solve(int k, vector<bool> isInfection) {
    if (k == K) {
        int newAnswer = 0;
        for (bool b : isInfection) if(b) newAnswer++;
        
        answer = max(answer, newAnswer);

        return;
    }
    
    vector<bool> rollbackInfection(isInfection);
    
    for (int pipe_num = 1; pipe_num <= 3; pipe_num++) {
        vector<bool> isVisited(N + 1, false);
        
        for (int node = 1; node <= N; node++) {
            if (isInfection[node] && !isVisited[node]) {
                queue<int> q;
                q.push(node);
                
                while(!q.empty()) {
                    for (int other_node : m[node][pipe_num]) {
                        if (isVisited[other_node]) continue;
                        
                        isInfection[other_node] = true;
                        isVisited[other_node] = true;
                        q.push(other_node);
                    }
                    
                    q.pop();
                }
            }
        }
        
        solve(k + 1, isInfection);
        
        // 복구
        for (int i = 1; i <= N; i++) {
            isInfection[i] = rollbackInfection[i];
        }
    }
}

/*

isInfection은 동일 값을 가리켜야하고
isVisited는 매번 새로 해야함

*/

/*
테스트 1
입력값 〉	10, 1, [[1, 2, 1], [1, 3, 1], [1, 4, 3], [1, 5, 2], [5, 6, 1], [5, 7, 1], [2, 8, 3], [2, 9, 2], [9, 10, 1]], 2
기댓값 〉	6
실행 결과 〉	테스트를 통과하였습니다.
테스트 2
입력값 〉	7, 6, [[1, 2, 3], [1, 4, 3], [4, 5, 1], [5, 6, 1], [3, 6, 2], [3, 7, 2]], 3
기댓값 〉	7
실행 결과 〉	실행한 결괏값 4이 기댓값 7과 다릅니다.
=> q.front()를 빼먹고 m[node][~]함. <- m[q.front()][~]
*/

