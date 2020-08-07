#ifndef BATTLE_STATE
#define BATTLE_STATE

#include "game_state.h"
#include "game.h"

#include "ECS.h"

#include <vector>
#include <unordered_map>

class BattleState : public GameState
{
public:
    BattleState(Game *g);
    ~BattleState();
    virtual void draw(float dt);
    virtual void update(float dt);
    virtual void handleInput(float dt);

    void loadTextures();
    void writeMessage(const std::string &s, const sf::Color c=sf::Color::Green);
private:
    sf::View view;
    ECS::EntityId player = -1;
    ECS::EntityManager Entities;
    sf::Vector2f direction = sf::Vector2f(0, 1);

    sf::Font font;
    sf::Text message;

    std::unordered_map<sf::Keyboard::Key, bool> is_pressed;

    std::vector<ECS::System*> systems;
};

#endif