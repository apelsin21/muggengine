#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "guiobject.hpp"
#include "texture2d.hpp"

namespace mugg {
    namespace gui {
        class GUIManager;
        
        class Sprite : public GUIObject {
            private:
                bool positionChanged, uvChanged, colorChanged;
            
                glm::vec3 positionBottomLeft, positionTopLeft, positionBottomRight, positionTopRight;
                glm::vec2 uvBottomLeft, uvTopLeft, uvBottomRight, uvTopRight;
                glm::vec3 colorBottomLeft, colorTopLeft, colorBottomRight, colorTopRight;
            public:
                Sprite(mugg::gui::GUIManager*);
                ~Sprite();
        
                virtual bool IsPositionChanged();
                virtual bool IsUVChanged();
                virtual bool IsColorChanged();

                //-----------------------------------------
                //POSITIONS START
                virtual glm::vec3 GetBottomLeftPosition();
                virtual void SetBottomLeftPosition(const glm::vec3&);
                
                virtual glm::vec3 GetTopLeftPosition();
                virtual void SetTopLeftPosition(const glm::vec3&);
                
                virtual glm::vec3 GetBottomRightPosition();
                virtual void SetBottomRightPosition(const glm::vec3&);
                
                virtual glm::vec3 GetTopRightPosition();
                virtual void SetTopRightPosition(const glm::vec3&);
                //POSITIONS END
                //-----------------------------------------
                
                //-----------------------------------------
                //UVS START
                virtual glm::vec2 GetBottomLeftUV();
                virtual void SetBottomLeftUV(const glm::vec2&);
                
                virtual glm::vec2 GetTopLeftUV();
                virtual void SetTopLeftUV(const glm::vec2&);
                
                virtual glm::vec2 GetBottomRightUV();
                virtual void SetBottomRightUV(const glm::vec2&);
                
                virtual glm::vec2 GetTopRightUV();
                virtual void SetTopRightUV(const glm::vec2&);
                //UVS END
                //-----------------------------------------

                //-----------------------------------------
                //COLORS START
                virtual glm::vec3 GetBottomLeftColor();
                virtual void SetBottomLeftColor(const glm::vec3&);
                
                virtual glm::vec3 GetTopLeftColor();
                virtual void SetTopLeftColor(const glm::vec3&);
                
                virtual glm::vec3 GetBottomRightColor();
                virtual void SetBottomRightColor(const glm::vec3&);
                
                virtual glm::vec3 GetTopRightColor();
                virtual void SetTopRightColor(const glm::vec3&);
                //COLORS END
                //-----------------------------------------
        };
    }
}

#endif
