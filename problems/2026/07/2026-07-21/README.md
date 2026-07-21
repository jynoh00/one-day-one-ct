# 문제 이름
> 연속된 부분 수열의 합


## 문제 정보

- 플랫폼: 프로그래머스
- 문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/178870
- 난이도: Lv.2
- 사용 언어: C++
- 풀이 날짜: 2026-07-21

## 문제 요약

- 주어진 배열에서 조건을 만족하는 연속된 구간의 부분 배열 찾기
- 조건은 다음과 같다.
    - 부분 배열 내부 원소들의 합 = K
- 조건을 만족하는 부분 배열이 여러 개일 경우 다음의 우선순위로 하나의 부분 배열을 찾는다.
    1. 원소의 길이가 가장 작은 부분 배열
    2. 시작 원소의 인덱스가 가장 작은 부분 배열


## 접근 방법

1. 투포인터

```
투포인터를 활용한 부분합 구하기

조건을 만족하는 경우 정답 벡터에 추가한 후

최종적으로 정해진 조건에 맞게 정답 벡터를 정렬

정답 벡터의 0번째 pair가 구하려는 부분 배열
```



## 풀이

```cpp
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> sequence, int k) {
    vector<pair<int, int>> answers;
    vector<int> answer;
    
    // edge
    for (int i = 0; i < sequence.size(); i++) {
        if (sequence[i] == k) {
            answer.emplace_back(i);
            answer.emplace_back(i);
            return answer;
        }
    }
    
    int sum = sequence[0], startIdx = 0, endIdx = 1;
    while ((endIdx <= sequence.size()) && (startIdx <= endIdx)) {
        if (sum > k) {
            sum -= sequence[startIdx++];
            continue;
        }
        
        if (sum == k) {
            answers.emplace_back(make_pair(startIdx, endIdx - 1));
            sum -= sequence[startIdx++];
            sum += sequence[endIdx++];
            continue;
        }
        
        // sum < k
        sum += sequence[endIdx++];
    }
    
    // 마지막 원소가 부분 수열에 들어가는 경우
    if (sum == k) {
        answers.emplace_back(make_pair(startIdx, endIdx - 1));
    }

    // 정렬 pair.second - pair.first -> pair.first
    sort(answers.begin(), answers.end(), [] (const pair<int, int>& a, const pair<int, int>& b) {
        int diffA = a.second - a.first;
        int diffB = b.second - b.first;

        if (diffA == diffB) {
            return a.first < b.first;
        }

        return diffA < diffB;
    });

    answer.emplace_back(answers[0].first);
    answer.emplace_back(answers[0].second);

    return answer;
}
```

기존에 투포인터 개념에 대해 알고 있었고, 부분합 관련 문제를 풀어본 경험이 있어 비교적 쉽게 알고리즘을 떠올렸다.

이후 계획한 풀이 방식을 구현해 나갔으나 edge 케이스들을 통과하지 못하였다.

```cpp
// 잘못된 방식1
while ((endIdx < sequence.size()) && (startIdx <= endIdx)) {}

// 잘못된 방식2
while ((endIdx <= sequence.size()) && (startIdx < endIdx)) {}

// 수정한 방식
while ((endIdx <= sequence.size()) && (startIdx <= endIdx)) {}
```

먼저 위와 같은 별거 아닌 것처럼 느껴지는 조건문 범위 설정에서 문제가 발생하였다.

`startIdx`와 `endIdx`가 일치하는 상황이 발생할 수 있어 `statIdx <= endIdx`로 지정하였고

반복문에서 `endIdx`의 경우 다음처럼 `endIdx++`로 처리하였는데

```cpp
sum += sequence[endIdx++];
```

해당 방식으로 진행하였기에 마지막 원소를 더하고 이후 로직 전개가 진행되지 않는 문제가 발생함을 확인하여 수정을 진행했다.

## 복잡도

- 시간 복잡도: `O(NlogN)` // 정렬 과정 (sort)

<br/>

## 회고

### 잘한 점

- 알고리즘을 빠르게 파악하고, 코드를 작성할 수 있었다.
- 어제 학습한 람다식을 활용하여 특정 조건에 맞도록 배열의 정렬을 수행하였다.
- 놓친 케이스들을 테스트 케이스를 직접 생각하고 추가하며 찾아 문제를 해결하였다.
- 코어 덤프가 발생한게 인덱스 범위를 직접적으로 잘못넣은게 아니라 로직 처리가 잘못되어 정답에 추가되지 않았음을 빠르게 파악하였다.


### 어려웠던 점

- 엣지케이스 찾느라 시간이 다수 소요되었다.

### 새롭게 알게 된 점

- .

### 개선할 점

- 경계 조건을 정할 때 어떤 조건에 해당하는지 생각하며 작성하자
- 코드 구현 시간을 좀 더 줄일 수 있도록 하자