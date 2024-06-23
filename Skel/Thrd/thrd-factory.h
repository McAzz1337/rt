#ifndef THRD_FACTORY_H_INCLUDED
#define THRD_FACTORY_H_INCLUDED



//  app

    #include "thrd-ptr.h"



class ThrdFactoryBase;

typedef std::shared_ptr <ThrdFactoryBase> ThrdFactoryBasePtr;



class ThrdFactoryBase
{
    protected:

    static ThrdFactoryBasePtr InstancePtr;
        virtual ThrdPtr Make () = 0;


    public:

        static ThrdPtr make ();
};



template <class T>
class ThrdFactoryTmpl
    : public ThrdFactoryBase
{
    protected:

    virtual ThrdPtr Make () override
        {
            return std::make_shared <T> ();
        }


    public:

        static ThrdFactoryBasePtr construct ()
        {
            ThrdFactoryBase::InstancePtr
                = std::make_shared <ThrdFactoryTmpl <T>> ();
            return InstancePtr;
        }
};



#endif
