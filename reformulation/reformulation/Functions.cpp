#include "Functions.h"
#include "definitions.h"
#include <fstream>

Functions::Functions(void)
{
	fusionMatrix=vector<int>(FUSIONSIZE);
	compactMatrix=vector<int>(3*WORDSIZE*WORDSIZE);
	uncompactMatrix=vector<int>(3*WORDSIZE*WORDSIZE);
}


Functions::~Functions(void)
{
}


bool Functions::load(string file)
{
	ifstream is(file);
	if(is.fail())
	{
		cout<<"Functions paramters file "<<file<<" is not openable"<<endl;
		return false;
	}
	for(int i=0;i<FUSIONSIZE;i++)
		is>>fusionMatrix[i];
	for(int i=0;i<COMPACTSIZE;i++)
		is>>compactMatrix[i];
	for(int i=0;i<UNCOMPACTSIZE;i++)
		is>>uncompactMatrix[i];
	cout<<"Functions parameters are correctly loaded"<<endl;
	return true;
}

bool Functions::save(string file)
{
	ofstream os(file);
	if(os.fail())
	{
		cout<<"Functions paramters file "<<file<<" is not openable"<<endl;
		return false;
	}
	for(int i=0;i<FUSIONSIZE;i++)
		os<<fusionMatrix[i]<<" ";
	for(int i=0;i<COMPACTSIZE;i++)
		os<<compactMatrix[i]<<" ";
	for(int i=0;i<UNCOMPACTSIZE;i++)
		os<<uncompactMatrix[i]<<" ";
	cout<<"Functions parameters are correctly saved"<<endl;
	return true;
}

word computeMatrixVectorBlocAndUnlockMutex(word::iterator blocMatrix,word::iterator blocvector,pthread_mutex_t * mutex)
{
  word result;
  for(int i=0;i<WORDSIZE;i++)
  {
    float coeffRes=0.0f;
    word::iterator wordit=blocvector;
    for(int j=0;i<WORDSIZE;j++)
    {
      coeffRes+=(*blocMatrix)*(*wordit);
      ++blocMatrix;
      ++wordit;
    }
    result.push_back(coeffRes);
  }
  pthread_mutex_unlock (mutex);
  return result;
}

Request fusion(Request r1,Request r2)
{
  //TODO Start thread to compute all the stuff
}