#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "texture2d.hpp"
#include "color.hpp"

#include <iostream>
#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace mugg {
    namespace gui {
        class Image {
            private:
                mugg::graphics::Texture2D texture;
                mugg::graphics::Color color;

                glm::vec2 position;
                glm::vec2 resolution;
                bool hasValidTexture;
                
                int begin, end;
            public:
                Image();
                Image(mugg::graphics::Texture2D);
                Image(double, double);
                Image(double, double, mugg::graphics::Texture2D);
                ~Image();

                void SetY(double);
                void SetX(double);
                void SetXY(double, double);
        
                void SetWidth(int);
                void SetHeight(int);
                void SetResolution(int, int);

                int GetWidth();
                int GetHeight();

                double GetY();
                double GetX();

                void SetBegin(int);
                void SetEnd(int);

                int GetBegin();
                int GetEnd();

                void SetTexture(mugg::graphics::Texture2D);
                mugg::graphics::Texture2D GetTexture();

                void SetColor(mugg::graphics::Color);
                mugg::graphics::Color GetColor();
        };
    }
}

#endif
