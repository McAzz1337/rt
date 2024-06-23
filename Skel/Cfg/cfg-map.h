#ifndef CFG_MAP_H_INCLUDED
#define CFG_MAP_H_INCLUDED



//  app

    #include "cfg-line-ptr.h"


//  c++

    #include <map>
    #include <string>



class CfgMap
{
    typedef std::map <std::string, CfgLinePtr> MapT;
        typedef MapT::const_iterator MapI;

        MapT Map;


    public:

        CfgLinePtr find (const std::string & ident);
        void store (CfgLinePtr lineptr);
};



#endif
