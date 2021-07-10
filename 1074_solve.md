# 문제 1074
## 1. 문제 설명
#### 난이도 <img src="https://d2gd6pc034wcta.cloudfront.net/tier/10.svg" width="11em"></img>
한수는 크기가 2N × 2N인 2차원 배열을 Z모양으로 탐색하려고 한다. 예를 들어, 2×2배열을 왼쪽 위칸, 오른쪽 위칸, 왼쪽 아래칸, 오른쪽 아래칸 순서대로 방문하면 Z모양이다.

<img src="https://upload.acmicpc.net/21c73b56-5a91-43aa-b71f-9b74925c0adc/-/preview/" width="128px"></img>

만약, N > 1이 라서 왼쪽 위에 있는 칸이 하나가 아니라면, 배열을 크기가 2N-1 × 2N-1로 4등분 한 후에 재귀적으로 순서대로 방문한다.

다음 예는 22 × 22 크기의 배열을 방문한 순서이다.

<img src="https://upload.acmicpc.net/adc7cfae-e84d-4d5c-af8e-ee011f8fff8f/-/preview/" width="256px"></img>

N이 주어졌을 때, r행 c열을 몇 번째로 방문하는지 출력하는 프로그램을 작성하시오.

다음은 N=3일 때의 예이다.


<img src="https://upload.acmicpc.net/d3e84bb7-9424-4764-ad3a-811e7fcbd53f/-/preview/" width="512px"></img>

## 2. Solving Process
1. 2<sup>n</sup>x2<sup>n</sup> 크기의 배열을 탐색하는 과정은 재귀적으로 보임.
2. 첫 번째로 직접 배열을 생성해서 풀이할 수 있지만, 최대 2<sup>15</sup>x2<sup>15</sup>은 10억이 넘어가므로 공간적으로나 시간적으로나 비효율적.
3. n의 크기가 얼마가 됐든, 2차원 배열을 4등분 하면 방문하는 순서는 좌상, 우상, 좌하, 우하로 일정함. 편의상 좌상, 우상, 좌하, 우하를 각각 0, 1, 2, 3번 공간이라고 하겠음.
4. 입력받은 좌표의 위치에 따라 0번 공간이라면(0~2<sup>n-2</sup>)사이에, 1번이라면(2<sup>2n-2</sup> ~ 2<sup>2n-2</sup>x2) 2번이라면, (2<sup>2n-2</sup>x2 ~ 2<sup>2n-2</sup>x3) 3번이라면, (2<sup>2n-2</sup>x3 ~ 2<sup>2n</sup>) 사이에 있음을 알 수 있음.
5. 좌표가 N=n의 크기에서 어느 위치인지 구하면, 좌표가 속한 공간을 부분 2차원 배열로 보고 N=n-1의 크기에서 process 4번과 같은 방식으로 해결해나가면 된다.

말로 풀어서 수식적인 풀이를 했지만, 처음 이 문제를 봤을 땐 수식보단 이미 방문한 배열을 채워진 공간으로 보고 채워지는 순서의 규칙을 직관적으로 이해해서 풀었다.


## 3. Code

```cpp

#include <iostream>

unsigned int expInt(int x, int n){
	if(n==0) return 1u;
	return expInt(x, n-1) * (unsigned int)x;
}

unsigned int getArea(int n){ // 2^(2n-2)
	return expInt(2, 2*n-2);
}

int getAreaNumber(int n, int r, int c){
	n = expInt(2, n-1);
	return c / n + (r / n) * 2;
}

int main(){
	int N, r, c;
	
	std::cin >> N >> r >> c;
	
	int n = N;
	
	unsigned int sumA = 0;
	for(int i = n ; i != 0 ; i--){
		sumA += getArea(i) * (unsigned int)getAreaNumber(i, r, c);
		r %= expInt(2, i-1);
		c %= expInt(2, i-1);
	}
	
	std::cout << sumA << std::endl;
	return 0;
}

```
