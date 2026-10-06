#include <iostream>
#include "utils.h"
#include <string>

#define max_bins_v 30

using namespace std;


int main(){



	Bitset test(32);

	test.set_bit(0);


	for (int i = 0; i < 12; i++){

		test.set_bit(i);

	}
	
	Bitset test3;
	test3.resize(584121, 1);
	test3.set_bit(10268);
	
	cout << test3.get_bit(10);

	return 0;
}
