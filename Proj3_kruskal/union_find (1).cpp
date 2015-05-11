#include "union_find.hpp"
#include "edge.hpp"

Union_Find::Union_Find(unsigned long int N){ //228
	num_components = N;
	vector<Site> temp1 (N);
	id = temp1;
	for (Site i = 0; i < N; i++){
		id[i] = i;
	}
	vector<unsigned long int> temp2 (N,1);
	sz = temp2;
}

Component Union_Find::find(const Site p){
	if (p == id[p]){
		return p;
	}

	id[p] = find(id[p]);
	return id[p];
}

void Union_Find::onion(const Site p, const Site q){
	Component qval = find(q);
	Component pval = find(p);
	if (qval == pval){
		return;
	}
	if (sz[pval] < sz[qval]){
		id[pval] = qval;
		sz[qval] += sz[pval];
	}
	else{
		id[qval] = pval;
		sz[pval] += sz[qval];
	}
	num_components--;
}