#ifndef PERSON_H
#define PERSON_H

#include "spreaderRunner.h"
#include <iostream>
#include <iomanip>
#include "limits.h"

/*
    personv2 will be used to copy the basic person class over, since the person array will be deleted before simulate.
    personv2 will have additional useful information in addition to the critical info of person, such as dv and infection status
    personlimited will be a small struct to save space and time in the binary heap
*/
struct PersonLimited
{
  int ID, dv;
  PersonLimited(int id, int cost): ID(id), dv(cost) {}
  PersonLimited(): ID(-1), dv(INT_MAX) {}
  friend bool operator!=(const PersonLimited & rhs, const PersonLimited & lhs){ return rhs.ID != lhs.ID;}
  friend bool operator==(const PersonLimited & rhs, const PersonLimited & lhs){ return rhs.ID == lhs.ID;}
  friend bool operator<(const PersonLimited & lhs,const PersonLimited & rhs) { return lhs.dv < rhs.dv; }
  friend std::ostream& operator<<(std::ostream& os, const PersonLimited & dt)
  {
    os << "ID: " << std::setw(7) << dt.ID << " DV: " << dt.dv;
    return os;
  }
};


struct PersonV2
{
  PersonV2() {} //empty constructor to stop errors in binary heap
  PersonV2(int d, int ppl, Visitor * v): ID(d), peopleMet(ppl), infected(false), dv(INT_MAX) //faster initialization
  {
    visitors = new Visitor[peopleMet];
    for(int i = 0; i < peopleMet; i++) //deep copy of the visitor pointer array
    {
      visitors[i] = v[i];//since each visitor object has only 2 ints, with no points, a shallow copy is sufficient
    }
  }

  int ID;
  int peopleMet;
  bool infected;
  int dv;
  Visitor *visitors;


  friend bool operator!=(const PersonV2 & rhs, const PersonV2 & lhs){ return rhs.ID != lhs.ID;}
  friend bool operator==(const PersonV2 & rhs, const PersonV2 & lhs){ return rhs.ID == lhs.ID;}
  friend bool operator<(const PersonV2 & rhs, const PersonV2 & lhs){ return rhs.dv < lhs.dv;}

  friend std::ostream& operator<<(std::ostream& os, const PersonV2 & dt)
  {
    os << "ID: " << std::setw(7) << dt.ID << " Infected = " << dt.infected << " DV: " << dt.dv;
    return os;
  }
};

#endif
