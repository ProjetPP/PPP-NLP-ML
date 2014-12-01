#include "Trainer.h"
#include "definitions.h"
#include <utility> 
#include <sstream>
#include <fstream>

Trainer::Trainer(Dictionary* dico_, Functions* func_,float delta_):transfo(new Transformator(func_,dico_,delta_)),delta(delta_),intensity(delta_/10),func(func_),dico(dico_)
{

}


void Trainer::addToTrainingSet(string req, string answer)
{
  trainingSet.push_back(SetEntry(req,transfo->Makerequest(req),answer));
}


void Trainer::trainWord(string w)
{
  /*vector<word> modifs; 
  for(int i=0;i<WORDSIZE;i++)
  {
    modifs.push_back(word(WORDSIZE,0));
    modifs.back()[i]=intensity;
    modifs.push_back(word(WORDSIZE,0));
    modifs.back()[i]=-intensity;
  }
  
  vector<SetEntry> data;
  unsigned int i,t;
  t=trainingSet.size();
  for (i=0;i<t;i++)
  {
    if(trainingSet[i].origin.find(w)!=string::npos)
      data.push_back(trainingSet[i]);
  }*/
  word empty(WORDSIZE,0);
  for(unsigned int i=0;i< static_cast<unsigned int>(WORDSIZE);i++)
  {
    stringstream ss;
    ss<<"1_"<<i;
    word t(WORDSIZE,0);
    t[i]=intensity;
    dico->translateWord(w,Request(t,empty,empty));
    masscomputing(ss.str());
    ss.str("");
    ss<<"2_"<<i;
    t[i]=-2*intensity;
    dico->translateWord(w,Request(t,empty,empty));
    masscomputing(ss.str());
    t[i]=intensity;
    dico->translateWord(w,Request(t,empty,empty));
    ss.str("");
    ss<<"3_"<<i;
    t[i]=intensity;
    dico->translateWord(w,Request(empty,t,empty));
    masscomputing(ss.str());
    ss.str("");
    ss<<"4_"<<i;
    t[i]=-2*intensity;
    dico->translateWord(w,Request(empty,t,empty));
    masscomputing(ss.str());
    t[i]=intensity;
    dico->translateWord(w,Request(empty,t,empty));
    ss.str("");
    ss<<"5_"<<i;
    t[i]=intensity;
    dico->translateWord(w,Request(empty,empty,t));
    masscomputing(ss.str());
    ss.str("");
    ss<<"6_"<<i;
    t[i]=-2*intensity;
    dico->translateWord(w,Request(empty,empty,t));
    masscomputing(ss.str());
    t[i]=intensity;
    dico->translateWord(w,Request(empty,empty,t));
  }
}


void Trainer::trainCompact()
{
  for(unsigned int i=0;i< static_cast<unsigned int>(COMPACTSIZE);i++)
  {
    stringstream ss;
    ss<<"1_"<<i;
    this->func->compactMatrix[i]+=intensity;
    masscomputing(ss.str());
    ss.str("");
    ss<<"2_"<<i;
    this->func->compactMatrix[i]-=2*intensity;
    masscomputing(ss.str());
    this->func->compactMatrix[i]+=intensity;
  }
}

void Trainer::trainUncompact()
{
  for(unsigned int i=0;i< static_cast<unsigned int>(UNCOMPACTSIZE);i++)
  {
    stringstream ss;
    ss<<"1_"<<i;
    this->func->uncompactMatrix[i]+=intensity;
    masscomputing(ss.str());
    ss.str("");
    ss<<"2_"<<i;
    this->func->uncompactMatrix[i]-=2*intensity;
    masscomputing(ss.str());
    this->func->uncompactMatrix[i]+=intensity;
  }
}


void Trainer::masscomputing(string file)
{
  ofstream os(file);
  long unsigned int i,t;
  t=trainingSet.size();
  for (i=0;i<t;i++)
  {
    os<<transfo->reformulation(trainingSet[i].rt)<<" "<<trainingSet[i].answer<<endl;
  }
  os.close();
}

void Trainer::setDelta(float d)
{
  this->delta=d;
  this->intensity=delta/d;
  this->transfo->setDelta(d);
}
