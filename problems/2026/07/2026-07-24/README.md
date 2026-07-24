# 문제 이름
> 노란불 신호등 - 2025 카카오 하반기 1차


## 문제 정보

- 플랫폼: 프로그래머스
- 문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/468371
- 난이도: Lv.1
- 사용 언어: C++
- 풀이 날짜: 2026-07-24

## 문제 요약

- 모든 신호등은 초록 -> 노랑 -> 빨강 순으로 변한다. (반복)
- 각 신호등은 개별로 신호마다 걸리는 시간이 다르다. (초 단위)
- 모든 신호등이 노란불일 때 정전이 발생한다.
- 1초에 모든 신호등이 초록불로 시작

=> 정전이 일어나는 시간을 구하라. (정전이 일어날 수 없다면 -1을 반환)


## 접근 방법

1. 시뮬레이션

문제의 설명을 읽고 직관적으로 떠오른 풀이법

- while() 반복을 통해, 한 사이클이 1초
- 각 사이클마다 신호등의 상태를 변화시키고, 노란 불인지 검사한다.

=> 해당 풀이법은 사용하지 않았음.

이유 : 정전이 일어나지 않는 경우 또한 존재하기에 무한 루프 가능성이 있다 판단


2. and 연산

결국 측정하려는 것은 모든 신호등이 노란 불일 때만이다.

따라서 빨간 신호와 초록 신호는 사실상 동일 상태.

=> `노란 신호 : 1`, `그 외 : 0`으로 설정

이후에 생각한 알고리즘은 다음과 같다.

    1. 비트의 길이를 기준으로 내림차순 정렬
    2. 이후 길이가 동일한 비트는 and 연산 진행 => 길이가 다 다른 내림차순 비트 벡터가 만들어진다.
    3. 순차적으로 and 연산 진행, 단 다음 조건을 따른다.
        - 이전 비트 벡터와 이후 비트 벡터의 최소공배수를 구한 후, 해당 길이만큼 비트 반복
        - 이후에 and 연산을 진행한다.
    4. 비트 연산의 결과는 다음 판단할 비트 벡터와 함께 연산에 쓰인다.

```cpp
ex)

           초  노  빨
1번 신호등 : 2초 3초 2초
2번 신호등 : 3초 1초 3초
3번 신호등 : 2초 1초 1초

// 비트로 전환
1: 0011100
2: 0001000
3: 0010

// 비트 길이 기준 내림차순 정렬
0011100
0001000
0010

// 동일 길이 비트끼리는 모두 and 연산
0001000
0010

// 최소공배수만큼 비트 반복 후 and 연산
0001000000100000010000001000
0010001000100010001000100010
--
0000000000100000000000000000

// 비트 벡터 순회 -> 1이 나온다면 해당 위치 리턴
// 전체 순회했다면 리턴 -1
11 반환
```


## 풀이

비트로 전환

```cpp
vector<vector<bool>> states;
    
// init
for (vector<int> vec : signals) {
    vector<bool> tmp;
    for (int i = 0; i < vec[0]; i++) {
        tmp.emplace_back(false);
    }
    
    for (int j = 0; j < vec[1]; j++) {
        tmp.emplace_back(true);
    }
    
    for (int k = 0; k < vec[2]; k++) {
        tmp.emplace_back(false);
    }
    states.emplace_back(tmp);
}
```

길이 순으로 정렬

```cpp
// 길이 순 정렬 -> 내림차순
sort(states.begin(), states.end(), [](const vector<bool>& a, const vector<bool>& b) {
    return a.size() > b.size();
});
```

동일 길이 and 연산 -> 신규 `vector<vector<bool>>` 생성

