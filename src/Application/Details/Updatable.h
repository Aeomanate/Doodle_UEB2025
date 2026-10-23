#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
public:
    virtual bool Update(float dt) = 0;
    virtual ~Updatable() = default;
};

#endif //UPDATABLE_H
