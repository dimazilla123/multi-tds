#ifndef BATTLE_STATE
#define BATTLE_STATE

#include "game_state.h"
#include "game.h"

#include "ECS.h"

class BattleState : public GameState
{
public:
    BattleState(Game *g);
    ~BattleState();
    virtual void draw(float dt);
    virtual void update(float dt);
    virtual void handleInput();
private:
    sf::View view;
    ECS::EntityId player = -1;
};

#endif