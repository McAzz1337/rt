#ifndef PERMUTATION_H_INCLUDED
#define PERMUTATION_H_INCLUDED



//  c++

    #include <vector>



class Permutation
{
        int Size;
        int Count;
        std::vector <int> Data;


    public:

        Permutation (int size, bool perm);

        bool valid () const;
        int next ();
};



#endif
