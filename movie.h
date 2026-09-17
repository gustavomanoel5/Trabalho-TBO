#pragma once

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Movie{

	private:
		long long id;
		string type;
		string title;
		string og_title;
		bool is_adult;
		int start_year;
		int end_year;
		int runtime_min;
		vector<string> genres;

	public:
		Movie(){

		}
		Movie(const long long &id, const string &type, const string &title, const string &og_title, const string &is_adult, const string &start_year, const string &end_year, const string &runtime_min, const vector<string> &genres) {
			
			
			this -> id = id;
			this -> type = type;
			this -> title = title;
			this -> og_title = og_title;
			this -> is_adult = stoi(is_adult) == 1 ? true : false;
			this -> start_year = is_null(start_year, stoi(start_year), -1);
			this -> end_year = is_null(end_year, stoi(end_year), -1);
			this -> runtime_min = is_null(runtime_min, stoi(runtime_min), -1);
			this -> genres = genres;
			
		}
};


class MovieLib{

	public:
		long long starting_id;
		vector<Movie> all_movies;

		vector<vector<Movie>> movies_by_genre;

		void add_movie(const string &id, const string &type, const string &title, const string &og_title, const string &is_adult, const string &start_year, const string &end_year, const string &runtime_min, const vector<string> &genres){

			long long parsed_id = stoll(id) - starting_id;


			Movie mov(parsed_id, type, title, og_title, is_adult, start_year, end_year, runtime_min, genres);

			all_movies.push_back(mov);
		}

		
};
