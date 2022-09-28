---
title: "[자료구조] 우선순위 큐와 힙"
author: dapin1490
date: 2022-09-14T21:13:00+09:00
categories: [지식, IT]
tags: [지식, IT, 자료구조, 우선순위 큐, 힙, 과제]
render_with_liquid: false
---

<style>
	.x-understand { color: #ccb833; }
	.understand { color: #1380da; }
	.tab { white-space: pre; }
</style>

## 과제
```txt
우선순위 큐와 힙 내용 정리, C++를 이용한 우선순위큐 프로그래밍 방법 정리
백준 1966번 프린터 큐 풀이(필수)
백준 1655번 가운데를 말해요 풀이(선택)
```  

<br>
<hr>
<br>
  
## 우선순위 큐와 힙 내용 정리

<br>

### 힙도 자료구조다
  
힙 heap : 트리의 형태로 표현됨.  

<br>
  
트리 : 사이클이 없는 그래프. [참고 : [자료구조] 트리](https://dapin1490.github.io/satinbower/posts/it-data-structure-tree/), [참고 : [자료구조] 이진 탐색 트리](https://dapin1490.github.io/satinbower/posts/it-data-structure-binary-search-tree/)  
이진 트리 binary tree : 모든 노드가 두 개 이하의 자식을 가지는 트리.  
포화 이진 트리 : 단말 노드를 제외한 모든 노드가 두 개의 자식을 가지는 트리.  
완전 이진 트리 : 마지막 레벨을 제외한 모든 레벨에 노드가 완전히 채워져 있고, 마지막 레벨에서는 왼쪽부터 차례로 노드가 채워진 트리.  
거의 완전 이진 트리 nearly complete- : 마지막 레벨에서 노드가 왼쪽부터 채워지되, 한 노드가 자식 노드를 하나만 가져도 되는 트리.  

<br>
  
힙의 구성 조건  
- 거의 완전 이진 트리일 것
- 부모의 키가 자식의 키보다 크거나 같아야 함(루트가 최댓값을 가짐, max heap)
- 부모의 키가 자식의 키보다 작거나 같은 힙은 min heap
- 같은 부모 아래의 자식 노드의 정렬은 고려하지 않는다.

<br>
  
삽입 연산 수행 과정  
1. 힙을 구성하는 트리의 마지막 자리에 새 요소를 넣는다.
2. 전체 트리가 힙 성질을 만족할 때까지 새로 넣은 요소와 부모 노드를 비교하고 바꾼다.

<br>
  
삭제 연산 수행 과정  
1. 루트 노드를 삭제한다.
2. 마지막 노드를 루트로 가져온다.
3. 삽입 연산과 마찬가지로 힙 성질을 만족할 때까지 정렬한다.

<br>

### 우선순위 큐 : 정렬된 큐  
  
우선순위 큐는 힙을 이용해 구현한다.  
  
<br>
  
우선순위 큐에서 사용할 기능
- `insert(S, x)` : 새 요소 삽입
- `max(S)` : 최댓값 보기
- `extract_max(S)` : 최댓값 꺼내기
- `increase_key(S, x, k)` : 설명 제대로 못 들었음. 요소 x의 키 값을 k 증가.
  
<br>
  
우선순위 큐를 **배열로 구현**할 때 계산의 편의성을 위해 **0번 인덱스는 무시**한다.  
  
<br>

### 배열 다루기
- root : 첫 요소
- parent(i) = `i / 2`
- left(i) = `i * 2`, right(i) = `i * 2 + 1`
- `build_max_heap` : 어떤 배열 전체를 최대 힙으로 바꿔주는 것
- `max_heapify` : 특정 인덱스에 대한 서브트리를 최대 힙 조건을 만족하도록 바꾸는 것.
  
`max_heapify`
- 전제 : 주어진 인덱스의 자식노드를 루트로 하는 서브트리는 각각 힙 성질을 만족한다고 본다.
- 만약 주어진 인덱스의 요소와 그 자식 노드가 힙 성질을 만족하지 않는다면 두 자식 중 큰 쪽과 부모를 바꾼다.
- 만약 바꿨다면 교환한 자식 노드에 대해 다시 `max_heapify`를 호출한다.
  
`build_max_heap(A)`
- 주어진 배열 A를 최대 힙으로 바꾼다
- ```cpp
  for i=n/2 downto 1
    do max heapify(i)
  ```
- `i`가 `n/2`부터 시작하는 이유 : 인덱스가 가장 작은 리프노드가 `2/n + 1`부터 시작하고, 리프노드는 정렬할 필요가 없으니 리프노드 앞에서부터 시작.

<br>

### 힙 정렬
1. build max heap
2. find max A[1]
3. swap A[1] & A[n]
4. discard node n
5. run `max_heapify`
6. goto step 2, until empty

**주의**  
2번 과정에서 최댓값을 찾아낸 후, 배열에 남은 값을 한 칸씩 앞으로 당기지 않는다. 그렇게 한다고 해서 새로 만들어진 힙이 힙 성질을 만족한다고 보장할 수 없다.  
그렇기 때문에 배열의 마지막에 있는 값을 가져온다(`step 3`).

<br>
<hr>
<br>

## C++를 이용한 우선순위큐 프로그래밍 방법 정리

<br>

### 필요 헤더와 기본 사용 예시
* 디폴트는 내림차순 정렬이다.  
  
```cpp
#include <iostream> // cpp 기본 헤더
#include <queue>  // 큐와 우선순위 큐
using namespace std;

int main() {
    priority_queue<int> pq;

    pq.push(4);
    pq.push(7);
    pq.push(3);
    pq.push(1);
    pq.push(10);

    while (!pq.empty()) {
        cout << pq.top() << ' ';
        pq.pop();
    }
    // 출력 결과 : 10 7 4 3 1

    return 0;
}
```  

<br>
  
### 멤버 함수
- `empty` : 우선순위 큐가 비었는지 확인
- `size` : 우선순위 큐의 크기 확인
- `top` : 현재 우선순위 큐의 가장 앞에 있는(우선순위가 최상위인) 요소 확인
- `push` : 우선순위 큐에 값 넣기
- `emplace` : 우선순위 큐에 구조 넣기(큐의 요소가 단순 자료형이 아닐 때 사용)
- `pop` : 현재 `top`의 값 제거
- `swap` : 두 개의 우선순위 큐를 서로 바꾼다. (== 내용물을 바꾼다)
  
**◼ `push`와 `emplace`**  
`push`는 전달된 값을 복제해서 큐에 넣는다. 반면 `emplace`는 전달된 것을 복제하지 않고 전달된 인수로 객체를 바로 생성해 넣는다.  
  
<br>

### 나는 오름차순 우선순위 큐가 쓰고 싶다
* 우선순위 큐를 생성할 때 전달하는 인자가 달라진다.  
  
```cpp
// 템플릿 타입
template
<typename T, typename Container=std::vector<T>, typename Compare=std::less<T>>
class priority_queue

// 실제 사용할 때는
priority_queue<자료형, 구현체, 비교 연산자> 인스턴스명;
```  
  
- 자료형 : 정수, 불 등의 단순 자료형을 써도 되고 벡터, 구조체 등을 사용해도 된다.
- 구현체 : 보통 vector를 사용하며 STL에서 힙을 구현할 수 있는 자료구조면 뭐든 괜찮다고 한다. 원소를 저장할 컨테이너를 지정한다.
- 비교 연산자 : 비교를 위한 기준을 지정한다. 원소의 순서를 결정하는 조건자를 정의한 함수 객체 타입이 들어간다고 한다. 디폴트는 내림차순, `greater<T>`를 쓰면 오름차순, 그 외에 직접 지정한 기준이 있다면 그 기준을 전달하면 된다.
  
<br>

### 커스텀 비교 연산자 쓰기
특별히 원하는 비교 기준이 있다면 해당 기준에 따라 값을 비교하는 함수 객체를 만들어서 우선순위 큐의 생성자에 전달해야 한다. 그런데 나는 함수 객체가 뭔지도 몰랐으니 그것부터 잠깐 알아보고 가자.  
  * 함수 객체 : 함수처럼 동작하는 객체. 연산자를 오버로딩하는 데에 사용했다. [참고](https://blog.hexabrain.net/267)  
  
여기서 오버로딩할 연산자는 `()`이다. 함수 호출 연산자라고 한다. 이 연산자를 오버로딩하는 함수를 정의한 클래스 혹은 구조체의 객체가 함수 객체가 된다고 한다. 또한 이 함수 객체를 사용할 때는 보통의 다른 함수를 호출하는 것처럼 `function_name(parameter1, parameter2)` 이름, 괄호, 그 안에 파라미터 전달 형식으로 쓰는데, 이것은 `.operator()`가 생략된 것이라고 한다. 그러니 `.operator()`를 생략하지 않는다면 `function_name.operator()(parameter1, parameter2)` 이렇게 쓴다.  
함수 객체를 만들 때는 구조체로 정의해도 되고, 클래스 내부에 정의해도 되지만 여기서는 구조체로 정의한다. <span class="x-understand"><em>내 생각엔 클래스로 쓸 필요가 없어서 구조체를 쓰는 것 같다.</em></span> 구현 예시는 다음과 같다.  
  
```cpp
struct cmp {
    bool operator()(int a, int b) {
        return a > b;
    }
};
```  
  
예시 코드에서는 단순히 정수의 크기를 비교했지만 다른 구조체끼리 특정 속성을 비교하게 만들어도 되고, 그러려고 쓰는 것이다. 전달할 때는 구조체 이름만 호출하면 된다.  
  
```cpp
// 사용 예
priority_queue <int, vector<int>, cmp> pq;
```  

<br>

### 나는 큐에 넣을 내용물이 이미 준비되어 있다
우선순위 큐 인스턴스를 생성할 때, 큐에 들어갈 요소들이 먼저 준비되어 있다면 그것을 생성자에 전달해서 초기화할 수 있다. 당연히 생성될 큐의 요소와 준비된 배열의 타입이 일치해야 한다. 예시 코드를 보자([출처](https://thebook.io/006842/ch03/04/01/)).  
  
```cpp
using namespace std;

// 배열 초기화
string wrds[] {"one", "two", "three", "four"};
priority_queue<string> words {begin(wrds), end(wrds)}; // "two" "three" "one "four"

// 큐 복제
priority_queue<string> copy_words {words}; // words의 복제본
```  
  
예시의 배열은 영단어 4개로 이루어졌고, 생성된 큐는 문자열 내림차순 우선순위 큐이다. 배열은 중괄호 생성자를 이용해 초기화되었고 우선순위 큐는 이 배열의 시작과 끝을 받아 배열의 내용으로 구성되었다. 중괄호를 저렇게 쓰는 게 어떤 의미인지 몰라서 잠시 찾아봤는데 쉽게 이해가 가지 않아서 참고 자료[9][10]로만 올려두고, 나는 저것이 생성자라고만 말해두겠다. 내가 이해를 못했는데 설명하면 안 되지.  
  
요점은 꼭 빈 큐를 생성해야만 하는 건 아니라는 말이다. 큐 생성 시에 전달되는 배열은 정렬되어 있을 필요가 없고, 우선순위 큐 객체를 복제하는 것도 가능하다. 벡터를 많이들 쓰긴 하지만 `front(), push_back(), pop_back(), size(empty()` 함수를 지원하는 컨테이너라면 사용 가능하여 덱을 써도 된다고 한다.  

<br>
<hr>
<br>

## 에제 문제 풀이
내가 과제로 받은 우선순위 큐를 위한 예제 문제는 `백준 1966번 프린터 큐(필수), 백준 1655번 가운데를 말해요(선택)` 두 가지인데, 이것까지 한 포스트에 다 풀이하면 글이 너무 길어지니 보기 지루하지 않겠는가? 링크로 첨부한다.  
[[백준] 1966 프린터 큐](https://dapin1490.github.io/satinbower/posts/it-boj-1966/)  

<br>
<hr>
<br>

## 참고 자료
1. [[C++ STL] Priority_queue 사용법](https://kbj96.tistory.com/15)  
2. [C++ STL priority_queue 우선순위 큐 사용법](https://jungeu1509.github.io/algorithm/use-priorityqueue/)  
3. [priority_queue emplace() in C++ STL](https://www.geeksforgeeks.org/priority_queue-emplace-in-cpp-stl/)  
4. [priority_queue 사용법](https://dolphins-it.tistory.com/43)  
5. [C++14 STL 철저 입문 - 3.4 &#124; priority_queue&lt;T&gt; 컨테이너 어댑터 사용하기](https://thebook.io/006842/ch03/04/)  
6. [C++/STL 강좌 2편. 함수 객체(Function Object)](https://blog.hexabrain.net/267)  
7. [72) 함수 객체 - 코딩의 시작, TCP School](http://www.tcpschool.com/cpp/cpp_algorithm_functor)  
8. [[자료구조] 힙(heap)이란](https://gmlwjd9405.github.io/2018/05/10/data-structure-heap.html)  
9. [객체 생성시 괄호와 중괄호의 구분](https://infoscoco.com/17)  
10. [[Modern C++]Initializer_list](https://haedallog.tistory.com/8)  
11. [[HTML] HTML 특수문자 코드표 정리](https://postitforhooney.tistory.com/entry/HTML-HTML-%ED%8A%B9%EC%88%98%EB%AC%B8%EC%9E%90-%EC%BD%94%EB%93%9C%ED%91%9C-%EC%A0%95%EB%A6%AC)  