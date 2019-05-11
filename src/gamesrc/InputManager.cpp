#include "include/InputManager.hpp"

namespace cgf

{

InputManager InputManager::m_InputManager;

void InputManager::addKeyInput(sf::String name, sf::Keyboard::Key keyCode)
{
    MyKeys key;
    key.myInputType = KeyboardInput;
    key.myKeyCode   = keyCode;
    keys[name] = key;
}

bool InputManager::testEvent(sf::String name)
{
    mapT::iterator it = keys.find(name);
    if(it == keys.end())
        return false; // no such binding

    // Get iterator contents
    MyKeys k = it->second;

    // Keyboard event
    if (k.myInputType == KeyboardInput &&
        sf::Keyboard::isKeyPressed(k.myKeyCode))
            return true;

    // Binding type doesn't match
    return false;
}

} // namespace
