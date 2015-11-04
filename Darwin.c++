#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <vector>    // vector
#include <utility>   // pair

// #include "Darwin.h"

using namespace std;

enum Instruction {
	hop,
	lft,
	rght,
	infect,
	if_empty,
	if_wall,
	if_random,
	if_enemy,
	go
};

class Species {
	public:
	 	vector<pair<Instruction, int>> instructions;
		char name;

	public:
		Species() { // default constructor
			name = '.';
		}
		Species(char initial) {
			name = initial;

			if(initial == 'f') { // food
				(*this).addInstruction(lft);
				(*this).addInstruction(go, 0);
			}
			else if(initial == 'h') { // hopper
				(*this).addInstruction(hop);
				(*this).addInstruction(go, 0);
			}
			else if(initial == 'r') { // rover
				(*this).addInstruction(if_enemy, 9);
				(*this).addInstruction(if_empty, 7);
				(*this).addInstruction(if_random, 5);
				(*this).addInstruction(lft);
				(*this).addInstruction(go, 0);
				(*this).addInstruction(rght);
				(*this).addInstruction(go, 0);
				(*this).addInstruction(hop);
				(*this).addInstruction(go, 0);
				(*this).addInstruction(infect);
				(*this).addInstruction(go, 0);
			}
			else if(initial == 't') { // trap
				(*this).addInstruction(if_enemy, 3);
				(*this).addInstruction(lft);
				(*this).addInstruction(go, 0);
				(*this).addInstruction(infect);
				(*this).addInstruction(go, 0);
			} // initialized constructor
		}
		void addInstruction(Instruction ins) {
			pair<Instruction, int> action;
			action = make_pair(ins, -1);
			instructions.push_back(action);
		}
		void addInstruction(Instruction ins, int line) {
			pair<Instruction, int> control;
			control = make_pair(ins, line);
			instructions.push_back(control);
		}
		// void nextInstruction(Instruction ins, int pc);
};

class Creature {
	public:
		Species _s;
		int direction;
	 	int pc;
	 	bool didMove;
	 	bool isNull;

	public:
		Creature() { // default constructor
			isNull = true;
		}
	 	Creature(const Species& s, int d) { // initialized constructor
	 		_s = s;
	 		direction = d;
	 		pc = 0;
	 		didMove = false;
	 		isNull = false;
	 	}
	 	void makeMove(const Darwin& d) {
 			// moves
	 	}
};

template<typename T>;
class D_Iterator {
	private:
		T _v;
	
	public:
		D_Iterator(const T& v) {
			_v = v;
		}
		bool operator == (const D_Iterator& rhs) const {
			return (&_v == &(rhs._v));
		}
		bool operator != (const D_Iterator& rhs) const {
			return !(*this == rhs);
		}
		const T& operator * () const {
			return _v;
		}
		D_Iterator& operator ++ () { // pre increment
			++&_v;
			return *this;
		}
		D_Iterator& operator ++ (int) { // post increment
			D_Iterator d = *this;
			++*this;
			return d;
		}
};

class Darwin { 
	public:
		int x_axis;
		int y_axis;
		int turn;

	public:
		vector<Creature> grid;

		Darwin() {
		}
		Darwin(int h, int w) {
			x_axis = w;
			y_axis = h;
			for(int i = 0; i < w*h; i++) {
				Creature c;
				grid.push_back(c);
			}
		}
		void addCreature(const Creature& c, int x, int y) {
			int position = (x + 1) * (y + 1); 
			grid[position-1] = c;
		}
		void executeTurn() {
			++turn; 
			D_Iterator b = (*this).begin();
			D_Iterator e = (*this).end();
			while(b != e) {
				if(!(*b).isNull)
					(*b).makeMove(*this);
				++b;
			}
		}
		// void createGrid(int);
		// Creature at(int);
		D_Iterator begin() {
			D_Iterator<Creature> b = grid[0];
			return b;
		}
		D_Iterator end() {
			int end = x_axis*y_axis;
			D_Iterator<Creature> e = grid[end-1];
			return e;
		}
};
