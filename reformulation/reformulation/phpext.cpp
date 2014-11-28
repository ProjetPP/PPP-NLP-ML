#include <phpcpp.h>
#include "reformulation.h"

using namespace std;



Php::Value 
reformulation_init()
{
  if(init())
    return true;
  else
    return false;
}

Php::Value 
reformulation_save()
{
  save();
  return true;
}

void
reformulation_setDelta(Php::Parameters &params)
{
  float delta=static_cast<float>(static_cast<double>(params[0]));
  setLearningprecision(delta);
}

Php::Value 
reformulation_reformulation(Php::Parameters &params)
{
  string req=params[0];
  return reformulation(req);
}

Php::Value
reformulation_testtag(Php::Parameters &params)
{
  string req=params[0];
  return testtag(req);
}

/**
 *  Switch to C context, because the Zend-engine calls the get_module() method
 *  in C context, and not in C++ context
 */
extern "C" {
    

    PHPCPP_EXPORT void *get_module() 
    {
        // create an instance of the Php::Extension class
        static Php::Extension extension("reformulation", "1.0");
        
        // add the bubblesort function to the extension, we also tell the 
        // extension that the function receives one parameter by value, and
        // that that parameter must be an array
        extension.add("reformulation_init", reformulation_init);
	extension.add("reformulation_save", reformulation_save);
	extension.add("reformulation_setDelta", reformulation_setDelta,{Php::ByVal("input",Php::Type::Float)});
	extension.add("reformulation_reformulation", reformulation_reformulation,{Php::ByVal("input",Php::Type::Numeric)});
	extension.add("reformulation_testtag", reformulation_testtag,{Php::ByVal("input",Php::Type::String)});
        
        // return the extension
        return extension;
    }
}