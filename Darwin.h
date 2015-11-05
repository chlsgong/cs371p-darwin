#ifndef DARWIN_H
#define DARWIN_H

#include <vector> 	 // vector
#include <iterator>  // iterator
#include <utility>   // pair

class Darwin;

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
	 	std::vector<std::pair<Instruction, int>> instructions;
	 	char name;

	public:
		Species();
		Species(char);
		void addInstruction(Instruction);
		void addInstruction(Instruction, int);
		std::pair<Instruction, int> nextInstruction(int);
};

class Creature {
	public:
		Species _s;
		int direction;
	 	int pc;
	 	bool didMove;
	  	bool isNull;

	public:
		Creature();
	 	Creature(const Species&, int);
	 	void makeMove(Darwin&, int);
};

class Darwin { 
	public:
		std::vector<Creature> grid;
		int x_axis;
		int y_axis;
		int turn;

	public:
		Darwin();
		Darwin(int, int);
		void addCreature(const Creature&, int, int);
		Creature& spaceAhead(Creature&, int);
		// void createGrid(int);
		// void executeTurn();
		// D_Iterator begin();
		// D_Iterator end();
		// Creature at(int i) {
		// 	return grid[i];
		// }
};

#endif // DARWIN_H
