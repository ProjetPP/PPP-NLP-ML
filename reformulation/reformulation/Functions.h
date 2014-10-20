#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Request.h"
#include <string>
#include <vector>
#include <pthread.h>
#include "definitions.h"

using namespace std;

class Functions
{
public:
	Functions(void);
	~Functions(void);
	bool load(string file);
	bool save(string file);
	Request fusion(Request r1,Request r2);
	word compact(Request r);
	Request uncompact(word w);
private:
	vector<float> fusionMatrix;
	vector<float> compactMatrix;
	vector<float> uncompactMatrix;
};

struct vectorMatrixData
{
  word::iterator blocMatrix;
  word::iterator blocvector;
  word result;
};

word& operator+=(word& w1,word w2);
word operator+(word w1,word w2);

word computeMatrixVectorBloc(word::iterator blocMatrix,word::iterator blocvector);
word computeSumWords(vector<word> listWord);
void *launchMatrixVectorCalculus(void* data);

#endif