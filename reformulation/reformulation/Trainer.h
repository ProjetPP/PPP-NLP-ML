#ifndef TRAINER_H
#define TRAINER_H
#include "Transformator.h"
#include "Request.h"

struct SetEntry
{
  string origin;
  RequestTree rt;
  string answer;
  SetEntry(string orig,RequestTree req,string answ):origin(orig),rt(req),answer(answ){} 
};

class Trainer
{
public:
  Trainer(Dictionary *dico,Functions *func,float delta);
  void addToTrainingSet(string req,string answer);
  void trainWord(string w);
  void trainCompact();
  void trainUncompact();
  void setDelta(float delta);
private:
  void masscomputing(string file);
  vector<SetEntry > trainingSet;
  Transformator* transfo;
  float delta;
  float intensity;
  Functions* func;
  Dictionary* dico;
};

#endif