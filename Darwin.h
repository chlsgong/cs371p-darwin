#include <vector> 	 // vector
#include <iterator>  // iterator

using namespace std;

class Darwin { 
	private:
		vector<Creature> grid;
		int x_axis;
		int y_axis;
		int turn;

	public:
		void Darwin(void);
		void Darwin(int, int);
		void addCreature(Creature, int, int);
		void createGrid(int);
		Creature at(int);
		Iterator begin(void);
		Iterator end(void);	
};

class Creature {
	private:
		int direction;
	 	int pc;
	 	bool didMove;

	public:
		void Creature(void);
	 	void Creature(Species);
	 	void makeMove(void);
};

class Species {
	private:
	 	vector<int> instructions;
		string name;

	public:
		void Species(void);
		void addInstruction(int);
};

void executeTurn(void);

void hop(void);
void left(void);
void right(void);
void infect(void);
void if_empty(int);
void if_wall(int);
void if_random(int);
void if_enemy(int);
void go(int);
