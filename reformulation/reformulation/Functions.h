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
	Request merge(Request r1,Request r2);
	word compact(Request r);
	Request uncompact(word w);
	void clearGradient();
	void BackPropagationMerge(vector<float> input,Request gradOutput);
	void BackPropagationCompact(vector<float> input,Request gradOutput);
	void BackPropagationUncompact(vector<float> input,Request gradOutput);
private:
	vector<float> mergeMatrix;
	vector<float> compactMatrix;
	vector<float> uncompactMatrix;
	
	vector<float> gradInputMerge;
	vector<float> gradInputCompact;
	vector<float> gradInputUncompact;
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