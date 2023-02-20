#include<vector>
#include<cassert>

#pragma GCC optimize("O3")
#pragma GCC target("avx2,bmi,bmi2")

struct matrix {
	int n; vector<int> data;
	matrix(int n_) : n(n_), data(n * n, 0) { }
	int& operator()(int i, int j) { return data[i * n + j]; }
	int size() { return n; }
};

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


