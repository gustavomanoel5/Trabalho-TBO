#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "utils.h"
#include "movie.h"
#include "cinema.h"

#define prefix_size 2
#define max_str_len 1028
// arbitrary ridiculous bullshit because this compiler seems to looove messing with poor ladies like myself

using namespace std;

class FileManager{

	public:
		string filename;

		FileManager(string fname){
			filename = fname;
		}

	
		



};

class MovieFileManager: public FileManager {
		
	public:

		MovieFileManager(string filename) : FileManager(filename){}

		bool fetch_movies(MovieLib &lib){
		
        		ifstream file(filename);
        		if (!file.is_open()) return 1;

        		string line; bool ignore_first = true;

        		while(getline(file, line)){
					
						if (ignore_first){
							ignore_first = false;
							continue;
						}

                		vector<string> tokens = _split(line, '\t');
						tokens[0] = tokens[0].substr(prefix_size);

						if (lib.all_movies.size() == 0) {
							lib.starting_id = stoll(tokens[0]);
						}
						
						
						
                		lib.add_movie(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7], _split(tokens[8], ','));
        		}


        	return 0;

		};


};

class CinemaFileManager: public FileManager{

	public:

		CinemaFileManager(string filename): FileManager(filename){};

		bool fetch_cinemas(CinemaLib &lib){
		
        		ifstream file(filename);
        		if (!file.is_open()) return 1;

        		string line; bool ignore_first = true;

        		while(getline(file, line)){
					
						if (ignore_first){
							ignore_first = false;
							continue;
						}

                		vector<string> tokens = _split(line, ',');
				tokens[0] = trim(tokens[0]).substr(prefix_size);

				vector<ll> movies_id;
				for (int i = 5; i < tokens.size(); i++){

					movies_id.push_back(stoll(trim(tokens[i]).substr(prefix_size)));


				}
						
						
                		lib.add_cinema(trim(tokens[0]), trim(tokens[1]), trim(tokens[2]), trim(tokens[3]), trim(tokens[4]), movies_id);
        		}


        	return 0;

		};

};
