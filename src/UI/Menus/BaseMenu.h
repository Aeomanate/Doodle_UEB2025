#ifndef BASEMENU_H
#define BASEMENU_H

#include "3rd-party/Framework.h"
#include "Application/Details/Updatable.h"
#include "EventsHandling/ListenersEmitters.h"

class BaseMenu: public Updatable
{
public:
    BaseMenu();

public: // Update interface
    bool Update(float dt) override;

public: // Emitters
    SIMPLE_EMITTER(CloseRequest);

protected: // Listeners
    DATA_LISTENER(KeyPressed, FRKey);


private:
};


#endif //BASEMENU_H
