//  self

    #include "cfg-map.h"


//  app

    #include "cfg-line.h"


//  c++

    using namespace std;



CfgLinePtr CfgMap :: find (const string & ident)
{
    MapI iter = Map.find (ident);
    return iter == Map.end() ? nullptr : iter->second;
}



void CfgMap :: store (CfgLinePtr lineptr)
{
    Map [lineptr->ident()] = lineptr;
}
