#ifndef CFG_FILE_H_INCLUDED
#define CFG_FILE_H_INCLUDED



//  app

    class CfgMap;

    #include "cfg-line-ptr.h"


//  c++

    #include <string>
    #include <vector>



class CfgFile
{
        static std::string DefaultContents;

        std::vector <CfgLinePtr> LinePtrs;

        int IdentMaxLen() const;


    public:

        void read (std::istream & file);
        void write (std::ostream & file);

        void read (const std::string & filename);
        void write (const std::string & filename);

        CfgLinePtr append (const std::string & ident, const std::string & value);
        void makeMap (CfgMap & map) const;
};



#endif
