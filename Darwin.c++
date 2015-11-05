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
		(*this).addInstruction(LEFT);
		(*this).addInstruction(GO, 0);
	}
	else if(initial == 'h') { // hopper
		(*this).addInstruction(HOP);
		(*this).addInstruction(GO, 0);
	}
	else if(initial == 'r') { // rover
		(*this).addInstruction(IF_ENEMY, 9);	// 0
		(*this).addInstruction(IF_EMPTY, 7);	// 1
		(*this).addInstruction(IF_RANDOM, 5);	// 2
		(*this).addInstruction(LEFT);			// 3
		(*this).addInstruction(GO, 0);			// 4
		(*this).addInstruction(RIGHT);			// 5
		(*this).addInstruction(GO, 0);			// 6
		(*this).addInstruction(HOP);			// 7
		(*this).addInstruction(GO, 0);			// 8
		(*this).addInstruction(INFECT);			// 9
		(*this).addInstruction(GO, 0);			// 10
	}
	else if(initial == 't') { // trap
		(*this).addInstruction(IF_ENEMY, 3);
		(*this).addInstruction(LEFT);
		(*this).addInstruction(GO, 0);
		(*this).addInstruction(INFECT);
		(*this).addInstruction(GO, 0);
	} // initialized constructor
}
void Species::addInstruction(Instruction ins) { // adds actions
	if(name == '.')
		name = 'd';
	pair<Instruction, int> action;
	action = make_pair(ins, -1);
	instructions.push_back(action);
}
void Species::addInstruction(Instruction ins, int line) { // adds controls
	if(name == '.')
		name = 'd';
	pair<Instruction, int> control;
	control = make_pair(ins, line);
	instructions.push_back(control);
}
pair<Instruction, int> Species::nextInstruction(int pc) {
	assert(pc > -1);
	assert(pc < (int) instructions.size());
	return instructions[pc];
}

// class Creature

Creature::Creature() { // default constructor
	isNull = true;
	didMove = true;
}
Creature::Creature(const Species& s, int d) { // initialized constructor
	_s = s;
	direction = d;
	pc = 0;
	didMove = false;
	isNull = false;
}
int Creature::makeMove(Darwin& d, int i) {
	assert(i > -1);
	assert(i < (int) (d.grid).size());
	// moves
	if(!isNull && !didMove) {
		// cout << _s.name << " " << direction << endl;
		if(pc >= (int) (_s.instructions).size())
			pc = 0;
		pair<Instruction, int> nextIns = _s.nextInstruction(pc);
		switch(nextIns.first) {
			case HOP: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer != this || (*c_pointer).isNull) {
					if(direction == 0) {	// west
						++pc;
						didMove = true;
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i - 1] = c_tmp;
					}
					else if(direction == 1) {	// north
						++pc;
						didMove = true;
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i - d.x_axis] = c_tmp;
					}
					else if(direction == 2) {	// east
						++pc;
						didMove = true;
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i + 1] = c_tmp;
					}
					else if(direction == 3) {	// south
						++pc;
						didMove = true;
						Creature c_tmp = *this;
						d.grid[i] = *c_pointer;
						d.grid[i + d.x_axis] = c_tmp;
					}
				}
			}break;
		
			case LEFT: {
				direction -= 1;
				if(direction < 0)
					direction = 3;
				++pc;
				didMove = true;
			}break;

			case RIGHT: {
				direction += 1;
				if(direction > 3)
					direction = 0;
				++pc;
				didMove = true;
			}break;

			case INFECT: {
				Creature* c_pointer = &(d.spaceAhead(*this, i));
				if(c_pointer != this && (*c_pointer)._s.name != _s.name) {
					(*c_pointer)._s = _s;
					(*c_pointer).pc = 0;
				}
				++pc;
				didMove = true;
			}break;

			case IF_EMPTY: {
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

			case IF_WALL: {
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

			case IF_RANDOM: {
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

			case IF_ENEMY: {
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

			case GO: {
				pc = nextIns.second;
				(*this).makeMove(d, i);
			}break;
		}
	}
	return pc;
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
	assert(h > 0);
	assert(w > 0);
	x_axis = w;
	y_axis = h;
	turn = 0;
	for(int i = 0; i < w*h; i++) {
		Creature c;
		grid.push_back(c);
	}
}
void Darwin::addCreature(const Creature& c, int y, int x) {
	assert(y > -1);
	assert(y < y_axis);
	assert(x > -1);
	assert(x < x_axis);
	int position = (x_axis * y) + x; 
	grid[position] = c;
}
Creature& Darwin::spaceAhead(Creature& c, int i) {
	assert(i > -1);
	assert(i < (int) grid.size());
	int d = c.direction;
	if(d == 0 && i - 1 >= 0 && (i % x_axis) != 0) // west
		return grid[i - 1];
	else if(d == 1 && i - x_axis >= 0) // north
		return grid[i - x_axis];
	else if(d == 2 && i + 1 < x_axis*y_axis && ((i + 1) % x_axis) != 0) // east
		return grid[i + 1];
	else if(d == 3 && i + x_axis < x_axis*y_axis) // south
		return grid[i + x_axis]; 
	else
		return c; // wall
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
	b = (*this).begin();
	while(b != e) {
		grid[*b].reset();
		++b;
	}
}
Creature Darwin::at(int i) {
	assert(i > -1);
	assert(i < (int) grid.size());
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
