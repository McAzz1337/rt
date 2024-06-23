//  self

    #include "permutation.h"


//  c++

    #include <algorithm>
    #include <chrono>
    #include <numeric>
    #include <random>

    using namespace std;
    using namespace std::chrono;



Permutation :: Permutation (int size, bool perm)
    : Size (size)
    , Count (0)
    , Data (size)
{
    iota (Data.begin(), Data.end(), 0);

    if (perm)
    {
        auto seed = system_clock::now() .time_since_epoch() .count();
        default_random_engine rand ((unsigned) seed);
        shuffle (Data.begin(), Data.end(), rand);
    }
}



bool Permutation :: valid () const
{
    return Count < Size;
}



int Permutation :: next ()
{
    return Data [Count++];
}
