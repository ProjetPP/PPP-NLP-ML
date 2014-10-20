#include "Functions.h"
#include "definitions.h"
#include <fstream>
#include <list>
#include <pthread.h>

Functions::Functions(void)
{
  fusionMatrix=vector<float>(FUSIONSIZE);
  compactMatrix=vector<float>(COMPACTSIZE);
  uncompactMatrix=vector<float>(UNCOMPACTSIZE);
  for(int i=0;i<FUSIONSIZE;i++)
    fusionMatrix[i]=((static_cast<float>(rand()%2000))/1000.0f-1.0f)/WORDSIZE;
  for(int i=0;i<COMPACTSIZE;i++)
    compactMatrix[i]=((static_cast<float>(rand()%2000))/1000.0f-1.0f)/WORDSIZE;
  for(int i=0;i<UNCOMPACTSIZE;i++)
    uncompactMatrix[i]=((static_cast<float>(rand()%2000))/1000.0f-1.0f)/WORDSIZE;
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

word& operator+=(word& w1,word w2)
{
  for(int i=0;i<WORDSIZE;i++)
    w1[i]+=w2[i];
  return w1;
}

word operator+(word w1,word w2)
{
  word r;
  for(int i=0;i<WORDSIZE;i++)
    r.push_back(w1[i]+w2[i]);
  return r;
}

word computeMatrixVectorBloc(word::iterator blocMatrix,word::iterator blocvector)
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
  return result;
}

word computeSumWords(vector<word> listWord)
{
  unsigned int s=listWord.size();
  word r=listWord[0];
  for(unsigned int i=1;i<s;i++)
  {
    r+=listWord[i];
  }
  return r;
}

void *launchMatrixVectorCalculus(void* data)
{
  vectorMatrixData* resource=static_cast<vectorMatrixData*>(data);
  resource->result=computeMatrixVectorBloc(resource->blocMatrix,resource->blocvector);
  return 0;
}

Request Functions::fusion(Request r1,Request r2)
{
  //TODO Start :ad to compute all the stuff
  pthread_t tid[18];
  vectorMatrixData data[18];
  vector<float>::iterator it=this->fusionMatrix.begin();
  for(int i=0;i<18;i++)
  {
    data[i].blocMatrix=it;
    it+=WORDSIZE*WORDSIZE;
    switch(i%6)
    {
      case 0:
	data[i].blocvector=r1.getSubjectIterator();
	break;
      case 1:
	data[i].blocvector=r1.getPredicateIterator();
	break;
      case 2:
	data[i].blocvector=r1.getObjectIterator();
	break;
      case 3:
	data[i].blocvector=r2.getSubjectIterator();
	break;
      case 4:
	data[i].blocvector=r2.getPredicateIterator();
	break;
      case 5:
	data[i].blocvector=r2.getObjectIterator();
	break;
    }
     pthread_create(&tid[i],NULL,launchMatrixVectorCalculus,&data[i]);
  }
  /// wait all threads
  for (int i = 0; i < 18; i++) 
  {
    pthread_join(tid[i], NULL);  
  }
  return Request(data[0].result+data[1].result+data[2].result+data[3].result+data[4].result+data[5].result,
		 data[6].result+data[7].result+data[8].result+data[9].result+data[10].result+data[11].result,
		 data[12].result+data[13].result+data[14].result+data[15].result+data[16].result+data[17].result);
}

word Functions::compact(Request r)
{
  pthread_t tid[3];
  vectorMatrixData data[3];
  vector<float>::iterator it=this->compactMatrix.begin();
  for(int i=0;i<3;i++)
  {
    data[i].blocMatrix=it;
    it+=WORDSIZE*WORDSIZE;
    switch(i)
    {
      case 0:
	data[i].blocvector=r.getSubjectIterator();
	break;
      case 1:
	data[i].blocvector=r.getPredicateIterator();
	break;
      case 2:
	data[i].blocvector=r.getObjectIterator();
	break;
    }
     pthread_create(&tid[i],NULL,launchMatrixVectorCalculus,&data[i]);
  }
  /// wait all threads
  for (int i = 0; i < 3; i++) 
  {
    pthread_join(tid[i], NULL);  
  }
  
  return data[0].result+data[1].result+data[2].result;
}

Request Functions::uncompact(word w)
{
  pthread_t tid[3];
  vectorMatrixData data[3];
  vector<float>::iterator it=this->uncompactMatrix.begin();
  for(int i=0;i<3;i++)
  {
    data[i].blocMatrix=it;
    it+=WORDSIZE*WORDSIZE;
    data[i].blocvector=w.begin();
    pthread_create(&tid[i],NULL,launchMatrixVectorCalculus,&data[i]);
  }
  /// wait all threads
  for (int i = 0; i < 3; i++) 
  {
    pthread_join(tid[i], NULL);  
  }
  
  return Request(data[0].result,data[1].result,data[2].result);
}