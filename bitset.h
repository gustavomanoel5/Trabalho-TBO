#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cinttypes>


using namespace std;

#define ull uint64_t
#define ull_size sizeof(ull)

const ull max_ull = -1;
class BitPointer {

	private:
		char * p;
		ull sect;

	public:

		BitPointer(){};

		void set_pos(char * p, const ull &sect) {

			assert(sect <= max_ull);

			this -> p = p;
			this -> sect = sect;


		}


		char * get_pos(){

			return p;		

		}

		ull get_sect(){

			return sect;

		}
};

class Bitset {

	private:
		char * data;
		BitPointer bit_p;


	public:
		Bitset(const ull &size, const ull &sections = 1){

			data = (char *) calloc(size, sections);
			bit_p.set_pos(data, 0);
		}

		void resize(const ull &size, const ull &mult){

			
	
		}

		char * get_data(){

			return data;

		}
	
		void set_bit(const ull &pos, const ull &section = 0){

			
			for (int i = 0; i < section; i++){

				bit_p.set_pos((bit_p.get_pos() + ull_size), bit_p.get_sect() + 1);

			}
			
			bit_p.set_pos(bit_p.get_pos() + pos / 8, bit_p.get_sect());

			*(bit_p.get_pos()) = *(bit_p.get_pos()) | (1 << (pos % 8)); 
		}


		short get_bit(const ull &pos, const ull &section = 0){
		
			bit_p.set_pos(data, 0);	
			for (int i = 0; i < section; i++){

				bit_p.set_pos(bit_p.get_pos() + ull_size, bit_p.get_sect() + 1);

			}

			bit_p.set_pos(bit_p.get_pos() + pos / 8, bit_p.get_sect());

			if (pos % 8 == 0) {


			}	
			return *(bit_p.get_pos()) & (1 << (pos % 8 ));
		}

};
