#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

#include "bitset.h"
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

		vector<pair<string, Bitset>> movies_by_genre;
		vector<pair<string, Bitset>> movies_by_type;
		vector<ll> movies_by_duration;
		vector<ll> movies_by_start_year;



		void add_movie(const string &id, const string &type, const string &title, const string &og_title, const string &is_adult, const string &start_year, const string &end_year, const string &runtime_min, const vector<string> &genres){

			long long parsed_id = stoll(id) - starting_id;


			Movie mov(parsed_id, type, title, og_title, is_adult, start_year, end_year, runtime_min, genres);

			all_movies.push_back(mov);
		}




		void sort_by_genre(){

			movies_by_genre.resize(STR_HASH_MOD);




			for (ll i = 0; i < all_movies.size(); i++){

				for (string genre : all_movies[i].genres){

					if (movies_by_genre[stohash(genre)].first == genre) {

						movies_by_genre[stohash(genre)].second.set_bit(i);


					}

					else if (movies_by_genre[stohash(genre)].first.size() > 0){

						cerr << "CONFLITO DE HASH: DADOS SOBRESCRITOS (" << genre << " e " << movies_by_genre[stohash(genre)].first << ")\n";

					}

					else {

						movies_by_genre[stohash(genre)].first = genre;

						movies_by_genre[stohash(genre)].second.resize(all_movies.size(), 1);

						movies_by_genre[stohash(genre)].second.set_bit(i);				


					}

				}

			}


		}

		void sort_by_type(){
			movies_by_type.resize(STR_HASH_MOD);
			for (ll i = 0; i < all_movies.size(); i++){


				if (movies_by_type[stohash(all_movies[i].type)].first == all_movies[i].type) {

					movies_by_type[stohash(all_movies[i].type)].second.set_bit(i);

				}

				else if (movies_by_type[stohash(all_movies[i].type)].first.size() > 0) {

					cerr << "CONFLITO DE HASH: DADOS SOBRESCRITOS (" << all_movies[i].type << " e " << movies_by_type[stohash(all_movies[i].type)].first << ")\n";

				}

				else {
					movies_by_type[stohash(all_movies[i].type)].first = all_movies[i].type;
					movies_by_type[stohash(all_movies[i].type)].second.resize(all_movies.size(), 1);
					movies_by_type[stohash(all_movies[i].type)].second.set_bit(i);				

				}


			}


		}

		//quick sort here	



		void quick_sort(vector<Movie>& vec, ll low, ll high, const string& type) {
			if (type != "duration" && type != "year") return;

			while (low < high) {

				ll p = low + rand() % (high - low + 1);
				ll pivot = type == "year" ? vec[p].start_year : vec[p].runtime_min;

				ll lt = low, i = low, gt = high;

				while (i <= gt) {

					if ( (type == "year" ? vec[p].start_year : vec[i].runtime_min) < pivot) swap(vec[lt++], vec[i++]);
					else if ( (type == "year" ? vec[p].start_year : vec[i].runtime_min) > pivot) swap(vec[i], vec[gt--]);

					else i++;
				}

				if (lt - low < high - gt) {

					quick_sort(vec, low, lt - 1, type);
					low = gt + 1;
				} 
				else {
				
					quick_sort(vec, gt + 1, high, type);
					high = lt - 1;
				}
			}
		}


		void sort_by_duration() {

			quick_sort(all_movies, 0, all_movies.size() - 1, "duration");


			for (ll i = 0; i < all_movies.size(); i++){

				movies_by_duration.push_back(i);				

			}

		}

		void sort_by_year() {

			quick_sort(all_movies, 0, all_movies.size() - 1, "year");


			for (ll i = 0; i < all_movies.size(); i++){

				movies_by_start_year.push_back(i);				

			}

		}
		

		bool movie_is_type(const ll &movie, const string &type){


			return movies_by_type[stohash(type)].second.get_bit(movie);	

		}

		bool movie_is_genre(const ll &movie, const string &genre){


			return movies_by_genre[stohash(genre)].second.get_bit(movie);	

		}


};
