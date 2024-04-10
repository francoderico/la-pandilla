struct halfplane:public ln{ // polygon intersecting left side of halfplanes
	double angle;
	halfplane(){}
	halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(halfplane b)const{return angle<b.angle;}
	bool out(pt q){return pq%(q-p)<-EPS;}
};
vector<pt> intersect(vector<halfplane> b){
	vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	forn(i, 4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
	sort(all(b));
	int n=sz(b),q=1,h=0;
	vector<halfplane> c(sz(b)+10);
	forn(i, n){
		while(q<h&&b[i].out(c[h]^c[h-1])) h--;
		while(q<h&&b[i].out(c[q]^c[q+1])) q++;
		c[++h]=b[i];
		if(q<h&&abs(c[h].pq%c[h-1].pq)<EPS){
			if(c[h].pq*c[h-1].pq<=0) return {};
			h--;
			if(b[i].out(c[h].p)) c[h]=b[i];
		}
	}
	while(q<h-1&&c[q].out(c[h]^c[h-1]))h--;
	while(q<h-1&&c[h].out(c[q]^c[q+1]))q++;
	if(h-q<=1)return {};
	c[h+1]=c[q];
	vector<pt> s;
	forr(i,q,h+1) s.pb(c[i]^c[i+1]);
	return s;
}