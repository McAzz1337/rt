#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED



//  c++

    #include <memory>



class SingletonBase
{
    protected:

        static void Check (void * ptr);
};



template <class T>
class Singleton
    : public SingletonBase
{
        static std::shared_ptr <T> InstPtr;


    public:

        static std::shared_ptr <T> instptr ()
        {
            if (InstPtr == nullptr)
                Check ((InstPtr = std::make_shared <T> ()) .get());
            return InstPtr;
        }
};



template <class T>
std::shared_ptr <T> Singleton <T> :: InstPtr = nullptr;



#endif
