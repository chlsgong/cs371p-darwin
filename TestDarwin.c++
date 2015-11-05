#include <vector> 	 // vector
#include <iterator>  // iterator
#include <utility>   // pair
#include <algorithm> // equal

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// species constructor

TEST(SpeciesFixture, species_1) {
	Species s;
	ASSERT_EQ(s.instructions.size(), 0);
}
TEST(SpeciesFixture, species_2) {
	Species s('f');
	ASSERT_EQ(s.instructions.size(), 2);
}
TEST(SpeciesFixture, species_3) {
	Species s('r');
	ASSERT_EQ(s.instructions.size(), 11);
}

// addInstruction

TEST(SpeciesFixture, addInstruction_1) {
	Species s;
	s.addInstruction(HOP);
	s.addInstruction(GO, 0);
	ASSERT_EQ(s.instructions.size(), 2);
}
TEST(SpeciesFixture, addInstruction_2) {
	Species s;
	for(int i = 0; i < 999999; i++)
		s.addInstruction(HOP);
	ASSERT_EQ(s.instructions.size(), 999999);
}
TEST(SpeciesFixture, addInstruction_3) {
	Species s;
	s.addInstruction(HOP);
	s.addInstruction(LEFT);
	s.addInstruction(RIGHT);
	s.addInstruction(IF_ENEMY, 5);
	s.addInstruction(GO, 0);
	s.addInstruction(INFECT);
	s.addInstruction(GO, 0);
	ASSERT_EQ(s.instructions.size(), 7);
}
TEST(SpeciesFixture, addInstruction_4) {
	Species s;
	s.addInstruction(IF_EMPTY, 0);
	s.addInstruction(IF_RANDOM, 1);
	s.addInstruction(IF_WALL, 2);
	s.addInstruction(IF_ENEMY, 3);
	s.addInstruction(GO, 4);
	ASSERT_EQ(s.instructions.size(), 5);
}
TEST(SpeciesFixture, addInstruction_5) {
	Species s;
	for(int i = 0; i < 100; i++) {
		s.addInstruction(HOP);
		s.addInstruction(LEFT);
		s.addInstruction(RIGHT);
	}
	ASSERT_EQ(s.instructions.size(), 300);
}
TEST(SpeciesFixture, addInstruction_6) {
	Species s;
	vector<pair<Instruction, int>> v;
	s.addInstruction(HOP);
	v.push_back(make_pair(HOP, -1));
	s.addInstruction(GO, 0);
	v.push_back(make_pair(GO, 0));
	ASSERT_TRUE(equal(s.instructions.begin(), s.instructions.end(), v.begin()));
}

// nextInstruction

TEST(SpeciesFixture, nextInstruction_1) {
	Species s('t');
	Instruction in = IF_ENEMY;
	Instruction ins_1 = s.nextInstruction(0).first;
	ASSERT_EQ(ins_1, in);
	in = LEFT;
	Instruction ins_2 = s.nextInstruction(1).first;
	ASSERT_EQ(ins_2, in);
}
TEST(SpeciesFixture, nextInstruction_2) {
	Species s1('r');
	Species s2;
	s2.addInstruction(IF_ENEMY, 9);
	s2.addInstruction(IF_EMPTY, 7);
	s2.addInstruction(IF_RANDOM, 5);
	s2.addInstruction(LEFT);
	s2.addInstruction(GO, 0);
	s2.addInstruction(RIGHT);
	s2.addInstruction(GO, 0);
	s2.addInstruction(HOP);
	s2.addInstruction(GO, 0);
	s2.addInstruction(INFECT);
	s2.addInstruction(GO, 0);
	Instruction ins_1;
	Instruction ins_2;
	for(int i = 0; i < 11; i++) {
		ins_1 = s1.nextInstruction(i).first;
		ins_2 = s2.nextInstruction(i).first;
		ASSERT_EQ(ins_1, ins_2);
	}
}
TEST(SpeciesFixture, nextInstruction_3) {
	Species s('f');
	int n = 0;
	int line = s.nextInstruction(1).second;
	ASSERT_EQ(line, n);
}

