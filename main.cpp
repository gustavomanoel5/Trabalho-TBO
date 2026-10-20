#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ranges>
#define cls() cout << "\x1B[2J\x1B[H" << std::flush 

#include "file_manager.h"

using namespace std;


bool VERBOSE = false;

//descent parser here

vector<string> tokens;
size_t pos;

vector<vector<string>> parse_or();

vector<vector<string>> parse_primary() {
	if (tokens[pos] == "(") {
		pos++;
		vector<vector<string>> r = parse_or();
		pos++;
		return r;
	}
	string term = tokens[pos] + " " + tokens[pos + 1];
	pos += 2;
	return {{term}};
}

vector<vector<string>> parse_and() {
	vector<vector<string>> r = parse_primary();
	while (pos < tokens.size() && tokens[pos] == "e") {
		pos++;
		vector<vector<string>> rhs = parse_primary();
		vector<vector<string>> merged;
		for (auto& a : r)
			for (auto& b : rhs) {
				auto req = a;
				req.insert(req.end(), b.begin(), b.end());
				merged.push_back(req);
			}
		r = merged;
	}
	return r;
}

vector<vector<string>> parse_or() {
	vector<vector<string>> r = parse_and();
	while (pos < tokens.size() && tokens[pos] == "ou") {
		pos++;
		vector<vector<string>> rhs = parse_and();
		r.insert(r.end(), rhs.begin(), rhs.end());
	}
	return r;
}

vector<vector<string>> parse_expression(const string& expr) {
	string s;
	for (char c : expr) {
		if (c == '(' || c == ')') { s += ' '; s += c; s += ' '; }
		else s += c;
	}
	tokens.clear();
	istringstream ss(s);
	string t;
	while (ss >> t) tokens.push_back(t);
	pos = 0;
	return parse_or();
}

void search_movies(MovieLib &ml){


	vector<ll> result;

	int opt;



	cout << "Selecione o tipo de busca: \n";
	cout << "[1] Por tipo/genero\n[2] Por ano\n[3] Por duracao\n[0] Cancelar\n> ";


	cin >> opt;


	if (opt == 0) return;
	ll runtime;

	cout << "==============================================================================================================================================================\n";
	if (opt != 1) {

		cls();
		ll start, end;
		cout << "Ponto inicial: ";
		cin >> start;
		cout << "Ponto final: ";
		cin >> end;

		cin.ignore();

		auto begin_search = chrono::high_resolution_clock::now();
		result = opt == 2 ? ml.get_slice_by_year(start, end) : ml.get_slice_by_duration(start, end); 
		auto stop_search = chrono::high_resolution_clock::now();

		auto duration_search = chrono::duration_cast<chrono::microseconds> (stop_search - begin_search);

		runtime = (ll) duration_search.count();
	}

	else {

		string _opt;
		cls();

		cout << "Rotulos: tipo/genero\tOperacoes: e, ou\n";
		cout << "Digite sua busca como uma expressão: [tipo|genero] [nome]; encadeie com parenteses, ex: (tipo short e genero war) ou (tipo movie e genero Drama)\n";
		cout << "Cheatsheet de tipos:\n";
		for (int i = 0; i < ml.types.size(); i++){

			cout << "[" << i + 1 << "] " << ml.types[i] << endl;

		}
		cout << "\n * * * \n Cheatsheet de generos:\n";
		for (int i = 0; i < ml.genres.size(); i++){


			cout << "[" << i + 1 << "] " << ml.genres[i] << endl;
		}



		cout << "> ";

		cin.ignore();
		getline(cin, _opt);
		vector<vector<string>> parsed_search = parse_expression(_opt);


		auto begin_search = chrono::high_resolution_clock::now();
		result = ml.search(parsed_search);
	auto stop_search = chrono::high_resolution_clock::now();

	auto duration_search = chrono::duration_cast<chrono::microseconds> (stop_search - begin_search);
	runtime = (ll) duration_search.count();
}

cout << "==============================================================================================================================================================\n";	
cout << "RESULTADO:";
if (!VERBOSE) {
	for (ll i = 0; i < result.size(); i++){

		cout << result[i];
		if (i != result.size() - 1) cout << ", ";

	}

	cout << '\n';
}

else {

	for (ll i = 0; i < result.size(); i++){

		ml.print_movie(result[i]);
		cout << "- - - - - - - - - - - - - - - - - - - - \n";
	}

	cout << '\n';

}



cout << "[EXECUTADO EM " << runtime << " microsseg, " << result.size() << " RESULTADOS]\n[Pressione Enter para continuar...]";

cout << '\n';

cin.ignore();

cls();
}



