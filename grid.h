#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <limits>

#include "cinema.h"

using namespace std;

/* Módulo 3: grade espacial para buscar cinemas por distância.
Cinemas com a mesma coordenada são agrupados num ponto; a grade distribui os pontos.
Só guarda posições do vetor all_cinemas (CinemaLib), nunca cópias dos cinemas.*/

// centro, raio e cinemas dentro de +-1 bilhão: dx * dx + dy * dy fica abaixo de 8e18 e cabe em long long
const long long LIMITE_BUSCA = 1000000000;

bool dentro_do_limite(const long long &valor){

    return valor >= -LIMITE_BUSCA && valor <= LIMITE_BUSCA;

}

class Ponto {

    public:
        long long x;
        long long y;
        vector<int> cinemas; 

        Ponto(const long long &x, const long long &y){

            this -> x = x;
            this -> y = y;

        }

};

class Grid {

    public:
        long long inicio_mapa;
        long long tamanho_celula;
        int numero_divisoes;
        vector<Ponto> pontos;
        // posições em pontos; célula (coluna, linha) fica em linha * numero_divisoes + coluna
        vector<vector<int>> lista_celulas; 

        Grid(const long long &inicio = 100000, const long long &fim = 1000000, const int &divisoes = 10){

            inicio_mapa = inicio;
            numero_divisoes = divisoes;
            tamanho_celula = (fim - inicio) / divisoes;
            if (tamanho_celula < 1) tamanho_celula = 1;

        }

        // coluna x ou linha y de uma coordenada o que cai fora do mapa vai para a borda
        int achar_indice(const long long &valor) const {

            long long indice = (valor - inicio_mapa) / tamanho_celula;

            if (indice < 0) return 0;
            if (indice >= numero_divisoes) return numero_divisoes - 1;
            return indice;

        }

        int posicao_celula(const int &coluna, const int &linha) const {

            return linha * numero_divisoes + coluna;

        }

        void montar(const vector<Cinema> &cinemas){

            // assign (e não resize) e clear para que montar de novo não duplique nada
            lista_celulas.assign(numero_divisoes * numero_divisoes, vector<int>());
            pontos.clear();

            for (int i = 0; i < cinemas.size(); i++){

                int celula = posicao_celula(achar_indice(cinemas[i].x), achar_indice(cinemas[i].y));

                // mesma coordenada => mesma célula, então basta procurar o ponto nesta célula
                int ponto = -1;
                for (int p : lista_celulas[celula]){

                    if (pontos[p].x == cinemas[i].x && pontos[p].y == cinemas[i].y){
                        ponto = p;
                        break;
                    }

                }

                if (ponto == -1){

                    ponto = pontos.size();
                    pontos.push_back(Ponto(cinemas[i].x, cinemas[i].y));
                    lista_celulas[celula].push_back(ponto);

                }

                pontos[ponto].cinemas.push_back(i);

            }

        }

        // devolve as posições (no vetor all_cinemas) dos cinemas a até `raio` do centro
        vector<int> buscar(const long long &centro_x, const long long &centro_y, const long long &raio) const {

            vector<int> encontrados;
            if (raio < 0) return encontrados;

            // fora do limite, raio * raio e dx * dx + dy * dy estourariam long long
            if (!dentro_do_limite(centro_x) || !dentro_do_limite(centro_y) || !dentro_do_limite(raio)) return encontrados;

            // só as células que o quadrado [centro - raio, centro + raio] toca
            int coluna_ini = achar_indice(centro_x - raio);
            int coluna_fim = achar_indice(centro_x + raio);
            int linha_ini = achar_indice(centro_y - raio);
            int linha_fim = achar_indice(centro_y + raio);

            for (int linha = linha_ini; linha <= linha_fim; linha++){

                for (int coluna = coluna_ini; coluna <= coluna_fim; coluna++){

                    for (int p : lista_celulas[posicao_celula(coluna, linha)]){

                        // uma conta por ponto; se ele está dentro, todos os seus cinemas entram
                        long long dx = pontos[p].x - centro_x;
                        long long dy = pontos[p].y - centro_y;

                        if (dx * dx + dy * dy <= raio * raio){
                            for (int c : pontos[p].cinemas) encontrados.push_back(c);
                        }

                    }

                }

            }

            return encontrados;

        }

};


// Módulo 3: monta a grade e lê buscas por distância até o usuário digitar um raio negativo
void busca_espacial(const CinemaLib &cinema_lib){

	cout << fixed << setprecision(2);

	auto inicio_grade = chrono::steady_clock::now();
	Grid grid;
	grid.montar(cinema_lib.all_cinemas);
	auto fim_grade = chrono::steady_clock::now();

	cout << "grade montada em " << chrono::duration<double, milli>(fim_grade - inicio_grade).count() << " ms ("
	     << cinema_lib.all_cinemas.size() << " cinemas em " << grid.pontos.size() << " pontos)\n";

	long long x, y, raio;
	while (true){

		cout << "\nbusca por distancia - digite X Y raio (raio negativo para sair): ";

		if (!(cin >> x >> y >> raio)){

			if (cin.eof()) break;

			// limpa o erro e descarta o resto da linha; sem isso o cin segue falhando, inclusive no menu
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "entrada invalida: digite tres numeros inteiros\n";
			continue;

		}

		if (raio < 0) break;

		if (!dentro_do_limite(x) || !dentro_do_limite(y) || !dentro_do_limite(raio)){

			cout << "X, Y e raio precisam ficar entre -" << LIMITE_BUSCA << " e " << LIMITE_BUSCA << "\n";
			continue;

		}

		auto inicio_busca = chrono::steady_clock::now();
		vector<int> encontrados = grid.buscar(x, y, raio);
		auto fim_busca = chrono::steady_clock::now();

		cout << encontrados.size() << " cinemas encontrados em "
		     << chrono::duration<double, micro>(fim_busca - inicio_busca).count() << " us\n";

		for (int i = 0; i < encontrados.size() && i < 10; i++){

			const Cinema &cinema = cinema_lib.all_cinemas[encontrados[i]];
			cout << "  " << cinema.name << " (" << cinema.x << ", " << cinema.y << ") R$ " << cinema.price << "\n";

		}
		if (encontrados.size() > 10) cout << "  ... e mais " << encontrados.size() - 10 << "\n";

	}

}
