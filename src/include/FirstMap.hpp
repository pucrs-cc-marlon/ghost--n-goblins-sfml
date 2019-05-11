#ifndef PLAY_PHYSICS_H_
#define PLAY_PHYSICS_H_

#include "GameState.hpp"
#include "InputManager.hpp"
#include "Sprite.hpp"
#include "Player.hpp"

namespace cgf
{
    class FirstMap : public cgf::GameState
    {
        public:
            void init(cgf::Game* game);
            void cleanup();

            void pause();
            void resume();

            void handleEvents(cgf::Game* game);
            void update(cgf::Game* game);
            void draw(cgf::Game* game);

            // Implement Singleton Pattern
            static FirstMap* instance()
            {
                return &m_FirstMap;
            }

        protected:
            FirstMap() {}

        private:
            static FirstMap m_FirstMap;

            cgf::InputManager* im;

            Player* player;
            int x, y;
            int dirx, diry;

            cgf::Sprite background;
            cgf::Sprite ball;

            sf::RenderWindow* window;
            sf::Font font;
            sf::Text text;

    };
}
#endif
