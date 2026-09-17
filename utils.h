#pragma once

#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define ll long long
#define is_null(x, y, z) x == R"(\N)" ? z : y 

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

