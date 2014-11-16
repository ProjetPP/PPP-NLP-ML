#ifndef REQUEST_H
#define REQUEST_H
#include <vector>
#include <cmath>
#include <iostream>
#include "definitions.h"

using namespace std;

class Request
{
public:
  //random request generated
  Request(void);
  //Request in invalide with this constructor
  Request(int invalid);
  //Request is filled with zeros
  Request(bool nulconstructor);
  //Maybe you have some data
  Request(word subject,word predicate,word object);
  ~Request(void);
  bool isValid() const __attribute__((pure));
  //Distance operator using norm 2, transformedDistance compute a real for distance comparaison
  //That means we can use them to find nearest neighbour, it distance > limit it return infinity
  //this functions does not check if the Request is valid, use try/catch to use them safe
  float getTransformedDistanceSubject(Request& r,float limit) const __attribute__((pure));
  float getTransformedDistanceObject(Request& r,float limit) const __attribute__((pure));
  float getTransformedDistancePredicate(Request& r,float limit) const __attribute__((pure));
  float getDistance2subject(Request r) const __attribute__((pure));
  float getDistance2object(Request r) const __attribute__((pure));
  float getDistance2predicate(Request r) const __attribute__((pure));

  //operator to save and load
  ostream& output(ostream& os);
  istream& input(istream& is);
  //Some getters
  word getSubject();
  word getObject();
  word getPredicate();
  word::iterator getSubjectIterator() __attribute__((pure));
  word::iterator getObjectIterator() __attribute__((pure));
  word::iterator getPredicateIterator() __attribute__((pure));
  Request operator+(Request a);
  void operator+=(Request a);
  void reset();
private:
  word subject;
  word object;
  word predicate;
};

ostream& operator<<(ostream& os,Request& req);
istream& operator>>(istream& is,Request& req);


word& operator+=(word& w1,word w2);
word operator+(word w1,word w2);

void normalizeWord(word& w);

#endif
