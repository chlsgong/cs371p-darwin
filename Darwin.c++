#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <vector>    // vector
#include <utility>   // pair

#include "Darwin.h"

using namespace std;

//class Species

Species::Species() { // default constructor
	name = '.';
}
Species::Species(char initial) {
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
void Species::addInstruction(Instruction ins) { // adds actions
	pair<Instruction, int> action;
	action = make_pair(ins, -1);
	instructions.push_back(action);
}
void Species::addInstruction(Instruction ins, int line) { // adds controls
	pair<Instruction, int> control;
	control = make_pair(ins, line);
	instructions.push_back(control);
}
pair<Instruction, int> Species::nextInstruction(int pc) {
	return instructions[pc];
}

// class Creature

Creature::Creature() { // default constructor
	isNull = true;
}
Creature::Creature(const Species& s, int d) { // initialized constructor
	_s = s;
	direction = d;
	pc = 0;
	didMove = false;
	isNull = false;
}
void Creature::makeMove(Darwin& d, int i) {
	// moves
	if(!isNull && !didMove) {
		cout << "test" << endl;
		if(pc >= (int) (_s.instructions).size())
			pc = 0;
		pair<Instruction, int> nextIns = _s.nextInstruction(pc);
		switch(nextIns.first) {
			case hop: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer != this || (*c_pointer).isNull) {
					if(direction == 0) {	// west
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i - 1] = c_tmp;
					}
					else if(direction == 1) {	// north
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i - d.x_axis] = c_tmp;
					}
					else if(direction == 2) {	// east
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i + 1] = c_tmp;
					}
					else if(direction == 3) {	// south
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i + d.x_axis] = c_tmp;
					}
				}
				++pc;
				didMove = true;
			}break;
		
			case lft: {
				direction -= 1;
				cout << direction << endl;
				if(direction < 0)
					direction = 3;
				++pc;
				didMove = true;
			}break;

			case rght: {
				direction += 1;
				if(direction > 3)
					direction = 0;
				++pc;
				didMove = true;
			}break;

			case infect: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer != this && ((*c_pointer)._s).name != _s.name) {
					(*c_pointer)._s = _s;
					(*c_pointer).pc = 0;
				}
				++pc;
				didMove = true;
			}break;

			case if_empty: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer == this || !(*c_pointer).isNull) {
					++pc;
					(*this).makeMove(d, i);
				}
				else {
					pc = nextIns.second;
					(*this).makeMove(d, i);
				}
			}break;

			case if_wall: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer != this) {
					++pc;
					(*this).makeMove(d, i);
				}
				else {
					pc = nextIns.second;
					(*this).makeMove(d, i);
				}
			}break;

			case if_random: {
				int n = rand();
				if(n % 2 == 0) {
					++pc;
					(*this).makeMove(d, i);
				}
				else {
					pc = nextIns.second;
					(*this).makeMove(d, i);
				}
			}break;

			case if_enemy: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer == this || (*c_pointer).isNull || ((*c_pointer)._s).name == _s.name) {
					++pc;
					(*this).makeMove(d, i);
				}
				else {
					pc = nextIns.second;
					(*this).makeMove(d, i);
				}
			}break;

			case go: {
				pc = nextIns.second;
				(*this).makeMove(d, i);
			}break;
		}
	}
}
void Creature::reset() {
	didMove = false;
}

// class Darwin

Darwin::Darwin() {
	x_axis = 10;
	y_axis = 10;
	turn = 0;
	for(int i = 0; i < 100; i++) {
		Creature c;
		grid.push_back(c);
	}
}
Darwin::Darwin(int h, int w) {
	x_axis = w;
	y_axis = h;
	turn = 0;
	for(int i = 0; i < w*h; i++) {
		Creature c;
		grid.push_back(c);
	}
}
void Darwin::addCreature(const Creature& c, int y, int x) {
	int position = (x_axis * y) + x; 
	grid[position] = c;
	cout << (grid[position]._s).name << endl;
}
Creature& Darwin::spaceAhead(Creature& c, int i) {
	int d = c.direction;
	if(d == 0 && i - 1 >= 0) // west
		return grid[i - 1];
	else if(d == 1 && i - x_axis >= 0) // north
		return grid[i - x_axis];
	else if(d == 2 && i + 1 < x_axis*y_axis) // east
		return grid[i + 1];
	else if(d == 3 && i + x_axis < x_axis*y_axis) // south
		return grid[i + x_axis]; 
	else
		return c;
}
void Darwin::createGrid() {
	cout << "Turn = " << turn << "." << endl;
	cout << "  ";
	for(int i = 0; i < x_axis; i++) {
		cout << (i % 10);
	}
	cout << endl;
	int j = 0;
	for(int i = 0; i < y_axis; i++) { // rows
		cout << (i % 10) << " ";
		for( ; j < (i + 1)*x_axis; j++) { // columns
			cout << (grid[j]._s).name;
		}
		cout << endl;
	}
	cout << endl;
}
void Darwin::executeTurn() {
	++turn; 
	D_Iterator<int> b = (*this).begin();
	D_Iterator<int> e = (*this).end();
	while(b != e) {
		grid[*b].makeMove(*this, *b);
		++b;
	}
	while(b != e) {
		grid[*b].reset();
		++b;
	}
}
Creature Darwin::at(int i) {
	return grid[i];
}
D_Iterator<int> Darwin::begin() { // beginning of grid
	D_Iterator<int> b(0);
 	return b;
}
D_Iterator<int> Darwin::end() { // end of grid
 	int end = x_axis*y_axis;
 	D_Iterator<int> e(end); // 1 past last index
	return e;
}
