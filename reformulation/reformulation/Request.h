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
	Request(void);
	//Request in invalide with this constructor
	Request(int invalid);
	//Maybe you have some data
	Request(word subject,word predicte,word object);
	~Request(void);
	bool isValid() const __attribute__((pure));
	//Distance operator using norm 1 or square of norm 2
	//this functions does not check if the Request is valid, use try/catch to use them safe
	float getDistance1subject(Request r) const __attribute__((pure));
	float getDistance1object(Request r) const __attribute__((pure));
	float getDistance1predicate(Request r) const __attribute__((pure));
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
	word::iterator getSubjectIterator();
	word::iterator getObjectIterator();
	word::iterator getPredicateIterator();
private:
	word subject;
	word object;
	word predicate;
};

ostream& operator<<(ostream& os,Request& req);
istream& operator>>(istream& is,Request& req);

#endif
