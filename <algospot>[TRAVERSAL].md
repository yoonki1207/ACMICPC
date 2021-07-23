# 문제 TRAVERSAL (출처: algospot.com)

난이도 下

## 1. Problem

* ### 문제

트리를 순회하는 알고리즘은 트리의 모든 노드들을 특정 순서에 맞춰 방문하지만, 트리는 배열처럼 1차원적인 구조가 아니기 때문에 단 한 가지의 당연한 순서가 존재하지 않습니다. 때문에 필요에 맞춰 순서를 정의해야 합니다. 이진 트리(binary tree)는 모든 노드에 왼쪽과 오른쪽, 최대 두 개의 자손이 있는 트리를 말하는데, 이진 트리의 순회 순서 중 유명한 세 가지로 전위 순회(preorder traverse), 중위 순회(inorder traverse) 그리고 후위 순회(postorder traverse)가 있습니다. 이들은 모두 왼쪽 서브트리를 오른쪽보다 먼저 방문한다는 점에선 같지만, 트리의 루트를 언제 방문하는지가 서로 다릅니다.

전위 순회는 맨 처음에 트리의 루트를 방문하고, 왼쪽과 오른쪽 서브트리를 순서대로 방문합니다. 중위 순회는 왼쪽과 오른쪽 서브트리 사이에 트리의 루트를 방문하고, 후위 순회는 왼쪽과 오른쪽 서브트리를 모두 방문한 뒤에야 루트를 방문합니다.

다음 그림은 이진 트리의 한 예를 보여 줍니다. 이 트리를 전위 순회하면 모든 노드를 27, 16, 9, 12, 54, 36, 72의 순서대로 방문하게 됩니다. 반면 중위 순회했을 때는 9, 12, 16, 27, 36, 54, 72의 순서로, 후위 순회했을 때는 12, 9, 16, 36, 72, 54, 27의 순서로 방문하게 되지요.

<img src="http://algospot.com/media/judge-attachments/bbdb1ada72f7eb16c9291ed59d4761ff/traversal.png" alt="">

어떤 이진 트리를 전위 순회했을 때 노드들의 방문 순서와, 중위 순회했을 때 노드들의 방문 순서가 주어졌다고 합시다. 이 트리를 후위 순회했을 때 각 노드들을 어떤 순서대로 방문하게 될지 계산하는 프로그램을 작성하세요.

* ### 입력

입력의 첫 줄에는 테스트 케이스의 수 C (1≤C≤100)가 주어집니다. 각 테스트 케이스는 세 줄로 구성되며, 첫 줄에는 트리에 포함된 노드의 수 N (1≤N≤100)이 주어집니다. 그 후 두 줄에 각각 트리를 전위 순회했을 때와 중위순회 했을 때의 노드 방문 순서가 N개의 정수로 주어집니다. 각 노드는 1000 이하의 자연수로 번호 매겨져 있으며, 한 트리에서 두 노드의 번호가 같은 일은 없습니다.

* ### 출력

각 테스트 케이스마다, 한 줄에 해당 트리의 후위 순회했을 때 노드들의 방문 순서를 출력합니다

### 예제 입력
```
2
7
27 16 9 12 54 36 72
9 12 16 27 36 54 72
6
409 479 10 838 150 441
409 10 479 150 838 441
```
### 예제 출력
```
12 9 16 36 72 54 27
10 150 441 838 479 409
```

## 2. Solving Process

이진 트리의 순회 방법에는 3가지가 있다.
* 전위 순회(pre-order)
* 중위 순회(in-order)
* 후위 순회(post-order)

이 순회들은 각각 root 노드를 언제 방문 하는지에대한 차이가 있다.

전위는 root -> left sub tree -> right sub tree<br/>
중위는 left sub tree -> root -> right sub tree<br/>
후위는 left sub tree -> right sub tree -> root<br/>

즉 left sub tree와 right sub tree만 찾으면 후위순회를 쉽게 구현할 수 있다.

예제 출력을 예로 들면, root는 전위 순회의 제일 첫 번째 출력물은 '27'이다.<br/>
중위에서 '27'을 기준으로 왼쪽과 오른쪽을 나누면 left sub tree와 right sub tree를 찾을 수 있다.<br/>
left sub tree와 right sub tree의 길이를 구해서 전위 순회에서 left sub tree와 right sub tree의 시작점을 알 수 있다.<br/>
즉슨, left sub tree와 right sub tree의 root를 알 수 있다는 것이기 때문에 이를 재귀적으로 구현해주면 후위 순회를 구현할 수 있다.

## 3. What I learned

나는 이 기본적이고 아주 쉬운 문제를 풀면서 여러번 막혔었다. 이유는 논리력이 문제인 것 같다. 처음 코드를 짰을 때, 간단하게 할 수 있는 코드를 복잡하게 만들었으며, 중복
검사도 있었고 최적화는 개나 줘 버린데다가 논리가 꼬여 코드가 제데로 작동하지도 않았다. 여러번의 시행착오 끝에 나름 깔끔해진 코드를 만들 수 있었다.

### 4. Code


``` cpp
#include<iostream>

int c, n;
int preorder[100];
int inorder[100];

void solve(const int pre[], const int ino[], const int len){
    if(!len) return;
    const int root =  *pre;
    if(len == 1){
        std::cout << root << " ";
        return;
    }
    int index = 0;
    while(ino[index] != root && index < len) index++; // index = 0 ~ len - 1

    solve(pre + 1, ino , index);
    solve(pre + 1 + index, ino + 1 + index, len - index - 1);

    std::cout << root << " ";
    return;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> c;

    for(int i = 0 ; i < c ; i++){
        std::cin >> n;
        for(int j = 0 ; j < n ; j++)
            std::cin >> preorder[j];
        for(int j = 0 ; j < n ; j++)
            std::cin >> inorder[j];
        solve(preorder, inorder, n);
        std::cout << "\n";
    }

    return 0;
}
```

