#ifndef DARWIN_H
#define DARWIN_H

#include <vector> 	 // vector
#include <iterator>  // iterator
#include <utility>   // pair

class Darwin;

enum Instruction {
	HOP,
	LEFT,
	RIGHT,
	INFECT,
	IF_EMPTY,
	IF_WALL,
	IF_RANDOM,
	IF_ENEMY,
	GO
};

class Species {
	public:
	 	std::vector<std::pair<Instruction, int>> instructions;
	 	char name;

		Species();
		Species(char);
		void addInstruction(Instruction);
		void addInstruction(Instruction, int);
		std::pair<Instruction, int> nextInstruction(int);
};

class Creature {
	private:
	 	int pc;
	 	bool didMove;
	  	bool isNull;

	public:
		Species _s;
		int direction;

		Creature();
	 	Creature(const Species&, int);
	 	void makeMove(Darwin&, int);
	 	void reset();
};

template<typename T>
class D_Iterator {
	private:
		T _v;

	public:
		D_Iterator(const T& v) {
			_v = v;
		}
		bool operator == (const D_Iterator<T>& rhs) const {
			return (_v == rhs._v);
		}
		bool operator != (const D_Iterator<T>& rhs) const {
			return !(*this == rhs);
		}
		const T& operator * () const {
			return _v;
		}
		D_Iterator<T> operator ++ () { // pre increment
			++_v;
			return *this;
		}
		D_Iterator<T> operator ++ (int) { // post increment
			D_Iterator<T> d = *this;
			++*this;
			return d;
		}
};

class Darwin { 
	private:
		int y_axis;
		int turn;

	public:
		std::vector<Creature> grid;
		int x_axis;

		Darwin();
		Darwin(int, int);
		void addCreature(const Creature&, int, int);
		Creature& spaceAhead(Creature&, int);
		// void move(const Creature&, int);
		void createGrid();
		void executeTurn();
		D_Iterator<int> begin();
		D_Iterator<int> end();
		Creature at(int);
};

#endif // DARWIN_H
