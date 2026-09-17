#pragma once

#include "utils.h"

using namespace std;

class Cinema{

	public:

		int id;
		string name;
		ll x;
		ll y;
		double price;
		vector<ll> movies;

		Cinema(){}
		Cinema(const ll &id, const string &name, const ll &x, const ll &y, const double &price, const vector<ll> &movies){

			this -> id = id;
			this -> name = name;
			this -> x = x;
			this -> y = y;
			this -> price = price;
			this -> movies = movies;

		}

};



class CinemaLib{

	public:
		vector<Cinema> all_cinemas;


		void add_cinema(const string &id,const string &name,const string &x,const string &y,const string &price, const vector<ll> &movies) {

			Cinema new_cinema(stoll(id), name, is_null(x, stoll(x), (ll) nullptr), is_null(y, stoll(y), (ll) nullptr), is_null(price, stod(price), -1), movies);

			all_cinemas.push_back(new_cinema);

		}

};
