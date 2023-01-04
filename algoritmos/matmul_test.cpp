#include<iostream>
#include<vector>
#include<cassert>

#define forr(i,a,b) for(int i=a;i<int(b);++i)
using namespace std;

constexpr int n = 3107;

#pragma GCC optimize("O3")
#pragma GCC target("avx2,bmi,bmi2")

struct matrix {
	int n; vector<int> data;
	matrix(int n_) : n(n_), data(n * n, 0) { }
	int& operator()(int i, int j) { return data[i * n + j]; }
	int size() { return n; }
};

matrix matmul_naive(matrix& a, matrix& b) {
	assert(a.size() == b.size());
	matrix result(a.size());
	forr(i,0,n) forr(k,0,n) forr(j,0,n)
		result(i, j) += a(i, k) * b(k, j);
	return result;
}

matrix matmul(matrix& a, matrix& b) {
	constexpr int s = 256;
	assert(a.size() == b.size());
	const int n = a.size(); matrix result(n);
	for(int ib=0;ib<n;ib+=s){int li=min(ib+s,n);
		for(int kb=0;kb<n;kb+=s){int lk=min(kb+s,n);
			for(int jb=0;jb<n;jb+=s){int lj=min(jb+s,n);
				forr(i,ib,li) forr(k,kb,lk) forr(j,jb,lj)
					result(i, j) += a(i, k) * b(k, j);
			}
		}
	}
	return result;
}

int main() {

	matrix a(n);
	matrix b(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			a(i, j) = rand();
			b(i, j) = rand();
		}
	}

	matrix c = matmul(a, b);
	matrix d = matmul_naive(a, b);

	int result_c = 0;
	int result_d = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			result_c ^= c(i, j);
			result_d ^= d(i, j);
		}
	}

	assert(result_c == result_d);
	cout << result_c << " -- " << result_d << '\n';
}
