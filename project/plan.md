## 주제
**하천 쓰레기 민원 조회 시스템 만들기**  
주 사용 대상 : 민원 접수 및 처리 담당 공무원  
  
## 주요 기능
- 지역별 민원 관리
- 민원 신고
- 민원 조회/검색
- 민원 처리
- 파일 형태로 데이터 저장 밎 재사용(보안 문제까지는 아직 내가 해결할 수 있는 부분이 아님)
  
## 필요 사항
- 개별 민원 노드
- 누적 민원 노드
- 민원 처리 시스템 클래스
  
---
  
## class complain *// 개별 민원 노드*
- private:
    - string pic_name *// 사진 이름(필요시 절대/상대 파일 경로 포함, 사진 크기를 비롯해 사진 파일 자체에 대한 각종 정보는 원본 파일의 정보에 포함된다고 본다)*
    - int comp_date *// 민원 신고 날짜*
    - pair&lt;double, double&gt; coordinates *// 사진 좌표*
- public:
    - int wastes[5] *// 멤버 변수지만 어차피 getter를 써도 포인터로 전달되어 원본 수정이 가능하니 public 변수로 사용*
    - 생성자
    - string get_name
    - pair&lt;double, double&gt; get_codi
    - void rename(string) *// 사진 이름 변경*

이 클래스는 기록과 조회 목적이 크기 때문에 getter는 필요하지만 setter는 그다지 필요하지 않음.  
  
## class accumed_compls *// 누적 민원 노드*
- private:
    - int waste_code *// 쓰레기 분류 번호*
    - vector&lt;complain&gt; compls *// 쓰레기 분류 번호에 따른 해당 쓰레기 관련 민원 벡터*
- public:
    - 생성자
    - int get_num *// 쓰레기 분류 번호 반환*
    - int get_compls_size *// 민원 노드 벡터 길이(누적 민원 수) 반환*
    - void add_compl *// 민원 추가*
    - void clear_compls *// 민원 처리(누적 민원 벡터를 clear하며, 개별 민원 중 2종류 이상의 쓰레기가 포함된 민원의 경우 쓰레기 포함 표기를 수정한 후 clear해야 한다.)*
  
## class compl_system *// 민원 처리 시스템 클래스*
- private:
    - int area_code *// 지역 코드(행정동/법정동 등등)*
    - accumed_compls compls_list[5] *// 쓰레기 분류별 누적 민원 배열*
    - vector&lt;complain&gt; *// 전체 민원 벡터*
    - multimap&lt;string, complain&gt; comp_map *// 사진 이름 기준 전체 민원 멀티맵*
    - multimap&lt;double, complain&gt; longitude_map *// 경도 기준 전체 민원 멀티맵*
    - multimap&lt;double, complain&gt; latitude_map *// 위도 기준 전체 민원 멀티맵*
    - multimap&lt;int, complain&gt; latitude_map *// 민원 접수 날짜 기준 전체 민원 멀티맵*
- public:
    - 생성자
    - void receive_compl *// 민원 접수*
    - void view_all(sort_by) *// 정렬 기준(sort_by)에 따른 전체 민원 조회(출력하게 할 것이므로 반환값 없음)*
    - void search_compl(search_by) *// 검색 기준(search_by)에 따른 특정 민원 검색*
    - bool is_enough(waste_code) *// 특정 분류의 쓰레기 민원이 충분히 많아 처리해도 될만한지 확인*
    - void clear_compls(waste_code) *// 특정 분류의 쓰레기 관련 민원 일괄 처리*
    - void load_save *// 파일에 기록된 데이터를 통한 이전 업무 기록 로드. 매번 새 시스템을 생성할 수는 없으니까.*
    - void save_task *// 업무 진행 상황을 파일로 기록. 업무를 종료하거나 중간 저장이 필요할 때 실행.*
  
민원을 처리함에 있어서 사진의 크기가 중요할까? 사진 크기 기준 정렬을 사용할지, 조회와 검색이 가능하게 할지 고민을 조금 했는데, 필요 없다고 결론내렸다. 특정 민원을 찾을 때 민원이 접수된 날짜나 위치를 검색해서 찾지 사진의 크기를 검색해서 찾을 이유는 어지간히 예외적인 상황이 아닌 이상 없을 거라고 본다.  
  
