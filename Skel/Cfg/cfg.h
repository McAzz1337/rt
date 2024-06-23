#ifndef CFG_H_INCLUDED
#define CFG_H_INCLUDED



//  self

    class Cfg;


//  app

    #include "io.h"
    #include "cfg-file.h"
    #include "cfg-map.h"
    #include "singleton.h"


//  c++

    #include <sstream>



typedef std::shared_ptr <Cfg> CfgPtr;



class Cfg
    : public Singleton <Cfg>
{
        static std::string Filename;

        CfgFile File;
        CfgMap Map;

        void SetValue (const std::string & ident, const std::string & value);
        std::string Value (const std::string & ident);


    public:

        Cfg ();
        ~ Cfg ();

        static void setFilename (const std::string & filename);
        static void setValueString (const std::string & ident, const std::string & value);
        static std::string valueString (const std::string & ident);

        template <class T>
        static void setValue (const std::string & ident, const T & value);

        template <class T>
        static void getValue (const std::string & ident, T & var, const T & def);
};



template <class T>
void Cfg :: getValue (const std::string & ident, T & var, const T & def)
{
    std::string str = valueString (ident);
    std::istringstream file (str);
    if (! (file >> var))
    {
        var = def;
        setValue (ident, var);
    }
}



template <class T>
void Cfg :: setValue (const std::string & ident, const T & value)
{
    std::ostringstream file;
    file << value;
    setValueString (ident, file.str());
}



template <class T>
class CfgVar
{
        T Var;
        CfgPtr CfgInstPtr;
        std::string Ident;


    public:

        CfgVar (const std::string & ident, const T & def);
        ~ CfgVar ();

        CfgVar & operator = (const T & var);
        operator T ();
        operator T () const;
};



template <class T>
CfgVar<T> :: CfgVar (const std::string & ident, const T & def)
    : CfgInstPtr (Cfg::instptr())
    , Ident (ident)
{
    CfgInstPtr->getValue (Ident, Var, def);
}



template <class T>
CfgVar<T> :: ~ CfgVar ()
{
    CfgInstPtr->setValue (Ident, Var);
}



template<class T>
CfgVar <T> & CfgVar <T> :: operator = (const T & var)
{
    Var = var;
    return *this;
}



template <class T>
CfgVar <T> :: operator T ()
{
    return Var;
}



template <class T>
CfgVar <T> :: operator T () const
{
    return Var;
}



#endif
