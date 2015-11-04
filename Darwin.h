#ifndef DARWIN_H
#define DARWIN_H

#include <vector> 	 // vector
#include <iterator>  // iterator
#include <utility>   // pair

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
		Species();
		Species(char);
		void addInstruction(Instruction);
		void addInstruction(Instruction, int);
		// void doNext(Instruction, int);
};

class Creature {
	public:
		Species _s;
		int direction;
	 	int pc;
	 	bool didMove;

	public:
		Creature();
	 	Creature(Species, int);
	 	// void makeMove(void);
};

class Darwin { 
	public:
		vector<Creature> grid;
		int x_axis;
		int y_axis;
		int turn;

	public:
		Darwin();
		Darwin(int, int);
		void addCreature(Creature, int, int);
		// void createGrid(int);
		// void executeTurn(void);
		// Creature at(int);
		// Iterator begin(void);
		// Iterator end(void);	
};

#endif // DARWIN_H
