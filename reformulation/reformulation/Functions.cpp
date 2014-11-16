#include "Functions.h"
#include "definitions.h"
#include <fstream>
#include <list>
#include <pthread.h>
#include <iostream>

Functions::Functions(void):
  mergeMatrix(vector<float>(MERGESIZE)),
  compactMatrix(vector<float>(COMPACTSIZE)),
  uncompactMatrix(vector<float>(UNCOMPACTSIZE)),
  gradInputMerge1(Request(true)),
  gradInputMerge2(Request(true)),
  gradInputCompact(Request(true)),
  gradInputUncompact(vector<float>(UNCOMPACTSIZE,0)),
  gradMergeMatrix(vector<float>(MERGESIZE,0)),
  gradCompactMatrix(vector<float>(COMPACTSIZE,0)),
  gradUncompactMatrix(vector<float>(UNCOMPACTSIZE,0))
{
  for(long unsigned int i=0;i<MERGESIZE;i++)
    mergeMatrix[i]=((static_cast<float>(rand()%2000))/1000.0f-1.0f)/WORDSIZE;
  for(long unsigned int i=0;i<COMPACTSIZE;i++)
    compactMatrix[i]=((static_cast<float>(rand()%2000))/1000.0f-1.0f)/WORDSIZE;
  for(long unsigned int i=0;i<UNCOMPACTSIZE;i++)
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
  for(long unsigned int i=0;i<MERGESIZE;i++)
    is>>mergeMatrix[i];
  for(long unsigned int i=0;i<COMPACTSIZE;i++)
    is>>compactMatrix[i];
  for(long unsigned int i=0;i<UNCOMPACTSIZE;i++)
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
  for(long unsigned int i=0;i<MERGESIZE;i++)
    os<<mergeMatrix[i]<<" ";
  for(long unsigned int i=0;i<COMPACTSIZE;i++)
    os<<compactMatrix[i]<<" ";
  for(long unsigned int i=0;i<UNCOMPACTSIZE;i++)
    os<<uncompactMatrix[i]<<" ";
  cout<<"Functions parameters are correctly saved"<<endl;
  return true;
}



word computeMatrixVectorBloc(word::iterator blocMatrix,word::iterator blocvector)
{
  word result;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    float coeffRes=0.0f;
    word::iterator wordit=blocvector;
    for(long unsigned int j=0;j<WORDSIZE;j++)
    {
      coeffRes+=(*blocMatrix)*(*wordit);
      ++blocMatrix;
      ++wordit;
    }
    result.push_back(coeffRes);
  }
  return result;
}

word computeVectorMatrixBloc(word::iterator blocMatrix,word::iterator blocvector)
{
  word result;
  for(long unsigned int i=0;i<WORDSIZE;i++)
  {
    float coeffRes=0.0f;
    word::iterator wordit=blocvector;
    word::iterator matrit=blocMatrix;
    blocMatrix+=static_cast<long int>(i);
    for(long unsigned int j=0;j<WORDSIZE;j++)
    {
      coeffRes+=(*matrit)*(*wordit);
      matrit+=WORDSIZE;
      ++wordit;
    }
    result.push_back(coeffRes);
  }
  return result;
}

word computeSumWords(vector<word> listWord)
{
  long unsigned int s=listWord.size();
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

void *launchVectorMatrixCalculus(void* data)
{
  vectorMatrixData* resource=static_cast<vectorMatrixData*>(data);
  resource->result=computeVectorMatrixBloc(resource->blocMatrix,resource->blocvector);
  return 0;
}

Request Functions::merge(Request r1,Request r2)
{
  pthread_t tid[18];
  vectorMatrixData data[18];
  vector<float>::iterator it=this->mergeMatrix.begin();
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

  word w=data[0].result+data[1].result+data[2].result;
  normalizeWord(w);
  return w;
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

void Functions::clearGradient()
{
  for(long unsigned int i=0;i<WORDSIZE;i++)
    gradInputUncompact[i]=0;
  gradInputCompact.reset();
  gradInputMerge1.reset();
  gradInputMerge2.reset();
  for(long unsigned int i=0;i<MERGESIZE;i++)
    gradMergeMatrix[i]=0;
  for(long unsigned int i=0;i<COMPACTSIZE;i++)
    gradCompactMatrix[i]=0;
  for(long unsigned int i=0;i<UNCOMPACTSIZE;i++)
    gradUncompactMatrix[i]=0;
}

pair<Request,Request> Functions::BackPropagationMerge(Request inputr1,Request inputr2,Request gradOutput)
{
  pthread_t tid[18];
  vectorMatrixData data[18];
  vector<float>::iterator it=this->mergeMatrix.begin();
  for(int i=0;i<18;i++)
  {
    data[i].blocMatrix=it;
    it+=WORDSIZE*WORDSIZE;
    switch(i%3)
    {
      case 0:
  data[i].blocvector=gradOutput.getSubjectIterator();
  break;
      case 1:
  data[i].blocvector=gradOutput.getPredicateIterator();
  break;
      case 2:
  data[i].blocvector=gradOutput.getObjectIterator();
  break;
    }
     pthread_create(&tid[i],NULL,launchVectorMatrixCalculus,&data[i]);
  }
  /// wait all threads
  for (int i = 0; i < 18; i++)
  {
    pthread_join(tid[i], NULL);
  }
  Request r1(data[0].result+data[6].result+data[12].result,
     data[1].result+data[7].result+data[13].result,
     data[2].result+data[8].result+data[14].result);
  Request r2(data[3].result+data[9].result+data[15].result,
     data[4].result+data[10].result+data[16].result,
     data[5].result+data[11].result+data[17].result);
  gradInputMerge1+=r1;
  gradInputMerge2+=r2;
  return pair<Request,Request>(gradInputMerge1,gradInputMerge1);
}

Request Functions::BackPropagationCompact(Request input,word gradOutput)
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
  data[i].blocvector=gradOutput.begin();
  break;
      case 1:
  data[i].blocvector=gradOutput.begin();
  break;
      case 2:
  data[i].blocvector=gradOutput.begin();
  break;
    }
     pthread_create(&tid[i],NULL,launchVectorMatrixCalculus,&data[i]);
  }
  /// wait all threads
  for (int i = 0; i < 3; i++)
  {
    pthread_join(tid[i], NULL);
  }
  Request r(data[0].result,data[1].result,data[2].result);
  gradInputCompact+=r;
  return r;
}

