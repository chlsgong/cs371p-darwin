#include <vector> 	 // vector
#include <iterator>  // iterator
#include <utility>   // pair
#include <algorithm> // equal
#include <cstdlib>   // rand

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
	ASSERT_EQ(direction1, 0);
	ASSERT_EQ(direction2, 3);
}

// makeMove

TEST(CreatureFixture, makeMove_hop_1) {
	Species s('h');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[17];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_2) {
	Species s('h');
	Creature c(s, 1);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[13];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_3) {
	Species s('h');
	Creature c(s, 2);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[19];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_4) {
	Species s('h');
	Creature c(s, 3);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[23];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_5) {
	Species s('h');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	int position = 0;
	c.makeMove(d, position);
	Creature t = d.grid[0];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_6) {
	Species s('h');
	Creature c(s, 1);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	int position = 0;
	c.makeMove(d, position);
	Creature t = d.grid[0];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_7) {
	Species s('h');
	Creature c(s, 2);
	Darwin d(5, 5);
	d.addCreature(c, 4, 4);
	int position = 24;
	c.makeMove(d, position);
	Creature t = d.grid[24];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_hop_8) {
	Species s('h');
	Creature c(s, 3);
	Darwin d(5, 5);
	d.addCreature(c, 4, 4);
	int position = 24;
	c.makeMove(d, position);
	Creature t = d.grid[24];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(CreatureFixture, makeMove_left_1) {
	Species s('f');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	ASSERT_EQ(c.direction, 3);
}
TEST(CreatureFixture, makeMove_right_2) {
	Species s('m');
	s.addInstruction(RIGHT);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	ASSERT_EQ(c.direction, 1);
}
TEST(CreatureFixture, makeMove_infect_1) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 2);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	c1.makeMove(d, 0);
	Creature t = d.grid[1];
	int direction = c1.direction;
	ASSERT_EQ(t._s.name, 't');
	ASSERT_EQ(direction, 2);
}
TEST(CreatureFixture, makeMove_infect_2) {
	Species s1('t');
	Species s2('t');
	Creature c1(s1, 2);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	int position = 0;
	c1.makeMove(d, position);
	Creature t = d.grid[1];
	int direction = c1.direction;
	ASSERT_EQ(t._s.name, 't');
	ASSERT_EQ(direction, 1);
}
TEST(CreatureFixture, makeMove_if_empty_1) {
	Species s('m');
	s.addInstruction(IF_EMPTY, 3);
	s.addInstruction(RIGHT);
	s.addInstruction(GO, 0);
	s.addInstruction(HOP);
	s.addInstruction(GO, 0);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[17];
	int direction = t.direction;
	ASSERT_EQ(t._s.name, c._s.name);
	ASSERT_EQ(direction, 0);
}
TEST(CreatureFixture, makeMove_if_empty_2) {
	Species s1('m');
	Species s2('f');
	s1.addInstruction(IF_EMPTY, 3);
	s1.addInstruction(RIGHT);
	s1.addInstruction(GO, 0);
	s1.addInstruction(HOP);
	s1.addInstruction(GO, 0);
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 3, 3);
	d.addCreature(c2, 3, 2);
	int position = 18;
	c1.makeMove(d, position);
	Creature t = d.grid[17];
	int direction = c1.direction;
	ASSERT_NE(t._s.name, c1._s.name);
	ASSERT_EQ(direction, 1);
}
TEST(CreatureFixture, makeMove_if_wall_1) {
	Species s('m');
	s.addInstruction(IF_WALL, 3);
	s.addInstruction(HOP);
	s.addInstruction(GO, 0);
	s.addInstruction(RIGHT);
	s.addInstruction(GO, 0);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	int position = 0;
	c.makeMove(d, position);
	int direction = c.direction;
	ASSERT_EQ(direction, 1);
}
TEST(CreatureFixture, makeMove_if_wall_2) {
	Species s('m');
	s.addInstruction(IF_WALL, 3);
	s.addInstruction(HOP);
	s.addInstruction(GO, 0);
	s.addInstruction(RIGHT);
	s.addInstruction(GO, 0);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[17];
	int direction = c.direction;
	ASSERT_EQ(t._s.name, c._s.name);
	ASSERT_EQ(direction, 0);
}
TEST(CreatureFixture, makeMove_if_enemy_1) {
	Species s('t');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	Creature t = d.grid[17];
	int direction = c.direction;
	ASSERT_NE(t._s.name, c._s.name);
	ASSERT_EQ(direction, 3);
}
TEST(CreatureFixture, makeMove_if_enemy_2) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 2);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	c1.makeMove(d, 0);
	Creature t = d.grid[1];
	int direction = c1.direction;
	ASSERT_EQ(t._s.name, 't');
	ASSERT_EQ(direction, 2);
}
TEST(CreatureFixture, makeMove_go_1) {
	Species s('m');
	s.addInstruction(GO, 1);
	s.addInstruction(LEFT);
	s.addInstruction(RIGHT);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	int direction = c.direction;
	ASSERT_EQ(direction, 3);
}
TEST(CreatureFixture, makeMove_go_2) {
	Species s('m');
	s.addInstruction(GO, 2);
	s.addInstruction(LEFT);
	s.addInstruction(RIGHT);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	int position = 18;
	c.makeMove(d, position);
	int direction = c.direction;
	ASSERT_EQ(direction, 1);
}

