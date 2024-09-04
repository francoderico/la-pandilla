// this file needs sc = double
struct line {
	pt p, pq;
	line() {}
	line(pt p_, pt q_):p(p_),pq(q_-p_){}
};
bool parallel(line a, line b) {
	return abs(det(unit(a.pq),unit(b.pq)))<=EPS;
}
pt intersect(line& a, line& b) {
	if(parallel(a, b))return pt(DINF, DINF);
	return b.p+(det(a.p-b.p,a.pq)/det(b.pq,a.pq))*b.pq;
}

struct halfplane : public line { // representa lado izquierdo de (a->b)
	double angle;
	halfplane(){}
	halfplane(pt a, pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(halfplane b)const{return angle<b.angle;}
	bool out(pt q){return det(pq,q-p)<-EPS;}
};
vector<pt> intersect(vector<halfplane> b) {
	vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	forn(i,4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
	sort(all(b));
	int n=sz(b),q=1,h=0;
	vector<halfplane> c(sz(b)+10);
	forn(i,n) {
		while(q<h&&b[i].out(intersect(c[h],c[h-1])))h--;
		while(q<h&&b[i].out(intersect(c[q],c[q+1])))q++;
		c[++h]=b[i];
		if(q<h&&abs(det(c[h].pq,c[h-1].pq))<EPS){
			if(dot(c[h].pq,c[h-1].pq)<=0) return {};
			h--;
			if(b[i].out(c[h].p)) c[h]=b[i];
		}
	}
	while (q<h-1&&c[q].out(intersect(c[h],c[h-1])))h--;
	while (q<h-1&&c[h].out(intersect(c[q],c[q+1])))q++;
	if (h-q<=1)return{};
	c[h+1] = c[q];
	vector<pt> s;
	forr(i,q,h+1) s.pb(intersect(c[i],c[i+1]));
	return s;
}
