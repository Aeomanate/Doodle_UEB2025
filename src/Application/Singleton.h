#ifndef SINGLETON_H
#define SINGLETON_H


template<class Derived>
class Singleton
{
public:
    static Derived& GetInstance()
    {
        static Derived instance;

        return instance;
    }


protected:
    Singleton() = default;
};

#endif //SINGLETON_H
