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
	Species s;
	Creature c(s);
	cout << (c._s).name << endl;
	Darwin d(10, 10);
	cout << ((d.grid)[0, 0]).name << endl;
	d.addCreature(c, 3, 4);
}

// g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread