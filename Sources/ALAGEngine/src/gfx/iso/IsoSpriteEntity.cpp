#include "ALAGE/gfx/SceneNode.h"
#include "ALAGE/gfx/iso/IsoSpriteEntity.h"
#include "ALAGE/core/AssetHandler.h"
#include "ALAGE/utils/Mathematics.h"

namespace alag
{

IsoSpriteEntity::IsoSpriteEntity() : IsoSpriteEntity(sf::IntRect (0,0,0,0))
{
}

IsoSpriteEntity::IsoSpriteEntity(const sf::Vector2i &v) : IsoSpriteEntity(sf::IntRect (0,0,v.x, v.y))
{
}

IsoSpriteEntity::IsoSpriteEntity(const sf::IntRect &r) : SpriteEntity(r)
{
    m_isoToCartZFactor = 1;
}


IsoSpriteEntity::~IsoSpriteEntity()
{
    //dtor
}


void IsoSpriteEntity::PrepareShader(sf::Shader* shader)
{
    SpriteEntity::PrepareShader(shader);

    if(!Is3D())
    {
        shader->setUniform("useNormalMap", false);
        shader->setUniform("depthMap",*AssetHandler<TextureAsset>::Instance()->LoadAssetFromFile("../data/heightmap.png")->GetTexture());
        shader->setUniform("useDepthMap",true);
        shader->setUniform("height",(-(float)sf::Sprite::getTextureRect().height*(float)getScale().y)/m_isoToCartZFactor);
    }

    shader->setUniform("normalProjMatInv",sf::Glsl::Mat3(IdMat3X3));
}

void IsoSpriteEntity::ComputeShadow(Light* light)
{
    if(light != nullptr && light->GetParentNode() != nullptr
     &&GetParentNode() != nullptr)
    {
        if(light->GetType() == DirectionnalLight
            && (GetShadowCastingType() == DirectionnalShadow || GetShadowCastingType() == AllShadows))
        {
            sf::Vector3f lightDirection = light->GetDirection();
            sf::Vector3f casterPos = GetParentNode()->GetGlobalPosition();

            sf::Texture* shadowTexture = &m_shadowMap[light];
            m_shadowSprite[light].setTexture(*shadowTexture);
        }

        AddToLightList(light);
    }
}

void IsoSpriteEntity::SetIsoToCartZFactor(float factor)
{
    m_isoToCartZFactor = factor;
}


}