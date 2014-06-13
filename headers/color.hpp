#ifndef COLOR_HPP
#define COLOR_HPP

namespace mugg {
    namespace graphics {
        class Color {
            public:
                float r,g,b,a;

                Color(float r, float g, float b, float a);
                Color();
                
                void Set(Color color);
                void Set(float r, float g, float b, float a);

                void Clamp();
        };
    }
}

#endif
