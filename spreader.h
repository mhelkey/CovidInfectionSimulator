#ifndef SPREADER_H
#define SPREADER_H

#include "spreaderRunner.h"
#include "Person.h"
#include "BinaryHeap.h"

class Spreader
{
  PersonV2 * table; 
public:
  int popul;
  Spreader(const Person *people, int population);
  int simulate(int starterIDs[], int starterCount, int commandLineOption);
};

#endif /* SPREADER_H */
