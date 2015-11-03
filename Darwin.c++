#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <cassert>   // array

using namespace std;

class Darwin { 
	private:
		vector<Creature> grid;
		int x_axis;
		int y_axis;
		int turn;

	public:
		void Darwin(int w, int h) {
			x_axis = w;
			y_axis = h;
			for(int i = 0; i < w*h; i++) {
				Creature c;
				grid.push_back(c);
			}
		}
		void addCreature(Creature c, int x, int y) {

		}

		void createGrid(int);
		Creature at(int);
		Iterator begin(void);
		Iterator end(void);
};

class Creature {
	private:
		Species _s;
		int direction;
	 	int pc;
	 	bool didMove;

	public:
		void Creature() {

		}
	 	void Creature(Species s) {
	 		_s = s;
	 	}
};

class Species {
	private:
	 	vector<int> instructions;
		string name;

	public:
		void Species() {
			name = '.';
		}

		void addInstruction(int);
		void doNext(Instruction, pc);
};
