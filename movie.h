#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "utils.h"



using namespace std;

class Movie{

			
	public:
		long long id;
		string type;
		string title;
		string og_title;
		bool is_adult;
		int start_year;
		int end_year;
		int runtime_min;
		vector<string> genres;

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

		vector<pair<string, vector<ll>>> movies_by_genre;
		vector<pair<string, vector<ll>>> movies_by_type;
		vector<pair<int, ll>> movies_by_duration;
		vector<pair<int, ll>> movies_by_start_year;

		void add_movie(const string &id, const string &type, const string &title, const string &og_title, const string &is_adult, const string &start_year, const string &end_year, const string &runtime_min, const vector<string> &genres){

			long long parsed_id = stoll(id) - starting_id;


			Movie mov(parsed_id, type, title, og_title, is_adult, start_year, end_year, runtime_min, genres);

			all_movies.push_back(mov);
		}



	
		void sort_by_genre(){
			movies_by_genre.resize(STR_HASH_MOD);
			for (Movie item : all_movies){

				for (string genre : item.genres){

					if (movies_by_genre[stohash(genre)].first == genre) {

						movies_by_genre[stohash(genre)].second.push_back(item.id);

					}

					else if (movies_by_genre[stohash(genre)].second.size() != 0){

						cerr << "CONFLITO DE HASH: DADOS SOBRESCRITOS (" << genre << " e " << movies_by_genre[stohash(genre)].first << ")\n";

					}

					else {

						movies_by_genre[stohash(genre)].first = genre;
						movies_by_genre[stohash(genre)].second.push_back(item.id);				
	
					}
	
				}

			}


		}

		void sort_by_type(){
			movies_by_type.resize(STR_HASH_MOD);
			for (Movie item : all_movies){


					if (movies_by_type[stohash(item.type)].first == item.type) {

						movies_by_type[stohash(item.type)].second.push_back(item.id);

					}

					else if (movies_by_type[stohash(item.type)].second.size() != 0){

						cerr << "CONFLITO DE HASH: DADOS SOBRESCRITOS (" << item.type << " e " << movies_by_type[stohash(item.type)].first << ")\n";

					}

					else {

						movies_by_type[stohash(item.type)].first = item.type;
						movies_by_type[stohash(item.type)].second.push_back(item.id);				
	
					}
	

			}


		}
};
