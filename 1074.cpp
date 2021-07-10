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