void search_cinemas(CinemaLib &cl){


}

void search_menu(MovieLib &ml, CinemaLib &cl) {


	int opt;
	cout << "Selecione o que buscar: \n";
	cout << "[1] Filmes\n[0] Cancelar \n> ";

	cin >> opt;	

	cls();	
	switch(opt){

		case 1:
			search_movies(ml);

			break;
		case 2:
			cout << "[Nao implementado, pressione Enter para voltar...]";
			cin.ignore();

	}
}


void cli(MovieLib &ml, CinemaLib &cl){

	vector<string> opt_list = {"Busca"};
	int opt;
	while(true) {

		cout << "Lista de Opcoes: \n";

		for (int i = 1; i <= opt_list.size(); i++){

			cout << "[" << i << "] " << opt_list[i - 1] << endl;

		}
		cout << "[0] Sair\n> ";

		cin >> opt;		


		cls();
		switch(opt){
			case 0:
				return;
			case 1:	
				search_menu(ml, cl);
				break;
			case 2:

				break;
			default:
				cout << "Opcao invalida.\n";
		}
	}

}

int main(int argc, char * argv[]){

	ios::sync_with_stdio(false);

	MovieFileManager mfm("data/filmesCrop.txt");
	MovieLib movie_lib;

	CinemaFileManager cfm("data/cinemas.txt");
	CinemaLib cinema_lib;

	auto begin_fm = chrono::high_resolution_clock::now();
	if (mfm.fetch_movies(movie_lib)) cerr << "error loading movies\n";
	auto stop_fm = 	chrono::high_resolution_clock::now();

	auto begin_fc = chrono::high_resolution_clock::now();
	if (cfm.fetch_cinemas(cinema_lib)) cerr << "error loading cinemas\n";
	auto stop_fc = 	chrono::high_resolution_clock::now();

	vector<string> types(STR_HASH_MOD, "");



	auto begin_hsg = chrono::high_resolution_clock::now();
	movie_lib.sort_by_genre();
	auto stop_hsg = chrono::high_resolution_clock::now();

	auto begin_hst = chrono::high_resolution_clock::now();
	movie_lib.sort_by_type();


	auto stop_hst = chrono::high_resolution_clock::now();

	auto begin_qs = chrono::high_resolution_clock::now();

	movie_lib.sort_by_duration();
	movie_lib.sort_by_year();

	auto stop_qs = chrono::high_resolution_clock::now();

	auto duration_fm = chrono::duration_cast<chrono::microseconds> (stop_fm - begin_fm);
	auto duration_fc = chrono::duration_cast<chrono::microseconds> (stop_fc - begin_fc);
	auto duration_qs = chrono::duration_cast<chrono::microseconds> (stop_qs - begin_qs);


	auto duration_hsg = chrono::duration_cast<chrono::microseconds> (stop_hsg - begin_hsg);
	auto duration_hst = chrono::duration_cast<chrono::microseconds> (stop_hst - begin_hst);



	cout << "[FETCHING TIME: movies: " << duration_fm.count() << " microsec cinemas: " << duration_fc.count() << " microsec]\n";	
	cout << "[SORTING TIME: hash/bitset: (genres: " << duration_hsg.count() << " microsec | type: " << duration_hst.count() << " microsec) quicksort: " << duration_qs.count() << " microsec]\n";


	cout << "[Pressione enter para continuar...]\n";
	cin.ignore();


	if (argc > 1){

		for (int i = 0; i < sizeof(argv[i]); i++){

			switch(argv[1][i]){

				case 'c':
					cls();	
					cli(movie_lib, cinema_lib);

				case 'r':
					break;

				case 'v':

					VERBOSE = true;
			}

		}


		return 0;
	}


	cout << "[TESTS]\n";

	cout << movie_lib.movie_is_type(0, "short") << endl;
	cout << movie_lib.movie_is_genre(1000, "Action") << endl;



	for (ll i = 0; i < movie_lib.all_movies.size(); i++){

	cout << movie_lib.movies_by_duration[i] << endl;

	}

//	vector<ll> test_a = movie_lib.get_slice_by_duration(1, 6000);

//	cout << endl;
//	cout << movie_lib.all_movies[movie_lib.movies_by_duration[0]].runtime_min << endl;
	return 0;
}


