#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <ranges>

#include "bitset.h"

using namespace std;

#define ll long long
#define is_null(x, y, z) x == R"(\N)" ? z : y 
#define STR_HASH_MOD 1e3 + 5





/*vector<string> _split(const string &str, const char &del){


	vector<string> r;

	for (auto word : views::split(str, del)){

		r.emplace_back(word.begin(), word.end());

	}

        return r;

}*/

vector<string> _split(const string &str, const char &del){

        stringstream ss(str);

        string token;

        vector<string> r;

        while(getline(ss, token, del)){
                r.push_back(token);
        }

        return r;

}

string trim(const string &str){

	string trimmed_str;
	
	ll ltrim = -1; ll rtrim = -1; 
	for (int i = 0; i < str.size(); i++){

		if (ltrim == -1 && str[i] != ' ') ltrim = i;
		if (rtrim == -1 && str[str.size() - i] != ' ') rtrim = i;

		if (ltrim != -1 && rtrim != -1) break;
	}

	trimmed_str = str.substr(ltrim, str.size() - rtrim - ltrim);

	return trimmed_str;
	
}

vector<pair<string, ll>> hash_mem;

ll stohash(const string &str){

	for (pair<string, ll> item : hash_mem){

		if (item.first == str) return item.second;

	}

	const ll p = 31;
	const ll m = STR_HASH_MOD;
	ll hash_val = 0;
	ll p_pow = 1;

	for (char c : str) {

		hash_val = (hash_val + (c - 'A' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;

	}

	hash_mem.push_back({str, hash_val});
	return hash_val;
}


ll bin_search(const vector <pair<int, ll>> &v, int val, const ll i = -1, const ll p = -1){ // FOR PAIRS OF INT & LL

	ll start = i == -1 ? v.size() / 2 - 1 : i;
	ll prev = p == -1 ? start : p;

	

	cout << "looking for " << val << " at: " << start << " currently at: " << v[start].first << endl;
	if (v[start].first == val) return start;
	else if (start == 0 || start == v.size() - 1) return -1;
	else if (v[start].first < val) {
		start = prev > start ? start + (prev - start) / 2 : start + (v.size() - start) / 2;
		return bin_search(v, val, start, prev);
	
	}
	else {
		start = prev < start ? start - (start - prev) / 2 : start / 2;
		return bin_search(v, val, start, prev);
	}
}
