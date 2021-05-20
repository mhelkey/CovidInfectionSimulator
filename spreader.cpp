#include <iostream>  // for debugging
#include <cstring>
#include "spreader.h"

using namespace std;

Spreader::Spreader(const Person *people, int population)
{
  popul = population;
  
  table = new PersonV2[population];
  for(int i = 0; i < population; i++)//moderately inefficient since we have to copy all of the pople in O(n) time
  {
   table[i] = PersonV2(people[i].ID, people[i].peopleMet, people[i].visitors); //faster initilization using lists
  }
  
} // Spreader()


int Spreader::simulate(int starterIDs[], int starterCount, int commandLineOption)
{
  PersonLimited temp(-1,-1);
  int mod, potentialDV, period, visitorID;
  BinaryHeap<PersonLimited> heap(popul/20);//should be adjusted based on density of edges of graph. with these files, size/20 is sufficient
  for(int i = 0; i < starterCount; i++) //inserts all initial infected people (maximum of 10 runs, no not gonna bother with it)
  {
    heap.insert(PersonLimited(starterIDs[i], 0)); //inserts the personlimited initial infected into the heap
  }

  while(!heap.isEmpty())// && numInfected45 <= popul + 3)
  {
    if(table[heap.findMin().ID].infected) { heap.deleteMin(); continue; } //person is already infected. can skip process
    heap.deleteMin(temp); 

    table[temp.ID].infected = true;//marks the original in the array as infected

    for(int i =0 ; i < table[temp.ID].peopleMet; i++) //inserts all of the people this person will meet, 
    //with DV equal to how frequently they visit
    {
      visitorID = table[temp.ID].visitors[i].ID; //visitor being visited. set as int to reduce lookups
      if(table[visitorID].infected) { continue; }// if the visited person is already infected, just skips this process
      /*
          let A be the parent infected person, B be the person to be infected
          for most cases
          B.dv = A.dv + 3+  B.period - (A.dv+3)%B.period 
          however in edge cases of (A.dv+3)%b.period ==0
          the calculated B.dv is one full period longer than it should be
          thus in these edge cases, the correct B.dv is just equal to A.dv + 3
      */
      period = table[temp.ID].visitors[i].period;
      mod = (temp.dv + 3)%period; //the mod value. calculated only once to save time
      if(mod != 0)
      	potentialDV = period - mod + temp.dv + 3; //the dv value assuming the edge case is not occuring
      if(mod == 0)
        potentialDV = temp.dv + 3;
      // cout << table[visitorID].dv << endl;
      
      if(potentialDV < table[visitorID].dv) 
      { 
        table[visitorID].dv = potentialDV; heap.insert(PersonLimited(visitorID, potentialDV));
      } //makes sure that we are making the dv smaller. reduces unnecessary heap insertions
    }
  }
  return table[temp.ID].dv; // returns the last DV
}//simulate()
