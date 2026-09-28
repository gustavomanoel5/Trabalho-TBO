#include <iostream>
#include "utils.h"
#include <string>

#define max_bins_v 30

using namespace std;


int main(){



	Bitset test(32);

	test.set_bit(0);

	Bitset test2(32);


	for (int i = 0; i < 12; i++){

		test.set_bit(i);

	}

	cout << (*(test.get_data()) & 0)<< endl;
	cout << (test2.get_bit(32) & test.get_bit(32)) << endl;
	return 0;
}
