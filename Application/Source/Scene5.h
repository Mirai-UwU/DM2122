#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Scene5 : public Scene {

    enum UNIFORM_TYPE {
        U_MVP = 0,
        U_TOTAL,
    };

    enum GEOMETRY_TYPE {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_SPHERE,
        NUM_GEOMETRY,
    };

public:
    Scene5();
    ~Scene5();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

private:

    float rotateAngle;
    float translateX;
    float scaleAll;

    Camera camera;
    Mesh* meshList[NUM_GEOMETRY];
    MS modelStack, viewStack, projectionStack;
    unsigned m_vertexArrayID;
    unsigned m_parameters[U_TOTAL];
    unsigned m_programID;
};

#endif