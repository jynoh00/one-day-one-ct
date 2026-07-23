# 문제 이름
> 바이러스 파이프 - 2025 카카오 하반기 1차


## 문제 정보

- 플랫폼: 프로그래머스
- 문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/468373
- 난이도: Lv.2
- 사용 언어: C++
- 풀이 날짜: 2026-07-23

## 문제 요약

- `n` : 전체 배양체의 개수 
- `infeciton` : 감염된 배양체의 번호 (1 ~ )
- `edges` : (배양체 번호 a, 배양체 번호 b, 파이프 종류)
- `k` : 파이프 열고 -> 닫는 행동 수

k번 파이프 열고 닫았을 때, 전체 감염된 배양체의 수

- 전체 파이프의 종류는 3개이며, 각 배양체는 다른 배양체와 파이프를 통해 연결되어 있다.
- 초기 파이프들은 모두 닫혀있는 상태이며, 이후 파이프를 열고->닫는 일련의 과정을 거친다.
- 파이프가 열려있을 때 감염된 배양체에 연결된 다른 배양체들은 감염된다.
- 새로 감염된 배양체와 열려있는 파이프로 연결되어 있는 다른 배양체들 또한 감염된다.

파이프를 k번 열고 닫는 과정을 수행한 후, 최종적으로 감연된 배양체 개수의 최댓값을 `return`


## 접근 방법

1. 전체 경우의 수

결국 구하려는 목적은 `K`번 파이프를 열고, 닫는 과정 이후의 감염된 배양체의 수이다.

따라서 어떤 파이프를 열고 닫을지가 하나의 사이클이 되기에, 큰 틀에서의 경우의 수는 `3^K`이 된다. (파이프의 종류 3개)

이때 K의 값이 최대 `10`이기에, 약 `59000`번의 연산을 진행한다.

2. 내부 감염 로직 시간 복잡도

전체 연산의 수는 정해졌고, 내부적으로 단일 파이프를 열고 닫는 과정에서의 시간복잡도가 중요해졌다.

처음 생각한 것은 `dfs, bfs`로 감염된 노드에서 열린 파이프를 통해 주변 노드들을 전부 탐색하고 감염하는 방법이다.

생각한 과정은 다음과 같다.

```cpp
// 파이프 열림

for (전체 노드 순회) {
    if (감염o && 방문x) => bfs(해당 노드 기준);
}

bfs(시작 노드) {
    q.push(시작 노드);

    while(!q.empty()) {
        for (열린 파이프 기준 주변 노드 순회) {
            if (방문o) => continue;

            is감염[노드] = true;
            is방문[노드] = true;
            q.push(노드);
        }
        q.pop();
    }
}
```

## 풀이



```cpp
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
```
```cpp
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
                isVisited[node] = true;
                
                while(!q.empty()) {
                    
                    for (int other_node : m[q.front()][pipe_num]) { // q.front()
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
```

접근 방법에서 계획한대로 전체 파이프 선택 경우의 수를 모두 고려하고 각 과정 안에서는 `BFS`를 활용하여 문제를 풀이하였다.



## 복잡도

- 시간 복잡도: `O((3^k) * (NlogN + E))`

<br/>

## 회고

### 잘한 점

- 답을 보지 않고 결국 풀어 맞출 수 있었다.
- 처음 생각했던 접근 방법이 맞았고, 생각한 알고리즘 그대로 구현하였다.


### 어려웠던 점

- 생각했던 알고리즘이 너무 복잡해보이고, 구현 코드가 난잡스러워서 도중에 잘못된 것 아닌가 생각이 들었다.
    - 결과적으로 도중에 다 지우고 생각해보다 다시 이전 방법으로 구현하다보니 시간이 오래 걸렸다.
- 실수가 없게 코드를 작성해야한다 생각하니 기본적인 구현 속도에서 느리다는 느낌을 받았다.
    - 그럼에도 중간에 코어 덤프 에러가 발생하였다. => 재귀함수에서 `return`절을 빼먹었었다.


### 새롭게 알게 된 점

- x

### 개선할 점

- 일단 생각한 알고리즘을 코드로 구현하는 능력을 키우자
    - 구현 능력이 좋았다면 도중에 알고리즘이 잘못됐다 생각하고 고민하는 시간이 없었을 것이다.
- 재귀함수를 쓸 때는 올바르게 종료 조건을 만족했는지 확인하자
- bfs, queue를 사용할 때는 `q.front()`, `q.pop()` 하는 것 빼먹지 말자