// reset

TEST(CreatureFixture, reset_1) {
	Species s('r');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	c.makeMove(d, 18);
	c.reset();
	int pc = c.makeMove(d, 17);
	ASSERT_EQ(pc, 8);
}
TEST(CreatureFixture, reset_2) {
	Species s('h');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	c.makeMove(d, 0);
	c.reset();
	int pc = c.makeMove(d, 0);
	ASSERT_EQ(pc, 0);
}

// D_Iterator constructor

TEST(D_IteratorFixture, constructor_1) {
	D_Iterator<int> x(0);
	ASSERT_EQ(*x, 0);
}
TEST(D_IteratorFixture, constructor_2) {
	D_Iterator<int> x(999999);
	ASSERT_EQ(*x, 999999);
}
TEST(D_IteratorFixture, constructor_3) {
	D_Iterator<double> x(0.5);
	ASSERT_EQ(*x, 0.5);
}

// == operator

TEST(D_IteratorFixture, equal_operator_1) {
	D_Iterator<int> x(0);
	D_Iterator<int> y(0);
	ASSERT_TRUE(x == y); 
}
TEST(D_IteratorFixture, equal_operator_2) {
	D_Iterator<int> x(0);
	D_Iterator<int> y(1);
	ASSERT_FALSE(x == y); 
}
TEST(D_IteratorFixture, equal_operator_3) {
	D_Iterator<double> x(0.5);
	D_Iterator<double> y(0.5);
	ASSERT_TRUE(x == y); 
}
TEST(D_IteratorFixture, equal_operator_4) {
	D_Iterator<double> x(0.5);
	D_Iterator<double> y(1.5);
	ASSERT_FALSE(x == y); 
}

// != operator

TEST(D_IteratorFixture, not_equal_operator_1) {
	D_Iterator<int> x(0);
	D_Iterator<int> y(1);
	ASSERT_TRUE(x != y); 
}
TEST(D_IteratorFixture, not_equal_operator_2) {
	D_Iterator<int> x(0);
	D_Iterator<int> y(0);
	ASSERT_FALSE(x != y); 
}
TEST(D_IteratorFixture, not_equal_operator_3) {
	D_Iterator<double> x(0.5);
	D_Iterator<double> y(1.5);
	ASSERT_TRUE(x != y);
}
TEST(D_IteratorFixture, not_equal_operator_4) {
	D_Iterator<double> x(0.5);
	D_Iterator<double> y(0.5);
	ASSERT_FALSE(x != y);
}

// * operator

TEST(D_IteratorFixture, dereference_operator_1) {
	D_Iterator<int> x(0);
	int i = *x + 1;
	ASSERT_EQ(i, 1);
}
TEST(D_IteratorFixture, dereference_operator_2) {
	D_Iterator<int> x(436375);
	ASSERT_EQ(x, 436375);
}

// pre-increment operator

TEST(D_IteratorFixture, pre_increment) {
	D_Iterator<int> x(0);
	++x;
	ASSERT_EQ(x, 1);
}

// post increment operator

TEST(D_IteratorFixture, post_increment) {
	D_Iterator<int> x(3);
	x++;
	ASSERT_EQ(x, 4);
}

// Darwin constructors

TEST(DarwinFixture, constructor_1) {
	Darwin d;
	int size = (d.grid).size();
	ASSERT_EQ(size, 100);
}
TEST(DarwinFixture, constructor_2) {
	Darwin d(1, 1);
	int size = (d.grid).size();
	ASSERT_EQ(size, 1);
}
TEST(DarwinFixture, constructor_3) {
	Darwin d(100, 100);
	int size = (d.grid).size();
	ASSERT_EQ(size, 10000);
}

// addCreature

