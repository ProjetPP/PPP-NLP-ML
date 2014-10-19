#include "Request.h"
#include "definitions.h"
#include <cstdlib>

Request::Request(void) :
subject(vector<float>(WORDSIZE,0)), object(vector<float>(WORDSIZE,0)), predicate(vector<float>(WORDSIZE,0))
{
	predicate=vector<float>(WORDSIZE,0);
	subject=vector<float>(WORDSIZE,0);
	object=vector<float>(WORDSIZE,0);
	for(unsigned int i=0;i<WORDSIZE;i++)
	{
		predicate[i]=(static_cast<float>(rand()%2000))/1000.0f-1.0f;
		subject[i]=(static_cast<float>(rand()%2000))/1000.0f-1.0f;
		object[i]=(static_cast<float>(rand()%2000))/1000.0f-1.0f;
	}
}

Request::Request(int invalid) :
subject(vector<float>(0)), object(vector<float>(0)), predicate(vector<float>(0))
{
    (void) invalid;
}

Request::Request(word subject,word predicte,word object):
subject(subject), object(object), predicate(predicate)
{
  
}

Request::~Request(void)
{
}

bool Request::isValid() const
{
	return !predicate.empty();
}

float Request::getDistance1subject(Request r) const
{
	float sum=0.0f;
	for(int i=0;i<WORDSIZE;i++)
	{
		sum+=abs(subject[static_cast<size_t>(i)]-r.subject[static_cast<size_t>(i)]);
	}
	return sum/static_cast<float>(WORDSIZE);
}

float Request::getDistance1object(Request r) const
{
	float sum=0.0f;
	for(int i=0;i<WORDSIZE;i++)
	{
		sum+=abs(object[static_cast<size_t>(i)]-r.object[static_cast<size_t>(i)]);
	}
	return sum/static_cast<float>(WORDSIZE);
}

float Request::getDistance1predicate(Request r) const
{
	float sum=0.0f;
	for(int i=0;i<WORDSIZE;i++)
	{
		sum+=abs(predicate[static_cast<size_t>(i)]-r.predicate[static_cast<size_t>(i)]);
	}
	return sum/static_cast<float>(WORDSIZE);
}

float Request::getDistance2subject(Request r) const
{
	float sum=0.0f;
	float term;
	for(int i=0;i<WORDSIZE;i++)
	{
		term=(subject[static_cast<size_t>(i)]-r.subject[static_cast<size_t>(i)]);
		sum+=term*term;
	}
	return sqrt(sum/static_cast<float>(WORDSIZE));
}

float Request::getDistance2object(Request r) const
{
	float sum=0.0f;
	float term;
	for(int i=0;i<WORDSIZE;i++)
	{
		term=(object[static_cast<size_t>(i)]-r.object[static_cast<size_t>(i)]);
		sum+=term*term;
	}
	return sqrt(sum/static_cast<float>(WORDSIZE));
}

float Request::getDistance2predicate(Request r) const
{
	float sum=0.0f;
	float term;
	for(int i=0;i<WORDSIZE;i++)
	{
		term=(predicate[static_cast<size_t>(i)]-r.predicate[static_cast<size_t>(i)]);
		sum+=term*term;
	}
	return sqrt(sum/static_cast<float>(WORDSIZE));
}

ostream& Request::output(ostream& os)
{
	for(int i=0;i<WORDSIZE;i++)
	{
		os<<this->subject[static_cast<size_t>(i)]<<" "<<this->predicate[static_cast<size_t>(i)]<<" "<<this->object[static_cast<size_t>(i)]<<" ";
	}
	return os;
}

istream& Request::input(istream& is)
{
	for(int i=0;i<WORDSIZE;i++)
	{
		is>>this->subject[static_cast<size_t>(i)]>>this->predicate[static_cast<size_t>(i)]>>this->object[static_cast<size_t>(i)];
	}
	return is;
}

ostream& operator<<(ostream& os,Request& req)
{
	return req.output(os);
}

istream& operator>>(istream& is,Request& req)
{
	return req.input(is);
}

word Request::getSubject(){return subject;}
word Request::getObject(){return object;}
word Request::getPredicate(){return predicate;}

word::iterator Request::getSubjectIterator(){return subject.begin();}
word::iterator Request::getObjectIterator(){return object.begin();}
word::iterator Request::getPredicateIterator(){return predicate.begin();}