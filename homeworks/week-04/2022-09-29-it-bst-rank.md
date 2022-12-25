---
title: "[자료구조] 이진 탐색 트리 Rank"
author: dapin1490
date: 2022-09-29T23:55:00+09:00
categories: [지식, IT]
tags: [지식, IT, 자료구조, 이진 탐색 트리, 과제]
render_with_liquid: false
---

<style>
	.x-understand { color: #ccb833; }
	.understand { color: #1380da; }
	.tab { white-space: pre; }
  .underline { text-decoration: underline; }
</style>

# 과제

```txt
아래 내용을 포함하는 포트폴리오를 작성하고, 웹페이지 주소를 제출합니다.
1. Data structures augmentation 코딩
- Rank 구현
- AVL tree 구현
2. AVL tree 정의 등 강의 내용 정리
*Geeks for geeks 참조하세요.
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
3. Leet code 문제 풀이
https://leetcode.com/problems/balanced-binary-tree/
```  
  
# 목차
<ol>
  <li>Data structures augmentation</li>
  <li>Rank 구현
    <ol>
      <li>원래 예시 코드에서 달라진 점</li>
      <li>노드 클래스</li>
      <li>탐색 메소드</li>
      <li>삽입 메소드</li>
      <li>삭제 메소드</li>
      <li>Rank 메소드</li>
    </ol>
  </li>
</ol>  
  
## 다음 글
<a href="https://dapin1490.github.io/satinbower/posts/it-avl-tree/" target="_blank">[자료구조] 균형 이진 트리, AVL 트리</a>  

<br>
<hr>
<br>

# Data structures augmentation
**Data structures augmentation** : 데이터 구조가 효율적으로 구현될 수 있도록 기존 데이터 구조에 몇 가지 추가 정보를 추가하는 것을 의미한다<sup>[<a id="body-cite-1" href="#ref-cite-1" title="Augmenting Data Structure">1</a>]</sup>. <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">지난 글</a>에서는 트리에서 각 노드가 갖는 자손 노드의 수를 노드 클래스의 멤버 변수로 추가하여 특정 값보다 크거나 작은 값의 개수를 구하는 메소드를 구현했는데, 이것이 Data structures augmentation 자료구조 증강에 해당한다. 편의상 앞으로는 자료구조 증강이라 부르겠다.  
  
# Rank 구현
이진 탐색 트리는 모든 탐색을 루트에서부터 시작하고, 루트에서 수많은 가지로 뻗어나가는 형태이기 때문에 특정 범위의 값에 대한 연산이 곤란한 경우가 있다. 어떤 값보다 큰 요소의 개수, 작은 요소의 개수를 구하는 문제가 이런 문제이다. 이를 해결하기 위해 이진 탐색 트리의 각 노드에 자기 자신을 포함해 해당 노드가 갖는 자손 노드의 수를 멤버 변수로서 함께 저장할 수 있다. 코드는 <a href="https://dapin1490.github.io/satinbower/posts/it-bin-search-tree/" target="_blank" title="[자료구조] Big-O와 이진 탐색 트리">지난번</a>에 이미 보여주긴 했지만 이번엔 내가 그 코드를 구상한 과정을 설명해보겠다.  
  
<a id="bodylink-ghcode" href="https://github.com/dapin1490/satinbower/tree/main/assets/files/code/countBST.cpp" target="_blank" title="countBST.cpp">전체 코드 깃허브에서 보기</a>  
<a href="https://ideone.com/PCGu4u" target="_blank" title="countBST.cpp 실행 결과 보기">코드 실행 결과 보기</a>  

## 원래 예시 코드에서 달라진 점
<a href="https://github.com/dapin1490/satinbower/tree/main/assets/files/code/BSTexample.cpp" target="_blank" title="BSTexample.cpp">원래 예시 코드 깃허브에서 보기</a>  
<a href="https://ideone.com/ORGQ01" target="_blank" title="BSTexample.cpp 실행 결과 보기">코드 실행 결과 보기</a>  
  
원래 예시 코드에는 노드 클래스에 멤버 변수만 있고 모든 메소드가 트리 클래스에 있었다. 노드 클래스의 멤버 변수가 public으로 선언되었기 때문에 getter나 setter도 없이 모든 변수에 직접 접근했었다. 내가 Rank를 구현하기 위해 코드를 바꾸기 시작하면서, 이 변수들에 직접 접근하는 건 실수의 여지가 많다고 생각해서 getter와 setter를 만들고 멤버 변수는 모두 private으로 바꿨다. 하는 김에 생성자도 추가했는데 이건 필요해서 했다기보다는 내가 허전해서 만들었다. 어쨌든 일단은 이게 첫 번째이다.  
  
두 번째는 재귀로 구현된 대부분 메소드를 반복문으로 바꿨다는 것이다. 루트에서 특정 노드까지 따라가면서 자손 노드의 수를 세도록 만들 계획이었는데, 재귀로 해서는 개수가 제대로 세어지지 않을 게 뻔했기 때문에 최대한 재귀를 없애야 했다. 그 결과 삭제 메소드와 중위순회 메소드를 제외한 모든 메소드를 반복으로 구현할 수 있었다. 삭제 메소드는 한번에 모든 과정을 반복으로 구현하려다가 포인터를 다루는 부분에서 오류가 났고, 그것을 내 힘으로 고치지 못하는 문제가 있었지만, 약간의 과정을 추가하여 해당 오류를 피하고 재귀를 유지하면서 구현할 수 있었다. 이에 대한 설명은 삭제 메소드를 설명할 때 하겠다. 덧붙여, 중위순회 메소드는 카운트 변수를 함께 출력한다는 점 이외에는 바꿀 것이 없었기 때문에 설명하지 않는다.  
  
## 노드 클래스
가장 기본적으로 각 노드가 자신을 포함한 자손 노드의 수를 저장할 수 있어야 한다. 편의상 카운트 변수라고 부르자. 자기자신을 포함하기 때문에 리프노드라도 기본값은 1에서 시작한다. 이 값은 생성자에는 포함하지 않았고 멤버 변수 선언에서부터 초기화했다. 카운트 변수는 자주 증감연산을 할 수 있고, 보통은 1 단위로 증감하기 때문에 외부에서 불 때 구분하기 쉽도록 증감 메소드를 따로 만들었다.  
  
카운트 변수 이외에도 다양한 getter와 setter를 추가했고, 해당 노드가 리프노드인지 확인하는 메소드도 추가했다. 리프노드 확인 메소드는 삭제 연산에서 사용한다.  

```cpp
class node {
private:
  int data;
  node* left;
  node* right;

  int cnt = 1;

public:
  node(int d, node* l, node* r) {
    data = d;
    left = l;
    right = r;
  }
  ~node() {}

  int getData() { return data; }
  node* getLeft() { return left; }
  node* getRight() { return right; }
  int getcnt() { return cnt; }

  void setLeft(node* le) { left = le; }
  void setRight(node* ri) { right = ri; }
  void upcnt() { cnt += 1; }
  void downcnt() { cnt -= 1; }
  void setData(int d) { data = d; }

  bool isLeaf() { return left == nullptr && right == nullptr; }
};
```  
  
## 탐색 메소드
탐색을 재귀에서 반복으로 바꾸는 것은 쉽다. 재귀 호출이 있던 부분을 모두 서브트리로 이동하는 것으로 바꾸고, 탐색의 모든 과정을 while 반복문 안에 넣으면 된다. 탐색이 끝나면 결과를 바로 return한다. 특정 값을 찾는 탐색은 트리를 전혀 조작하지 않기 때문에 카운트 변수와는 상관이 없다. public 메소드와 private 메소드가 따로 구현된 것은 원래의 예시 코드를 그대로 따랐다.  

```cpp
private:
  node* find_impl(node* current, int value) { // private 탐색 메소드
    while (true) {
      if (current == nullptr) { // 현재 탐색하는 노드가 NULL인 경우
        cout << "No matching value found for " << value << ".\n";
        return NULL;
      }

      if (current->getData() == value) { // 원하는 값 찾음
        cout << value << " has been found.\n";
        return current;
      }
      else if (value < current->getData()) { // 원하는 값이 더 작음
        cout << "current is " << current->getData() << ". pointer moved to left.\n";
        current = current->getLeft(); // 왼쪽 서브트리로 이동
      }
      else { // 위의 모든 선택문을 패스했다면 원하는 값이 더 큰 경우임
        cout << "current is " << current->getData() << ". pointer moved to right.\n";
        current = current->getRight(); // 오른쪽 서브트리로 이동
      }
    }
  }

public:
  node* find(int value) { // 특정 값 탐색 메소드
    return find_impl(root, value); // 따로 구현된 private 탐색 메소드 호출
  }
```  

## 삽입 메소드
탐색 메소드와 같은 방식으로 하나의 큰 while문 안에 코드를 모두 넣고, 서브트리로 이동하는 코드만 재귀에서 포인터 이동으로 바꾸었다. 주의해야 할 점은 트리를 조작하는 메소드이기 때문에 카운트 변수도 같이 다루어야 한다는 것이다. 삽입 연산이니 새 노드가 추가되는 자리에 따라 그 조상 노드는 모두 카운트 변수가 1씩 증가해야 한다.  
  
삽입 연산은 방향이 정해져 있어 되돌아가는 일이 없으니 루트부터 매번 노드를 이동해 반복을 시작할 때마다 카운트 변수를 먼저 1씩 증가시키고 삽입 연산을 수행하도록 했다. public으로 정의된 함수는 크게 바꾸지 않았다.  

```cpp
private:
  void insert_impl(node* current, int value) { // private 삽입 메소드
    while (true) {
      current->upcnt(); // 노드가 삽입되는 경로를 따라 카운트 증가

      if (value < current->getData()) { // 삽입할 값이 현재 탐색하는 노드보다 작음
        if (current->getLeft() == nullptr) { // 왼쪽 서브트리 없음
          current->setLeft(new node{ value, NULL, NULL }); // 바로 붙임
          cout << "current is " << current->getData() << ", " << value << " is inserted left\n";
          return;
        }
        else { // 왼쪽 서브트리 있음
          current = current->getLeft(); // 왼쪽 서브트리로 이동
        }
      }
      else { // else: 삽입할 값이 현재 탐색하는 노드보다 크거나 같음
        if (current->getRight() == nullptr) { // 오른쪽 서브트리 없음
          current->setRight(new node{ value, NULL, NULL }); // 바로 붙임
          cout << "current is " << current->getData() << ", " << value << " is inserted right\n";
          return;
        }
        else { // else: 오른쪽 서브트리 있음
          current = current->getRight(); // 오른쪽 서브트리로 이동
        }
      }
    }
  }

public:
  void insert(int value) { // 삽입 메소드
    if (root == nullptr) { // 루트가 비어있다면
      root = new node{ value, nullptr, nullptr }; // 루트에 바로 넣음
      cout << value << " is inserted into root\n";
    }
    else // else: 루트가 비어있지 않다면
      insert_impl(root, value); // 따로 구현된 private 삽입 메소드 호출
  }
```  
  
## 삭제 메소드
삭제 메소드는 원래 private 메소드에서 모든 과정을 수행하고 public 메소드는 private 메소드를 호출하는 역할만 갖고 있었지만, 카운트 변수를 조작하는 과정을 추가하면서 원래 private 메소드가 수행하던 일부 과정을 public 메소드가 수행하게 되었다.  
  
우선 삭제의 과정을 간단히 정리해보자.  
(1) 삭제할 노드를 찾는다.  
<span class="tab">&nbsp; &nbsp; </span>(1.1) 삭제할 노드가 없으면 NULL을 반환하고 종료.  
(2) 삭제할 노드가 서브트리를 얼마나 갖고 있는지 검사한다.  
<span class="tab">&nbsp; &nbsp; </span>(2.1) 서브트리가 없다면 노드 삭제 후 오른쪽 서브트리를 반환하며 결과적으로 NULL이 반환된다.  
<span class="tab">&nbsp; &nbsp; </span>(2.2) 한쪽 서브트리만 있다면 노드 삭제 후 해당 서브트리의 포인터를 반환한다.  
(3) 삭제할 노드에 양쪽 서브트리가 다 있다면 후계자를 찾아 삭제할 노드의 데이터를 후계자의 것으로 대체한다.  
(4) 후계자로 쓰인 노드를 삭제하기 위해 원래 <span class="underline">삭제할 노드의 오른쪽 서브트리</span>에서부터 다시 1번 과정을 시작한다. 이때 원래 삭제하려고 했던 노드와 후계자 노드가 모두 같은 값을 갖고 있는 상태이기 때문에 트리 내의 키가 중복되어 삭제할 노드를 잘못 찾는 문제를 방지하기 위해 오른쪽 서브트리에서 탐색을 시작한다.  
  
나는 위의 과정 중 노드가 가진 서브트리의 수를 검사하고 후계자를 선출해 대체하는 부분을 public 메소드로 옮기고, private 메소드에는 순수하게 목표한 노드를 찾아가 삭제하는 과정만 남겼다. 그리고 두 가지 메소드로 분리된 그 과정들의 사이에 카운트 변수를 업데이트하는 메소드를 새로 정의해 호출하였다. 카운트 변수를 업데이트하는 메소드는 탐색 메소드와 유사하지만, 목표한 노드가 반드시 있음을 전제로 하고 경로상의 모든 노드의 카운트 변수를 1씩 감소시켜야 한다는 차이가 있다. 목표한 노드가 반드시 있다는 것은 이 메소드를 호출하기 전 탐색 메소드를 통해 확인함으로써 보장한다.  
  
메소드의 개수만 해도 4개가 하나의 작업을 위해 쓰이고, 이중 내가 수정하거나 만든 것이 3개이기 때문에 이 부분 코드가 좀 길다. 후계자 노드를 찾는 메소드는 수정하지 않았으므로 아래 코드블록에 포함하지 않는다. 전체 코드는 <a href="#bodylink-ghcode">여기</a>에서 볼 수 있다.   
  
```cpp
private:
  node* delete_impl(node* start, int value) { // private 특정 값 삭제 메소드
    cout << "current node is " << (start ? to_string(start->getData()) : "NULL") << ".\n";

    if (!start) { // 현재 노드가 NULL
      cout << "No value matches " << value << ".\n";
      return NULL; // 삭제한 노드 없음, NULL 반환
    }

    if (value < start->getData()) // 삭제할 값이 현재 노드보다 작음
      start->setLeft(delete_impl(start->getLeft(), value)); // 왼쪽 서브트리에 삭제 메소드 다시 호출
    else if (value > start->getData()) // else if: 삭제할 값이 현재 노드보다 큼
      start->setRight(delete_impl(start->getRight(), value)); // 오른쪽 서브트리에 삭제 메소드 다시 호출
    else { // else: 삭제할 값이 현재 노드와 같음
      if (!start->getLeft()) { // 왼쪽 서브트리가 없음
        cout << "there is no left subtree. bring the right subtree.\n";
        auto tmp = start->getRight(); // 현재 노드의 오른쪽 서브트리를 가져옴
        cout << "delete " << value << ".\n";
        delete start; // 현재 노드를 지움
        return tmp; // 아까 가져온 오른쪽 서브트리 반환
      }

      if (!start->getRight()) { // 오른쪽 서브트리가 없음
        cout << "there is no right subtree. bring the left subtree.\n";
        auto tmp = start->getLeft(); // 현재 노드의 왼쪽 서브트리 가져옴
        cout << "delete " << value << ".\n";
        delete start; // 현재 노드를 지움
        return tmp; // 아까 가져온 왼쪽 서브트리 반환
      }
    }

    return start;
  }

  void recount(node* value) { // 노드 삭제를 위해 누적 노드 개수를 수정하는 메소드
    node* current = root; // 루트에서 시작

    while (true) {
      if (!current) { // 현재 탐색하는 노드가 NULL인 경우
        cout << "error: No matching value found for " << value->getData() << ".\n";
        return; // 끝
      }

      current->downcnt(); // 현재 노드의 카운트 감소

      if (value->getData() > current->getData()) { // 원하는 값이 더 큼
        cout << "current is " << current->getData() << ". pointer moved to right.\n";
        current = current->getRight(); // 오른쪽 서브트리로 이동
        continue;
      }

      if (value->getData() < current->getData()) { // 원하는 값이 더 작음
        cout << "current is " << current->getData() << ". pointer moved to left.\n";
        current = current->getLeft(); // 왼쪽 서브트리로 이동
        continue;
      }

      /*
      원하는 값 찾음:
      후계자가 선정되어 값이 바뀌었거나 값이 같은 노드가 중복하여 존재하는 경우,
      삭제할 노드를 헷갈리지 않기 위해 객체 자체를 비교함
      */
      if (current == value) {
        cout << value->getData() << " has been found.\n";
        return;
      }

      // 원래 삭제하려던 노드의 후계자가 대신 삭제되어야 하는 경우
      // data는 같지만 노드 자체는 달라서 위의 선택문을 모두 통과하는 경우가 있음
      // 그럴 때는 후계자 선정 규칙에 따라 오른쪽 서브트리로 이동
      cout << "current is " << current->getData() << ". pointer moved to right.\n";
      current = current->getRight(); // 오른쪽 서브트리로 이동
      continue;
    }
  }

public:
  void deleteValue(int value) { // 특정 값 삭제
    node* del_node = find(value); // 삭제할 노드 찾기
    node* succ;

    if (del_node != NULL) { // 삭제할 노드가 있다면
      if (del_node->getLeft() != NULL && del_node->getRight() != NULL) { // 후계 필요
        succ = successor(del_node); // 후계 선정
        recount(succ); // 노드 삭제를 위해 누적 노드 개수를 수정하는 메소드
        del_node->setData(succ->getData()); // 삭제할 노드의 데이터를 후계의 데이터로 대체
        root->setRight(delete_impl(root->getRight(), succ->getData())); // 후계 노드 삭제
      }
      else { // 후계 필요 없음
        recount(del_node); // 노드 삭제를 위해 누적 노드 개수를 수정하는 메소드
        root = delete_impl(root, value); // private 삭제 메소드 호출
      }
    }
    else { // 삭제할 노드가 없음
      cout << "delete error: No value matches " << value << ".\n";
      return; // 돌아감
    }
  }
```  
  
## Rank 메소드
지금까지 여러 메소드들을 개조한 이유는 Rank 메소드를 구현하기 위해서였다. 다시 한 번 설명하자면 Rank 메소드는 트리에서 이진 탐색 트리에서 특정 값보다 크거나 작은 값의 개수를 세는 메소드를 말한다. 나는 key로 주어진 값보다 큰 것의 개수와 작은 것의 개수를 세는 메소드를 구현했다. 두 메소드는 서로 방향만 다를 뿐 과정은 동일하니 큰 값의 개수를 세는 메소드를 기준으로 설명하겠다. 코드블록에도 큰 값을 세는 메소드만 보여주겠지만 삭제 메소드에서와 마찬가지로 전체 코드는 <a href="#bodylink-ghcode">여기</a>에서 볼 수 있다.  
  
Rank를 구하는 과정은 다음과 같다. key 값보다 큰 것의 개수를 세는 과정을 기준으로 하며, **트리에 중복된 값이 저장되어 있을 수 있음을 전제로 한다**. 중복을 불허한다면 과정은 더 단순해질 수 있다.  
  
(1) 우선 key와 같은 값을 가진 노드를 찾을 때까지 탐색을 시작한다.  
(2) key와 다른 값을 가진 노드가 나왔다면 다음을 수행한다.  
<span class="tab">&nbsp; &nbsp; </span>(2.1) key보다 큰 값을 찾았다면 해당 노드를 개수에 포함하기 위해 +1을 하고, 오른쪽 서브트리가 있다면 오른쪽 자손의 수도 같이 더한다. 이후 왼쪽 서브트리로 이동한다.  
<span class="tab">&nbsp; &nbsp; </span>(2.2) key보다 작은 값을 찾았다면 오른쪽 서브트리로 이동한다.  
(3) key와 같은 값을 찾았다면 오른쪽 서브트리로 이동한다.  
(4) NULL에 도달할 때까지 (2)의 과정을 반복한다.  
(5) NULL에 도달했다면 지금까지 센 개수를 반환한다.  
  
작은 값을 세는 메소드는 위의 과정에서 좌우를 바꾸면 된다.  
  
참고를 위해, 중복을 불허한 트리의 Rank 구현 과정도 보자.  
(1) 원하는 값을 찾을 때까지 내려가면서  
(2) 자기 자신보다 작거나 같으면 or 크거나 같으면 +1,  
(3) 해당 노드의 왼쪽 or 오른쪽 자손 노드의 개수도 더한다.  
(4) 원하는 노드를 찾으면 해당 노드의 자신을 포함한 자손 노드의 개수를 세고 끝낸다.  
  
아래 코드는 key보다 큰 값의 개수를 세는 메소드이다. 클래스 외부에서 사용할 수 있어야 하기 때문에 public으로 정의되었다.  
  
```cpp
int countGreater(int key) { // 특정 값(key)보다 큰 요소의 개수 셈
  int cnt = 0;
  node* current = root;

  while (true) { // 반복 탐색
    cout << "current value is " << (current != NULL ? to_string(current->getData()) : "NULL") << "\n";

    if (current == NULL) // 더 탐색할 노드가 없음
      break; // 반복 종료

    if (key == current->getData()) { // key와 같은 값 찾음
      // 오른쪽에 더 큰 값이 남아있을 수 있으므로 오른쪽으로 이동
      cout << "find key value. go right.\n";
      current = current->getRight();
      continue;
    }
    else if (key < current->getData()) { // key보다 큰 값 찾음
      cnt += 1; // 일단 현재 노드를 카운트에 추가

      if (current->getRight() != NULL) // 오른쪽 서브트리가 있다면
        cnt += current->getRight()->getcnt(); // 오른쪽 서브트리의 노드 수도 추가

      // 왼쪽에 더 큰 값이 남아있을 수 있으므로 왼쪽으로 이동
      cout << "current value " << current->getData() << " is greater than key value. add right count and go left\n";
      current = current->getLeft();
      continue;
    }
    else if (key > current->getData()) { // key보다 작은 값 찾음
      // 오른쪽에 더 큰 값이 남아있을 수 있으므로 오른쪽으로 이동
      cout << "current value " << current->getData() << " is lesser than key value. Don't add count and go right\n";
      current = current->getRight();
      continue;
    }
  }

  return cnt; // 반복 종료 후 결과 반환
}
```


<br>
<hr>
<br>

# 참고 자료
[<a id="ref-cite-1" href="#body-cite-1">1</a>] Augmenting Data Structure <a href="https://www.includehelp.com/data-structure-tutorial/augmenting-data-structure.aspx" target="_blank" title="Augmenting Data Structure">https://www.includehelp.com/data-structure-tutorial/augmenting-data-structure.aspx</a>