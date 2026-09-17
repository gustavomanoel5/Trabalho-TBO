#include <iostream>

#include "file_manager.h"
#include "movie.h"
#include "utils.h"
#include "cinema.h"

using namespace std;

int main(int argc, char * argv[]){


	MovieFileManager mfm("data/filmesCrop.txt");
	MovieLib movie_lib;

	CinemaFileManager cfm("data/cinemas.txt");
	CinemaLib cinema_lib;

	if (mfm.fetch_movies(movie_lib)) cerr << "error loading movies\n";
	if (cfm.fetch_cinemas(cinema_lib)) cerr << "error loading cinemas\n";

	return 0;
}


