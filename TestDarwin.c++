#include <vector> 	 // vector
#include <iterator>  // iterator
#include <utility>   // pair

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// TEST(DarwinFixture, addInstruction_1) {
// 	Species s;
// 	s.addInstruction(rght);
// 	s.addInstruction(go, 0);
// 	int size = (s.instructions).size();
// 	cout << size << endl;
// 	ASSERT_EQ(size, 2);
// }

// TEST(DarwinFixture, addInstruction_2) {
// 	Species s('r');
// 	int size = (s.instructions).size();
// 	cout << size << endl;
// 	ASSERT_EQ(size, 11);
// }

TEST(DarwinFixture, addCreature_1) {
	Species s('f');
	Creature c(s, 0);
	cout << (c._s).name << endl;
	Darwin d(10, 10);
	d.addCreature(c, 3, 4);
	Creature c1 = (d.grid)[10*3 + 4];
	cout << (c1._s).name << endl;
	c1 = (d.grid)[18];
	cout << (c1._s).name << endl;
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

TEST(DarwinFixture, createGrid_1) {
	Species s1('f');
	Species s2('h');
	Creature c1(s1, 0);
	Creature c2(s2, 1);
	Darwin d(10, 10);
	d.addCreature(c1, 1, 2);
	d.addCreature(c2, 7, 7);
	d.createGrid();
	for(int i = 0; i < 10; i++) {
		//cout << (d.grid[10*1 + 2]).direction << endl;
		d.executeTurn();
		d.createGrid();
	}
}

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread