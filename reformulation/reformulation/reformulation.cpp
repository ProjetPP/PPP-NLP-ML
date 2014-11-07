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

using namespace std;


Dictionary dico;
Functions functions;

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

void init()
{
  if(!fileExists("dictionnary.txt"))
    dico.initializeFromClex("clex_lexicon.pl");
  else
    dico.load("dictionnary.txt");
  if(fileExists("functions.txt"))
    functions.load("functions.txt");
}

void save()
{
  dico.load("dictionnary.txt");
  functions.save("functions.txt");
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


struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject *
error_out(PyObject *m) {
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

static PyMethodDef myextension_methods[] = {
    {"error_out", (PyCFunction)error_out, METH_NOARGS, NULL},
    {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3

static int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "myextension",
        NULL,
        sizeof(struct module_state),
        myextension_methods,
        NULL,
        myextension_traverse,
        myextension_clear,
        NULL
};

#define INITERROR return NULL

PyObject *
PyInit_myextension(void)

#else
#define INITERROR return

void
initmyextension(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("myextension", myextension_methods);
#endif

    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("myextension.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}