시간복잡도가 비교적 낮은 검색 기능 구현을 위해 메모리를 다소 낭비하는 방식을 택했다. 전체 민원 벡터를 하나 두긴 하지만 이것만으로 매번 정렬하고 검색하는 것은 아무리 이진 탐색을 한다 해도 별로 좋은 방법이 아닌 것 같아서 멀티맵을 사용했다. 전체 민원 벡터는 전체 민원을 조회하고자 할 때에 사용하고, 멀티맵은 검색 결과를 조회할 때 사용한다.  
  
원래 준비된 데이터에는 날짜에 대한 정보가 없지만, 민원 처리 시스템을 만들고 있으니 민원 접수 날짜도 필요할 거라고 생각해 추가했다. 실제로 프로그램을 실행할 때는 임의의 날짜를 사용할 생각이다. 가능한 한 원본 사진이 찍힌 날짜 이후의 날짜를 입력하도록 하고 싶지만 그것은 힘들 것 같다. 이 프로젝트는 말은 시스템이라고 하지만 시뮬레이터에 더 가깝다.  
  
프로그램을 종료해도 민원을 처리한 기록은 남아야 하니까(컴퓨터는 꺼놓고 퇴근해야 하니까) 프로그램의 진행 상황을 파일로 저장하는 기능도 구현하고 싶다. 사실 데이터베이스를 쓰면 훨씬 깔끔하고 나도 편하게 할 수 있을 것 같지만, 그걸 쓰기 시작하면 내가 구상한 모든 자료구조가 필요가 없다.. 어차피 다양한 곳에 널린 쓰레기를 효율적으로 치우자! 라는 주제는 발에 채일 만큼 많을 거라고 예상했고, 실제로도 그랬다. 나까지 같은 소리를 하면서 뭔가 나만의 다른 점을 어필하기엔 딱히 다익스트라에 욕심도 없고, 그보다는 어떤 하나의 시스템을 직접 구상해보는 게 내 흥미를 더 끌어서 이런 프로젝트로 정했다. 데이터베이스를 쓸 수 없다는 점은 감수해야죠 뭐 어쩌겠습니까..  
  
## 추가로 필요한 것
  
### 시스템이 생성된 지역구 목록
지역 코드를 이용해 각 지역의 시스템을 분리하도록 구상했다. 그리고 출퇴근도 전제했으니, 프로그램이 시작될 때 지역 코드를 입력하면 해당 코드로 생성된 기록이 있는지 파악하여 이전의 기록을 로드하거나, 없다면 새로 만들도록 하고 싶다. 이 목록은 저장소 내에 지역 코드로 생성된 로그 파일이 있는지 검사하기만 하는 것으로 대체될 수 있다.
  
### 민원 처리 시스템 업무 기록
내 프로젝트의 주요 사용 대상은 공무원이다. 공무원은 출퇴근을 한다. 퇴근할 때는 컴퓨터를 끄고 가야 한다. 고로 프로그램이 실행 중 저장되고 변경된 데이터는 컴퓨터가 종료되어도 남을 수 있도록 어딘가에 기록되어야 한다. 세이브 파일을 만든다는 말이다.  
  
### 단위 테스트, TDD 배우기
참고  
- [Visual Studio에서 C/C++에 대한 단위 테스트 작성](https://learn.microsoft.com/ko-kr/visualstudio/test/writing-unit-tests-for-c-cpp?view=vs-2022)
- [Visual Studio에서 Microsoft Unit Testing Framework for C++ 사용](https://learn.microsoft.com/ko-kr/visualstudio/test/how-to-use-microsoft-test-framework-for-cpp?source=recommendations&view=vs-2022)
- [Microsoft.VisualStudio.TestTools.CppUnitTestFramework API 참조](https://learn.microsoft.com/ko-kr/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2022)
- [C++ 배열의 값이 전부 같은지 확인하는 방법 (std::equal)](https://torbjorn.tistory.com/357)
- [C++ 유닛 (단위) 테스트 쉽게 써보기](https://m.post.naver.com/viewer/postView.naver?volumeNo=16995308&memberNo=559061)