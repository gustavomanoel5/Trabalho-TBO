#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <span>
#include <string.h>

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
		vector<Movie> all_movies;

		vector<pair<string, Bitset>> movies_by_genre;
		vector<pair<string, Bitset>> movies_by_type;
		vector<ll> movies_by_duration;
		vector<ll> movies_by_start_year;

		vector<string> genres;
		vector<string> types;


		void add_movie(const ll &id, const string &type, const string &title, const string &og_title, const string &is_adult, const string &start_year, const string &end_year, const string &runtime_min, const vector<string> &genres){

			//long long parsed_id = stoll(id) - starting_id;


			Movie mov(id, type, title, og_title, is_adult, start_year, end_year, runtime_min, genres);

			all_movies.emplace_back(mov);
		}




		void sort_by_genre(){

			movies_by_genre.resize(STR_HASH_MOD);




			for (ll i = 0; i < all_movies.size(); i++){


				for (string genre : all_movies[i].genres){

					pair<string, Bitset> * hashed_movie = &movies_by_genre[stohash(genre)];

					if (hashed_movie -> first == genre) {

						hashed_movie -> second.set_bit(i);


					}

					else if (hashed_movie -> first.size() > 0){

						cerr << "CONFLITO DE HASH: DADOS SOBRESCRITOS (" << genre << " e " << hashed_movie -> first << ")\n";

					}

					else {

						hashed_movie -> first = genre;

						hashed_movie -> second.resize(all_movies.size(), 1);

						hashed_movie -> second.set_bit(i);				


						genres.emplace_back(genre);
					}

				}

			}


		}

		void sort_by_type(){
			movies_by_type.resize(STR_HASH_MOD);
			for (ll i = 0; i < all_movies.size(); i++){

				string this_type = all_movies[i].type;
				pair<string, Bitset> * hashed_type = &movies_by_type[stohash(this_type)];

				if (hashed_type -> first == this_type) {

					
					hashed_type -> second.set_bit(i);

				}

				else if (hashed_type -> first.size() > 0) {

					cerr << "CONFLITO DE HASH: DADOS SOBRESCRITOS (" << all_movies[i].type << " e " << movies_by_type[stohash(all_movies[i].type)].first << ")\n";

				}

				else {

					hashed_type -> first = this_type;
					hashed_type -> second.resize(all_movies.size(), 1);
					hashed_type -> second.set_bit(i);				

					types.emplace_back(this_type);
				}


			}


		}

		//quick sort here	



		void quick_sort(vector<ll>& vec, ll low, ll high, const string& type) {
			if (type != "duration" && type != "year") return;

			

			while (low < high) {

				

				ll p = low + rand() % (high - low + 1);
				

				Movie item_p = all_movies[vec[p]];
				ll pivot = type == "year" ? item_p.start_year : item_p.runtime_min;

				ll lt = low, i = low, gt = high;

				
				while (i <= gt) {
					
					Movie item_i = all_movies[vec[i]];
					if ( (type == "year" ? item_i.start_year : item_i.runtime_min) < pivot) swap(vec[lt++], vec[i++]);
					else if ( (type == "year" ? item_i.start_year : item_i.runtime_min) > pivot) swap(vec[i], vec[gt--]);

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
		/*void quick_sort_id(vector<Movie>& vec, ll low, ll high) {

			while (low < high) {

				ll p = low + rand() % (high - low + 1);
				ll pivot = vec[p].id;

				ll lt = low, i = low, gt = high;

				while (i <= gt) {

					if (vec[i].id < pivot) swap(vec[lt++], vec[i++]);
					else if ( vec[i].id > pivot) swap(vec[i], vec[gt--]);

					else i++;
				}

				if (lt - low < high - gt) {

					quick_sort_id(vec, low, lt - 1);
					low = gt + 1;
				} 
				else {

					quick_sort_id(vec, gt + 1, high);
					high = lt - 1;
				}
			}
		}*/

		void sort_by_duration() {

			movies_by_duration.resize(all_movies.size());
			iota(movies_by_duration.begin(), movies_by_duration.end(), 0);
				
			quick_sort(movies_by_duration, 0, movies_by_duration.size() - 1, "duration");



		}

		void sort_by_year() {

			movies_by_start_year.resize(all_movies.size());
			iota(movies_by_start_year.begin(), movies_by_start_year.end(), 0);
			quick_sort(movies_by_start_year, 0, movies_by_start_year.size() - 1, "year");


		}
/*
		void reset_order(){

			quick_sort_id(all_movies, 0, all_movies.size() - 1);

		}
*/
		bool movie_is_type(const ll &movie, const string &type){


			return movies_by_type[stohash(type)].second.get_bit(movie);	

		}

		bool movie_is_genre(const ll &movie, const string &genre){


			return movies_by_genre[stohash(genre)].second.get_bit(movie);	

		}

		ll bin_search_year(const vector<ll> &vec, const int &target, ll i = 0, ll min = -1, ll max = 0, int iter = 0){ 


			if (iter == 0) i = vec.size() % 2 == 0 ? vec.size() / 2 - 1 : vec.size() / 2;	
			if (max == 0) max = vec.size();

			iter++;


			//	cout << "vec: " << vec.size() << " finding " << target << " at [" << i << ", " << min << ", " << max << "] tried " << iter << "times\n";

			if (all_movies[vec[i]].start_year == target) return i;



			if (i == 0 || i == min || i == max){

				return i;

			}

			if (target > all_movies[vec[i]].start_year) {
				min = i;
				return bin_search_year(vec, target, i + (max - min)/2, min, max, iter);
			}

			max = i;
			return bin_search_year(vec, target, i - (i - min) / 2, min, max, iter);

		}

		vector<ll> get_slice_by_year(const int &start, const int &end){

			span<ll> cut_res;
			span<ll> span_res(movies_by_start_year);
			vector<ll> vec_res;

			ll floor = bin_search_year(movies_by_start_year, start);


			while(floor < span_res.size() && all_movies[span_res[floor]].start_year < start) {floor++;}
			while(floor > 0 && all_movies[span_res[floor - 1]].start_year == all_movies[span_res[floor]].start_year) {floor--;}

			ll ceiling =  bin_search_year(movies_by_start_year, end);

			while(all_movies[span_res[ceiling]].start_year > end && ceiling > 0) {ceiling--;}
			while(ceiling + 1 < span_res.size() && all_movies[span_res[ceiling + 1]].start_year == all_movies[span_res[ceiling]].start_year) {ceiling++;}

			if (ceiling == floor) {

				cout << "[BAD INPUT: NO RANGE]\n";
				return vec_res;
			}


			cut_res = span_res.subspan(floor, ceiling - floor);


			vec_res.assign(cut_res.begin(), cut_res.end());
			return vec_res;	

		}
		/*ll bin_search_duration(const vector <ll> &v, int val, const ll i = -1, const ll p = -1){ // FOR YEAR ONLY

		  ll start = i == -1 ? v.size() / 2 - 1 : i;
		  ll prev = p == -1 ? start : p;



		  cout << "looking for " << val << " at: " << start << " currently at: " << all_movies[v[start]].runtime_min << endl;

		  if (all_movies[v[start]].runtime_min == val) return start;
		  else if (start == 0 || start == v.size() - 1 || start == p) return start;
		  else if (all_movies[v[start]].runtime_min < val) {
		  start = prev > start ? start + (prev - start) / 2 : start + (v.size() - start) / 2;
		  return bin_search_duration(v, val, start, prev);

		  }
		  else {
		  start = prev < start ? start - (start - prev) / 2 : start / 2;
		  return bin_search_duration(v, val, start, prev);
		  }
		  }*/

		ll bin_search_runtime(const vector<ll> &vec, const int &target, ll i = 0, ll min = -1, ll max = 0, int iter = 0){ //stealing angel's code, let's pray


			if (iter == 0) i = vec.size() % 2 == 0 ? vec.size() / 2 - 1 : vec.size() / 2;	
			if (max == 0) max = vec.size();

			iter++;


			//	cout << "vec: " << vec.size() << " finding " << target << " at [" << i << ", " << min << ", " << max << "] tried " << iter << "times\n";

			if (all_movies[vec[i]].runtime_min == target) return i;



			if (i == 0 || i == min || i == max){

				return i;

			}

			if (target > all_movies[vec[i]].runtime_min) {
				min = i;
				return bin_search_runtime(vec, target, i + (max - min)/2, min, max, iter);
			}

			max = i;
			return bin_search_runtime(vec, target, i - (i - min) / 2, min, max, iter);

		} // and lo and behold, it worked on the first try, krilling meself fr

		vector<ll> get_slice_by_duration(const int &start, const int &end){

			span<ll> cut_res;
			span<ll> span_res(movies_by_duration);

			vector<ll> vec_res;

			ll floor = bin_search_runtime(movies_by_duration, start);

			while(floor < span_res.size() && all_movies[span_res[floor]].runtime_min < start) {floor++;}
			while(floor > 0 && all_movies[span_res[floor - 1]].runtime_min == all_movies[span_res[floor]].runtime_min && all_movies[span_res[floor-1]].runtime_min != -1) {floor--;}

			ll ceiling =  bin_search_runtime(movies_by_duration, end);

			while(all_movies[span_res[ceiling]].runtime_min > end && ceiling > 0) {ceiling--;}
			while(ceiling + 1 < span_res.size() && all_movies[span_res[ceiling + 1]].runtime_min == all_movies[span_res[ceiling]].runtime_min) {ceiling++;}


			if (ceiling == floor || floor > ceiling) {

				cerr << "[BAD INPUT: NO RANGE]\n";
				return vec_res;
			}

			cut_res = span_res.subspan(floor, ceiling - floor);

			vec_res.assign(cut_res.begin(), cut_res.end());
			return vec_res;	

		}


		vector<ll> search(const vector<vector<string>> &rules) {
			vector<ll> res;


			for (ll i = 0; i < (ll)all_movies.size(); i++) {
				bool any_rule = false;

				for (const vector<string> &rule : rules) {
					bool all_terms = true;

					for (const string &term : rule) {
						vector<string> item = _split(term, ' ');
						if (item.size() < 2) { 
							all_terms = false; 
							break;
						}


						bool has = false;
						if (item[0] == "tipo") {

							has = movies_by_type[stohash(item[1])].second.get_bit(i) != 0;
						} 
						else {
							Bitset * bit_set = &movies_by_genre[stohash(item[1])].second;
							if (bit_set -> get_size() == 0) {

								has = false;
								break;
							}
							has = bit_set -> get_bit(i);
						}

						if (!has) { 
							all_terms = false; 
							break; 
						}
					}

					if (all_terms) { 
						any_rule = true; 
						break; 
					}
				}

				if (any_rule) res.push_back(i);
			}
			return res;
		}

		void print_movie(const ll &id){

			string _null = "\\N"; 

			Movie mov = all_movies[id];
			cout << '[' << mov.title << " (" << (mov.og_title == _null ? mov.og_title : "sem titulo original") << ")";
			cout << " | Tipo: " << (mov.type != _null ? mov.type : "nulo") << " | Lancamento: " << ((mov.start_year != -1) ? to_string(mov.start_year) : "nulo");
			cout << " | Rating: "<< (mov.is_adult == true ? "+18" : "L") << " | Duracao (min): " << (mov.runtime_min != -1 ? to_string(mov.runtime_min) : "nulo") << endl;
			cout << " | Generos: ";
			for (string genre : mov.genres){

				cout << genre << ' ' << endl;

			}
			cout << "]\n";


		}	
};
