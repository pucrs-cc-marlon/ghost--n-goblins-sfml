/*
* Nome: Marlon Baptista de Quadros
*/
#ifndef CGF_TEXTUREMANAGER_H
#define CGF_TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace cgf{

class TextureManager
{
    private:
        static TextureManager m_TextureManager;
        std::map<std::string, sf::Texture*> imgs;
        std::string defaultImageDir;            // base dir to load images from

    public:
        virtual ~TextureManager();
        sf::Texture* findTexture(char* nomeArq);
        void setDefaultImageDir(char* dir);
        void releaseTexture(char* nomeArq);
        static TextureManager * getInstance ()
        {
            return & m_TextureManager;
        }

    protected:

        TextureManager ();
};

} // namespace cgf

#endif // CGF_TEXTUREMANAGER_H
