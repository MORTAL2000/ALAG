#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <SFML/System.hpp>
#include <vector>
#include "GState.h"

namespace alag
{

class GApp;

class StateManager
{
    public:
        StateManager();
        virtual ~StateManager();

        void Switch(GState*);
        void Push(GState*);
        GState* Pop(); //Return new current state
        GState* Peek();

        void HandleEvents(alag::EventManager*);
        void Update(sf::Time);
        void Draw(sf::RenderTarget*);

        void AttachGApp(GApp*);
        GApp* GetGApp();

    protected:

    private:
        std::vector<GState*> m_states;
        GApp *m_parentGApp;
};

}

#endif // STATEMANAGER_H
