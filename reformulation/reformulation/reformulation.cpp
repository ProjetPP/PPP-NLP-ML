// reformulation.cpp : definit le point d'entrée pour l'application console.
//
#include <Python.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"
#include "Functions.h"
#include <pthread.h>
#include <ctime>
#include "Transformator.h"

using namespace std;


Dictionary dico;
Functions functions;
Transformator transformator(&functions,&dico,0.1f);

inline bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }   
}

bool init()
{
  if(!fileExists("dictionnary.txt"))
  {
    if(!dico.initializeFromClex("clex_lexicon.pl"))
      return false;
  }
  else
    dico.load("dictionnary.txt");
  if(fileExists("functions.txt"))
  {
    if(!functions.load("functions.txt"))
      return false;
  }
  return true;
}

void save()
{
  dico.save("dictionnary.txt");
  functions.save("functions.txt");
}

void setLearningprecision(float delta)
{
  transformator=Transformator(&functions,&dico,delta);
}

string reformulation(string input)
{
  return transformator.reformulation(input);
}

/*int main(int argc, char* argv[])
{
  (void) argc;
  (void) argv;
  Dictionary dico;
  dico.initializeFromClex("clex_lexicon.pl");
  //dico.save("dictionnary.txt");
  //dico.load("dictionnary.txt");
  Functions functions;
  //functions.load("functions.txt");
   clock_t begin = clock();
  for(int i=0;i<10000;i++)
  {
    Request r1(0),r2(0);
    r1=dico["monkey"];
    r2=dico["lives"];
    
    Request r3=functions.merge(r1,r2);
  }
  clock_t end = clock();
  cout<<difftime(end,begin)<<endl;
  
  pthread_exit(0);
  return 0;
}*/

static PyObject *
reformulation_init(PyObject *self, PyObject *args)
{
  if (!PyArg_ParseTuple(args, ""))
        return NULL;
  if(init())
    return Py_True;
  else
    return Py_False;
}

static PyObject *
reformulation_save(PyObject *self, PyObject *args)
{
  if (!PyArg_ParseTuple(args, ""))
        return NULL;
  save();
  return Py_True;
}

static PyObject *
reformulation_setDelta(PyObject *self, PyObject *args)
{
  float delta;
  if (!PyArg_ParseTuple(args, "f",&delta))
        return NULL;
  setLearningprecision(delta);
  return Py_True;
}

static PyObject *
reformulation_reformulation(PyObject *self, PyObject *args)
{
  const char *entry;
  if (!PyArg_ParseTuple(args, "s",&entry))
        return NULL;
  string req=entry;
  //delete entry;
  return PyUnicode_FromString(reformulation(req).c_str());
}

static PyObject *
reformulation_testtag(PyObject *self, PyObject *args)
{
  const char *entry;
  cout<<"coucou"<<endl;
  if (!PyArg_ParseTuple(args, "s",&entry))
        return NULL;
  cout<<"Request is "<<entry<<endl;
  string req=entry;
  string res=transformator.testtaginput(req);
  //delete entry;
  return PyUnicode_FromString(res.c_str());
}

static PyObject *
reformulation_testreq(PyObject *self, PyObject *args)
{
  const char *entry;
  if (!PyArg_ParseTuple(args, "s",&entry))
        return NULL;
  
  string req=entry;
  //delete entry;
  transformator.testmakerequest(req);
  return Py_True;
}

struct module_state {
    PyObject *error;
};

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

static PyMethodDef reformulation_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {"init",  reformulation_init, METH_VARARGS,"First method you should call."},
    {"save",  reformulation_save, METH_VARARGS,"Saving is important."},
    {"setDelta",  reformulation_setDelta, METH_VARARGS,"Set delta factor for uncompact."},
    {"reformule",  reformulation_reformulation, METH_VARARGS,"Reformulate a request tree."},
    {"testtag",  reformulation_testtag, METH_VARARGS,"Test tag."},
    {"testreq",  reformulation_testreq, METH_VARARGS,"Test req."},
    {NULL, NULL}
};

static int reformulation_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int reformulation_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "reformulation",
        NULL,
        sizeof(struct module_state),
        reformulation_methods,
        NULL,
        reformulation_traverse,
        reformulation_clear,
        NULL
};

//PyObject *
PyMODINIT_FUNC
PyInit_libreformulation(void)

{
    PyObject *module = PyModule_Create(&moduledef);

    if (module == NULL)
        return NULL;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("reformulation.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        return NULL;
    }

    return module;
}

