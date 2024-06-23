//  self

    #include "cfg.h"


//  app

    #include "cfg-line.h"


//  c++

    using namespace std;



string Cfg::Filename = "config.cfg";



Cfg :: Cfg ()
{
    File.read (Filename);
    File.makeMap (Map);
}



Cfg :: ~ Cfg ()
{
    File.write (Filename);
}



void Cfg :: SetValue (const string & ident, const string & value)
{
    CfgLinePtr lineptr = Map.find (ident);
    if (lineptr)
        lineptr->setValue (value);
    else
    {
        lineptr = File.append (ident, value);
        Map.store (lineptr);
    }
}



string Cfg :: Value (const string & ident)
{
    CfgLinePtr lineptr = Map.find (ident);
    return lineptr ? lineptr->value() : string();
}



void Cfg :: setFilename (const string & filename)
{
    Filename = filename;
}



void Cfg :: setValueString (const string & ident, const string & value)
{
    instptr()->SetValue(ident, value);
}



string Cfg :: valueString (const string & ident)
{
    return instptr()->Value (ident);
}
