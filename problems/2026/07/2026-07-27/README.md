# 문제 이름
> 중요한 단어를 스포 방지 - 2025 카카오 하반기 1차


## 문제 정보

- 플랫폼: 프로그래머스
- 문제 링크: https://school.programmers.co.kr/learn/courses/30/lessons/468370
- 난이도: Lv.1
- 사용 언어: C++
- 풀이 날짜: 2026-07-27

## 문제 요약

- 중요 단어의 수를 리턴

- 스포방지단어 = 스포 방지 구간 내의 단어
    - (단어의 문자들 중 하나라도 스포 방지 구간에 포함되면, 스포 방지 단어)
- 중요 단어라면
    - 스포방지 단어여야 한다.
    - 스포 방지 구간이 아닌 구간에 등장하면 안된다.
    - 이전 공개된 스포 방지 단어와 중복이면 안된다.
        - (=> 이후 공개된 동일 단어는 그럼 중요 단어 x, 그럼 첫 중요 단어는 중복이라도 +1인가)
    - 여러 단어가 동시에 공개되면, 왼->오 순으로 판단 (위 괄호 내용이 맞다는 의미)   

- 스포 방지 구간
    - 구간은 겹치지 않는다.
    - 두 인덱스 모두 포함이다.


## 접근 방법

1. 인덱스, 단어 기반 map 활용 => 구현

- 1. 전체 단어 순회
- 2. 모자이크된 단어라면 => 모자이크 단어 맵에 추가
- 2. 모자이크되지 않은 단어라면 => 일반 단어 맵에 추가
- 3. 전체 단어 재순회
- 4. 이미 등장한 중요 단어 확인용 맵 생성 : 중요 단어 확인용 맵
- 5. 모자이크 단어 맵에 존재 && 일반 단어 맵에 비존재 && 중요 단어 확인용 맵에 비존재 => 정답++

별도로 알고리즘은 생각하지 않고 문제를 읽고 떠오른 풀이를 바로 적용하였다.

빠르게 풀이 전개 방식이 떠오른 것에 비해 구현 과정에서 속도가 느렸던 것 같다.

## 풀이

스포 방지 구간에 해당하는 `idx` 확인용 초기 과정 진행

```cpp
// init
map<int, bool> isSpoilerIdx;
for (vector<int> range : spoiler_ranges) {
    for (int i = range[0]; i <= range[1]; i++) {
        isSpoilerIdx[i] = true;
    }
}
```

스트링스트림 사용 문자열 단어로 분리 및 스포 방지 구간 여부 확인

```cpp
int now_idx = message[0] == ' ' ? 1 : 0;
string tmp_word;
while (ss >> tmp_word) {
    words.emplace_back(tmp_word);
    int start_idx = now_idx;
    int end_idx = now_idx + (tmp_word.size() - 1);
    
    bool isSpoilerWord = false;
    for (int i = start_idx; i <= end_idx; i++) {
        if (isSpoilerIdx[i]) {
            isSpoilerWord = true;
            break;
        }
    }
    
    if (isSpoilerWord) {
        // 스포 방지 단어 처리
        special_words[tmp_word] = true;
        
        // idx 증가
        now_idx += tmp_word.size() + 1;
        continue;
    }
    // 일반 단어 처리
    default_words[tmp_word] = true;
    
    // idx 증가 <- 공백 1칸 (공백은 연속해서 등장하지 않습니다)
    now_idx += tmp_word.size() + 1;
}
```

최종 정답 산출 로직

```cpp
// 카운트 과정
// 일반 단어인지 확인 후 카운트 제거    
map<string, bool> already_count_special;
for (string tmp_word : words) {
    if (special_words[tmp_word] && !default_words[tmp_word] && !already_count_special[tmp_word]) {
        already_count_special[tmp_word] = true;
        
        answer++;
    }
}

return answer;
```




## 복잡도

- 스포일러 인덱스 저장(init) = `O(NlogN)` <- `map` 삽입 `O(logN)`
- 전체 단어 순회 및 스포일러 판정 = `O(NlogN)` <- `map` 조회 `O(logN)`
- 최종 카운트 과정 = `O(NlogN)` <- `map` 조회 `O(logN)`

- 종합 시간 복잡도: `O(NlogN)`



<br/>

## 회고

### 잘한 점

- 문제 풀이 방법을 빠르게 생각해내었다.
- 첫 테스트 코드 통과 코드를 작성하기까지 빠르게 진행되었다.
- 구현 시간에 오래 걸렸다 앞서 작성하였지만, 잡다한 오타가 없어 디버깅 시간은 많이 단축되었다.
- 벡터를 활용하려다 맵 자료구조의 키 유일성을 떠올려 활용한 문제 풀이 방법이 좋았다.

### 어려웠던 점

- 첫 제출까지 나름 빠른 시간안에 진행되었는데, 엣지 케이스 찾는 것에 너무 많은 시간을 쏟았다.
    - 테스트 케이스 통과 개수 (74/77)

```cpp
int now_idx = 0;
```

위와 같이 초기 인덱스를 설정하고, `sstream`에서 단어를 검사할 때마다 공백을 생각하여 인덱스를 추가한 점은 좋았다.

```cpp
now_idx += tmp_word.size() + 1;
```

<br/>

다만 초기 인덱스 설정이 잘못되었다. 문자열의 첫 문자가 무조건 문자라는 보장이 없었다.

```cpp
int now_idx = message[0] == ' ' ? 1 : 0;
```

- 최근 들어 알고리즘 생각, 구현보다 엣지 케이스를 찾는게 더 어려워진 것 같다.
    - 이번 문제는 조건을 당연히 그럴 것이라 생각한 부분에서 문제가 발생하여 더 찾기 어려웠다.

### 새롭게 알게 된 점

- 일반적으로 `map`의 삽입, 조회, 삭제 시 시간복잡도는 `O(logN)`이다.

### 개선할 점

- 문제를 읽고 스스로 이럴 것이라 판단하는 과정이 무의식적으로 존재한다.
- 시간복잡도 생각을 안하고 문제를 일단 푸는 습관이 있는 것 같다.
