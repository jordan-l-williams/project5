// expmain.cpp
//
// ICS 46 Spring 2020
// Project #5: Rock and Roll Stops the Traffic
//
// Do whatever you'd like here.  This is intended to allow you to experiment
// with your code, outside of the context of the broader program or Google
// Test.

#include "Digraph.hpp"

int main()
{

    Digraph<int, int> d1;

    d1.addVertex(43 ,67);
    d1.addVertex(3,23);

    d1.addEdge(43, 2, 90);
    d1.edgeInfo(43, 2);
    d1.addEdge(3, 3, 91);


    return 0;
}

