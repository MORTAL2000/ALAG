#include "ALAGE/gfx/Light.h"
#include "ALAGE/gfx/ShadowCaster.h"

namespace alag
{

Light::Light()
{
    m_isALight = true;
    m_direction = sf::Vector3f(0,0,-1);
    m_diffuseColor = sf::Color::White;
    m_specularColor = sf::Color::White;
    m_constantAttenuation = 1;
    m_linearAttenuation = 0;
    m_quadraticAttenuation = 0;
    m_castShadow = false;
    m_requireShadowComputation = false;
}

Light::~Light()
{
    //dtor
}

LightType Light::GetType()
{
    return m_type;
}

sf::Vector3f Light::GetDirection()
{
    return m_direction;
}

sf::Color Light::GetDiffuseColor()
{
    return m_diffuseColor;
}

sf::Color Light::GetSpecularColor()
{
    return m_specularColor;
}

float Light::GetConstantAttenuation()
{
    return m_constantAttenuation;
}

float Light::GetLinearAttenuation()
{
    return m_linearAttenuation;
}

float Light::GetQuadraticAttenuation()
{
    return m_quadraticAttenuation;
}

bool Light::IsCastShadowEnabled()
{
    return m_castShadow;
}


void Light::SetType(LightType type)
{
    m_type = type;
    m_requireShadowComputation = true;
}

void Light::SetDirection(sf::Vector3f direction)
{
    m_direction = direction;
    m_requireShadowComputation = true;
}

void Light::SetDiffuseColor(sf::Color color)
{
    m_diffuseColor = color;
}

void Light::SetSpecularColor(sf::Color color)
{
    m_specularColor = color;
}

void Light::SetConstantAttenuation(float constAtt)
{
    if(constAtt >= 1)
        m_constantAttenuation = constAtt;
}

void Light::SetLinearAttunation(float linAtt)
{
    m_linearAttenuation = linAtt;
}

void Light::SetQuadraticAttenuation(float quadAtt)
{
    m_quadraticAttenuation = quadAtt;
}

void Light::EnableShadowCasting()
{
    m_castShadow = true;
    m_requireShadowComputation = true;
}

void Light::DisableShadowCasting()
{
    m_castShadow = false;
}

std::list<ShadowCaster*> *Light::GetShadowCasterList()
{
    return &m_shadowCasterList;
}

void Light::UpdateShadow()
{
    std::list<ShadowCaster *>::iterator casterIt;
    for(casterIt = m_shadowCasterList.begin() ; casterIt != m_shadowCasterList.end() ; ++casterIt)
    if(m_requireShadowComputation || (*casterIt)->IsRequiringShadowCasting(this))
    {
        (*casterIt)->ComputeShadow(this);
    }
}

}