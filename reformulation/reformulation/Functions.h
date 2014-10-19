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
private:
	vector<int> fusionMatrix;
	vector<int> compactMatrix;
	vector<int> uncompactMatrix;
};

word computeMatrixVectorBlocAndUnlockMutex(word::iterator blocMatrix,word::iterator blocvector,pthread_mutex_t * mutex);

#endif