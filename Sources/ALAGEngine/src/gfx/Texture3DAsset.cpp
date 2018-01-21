#include "ALAGE/core/AssetHandler.h"
#include "ALAGE/gfx/Texture3DAsset.h"
#include "ALAGE/utils/Parser.h"
#include "ALAGE/utils/Logger.h"
#include <istream>

namespace alag
{

Texture3DAsset::Texture3DAsset()
{
    m_allowLoadFromFile = true;
    m_allowLoadFromMemory = false;
    m_allowLoadFromStream = false;

    m_default_height = 0;

    m_colorMap  = nullptr;
    m_normalMap = nullptr;
    m_heightMap = nullptr;
}

Texture3DAsset::~Texture3DAsset()
{
    //dtor
}


bool Texture3DAsset::LoadNow()
{
    bool loaded = true;

    if(m_loadSource == LoadSourceFile)
    {
        TiXmlDocument file(m_filePath.c_str());

        if(!file.LoadFile())
        {
            Logger::Error("Cannot load texture3D from file: "+m_filePath);
            std::ostringstream errorReport;
            errorReport << "Because: "<<file.ErrorDesc();
            Logger::Error(errorReport);
            loaded = false;
        } else {
            TiXmlHandle hdl(&file);
            hdl = hdl.FirstChildElement();
            loaded = LoadFromXML(&hdl);
        }

        if(loaded)
            Logger::Write("Texture3D loaded from file: "+m_filePath);

    } else {
        Logger::Error("Cannot load asset");
        loaded = false;
    }

    m_loaded = loaded;
    return (m_loaded);
}

bool Texture3DAsset::LoadFromXML(TiXmlHandle *hdl)
{
    if(hdl == nullptr) return (false);

    if(hdl->FirstChildElement("name").Element() != nullptr)
        m_name = hdl->FirstChildElement("name").Element()->GetText();

    if(hdl->FirstChildElement("height").Element() != nullptr)
        m_default_height = Parser::ParseInt(hdl->FirstChildElement("height").Element()->GetText());

    TiXmlElement* textElem = hdl->FirstChildElement("texture").Element();
    while(textElem != nullptr)
    {
        if(std::string(textElem->Attribute("type")).compare("color") == 0)
            m_colorMap = AssetHandler<TextureAsset>::Instance()
                            ->LoadAssetFromFile(m_fileDirectory+textElem->GetText(),m_loadType);
        else if(std::string(textElem->Attribute("type")).compare("normal") == 0)
            m_normalMap = AssetHandler<TextureAsset>::Instance()
                            ->LoadAssetFromFile(m_fileDirectory+textElem->GetText(),m_loadType);
        else if(std::string(textElem->Attribute("type")).compare("depth") == 0)
            m_heightMap = AssetHandler<TextureAsset>::Instance()
                            ->LoadAssetFromFile(m_fileDirectory+textElem->GetText(),m_loadType);
        textElem = textElem->NextSiblingElement("texture");
    }

    return (true);
}


const sf::Texture& Texture3DAsset::GetTexture()
{
    return GetColorMap();
}

const sf::Texture& Texture3DAsset::GetColorMap()
{
    if(m_loaded && m_colorMap != nullptr)
        return m_colorMap->GetTexture();
    return (emptyTexture);
}

const sf::Texture& Texture3DAsset::GetNormalMap()
{
    if(m_loaded && m_normalMap != nullptr)
        return m_normalMap->GetTexture();
    return (emptyTexture);
}

const sf::Texture& Texture3DAsset::GetHeightMap()
{
    if(m_loaded && m_heightMap != nullptr)
        return m_heightMap->GetTexture();
    return (emptyTexture);
}


}