//  self

    #include "cfg-file.h"


//  app

    #include "cfg-line.h"
    #include "cfg-map.h"


//  c++

    #include <algorithm>
    #include <iomanip>
    #include <fstream>
    #include <sstream>

    using namespace std;


std::string CfgFile::DefaultContents = R"(
    geometry
    maximized

    image-width
    image-height

    thread-count
    lines-per-thread
    permute-lines

    show-canvas
    update-ms

    image-directory
)";



int CfgFile :: IdentMaxLen () const
{
    int maxlen = 0;
    for_each (LinePtrs.begin(), LinePtrs.end(), [& maxlen] (CfgLinePtr lp)
        { maxlen = max (maxlen, lp->identLength()); });
    return maxlen;
}



void CfgFile :: read (istream & file)
{
    LinePtrs.clear();
    CfgLinePtr lineptr;
    while ((lineptr = CfgLine::make (file)) != nullptr)
        LinePtrs.push_back (lineptr);
}



void CfgFile :: write (ostream & file)
{
    int n = int (LinePtrs.size());

    int i;
    for (i = 0; i < n; ++i)
        if (! LinePtrs [i] -> empty())
            break;

    int k = 0;
    for (k = n - 1; k >= 0; --k)
        if (! LinePtrs [k] -> empty())
            break;
    ++k;

    auto width = setw (IdentMaxLen() + 2);
    auto bak = file.flags();
    file.setf (ios::left, ios::adjustfield);
    for (int j = i; j < k; ++j)
    {
        const CfgLine & line = * LinePtrs [j];
        if (line.active() || line.empty())
            file << width << line << endl;
    }
    file.setf (bak, ios::adjustfield);
}



void CfgFile :: read (const string & filename)
{
    ifstream file (filename);
    if (file.good())
    {
        read (file);
        return;
    }

    istringstream sfile (DefaultContents);
    read (sfile);
}



void CfgFile :: write (const string & filename)
{
    ofstream file (filename);
    write (file);
}



CfgLinePtr CfgFile :: append (const string & ident, const string & value)
{
    CfgLinePtr lineptr = make_shared <CfgLine> (ident, value);
    LinePtrs.push_back (lineptr);
    return lineptr;
}



void CfgFile :: makeMap (CfgMap & map) const
{
    for (const auto & iter: LinePtrs)
        if (! iter->empty())
        {
            CfgLinePtr lineptr = map.find (iter->ident());
            if (lineptr)
                lineptr->remove();
            map.store (iter);
        }
}