TEST(DarwinFixture, addCreature_1) {
	Species s('t');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	Creature t = d.grid[18];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(DarwinFixture, addCreature_2) {
	Species s('t');
	Creature c1(s, 0);
	Creature c2(s, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 4, 4);
	Creature t1 = d.grid[0];
	Creature t2 = d.grid[24];
	ASSERT_EQ(t1._s.name, c1._s.name);
	ASSERT_EQ(t2._s.name, c2._s.name);
}
TEST(DarwinFixture, addCreature_3) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 0);
	Creature t = d.grid[0];
	ASSERT_EQ(t._s.name, c2._s.name);
}

// spaceAhead

TEST(DarwinFixture, spaceAhead_1) {
	Species s('t');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	d.spaceAhead(c, 18);
	Creature t1 = d.spaceAhead(c, 18);
	Creature t2 = d.grid[17];
	ASSERT_EQ(t1._s.name, t2._s.name);
}
TEST(DarwinFixture, spaceAhead_2) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 1);
	d.addCreature(c2, 0, 0);
	Creature t1 = d.spaceAhead(c1, 1);
	Creature t2 = d.grid[0];
	ASSERT_EQ(t1._s.name, t2._s.name);
}
TEST(DarwinFixture, spaceAhead_3) {
	Species s('h');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	Creature t = d.spaceAhead(c, 0);
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(DarwinFixture, spaceAhead_4) {
	Species s('r');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	Creature t = d.spaceAhead(c, 0);
	ASSERT_EQ(t._s.name, c._s.name);
}

// executeTurn

TEST(DarwinFixture, executeTurn_1) {
	Species s('h');
	Creature c(s, 2);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	d.executeTurn();
	Creature t = d.grid[1];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(DarwinFixture, executeTurn_2) {
	Species s1('h');
	Species s2('f');
	Creature c1(s1, 2);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 3, 3);
	d.executeTurn();
	Creature t1 = d.grid[1];
	Creature t2 = d.grid[18];
	ASSERT_EQ(t1._s.name, c1._s.name);
	ASSERT_EQ(t2.direction, 0);
}
TEST(DarwinFixture, executeTurn_3) {
	Species s('m');
	s.addInstruction(RIGHT);
	s.addInstruction(GO, 0);
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	d.executeTurn();
	d.executeTurn();
	Creature t = d.grid[0];
	ASSERT_EQ(t.direction, 2);
}
TEST(DarwinFixture, executeTurn_4) {
	Species s('t');
	Creature c(s, 2);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	d.executeTurn();
	Creature t = d.grid[0];
	ASSERT_EQ(t.direction, 1);
}
TEST(DarwinFixture, executeTurn_5) {
	Species s('r');
	Creature c(s, 2);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	d.executeTurn();
	Creature t = d.grid[1];
	ASSERT_EQ(t._s.name, c._s.name);
}
TEST(DarwinFixture, executeTurn_6) {
	Species s('f');
	Creature c(s, 2);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	d.executeTurn();
	Creature t = d.grid[0];
	ASSERT_EQ(t.direction, 1);
}

// begin

TEST(DarwinFixture, begin_1) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	D_Iterator<int> b = d.begin();
	ASSERT_EQ((d.grid[*b])._s.name, 't');
}
TEST(DarwinFixture, begin_2) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 0, 0);
	d.addCreature(c2, 0, 1);
	D_Iterator<int> b = d.begin();
	++b;
	ASSERT_EQ((d.grid[*b])._s.name, 'f');
}
TEST(DarwinFixture, begin_3) {
	Darwin d;
	D_Iterator<int> b = d.begin();
	D_Iterator<int> e = d.end();
	while(b != e) {
		++b;
	}
	ASSERT_EQ(*b, 100);
}

// end

TEST(DarwinFixture, end) {
	Species s1('t');
	Species s2('f');
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(5, 5);
	d.addCreature(c1, 4, 3);
	d.addCreature(c2, 4, 4);
	D_Iterator<int> e = d.end();
	ASSERT_EQ((d.grid[*e-1])._s.name, 'f');
}

// at

TEST(DarwinFixture, at_1) {
	Species s('f');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 3, 3);
	Creature t = d.at(18);
	ASSERT_EQ(t._s.name, 'f');
}
TEST(DarwinFixture, at_2) {
	Species s('h');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 4, 4);
	Creature t = d.at(24);
	ASSERT_EQ(t._s.name, 'h');
}
TEST(DarwinFixture, at_3) {
	Species s('t');
	Creature c(s, 0);
	Darwin d(5, 5);
	d.addCreature(c, 0, 0);
	Creature t = d.at(0);
	ASSERT_EQ(t._s.name, 't');
}

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread
