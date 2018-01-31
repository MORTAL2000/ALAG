#ifndef ISORECT_H
#define ISORECT_H

#include <ALAGE/gfx/RectEntity.h>

namespace alag
{

class IsometricScene;

class IsoRectEntity : public RectEntity
{
    friend class IsometricScene;

    public:
        IsoRectEntity();
        IsoRectEntity(sf::Vector2f rectSize);
        virtual ~IsoRectEntity();

        virtual void PrepareShader(sf::Shader *);

    protected:
        void SetIsoScene(IsometricScene *scene);

    private:
        IsometricScene *m_scene;
};

}

#endif // ISORECT_H
