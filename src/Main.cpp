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

        // sf::Event event;
        // while (game.getWindow()->pollEvent(event))
        // {
        //     if (event.type == sf::Event::Closed)
        //         game.close();
        //     if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		// 	    game.close();
        // }

        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        //     float xPos = shape.getGlobalBounds().width + shape.getPosition().x;
        //     if( xPos <= (float) game.getWindow()->getSize().x)
                // shape.move(0.5f, 0.f);
		// }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        //     if(shape.getPosition().x >= 0)
        //         shape.move(-0.5f, 0.f);
		// }

        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        //     float yPos = shape.getGlobalBounds().height + shape.getPosition().y;
        //     if( yPos <= (float) game.getWindow()->getSize().y)
        //         shape.move(0.f, 0.5f);
		// }
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        //     if(shape.getPosition().y >= 0)
        //         shape.move(0.f, -0.5f);
		// }

        game.handleEvents();
		game.update();
		game.draw();
    }
    game.clean();
    return 0;
}
