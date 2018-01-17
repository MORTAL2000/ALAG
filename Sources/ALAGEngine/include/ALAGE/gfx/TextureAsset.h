#ifndef TEXTUREASSET_H
#define TEXTUREASSET_H

#include "ALAGE/core/Asset.h"
#include <SFML/Graphics.hpp>

namespace alag
{

class TextureAsset : Asset
{
    public:
        TextureAsset();
        virtual ~TextureAsset();

        bool LoadFromFile(const std::string&);

    protected:

    private:
        sf::Texture m_texture;
};

}

#endif // TEXTUREASSET_H