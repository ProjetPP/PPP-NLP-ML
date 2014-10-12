#ifndef REQUEST_H
#define REQUEST_H
#include <vector>
#include <cmath>

using namespace std;

class Request
{
public:
	Request(void);
	//Request in invalide with this constructor
	Request(int invalid);
	~Request(void);
	bool isValid();
	//Distance operator using norm 1 or 2 
	//this functions does not check if the Request is valid, use try/catch to use them safe
	float getDistance1subject(Request r);
	float getDistance1object(Request r);
	float getDistance1predicate(Request r);
	float getDistance2subject(Request r);
	float getDistance2object(Request r);
	float getDistance2predicate(Request r);
private:
	vector<float> subject;
	vector<float> object;
	vector<float> predicate;
};

#endif