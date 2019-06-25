/*
* Nome: Marlon Baptista de Quadros
*/
#include "include/Sprite.hpp"
#include "include/tinyxml2.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
using namespace tinyxml2;

namespace cgf{

    TextureManager* Sprite::tm = TextureManager::getInstance();

    // Construtor
    Sprite::Sprite()
    {
        mirror = false;
        visible = true;
        // Init animation vars
        xspeed = 0;
        yspeed = 0;
    }

    bool Sprite::load(char filename[])
    {
        tex = tm->findTexture(filename);
        if(tex == NULL)
            return false;

        spriteW = tex->getSize().x;
        spriteH = tex->getSize().y;

        // Add a single frame as the whole image
        rect.left = 0;
        rect.width = spriteW;
        rect.top = 0;
        rect.height = spriteH;
        cout << "image: " << rect.left << "," << rect.top
            << " - " << rect.width << "x" << rect.height << endl;
        updateRect();
        return true;
    }

    bool Sprite::loadAnimation(char filename[]){
        XMLDocument doc;
        doc.LoadFile(filename);

        const char* name = "";

        int start = 0;
        int end = 0;
        bool loop = false;
        const char* seqName = "";

        XMLElement* element = doc.FirstChildElement( "animation" );
        element->QueryStringAttribute("name", &name);
        animationName = name;

        printf("Animation Name: %s \n", name);

        int cont = 0;

        for(const XMLElement* node=element->FirstChildElement(); node; node=node->NextSiblingElement()){
            AnimAttributes animAttr;
            node->QueryStringAttribute("name", &seqName);
            node->QueryAttribute("start", &start);
            node->QueryAttribute("end", &end);
            node->QueryAttribute("loop", &loop);

            animAttr.name = seqName;
            animAttr.start = start;
            animAttr.end = end;
            animAttr.loop = loop;

            animations[seqName] = animAttr;

            printf( "Name: %s - Attributes start: %d - end: %d - loop: %d \n",
                        animations[seqName].name,
                        animations[seqName].start,
                        animations[seqName].end,
                        animations[seqName].loop );
            cont++;
        }
        return true;
    }

    bool Sprite::loadXML(char filename[]){
        XMLDocument doc;
        doc.LoadFile(filename);

        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        int sprite_width = 0;
        int sprite_height = 0;
        const char* name = "";
        const char* image_path = "";

        XMLElement* element = doc.FirstChildElement( "TextureAtlas" );
        element->QueryStringAttribute("imagePath", &image_path);
        element->QueryAttribute("width", &sprite_width);
        element->QueryAttribute("height", &sprite_height);

        printf("File: %s - Width: %d - Height: %d \n", image_path, sprite_width, sprite_height);

        int cont = 0;

        for(const XMLElement* node=element->FirstChildElement(); node; node=node->NextSiblingElement()){
            SpriteAttributes spriteAttr;
            node->QueryStringAttribute("n", &name);
            node->QueryAttribute("x", &x);
            node->QueryAttribute("y", &y);
            node->QueryAttribute("w", &w);
            node->QueryAttribute("h", &h);
            spriteAttr.x = x;
            spriteAttr.y = y;
            spriteAttr.width = w;
            spriteAttr.height = h;
            spritesAttr.push_back(spriteAttr);
            printf( "Name: %s - Attributes x: %d - y: %d - w: %d - h: %d \n",
                        name,
                        spritesAttr[cont].x,
                        spritesAttr[cont].y,
                        spritesAttr[cont].width,
                        spritesAttr[cont].height );
            cont++;
        }
        return true;
    }

    Sprite::~Sprite()
    {
        //dtor
    }

    // Sets speed for the X axis (pixels/second)
    void Sprite::setXspeed(double xspeed)
    {
        this->xspeed = xspeed;
    }

    // Sets speed for the Y axis (pixels/second)
    void Sprite::setYspeed(double yspeed)
    {
        this->yspeed = yspeed;
    }

    // Sets the current frame
    void Sprite::updateRect()
    {
        vertices[0].position = sf::Vector2f(0, 0);
        vertices[1].position = sf::Vector2f(0, rect.height);
        vertices[2].position = sf::Vector2f(rect.width, rect.height);
        vertices[3].position = sf::Vector2f(rect.width, 0);

        float left = static_cast<float>(rect.left) + 0.0001;
        float right = left + rect.width;
        float top = static_cast<float>(rect.top);
        float bottom = top + rect.height;

        if(mirror) {
            float tmp = left;
            left = right;
            right = tmp;
        }

        vertices[0].texCoords = sf::Vector2f(left, top);
        vertices[1].texCoords = sf::Vector2f(left, bottom);
        vertices[2].texCoords = sf::Vector2f(right, bottom);
        vertices[3].texCoords = sf::Vector2f(right, top);

        spriteW = rect.width;
        spriteH = rect.height;
    }

    // Updates position according to time
    void Sprite::update(double deltaTime, bool updatePos)
    {
        if(updatePos) {
            // Move sprite according to its speed and the amount of time that has passed
            sf::Vector2f offset(xspeed/1000 * deltaTime, yspeed/1000 * deltaTime);
            move(offset);
        }
    }

    // Check bounding box collision between this and other sprite
    bool Sprite::bboxCollision(Sprite& other)
    {
        sf::Vector2f pos = this->getPosition();
        sf::Vector2f scale = this->getScale();

        float scalex2 = other.getScale().x;
        float scaley2 = other.getScale().y;

        float px2 = other.getPosition().x;
        float py2 = other.getPosition().y;

        float width1 = this->spriteW/2 * scale.x;
        float width2 = other.spriteW/2 * scalex2;

        float height1 = this->spriteH/2 * scale.y;
        float height2 = other.spriteH/2 * scaley2;

        float x0 = pos.x - width1;
        float y0 = pos.y - height1;
        float x1 = pos.x + width1;
        float y1 = pos.y + height1;

        float x2 = px2 - width2;
        float y2 = py2 - height2;
        float x3 = px2 + width2;
        float y3 = py2 + height2;

        return !(x1<x2 || x3<x0 || y1<y2 || y3<y0);
    }

    // Check circle collision between this and other sprite
    bool Sprite::circleCollision(Sprite& other)
    {
        int radius1 = max(this->spriteW, this->spriteH)/2;
        int radius2 = max(other.spriteW, other.spriteW)/2;
        radius1 *= this->getScale().x;
        radius2 *= other.getScale().y;
        float px1 = this->getPosition().x;
        float px2 = other.getPosition().x;
        float py1 = this->getPosition().y;
        float py2 = other.getPosition().y;
        float dist = sqrt(pow(px1 - px2, 2) + pow(py1 - py2, 2));
        //cout << "Radius: " << radius1 << " and " << radius2 << endl;
        //cout << "distance: " << dist << endl;
        return (dist < radius1 + radius2);
    }

    void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (tex && visible)
        {
            states.transform *= getTransform();
            states.texture = tex;
            target.draw(vertices, 4, sf::Quads, states);
        }
    }

} // namespace cgf