```cpp
vector<vector<bool>> ans_vec;

bool diffLength = false;
int counter = 0;
vector<bool> before;
for (vector<bool> now : states) {
    counter++;
    
    if (counter == 1) {
        before = now;
        
        continue;
    }
    
    // 길이 동일 & 연산
    if (before.size() == now.size()) {
        for (int i = 0; i < before.size(); i++) {
            before[i] = before[i] & now[i];
        }
        
        // 마지막 원소 엣지 케이스
        if (counter == states.size()) {
            ans_vec.emplace_back(before);
        }
        
        continue;
    }
    
    // 길이 불일치 => now가 더 작다.
    ans_vec.emplace_back(before);
    before.clear();
    before = now;
    
    // 마지막 원소 엣지 케이스
    if (counter == states.size()) {
        ans_vec.emplace_back(now);
        continue;
    }
}
```

최소공배수 기준으로 내림차순 and 연산 진행

```cpp
vector<bool> real_ans_vec;

for (int i = 0; i < ans_vec.size(); i++) {
    if (i == 0) {
        real_ans_vec = ans_vec[0];
        continue;
    }
    
    int a_size = real_ans_vec.size();
    int b_size = ans_vec[i].size();
    
    int lcmNum = lcm(a_size, b_size);
    
    vector<bool> aBack(real_ans_vec);
    vector<bool> bBack(ans_vec[i]);
    
    for (int j = 1; j < (lcmNum / a_size); j++) real_ans_vec.insert(real_ans_vec.end(), aBack.begin(), aBack.end());
    
    for (int j = 1; j < (lcmNum / b_size); j++) ans_vec[i].insert(ans_vec[i].end(), bBack.begin(), bBack.end());
    
    for (int j = 0; j < lcmNum; j++) real_ans_vec[j] = real_ans_vec[j] & ans_vec[i][j];
}
```

최종 결과 반환

```cpp
for (int i = 0; i < real_ans_vec.size(); i++) {
    if (real_ans_vec[i]) return (i + 1);
}

return -1;
```



## 복잡도

- 시간 복잡도: `O(S + N log N + N × L)` => `O(N * L)`

    => N = 5이기에, `O(L)`, L은 모든 신호 주기의 최소공배수

<br/>

## 회고

### 잘한 점

- 비트연산을 떠올리고 적용하였다.
- 엣지 케이스에 대해 경우의 수를 나누고 떠올려 문제를 해결할 수 있었다.

```cpp
// 길이 동일 & 연산
if (before.size() == now.size()) {
    for (int i = 0; i < before.size(); i++) {
        before[i] = before[i] & now[i];
    }
    
    // 마지막 원소 엣지 케이스 <- 해당 부분
    if (counter == states.size()) {
        ans_vec.emplace_back(before);
    }
    
    continue;
}
```

- 이전에 람다로 정렬하는 방법을 기억하고 활용하였다.

### 어려웠던 점

- 카카오 하반기 1차 바이러스 문제보다 레벨이 낮은데 더 어려웠다.
- 간단하게 풀 수 있을 것이라 생각하였는데, 너무 복잡한 알고리즘을  선정한 것 같다.
- 끝나고 다른 풀이와 비교해보니, 시뮬레이션을 통해서도 풀이가 가능하였다. -> `solution1-2.cpp`
- 이번에도 역시 시간이 오래 걸렸다. 1시간 30분. (바이러스 문제보다 더 걸림)
- 최소공배수 알고리즘이 기억이 나지 않았다.

```cpp
// 최대 공약수
int gcd(int a, int b) {
	if (a == 0) return b;
	return gcd(b % a, a);
}

// 최소 공배수
int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}
```

### 새롭게 알게 된 점

- x

### 개선할 점

- 최소 공배수, 최대 공약수 알고리즘 기억해둘 것 (차라리 외울 것)
- 알고있는 라이브러리여도, 작성하는데 시간이 아까우니 `bits/stdc++.h` 사용할 것
- 제한 사항을 보고 해당 알고리즘으로 풀이가 가능할지에 대한 판단이 아쉽다.
    - 시뮬레이션으로 하면 더 간략하게 풀 수 있었음
- 아직도 생각을 코드로 구현하는데 시간이 꽤 소요된다. (코테 풀이 반복하여 줄이자)