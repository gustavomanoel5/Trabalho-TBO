#include <iostream>
#include "utils.h"

#define max_bins_v 30

using namespace std;


int main(){



	vector<pair<int, ll>> bins_v;

	cout << "size: " << max_bins_v;	

	for (int i = 1; i <= max_bins_v; i++){

		pair<int, ll> np = {i, i+1};
		bins_v.push_back(np);
	}

	cout << bin_search(bins_v, max_bins_v / 2 - 1) << endl;
	cout << bin_search(bins_v, max_bins_v / 2 + 1) << endl;
	cout << bin_search(bins_v, max_bins_v) << endl;
	cout << bin_search(bins_v, 0) << endl;
	cout << bin_search(bins_v, 1) << endl;
	return 0;
}
