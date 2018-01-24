#ifndef TEXTUREASSET_H
#define TEXTUREASSET_H

#include "ALAGE/core/Asset.h"
#include <SFML/Graphics.hpp>

namespace alag
{

class TextureAsset : public Asset
{
    public:
        TextureAsset();
        TextureAsset(const AssetTypeID&);
        virtual ~TextureAsset();

        virtual bool LoadNow();

        virtual sf::Texture* GetTexture(LoadedAssetListener* = nullptr);

    protected:
        sf::Texture m_texture;

    private:
};

}

#endif // TEXTUREASSET_H
