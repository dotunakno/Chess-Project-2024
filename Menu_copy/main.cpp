#include "menu.h"
#include "game.h"
#include "pause.h"
#include "settings.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "My Chess Game");

    std::shared_ptr<State> menuState        = std::make_shared<Menu>();
    std::shared_ptr<State> gameState        = std::make_shared<Game>();
    std::shared_ptr<State> pauseState       = std::make_shared<Pause>();
    std::shared_ptr<State> settingsState    = std::make_shared<Settings>();

    std::shared_ptr<State> curState = menuState;

    while (window.isOpen()) {
        // UPDATE CURRENT STATE
        curState->update(window);

        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) window.close();
            curState->handleInput(window, event);
        }

        // DISPLAY CURRENT STATE
        curState->render(window);

        // SWITCH BETWEEN STATES
        if (curState->stateSwitch)
        {
            style curStyle = curState->curStyle;
            switch (curState->newState)
            {
                case (MENU):
                    curState = menuState;
                    break;
                case (GAME):
                    curState = gameState;
                    break;
                case (PAUSE):
                    curState = pauseState;
                    break;
                case (SETTINGS):
                    curState = settingsState;
                    break;
                default:
                    break;
            }
            curState->stateSwitch = 0;
            curState->curStyle = curStyle;
        }
    }

    return 0;
}