// creature constructors

TEST(CreatureFixture, creature_1) {
	Creature c;
	char species = c._s.name;
	ASSERT_EQ(species, '.');
}
TEST(CreatureFixture, creature_2) {
	Species s('f');
	Creature c(s, 0);
	char species = c._s.name;
	ASSERT_EQ(species, 'f');
}
TEST(CreatureFixture, creature_3) {
	Species s1('r');
	Species s2('r');
	Creature c1(s1, 0);
	Creature c2(s2, 3);
	int direction1 = c1.direction;
	int direction2 = c2.direction;
	ASSERT_NE(direction1, direction2);
}

TEST(DarwinFixture, addCreature_1) {
	Species s('f');
	Creature c(s, 0);
	Darwin d(10, 10);
	d.addCreature(c, 3, 4);
}

// TEST(DarwinFixture, begin_1) {
// 	Darwin d;
// 	D_Iterator<int> b = d.begin();
// 	D_Iterator<int> e = d.end();
// 	while(b != e) {
// 		cout << *b << endl;
// 		++b;
// 	}
// 	ASSERT_EQ(*b, 100);
// }

// TEST(DarwinFixture, createGrid_1) {
// 	Species s1('f');
// 	Species s2('h');
// 	Creature c1(s1, 0);
// 	Creature c2(s2, 1);
// 	Darwin d(10, 10);
// 	d.addCreature(c1, 1, 2);
// 	d.addCreature(c2, 7, 7);
// 	d.createGrid();
// 	for(int i = 0; i < 10; i++) {
// 		d.executeTurn();
// 		d.createGrid();
// 	}
// }

// TEST(DarwinFixture, createGrid_2) {
// 	Species s1('f');
// 	Species s2('h');
// 	Species s3('r');
// 	Species s4('t');
// 	Creature c1(s1, 3); // south
// 	Creature c2(s2, 1); // north
// 	Creature c3(s2, 2); // east
// 	Creature c4(s3, 1); // north
// 	Creature c5(s4, 2); // east
// 	Darwin d(20, 15);
// 	d.addCreature(c1, 17, 3);
// 	d.addCreature(c2, 8, 2);
// 	d.addCreature(c3, 10, 10);
// 	d.addCreature(c4, 19, 14);
// 	d.addCreature(c5, 0, 1);
// 	d.createGrid();
// 	for(int i = 0; i < 20; i++) {
// 		d.executeTurn();
// 		d.createGrid();
// 	}
// }

// TEST(DarwinFixture, createGrid_3) {
// 	Species s1('f');
// 	Species s2('h');
// 	Creature c1(s1, 2);
// 	Creature c2(s2, 1);
// 	Creature c3(s2, 2);
// 	Creature c4(s2, 3);
// 	Creature c5(s2, 0);
// 	Creature c6(s1, 1);
// 	Darwin d(8, 8);
// 	d.addCreature(c1, 0, 0);
// 	d.addCreature(c2, 3, 3);
// 	d.addCreature(c3, 3, 4);
// 	d.addCreature(c4, 4, 4);
// 	d.addCreature(c5, 4, 3);
// 	d.addCreature(c6, 7, 7);
// 	d.createGrid();
// 	for(int i = 0; i < 5; i++) {
// 		d.executeTurn();
// 		d.createGrid();
// 	}
// }

// TEST(DarwinFixture, createGrid_4) {
// 	srand(0);
// 	Species s1('t');
// 	Species s2('h');
// 	Species s3('r');
// 	Creature c1(s1, 3);
// 	Creature c2(s2, 2);
// 	Creature c3(s3, 1);
// 	Creature c4(s1, 0);
// 	Darwin d(7, 9);
// 	d.addCreature(c1, 0, 0);
// 	d.addCreature(c2, 3, 2);
// 	d.addCreature(c3, 5, 4);
// 	d.addCreature(c4, 6, 8);
// 	d.createGrid();
// 	for(int i = 0; i < 5; i++) {
// 		d.executeTurn();
// 		d.createGrid();
// 	}
// }

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread
