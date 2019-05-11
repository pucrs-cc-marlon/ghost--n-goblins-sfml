/*
* Nome: Marlon Baptista de Quadros
*/
#include "include/Game.hpp"
#include "include/FirstMap.hpp"

int main()
{
    std::cout << "Hello World Marlon!" << std::endl;

    cgf::Game game(5, 30);
    game.init("SFML works! Yeah!!", 800, 800, false);

    sf::CircleShape shape(game.getWindow()->getSize().x/4);

    shape.setFillColor(sf::Color::White);

    game.changeState(cgf::FirstMap::instance());

    while (game.isRunning())
    {
        game.handleEvents();
		game.update();
		game.draw();
    }
    game.clean();
    return 0;
}
