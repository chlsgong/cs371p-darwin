// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    Species s1('f');
    Species s2('h');
    Creature c1(s1, 2);
    Creature c2(s2, 1);
    Creature c3(s2, 2);
    Creature c4(s2, 3);
    Creature c5(s2, 0);
    Creature c6(s1, 1);
    Darwin d1(8, 8);
    d1.addCreature(c1, 0, 0);
    d1.addCreature(c2, 3, 3);
    d1.addCreature(c3, 3, 4);
    d1.addCreature(c4, 4, 4);
    d1.addCreature(c5, 4, 3);
    d1.addCreature(c6, 7, 7);
    d1.createGrid();
    for(int i = 0; i < 5; i++) {
        d1.executeTurn();
        d1.createGrid();
    }
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    Species s3('t');
    Species s4('h');
    Species s5('r');
    Creature c7(s3, 3);
    Creature c8(s4, 2);
    Creature c9(s5, 1);
    Creature c10(s3, 0);
    Darwin d2(7, 9);
    d2.addCreature(c7, 0, 0);
    d2.addCreature(c8, 3, 2);
    d2.addCreature(c9, 5, 4);
    d2.addCreature(c10, 6, 8);
    d2.createGrid();
    for(int i = 0; i < 5; i++) {
        d2.executeTurn();
        d2.createGrid();
    }
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    Darwin d3(72, 72);
    Species food('f');
    Species hopper('h');
    Species rover('r');
    Species trap('t');
    for(int i = 0; i < 10; i++) {
        int p = rand() % 5184;
        int x = p % 72;
        int y = p / 72;
        int dir = rand() % 4;
        Creature c(food, dir);
        d3.addCreature(c, y, x);
    }
    for(int i = 0; i < 10; i++) {
        int p = rand() % 5184;
        int x = p % 72;
        int y = p / 72;
        int dir = rand() % 4;
        Creature c(hopper, dir);
        d3.addCreature(c, y, x);
    }
    for(int i = 0; i < 10; i++) {
        int p = rand() % 5184;
        int x = p % 72;
        int y = p / 72;
        int dir = rand() % 4;
        Creature c(rover, dir);
        d3.addCreature(c, y, x);
    }
    for(int i = 0; i < 10; i++) {
        int p = rand() % 5184;
        int x = p % 72;
        int y = p / 72;
        int dir = rand() % 4;
        Creature c(trap, dir);
        d3.addCreature(c, y, x);
    }
    for(int i = 0; i < 1001; i++) {
        if(i < 10)
            d3.createGrid();
        else if(i > 99 && i % 100 == 0)
            d3.createGrid();
        d3.executeTurn();
    }
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}

//  g++ -pedantic -std=c++11 -Wall Voting.c++ RunVoting.c++ -o RunVoting
