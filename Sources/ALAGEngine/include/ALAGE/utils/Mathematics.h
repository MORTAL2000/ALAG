#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "ALAGE/Types.h"

#define PI 3.14159265359

const GLfloat IdMat3X3[9] = {1,0,0,0,1,0,0,0,1};

float ComputeDotProduct(sf::Vector3f v, sf::Vector3f w);
float ComputeDotProduct(sf::Vector2f v, sf::Vector2f w);
float ComputeSquareDistance(sf::Vector3f v, sf::Vector3f w);
float ComputeSquareDistance(sf::Vector2f v, sf::Vector2f w);

float LinInterp(sf::Vector2f left, float p, sf::Vector2f right);
int RandomNumber(int maxNbr, int seed = 0);

/*struct WaveParticle
{
    float height;
    sf::Vector2f velocity;
    float foam;
};*/
void GenerateGerstnerWave(sf::Glsl::Vec4 *particles, float *xDistribution, size_t tab_size, float steepness, float wave_length);
void GenerateGerstnerWave(sf::Glsl::Vec4 *tab, float *xDistribution, size_t tab_size,
                          float left_steepness, float right_steepness, float nbr_waves, float t);
//void GenerateGerstnerWave(WaveParticle *tab, size_t tab_size, float steepness, float wave_length);

float Abs(float a);
sf::Vector2f Normalize(sf::Vector2f v);
sf::Vector3f Normalize(sf::Vector3f v);

void SfColorToGlColor(const sf::Color&, float glColor[4]);

namespace alag {

struct Box
{
    sf::Vector3f position;
    sf::Vector3f size;
};

class Mat2x2
{
    public:
        Mat2x2();
        Mat2x2(sf::Vector2f u, sf::Vector2f v);
        Mat2x2( float, float,
                float, float);

        ~Mat2x2();

        Mat2x2 operator+(Mat2x2 const& m);
        Mat2x2 operator*(Mat2x2 const& m);
        Mat2x2 operator*(float const& k);
        sf::Vector2f operator*(sf::Vector2f const& v);

        GLfloat values[4];
};


class Mat3x3
{
    public:
        Mat3x3();
        Mat3x3(sf::Vector3f u, sf::Vector3f v, sf::Vector3f w);
        Mat3x3( float, float, float,
                float, float, float,
                float, float, float);
        Mat3x3(const float v[9]);

        ~Mat3x3();

        Mat3x3 operator+(Mat3x3 const& m);
        Mat3x3 operator*(Mat3x3 const& m);
        Mat3x3 operator*(float const& k);
        sf::Vector3f operator*(sf::Vector3f const& v) const;
        sf::Vector2f operator*(sf::Vector2f const& v) const;

        GLfloat values[9];
};

}


#endif // MATHEMATICS_H