word Functions::BackPropagationUncompact(word input, Request gradOutput)
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
  data[i].blocvector=gradOutput.getSubjectIterator();
  break;
      case 1:
  data[i].blocvector=gradOutput.getPredicateIterator();
  break;
      case 2:
  data[i].blocvector=gradOutput.getObjectIterator();
  break;
    }
     pthread_create(&tid[i],NULL,launchVectorMatrixCalculus,&data[i]);
  }
  /// wait all threads
  for (int i = 0; i < 3; i++)
  {
    pthread_join(tid[i], NULL);
  }
  word r=data[0].result+data[1].result+data[2].result;
  gradInputUncompact+=r;
  return r;
}

void Functions::accumulateGradients()
{
  for(long unsigned int i=0;i<MERGESIZE;i++)
    mergeMatrix[i]+=gradMergeMatrix[i];
  for(long unsigned int i=0;i<COMPACTSIZE;i++)
    compactMatrix[i]+=gradCompactMatrix[i];
  for(long unsigned int i=0;i<UNCOMPACTSIZE;i++)
    uncompactMatrix[i]+=gradUncompactMatrix[i];
}

void Functions::accGradMerge(Request inputr1, Request inputr2, Request gradOutput, float scale)
{
  //TODO
  word::iterator itmatrix=gradMergeMatrix.begin();
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<6;j++)
    {
      word::iterator itinput;
      switch(j)
      {
  case 0:
    itinput=inputr1.getSubjectIterator();
    break;
  case 1:
    itinput=inputr1.getPredicateIterator();
    break;
  case 2:
    itinput=inputr1.getObjectIterator();
    break;
  case 3:
    itinput=inputr2.getSubjectIterator();
    break;
  case 4:
    itinput=inputr2.getPredicateIterator();
    break;
  case 5:
    itinput=inputr2.getObjectIterator();
    break;
      }
      word::iterator itgradoutput;
      switch(i)
      {
  case 0:
    itgradoutput=gradOutput.getSubjectIterator();
    break;
  case 1:
    itgradoutput=gradOutput.getPredicateIterator();
    break;
  case 2:
    itgradoutput=gradOutput.getObjectIterator();
    break;
      }
      for(int k=0;k<WORDSIZE;k++)
      {
  for(int l=0;l<WORDSIZE;l++)
  {
    (*itmatrix)+=scale*(*itgradoutput)*(*itinput);
    ++itinput;
  }
  ++itgradoutput;
      }


    }
  }
}
void Functions::accGradCompact(Request input, word gradOutput, float scale)
{
  word::iterator itgradoutput=gradOutput.begin();
  word::iterator itsubject=input.getSubjectIterator();
  word::iterator itpredicate=input.getPredicateIterator();
  word::iterator itobject=input.getObjectIterator();
  word::iterator itmatrix=gradCompactMatrix.begin();
  for(int i=0;i<WORDSIZE;i++)
  {
    itsubject=input.getSubjectIterator();
      for(int j=0;j<WORDSIZE;j++)
      {
  (*itmatrix)+=(*itsubject)*(*itgradoutput);
  ++itsubject;
      }
      ++itgradoutput;
  }
  itgradoutput=gradOutput.begin();
  for(int i=0;i<WORDSIZE;i++)
  {
    itpredicate=input.getPredicateIterator();
      for(int j=0;j<WORDSIZE;j++)
      {
  (*itmatrix)+=(*itpredicate)*(*itgradoutput);
  ++itpredicate;
      }
      ++itgradoutput;
  }
  itgradoutput=gradOutput.begin();
  for(int i=0;i<WORDSIZE;i++)
  {
    itobject=input.getObjectIterator();
      for(int j=0;j<WORDSIZE;j++)
      {
  (*itmatrix)+=scale*(*itobject)*(*itgradoutput);
  ++itobject;
      }
      ++itgradoutput;;
  }
}

void Functions::accGradUncompact(word input, Request gradOutput, float scale)
{
  word::iterator itinput=input.begin();
  word::iterator itsubject=gradOutput.getSubjectIterator();
  word::iterator itpredicate=gradOutput.getPredicateIterator();
  word::iterator itobject=gradOutput.getObjectIterator();
  word::iterator itmatrix=gradUncompactMatrix.begin();
  for(int i=0;i<WORDSIZE;i++)
  {
    itinput=input.begin();
      for(int j=0;j<WORDSIZE;j++)
      {
  (*itmatrix)+=(*itsubject)*(*itinput);
  ++itinput;
      }
      ++itsubject;
  }
  for(int i=0;i<WORDSIZE;i++)
  {
    itinput=input.begin();
      for(int j=0;j<WORDSIZE;j++)
      {
  (*itmatrix)+=(*itpredicate)*(*itinput);
  ++itinput;
      }
      ++itpredicate;
  }
  for(int i=0;i<WORDSIZE;i++)
  {
    itinput=input.begin();
      for(int j=0;j<WORDSIZE;j++)
      {
  (*itmatrix)+=scale*(*itobject)*(*itinput);
  ++itinput;
      }
      ++itobject;
  }
}
