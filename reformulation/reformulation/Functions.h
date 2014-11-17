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
  pair<Request,Request> BackPropagationMerge(Request inputr1,Request inputr2,Request gradOutput);
  Request BackPropagationCompact(Request input,word gradOutput);
  word BackPropagationUncompact(word input,Request gradOutput);
  void accumulateGradients();
  void accGradMerge(Request inputr1,Request inputr2,Request gradOutput,float scale);
  void accGradCompact(Request input,word gradOutput,float scale);
  void accGradUncompact(word input,Request gradOutput,float scale);
private:
  vector<float> mergeMatrix;
  vector<float> compactMatrix;
  vector<float> uncompactMatrix;
  
  Request gradInputMerge1;
  Request gradInputMerge2;
  Request gradInputCompact;
  word gradInputUncompact;
  
  vector<float> gradMergeMatrix;
  vector<float> gradCompactMatrix;
  vector<float> gradUncompactMatrix;
  
  friend class Trainer;
};

struct vectorMatrixData
{
  word::iterator blocMatrix;
  word::iterator blocvector;
  word result;
};


word computeMatrixVectorBloc(word::iterator blocMatrix,word::iterator blocvector);
word computeVectorMatrixBloc(word::iterator blocMatrix,word::iterator blocvector);
word computeSumWords(vector<word> listWord);
void *launchMatrixVectorCalculus(void* data);
void *launchVectorMatrixCalculus(void* data);

#endif