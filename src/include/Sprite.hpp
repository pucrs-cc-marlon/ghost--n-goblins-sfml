/*
* Nome: Marlon Baptista de Quadros
*/

#ifndef CGF_SPRITE_H
#define CGF_SPRITE_H

#include <vector>
#include <map>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "TextureManager.hpp"

namespace cgf{

class Sprite : public sf::Drawable, public sf::Transformable
{
public:
    Sprite();
    virtual ~Sprite();

    bool load(char filename[]);
    bool load(char filename[], int w, int h, int hSpace, int vSpace, int xIni, int yIni,
                int column, int row, int total);
    bool loadXML(char filename[]);
    bool loadAnimation(char filename[]);

    void setVisible(bool vis) { visible = vis; }
    bool isVisible() { return visible; }

    // Mirroring (X-axis)
    void setMirror(bool mirror) { this->mirror = mirror; }
    bool getMirror() { return mirror; }

    // Sprite speed
    void setXspeed(double xspeed);
    void setYspeed(double yspeed);
    double getXspeed() { return xspeed; }
    double getYspeed() { return yspeed; }

    sf::Vector2u getSize() { return sf::Vector2u(spriteW, spriteH); }

    void update(double deltaTime, bool updatePos=true);
    void updateRect();

    // Basic collision checking
    bool bboxCollision(Sprite& other);
    bool circleCollision(Sprite& other);

private:

    static TextureManager* tm;

    // Rendering
    const sf::Texture* tex;
    sf::IntRect rect;
    sf::Vertex vertices[4];
    int spriteW, spriteH;       // width and height of a single sprite frame
    bool visible;
    bool mirror;

    // Motion
    double xspeed,yspeed;       // speed in pixels/s
    int updateCount;            // current count of updates

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

} // namespace cgf

#endif // CGF_SPRITE_H
