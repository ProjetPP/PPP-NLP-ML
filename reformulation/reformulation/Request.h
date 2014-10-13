#ifndef REQUEST_H
#define REQUEST_H
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Request
{
public:
	Request(void);
	//Request in invalide with this constructor
	Request(int invalid);
	~Request(void);
	bool isValid();
	//Distance operator using norm 1 or square of norm 2 
	//this functions does not check if the Request is valid, use try/catch to use them safe
	float getDistance1subject(Request r);
	float getDistance1object(Request r);
	float getDistance1predicate(Request r);
	float getDistance2subject(Request r);
	float getDistance2object(Request r);
	float getDistance2predicate(Request r);
	//operator to save and load
	ostream& output(ostream& os);
	istream& input(istream& is);
private:
	vector<float> subject;
	vector<float> object;
	vector<float> predicate;
};

ostream& operator<<(ostream& os,Request& req);
istream& operator>>(istream& is,Request& req);

#endif