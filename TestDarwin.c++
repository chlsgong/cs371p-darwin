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
	Creature c1 = (d.grid)[19];
	cout << (c1._s).name << endl;
	c1 = (d.grid)[18];
	cout << (c1._s).name << endl;
}

// TEST(DarwinFixture, begin_1) {
// 	Darwin d;
// 	D_Iterator b = d.begin();
// 	D_Iterator e = d.end();
// 	int i = 0;
// 	while(b != e) {
// 		++i;
// 	}
// 	ASSERT_EQ(i, 100);
// }

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread