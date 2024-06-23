#ifndef CFG_LINE_H_INCLUDED
#define CFG_LINE_H_INCLUDED



//  app

    #include "cfg-line-ptr.h"


//  c++

    #include <istream>



class CfgLine
{
        std::string Ident;
        std::string Value;
        bool Active;

        static std::string ReadIdent (std::istream & file);
        static std::string ReadValue (std::istream & file);


    public:

        CfgLine ();
        CfgLine (const std::string & ident, const std::string & value);

        static CfgLinePtr make (std::istream & file);

        std::string ident () const;
        int identLength () const;
        std::string value () const;
        bool active () const;
        bool empty () const;

        void setValue (const std::string & value);
        void remove ();

        void scan (std::istream & file);
        void print (std::ostream & file) const;
};



inline std::istream & operator >> (std::istream & file, CfgLine & line)
{
    line.scan (file);
    return file;
}



inline std::ostream & operator << (std::ostream & file, const CfgLine & line)
{
    line.print (file);
    return file;
}



#endif
