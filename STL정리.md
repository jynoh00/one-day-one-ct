# C++ 코딩 테스트 :: STL 정리

## 목차

1. [vector](#01-vector)
2. [algorithm](#02-algorithm)
3. [set](#03-set)
4. [unordered_set](#04-unordered_set)
5. [map](#05-map)
6. [unordered_map](#06-unordered_map)
7. [queue](#07-queue)
8. [stack](#08-stack)
9. [sstream](#09-sstream)
10. [cmath](#10-cmath)
11. [deque](#11-deque)

<br/>


## 01. vector

```cpp
#include <vector>
```

```cpp
vector<int> v;
vector<int> v1(5);        // 원소 5개, 모두 0
vector<int> v2(5, 10);    // 원소 5개, 모두 10
vector<vector<int>> graph(10);
```

| 사용법 | 설명 | 시간 복잡도 |
|---|---|---:|
| `v.push_back(x)` | 뒤에 원소 추가 | 평균 `O(1)` |
| `v.emplace_back(x)` | 뒤에 원소를 직접 생성 | 평균 `O(1)` |
| `v.pop_back()` | 마지막 원소 제거 | `O(1)` |
| `v[i]` | `i`번째 원소 접근 | `O(1)` |
| `v.front()` | 첫 번째 원소 | `O(1)` |
| `v.back()` | 마지막 원소 | `O(1)` |
| `v.size()` | 원소 개수 | `O(1)` |
| `v.empty()` | 비어 있는지 확인 | `O(1)` |
| `v.clear()` | 모든 원소 제거 | `O(N)` |
| `v.resize(n)` | 크기를 `n`으로 변경 | 상황에 따라 다름 |
| `v.assign(n, x)` | `x`를 `n`개 저장 | `O(N)` |
| `v.insert(pos, x)` | 특정 위치에 삽입 | `O(N)` |
| `v.erase(pos)` | 특정 위치의 원소 제거 | `O(N)` |


### 활용 상황

- 일반적인 배열과 수열
- 그래프의 인접 리스트
- 누적 합
- 동적 계획법
- 정렬, 이분 탐색, 투 포인터

```cpp
vector<vector<int>> graph(n + 1);

graph[1].emplace_back(2);
graph[2].emplace_back(1);
```

<br/>

## 02. algorithm

```cpp
#include <algorithm>
```

### 1) 정렬

```cpp
sort(v.begin(), v.end());                  // 오름차순
sort(v.begin(), v.end(), greater<int>());  // 내림차순
```

```cpp
vector<pair<int, int>> v;

sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) {
        return a.second < b.second;
    }
    return a.first < b.first;
});
```

| 함수 | 설명 | 시간 복잡도 |
|---|---|---:|
| `sort(first, last)` | 정렬 | `O(N log N)` |
| `stable_sort(first, last)` | 같은 우선순위의 기존 순서 유지 | `O(N log N)` |
| `nth_element(first, nth, last)` | `nth` 위치에 해당 순위 원소 배치 | 평균 `O(N)` |

### 2) 탐색, 개수 세기

```cpp
auto it = find(v.begin(), v.end(), 10);

int cnt = count(v.begin(), v.end(), 10);

auto min_it = min_element(v.begin(), v.end());
auto max_it = max_element(v.begin(), v.end());
```

```cpp
if (it != v.end()) {
    cout << "찾음";
}
```

### 이분 탐색

```cpp
sort(v.begin(), v.end());

bool exists = binary_search(v.begin(), v.end(), x);

auto lower = lower_bound(v.begin(), v.end(), x);
auto upper = upper_bound(v.begin(), v.end(), x);
```

| 함수 | 결과 |
|---|---|
| `lower_bound` | `x` 이상인 첫 번째 위치 |
| `upper_bound` | `x`보다 큰 첫 번째 위치 |
| `binary_search` | `x`의 존재 여부 |

```cpp
// 인덱스 구하기
int index = lower_bound(v.begin(), v.end(), x) - v.begin();

// x의 등장 횟수
int cnt = upper_bound(v.begin(), v.end(), x) - lower_bound(v.begin(), v.end(), x);
```

### 중복 제거

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
// unique는 실제 크기를 줄이지 않는다. => erase()와 함께 사용
```

### 기타 주요 함수

```cpp
reverse(v.begin(), v.end());       // 순서 뒤집기
fill(v.begin(), v.end(), -1);      // 모든 원소를 -1로 변경
swap(a, b);                        // 값 교환

int small = min(a, b);
int large = max(a, b);

next_permutation(v.begin(), v.end());
prev_permutation(v.begin(), v.end());
```

### 활용 상황

- 그리디 알고리즘: sort
- 이분 탐색: lower_bound, upper_bound
- 순열 완전 탐색: next_permutation
- 좌표 압축: sort, unique, lower_bound
- 중복 제거: sort, unique
- 최솟값과 최댓값 탐색: min_element, max_element



## 03. set
> 중복을 허용하지 않고 원소를 자동으로 정렬해 저장

```cpp
#include <set>

set<int> s;
set<int, greater<int>> descending;
```

```cpp
// vector <-> set 변환
vector<int> vec;

... // 벡터 내부에 원소 추가

// vector -> set
set<int> no_dupl(vec.begin(), vec.end()); // 중복 제거 + 오름차순 정렬

// set -> vector
vec.assign(s.begin(), s.end());

```

```cpp
s.insert(10);
s.insert(20);
s.erase(10);

if (s.find(20) != s.end()) {
    cout << "존재";
}

int cnt = s.count(20);  // 존재하면 1, 아니면 0
```

| 사용법 | 설명 | 시간 복잡도 |
|---|---|---:|
| `s.insert(x)` | 원소 삽입 | `O(log N)` |
| `s.erase(x)` | 원소 삭제 | `O(log N)` |
| `s.find(x)` | 원소 탐색 | `O(log N)` |
| `s.count(x)` | 원소 존재 여부 | `O(log N)` |
| `s.lower_bound(x)` | `x` 이상인 첫 원소 | `O(log N)` |
| `s.upper_bound(x)` | `x`보다 큰 첫 원소 | `O(log N)` |
| `s.size()` | 원소 개수 | `O(1)` |
| `s.empty()` | 비어 있는지 확인 | `O(1)` |

```cpp
int minimum = *s.begin(); // 최솟값
int maximum = *s.rbegin(); // 최댓값
```

`set의 원소는 직접 변경할 수 없다. 값을 변경하려면 기존 원소를 삭제한 뒤 새 값을 삽입`

### 활용 상황

- 중복 제거와 정렬을 동시에 처리
- 원소를 정렬된 상태로 유지
- 현재 최솟값이나 최댓값 관리
- 특정 값 이상 또는 초과인 가장 작은 값 탐색
- 스위핑, 그리디 알고리즘

<br/>

## 04. unordered_set



## 05. map

## 06. unordered_map

## 07. queue

## 08. stack

## 09. sstream

## 10. cmath

## 11. deque