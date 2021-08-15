# 문제 너드인가, 너드가 아닌가? 2

## 1. Problem

![www algospot com_judge_problem_read_NERD2 (3)](https://user-images.githubusercontent.com/17930226/129449027-6a88e9a5-a97b-4df2-ac1e-8e6b0a9e2ab8.png)
###### 출처: https://www.algospot.com/judge/problem/read/NERD2

## 2. Solving Process

어떤 지원자 A가 어떤 지원자 B보다 p, q가 두 크다면 지원자 B는 대회에 참여할 수 없다. 이를 A가 B를 **지배한다 라고 하자.**

지원자들의 q와 p를 좌표계에 대입해서 찍어보자. 그리고 어떤 참가자 C에대해 지배당하는 모든 지원자는 대회에 출전할 수 없으니 이 점들은 지워준다.

그럼 이 지원자들의 x좌표를 내림차순으로 정리했을 때, 지원자들의 y좌표는 오름차순으로 정렬되는 규칙이 생긴다. 이것이 이 문제의 **key point**이다.


이 알고리즘을 적용하는 가장 쉬운 자료구조는 배열이지만, 참여자의 수로 올 수 있는 최대의 경우는 50,000이므로 최대 시간복잡도는 O(N^2)로 시간 내에 풀 수 없다.

따라서 O(NlogN)인 자료구조로 풀어내야 한다.

이진 탐색 트리를 사용하면 O(NlogN)안에 풀 수 있다.

c++에는 균형잡힌 이진트리 구조인 map이 있다.

## 3. What I learnd

이 문제를 처음 풀 때 난 계층 구조에 집중했다. 

트리의 root에 (0, 0)인 노드를 기준으로 지배하는 노드가 leaf에 있도록 설정했다.

예를 들어 어떤 지원자를 추가할 때 지원자를 추가할 위치를 root부터 검색한다.

어떤 노드 A를 검사할 때 지원자가 A를 지배하면 A의 아이들을 검색하고, 아니라면 A의 child에 추가시키는 방식으로 풀이했다.

생각해보니 이 방식은 O(N^2)일 뿐더러 나는 q1 < q2이면 p1 > p2라는 규칙을 인지하지 못 했다.

어떻게 하면 이걸 구현할 수 있을까 고민하는 과정에서 c++ STL의 map 자료구조를 배웠고, 문제의 조건을 다시 한번 꼼꼼히 살펴봐야한다는 것을 느꼈다.

추가로 어떤 STL을 사용하려면 cpp reference을 읽고 그 특징을 꼼꼼히 봐야 문제를 해결할때 더 빠르게 풀 수 있다는 것을 느낌.

##4. Code

``` cpp

#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int C, N;
int sum;
map<int, int> coords;

bool isDominated(int x, int y){
    map<int, int>::iterator it = coords.lower_bound(x);
    if(it == coords.end()) return false;
    return it->second > y;
}

void removeDominated(const int x, const int y){
    coords.insert(make_pair(x, y));
    map<int, int>::iterator it = coords.find(x);

    if(it == coords.begin()) return;
    //if not empty
    --it;
    while(it->second < y){
        if(it == coords.begin()) {
            coords.erase(it);
            break;
        }
        else {
            map<int, int>::iterator tmp = it;
            tmp--;
            coords.erase(it);
            it = tmp;
        }
    }
}

int main(){
    cin >> C;
    for(int c = 0 ; c < C ; c++){
        cin >> N;
        coords.clear();
        sum = 0;
        for(int i = 0 ; i < N ; i++){
            int p, q;
            cin >> p >> q;
            if(!isDominated(p, q))
                removeDominated(p, q);
            sum += coords.size();
        }
        cout << sum << "\n";
    }
    return 0;
}


```

