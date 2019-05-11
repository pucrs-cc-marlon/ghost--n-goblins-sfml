#ifndef CGF_INPUT_MANAGER_H
#define CGF_INPUT_MANAGER_H

// Input Manager for keyboard, mouse and joystick global inputs
//
// Based on original code at https://github.com/LaurentGomila/SFML/wiki/Tutorial%3A-Manage-dynamic-key-binding
//

#include <map>
#include <SFML/Graphics.hpp>

namespace cgf
{

class InputManager
{
public:

    enum InputType
    {
        KeyboardInput,
    };

    // Implement Singleton Pattern
    static InputManager* instance()
    {
        return &m_InputManager;
    }

    void addKeyInput(sf::String name, sf::Keyboard::Key keyCode);
    bool testEvent(sf::String name);

    protected:

    InputManager() {}

private:

    struct MyKeys
    {
        InputType myInputType;
        sf::Keyboard::Key myKeyCode;
    };

    typedef std::map<std::string,MyKeys>  mapT;
    mapT keys;

    static InputManager m_InputManager;
};

} // namespace

#endif // INPUT_MANAGER_H
