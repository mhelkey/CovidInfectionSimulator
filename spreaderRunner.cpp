// Author Sean Davis

#include <iostream>
#include <fstream>
#include "CPUTimer.h"
#include "spreaderRunner.h"
#include "spreader.h"
//#include <type_traits>

using namespace std;

Person* readFile(const char *filename, int *population, int **starterIDs,
   int *starterCount)
{
  
  char comma;
  ifstream inf(filename);
  inf >> *population >> comma >> *starterCount ;
  *starterIDs = new int[*starterCount];
  
  for(int i = 0; i < *starterCount; i++)
    inf >> comma >> (*starterIDs)[i];
  
  Person *people = new Person[*population];
  
  for(int i = 0; i < *population; i++)
  {
    inf >> people[i].ID >> comma >> people[i].peopleMet;
    people[i].visitors = new Visitor[people[i].peopleMet];
    
    for(int j = 0; j < people[i].peopleMet; j++)
      inf >> comma >>  people[i].visitors[j].ID >> comma 
        >> people[i].visitors[j].period;
  }  // for each person
  
  return people;
}  // readFile()

int main(int argc, char** argv)
{
  Person *people;
  int population, *starterIDs, starterCount;
  people = readFile(argv[1], &population, &starterIDs, &starterCount);
  CPUTimer ct;
  Spreader *spreader = new Spreader(people, population);
  for(int i = 0; i < population; i++)
   delete[] people[i].visitors;
    
  delete[] people;
  // /int days = 0;
  // cout << spreader->popul << endl;
  int days = spreader->simulate(starterIDs, starterCount, argc);
  // cout << "check me:" << std::is_trivially_copyable<Person>::value << endl;
  cout << "CPU Time: " << ct.cur_CPUTime() << ' ' << "Days for complete infection: " << days << endl;
  return 0;
} // main()

