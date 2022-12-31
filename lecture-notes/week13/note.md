## 벨만 포드
모든 간선을 매번 확인해 최단거리를 구함. 다익스트라를 포함할 수 있으며 음수 가중치 사용 가능. 교수가 자꾸 다익스트라보다 훨씬 간단하다고 주장하는데 절대 못 믿음. 알고리즘이라는 이름 달고 간단한 거 한 번도 못 봤음.

### 문제
음수 간선 사이클에 빠질 수 있음

### 해결
경로 탐색 후 음수 간선 사이클이 있는지 확인하기 → 만약 네거티브 사이클이 있다면 그 문제는 벨만 포드로 풀 수 없음. non-parametical 문제라고 불림.

### 과정
- 초기화 : 각 정점까지 가는 거리 무한, 시작점까지 가는 거리는 0, 경로 NULL  
- 정점 개수만큼 모든 간선에 대해 반복  
  - (1) 간선 선택 (2) relax : 지금 새로 알게 된 거리가 원래 알던 것보다 짧으면 업데이트

## 질문할 내용
- 크루스칼 사이클 검사 union 말고 간선이 거치는 노드를 방문 배열로 기록해서 한 번 방문한 곳을 다시 방문하지 않게 해도 되는 거 아닌가?
- 기말 평가 점수에 포함되는 자료구조에 벡터랑 맵도 들어가나?

## 오늘 블로그 과제 평가 번호
13, 28, 6, 2, 25

## 기말 고사 공지
자리마다 콘센트는 있는데 혹시 모르니 충전 잘 해와라
간단한 공지가 있으니 일찍 올수록 좋다