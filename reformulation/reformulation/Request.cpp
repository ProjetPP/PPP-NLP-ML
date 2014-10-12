#include "Request.h"


Request::Request(void)
{
	predicate=vector<float>(50,0);
	subject=vector<float>(50,0);
	object=vector<float>(50,0);
	for(unsigned int i=0;i<50;i++)
	{
		predicate[i]=((float)(rand()%2000))/1000.0f-1.0f;
		subject[i]=((float)(rand()%2000))/1000.0f-1.0f;
		object[i]=((float)(rand()%2000))/1000.0f-1.0f;
	}
}

Request::Request(int invalid)
{
}

Request::~Request(void)
{
}

bool Request::isValid()
{
	return !predicate.empty();
}

float Request::getDistance1subject(Request r)
{
	float sum=0.0f;
	for(int i=0;i<50;i++)
	{
		sum+=abs(subject[i]-r.subject[i]);
	}
	return sum/50.0f;
}

float Request::getDistance1object(Request r)
{
	float sum=0.0f;
	for(int i=0;i<50;i++)
	{
		sum+=abs(object[i]-r.object[i]);
	}
	return sum/50.0f;
}

float Request::getDistance1predicate(Request r)
{
	float sum=0.0f;
	for(int i=0;i<50;i++)
	{
		sum+=abs(predicate[i]-r.predicate[i]);
	}
	return sum/50.0f;
}

float Request::getDistance2subject(Request r)
{
	float sum=0.0f;
	float term;
	for(int i=0;i<50;i++)
	{
		term=(subject[i]-r.subject[i]);
		sum+=term*term;
	}
	return sqrt(sum/50.0f);
}

float Request::getDistance2object(Request r)
{
	float sum=0.0f;
	float term;
	for(int i=0;i<50;i++)
	{
		term=(object[i]-r.object[i]);
		sum+=term*term;
	}
	return sqrt(sum/50.0f);
}

float Request::getDistance2predicate(Request r)
{
	float sum=0.0f;
	float term;
	for(int i=0;i<50;i++)
	{
		term=(predicate[i]-r.predicate[i]);
		sum+=term*term;
	}
	return sqrt(sum/50.0f);
}