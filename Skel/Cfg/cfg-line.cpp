//  self

    #include "cfg-line.h"


//  c++

    using namespace std;



CfgLine :: CfgLine ()
    : CfgLine ("", "")
{
}



CfgLine :: CfgLine (const string & ident, const string & value)
    : Ident (ident)
    , Value (value)
    , Active (true)
{
}



string CfgLine :: ReadIdent (istream & file)
{
    string str;
    int chr;

    while ((chr = file.peek()) != EOF && chr != '\n')
    {
        if (isspace (chr = file.get()))
        {
            if (str.empty())
                continue;
            else
                break;
        }
        str += chr;
    }

    return str;
}



string CfgLine :: ReadValue (istream & file)
{
    string str;
    int chr;
    bool space = false;

    Loop:
    switch (chr = file.get())
    {
        case EOF:
        case '\n':
            break;

        case ' ':
        case '\t':
            if (! str.empty())
                space = true;
            goto Loop;

        default:
            if (space)
            {
                space = false;
                str += ' ';
            }
            str += chr;
            goto Loop;

    }

    return str;
}



CfgLinePtr CfgLine :: make (istream & file)
{
    CfgLinePtr lineptr = make_shared <CfgLine> ();
    return file >> *lineptr ? lineptr : nullptr;
}



string CfgLine :: ident () const
{
    return Ident;
}



int CfgLine :: identLength () const
{
    return Active ? int (Ident.length()) : 0;
}



string CfgLine :: value() const
{
    return Value;
}



bool CfgLine :: active () const
{
    return Active;
}



bool CfgLine :: empty () const
{
    return Ident.empty() && Value.empty();
}



void CfgLine :: setValue (const string & value)
{
    Value = value;
}



void CfgLine :: remove ()
{
    Active = false;
}



void CfgLine :: scan (istream & file)
{
    Active = true;
    Ident = ReadIdent (file);
    Value = ReadValue (file);
}



void CfgLine :: print (ostream & file) const
{
    static const string space (5, ' ');
    file << Ident << space << Value;
}
