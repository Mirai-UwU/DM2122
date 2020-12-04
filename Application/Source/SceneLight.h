#ifndef SCENE_LIGHT_H
#define SCENE_LIGHT_H

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneLight : public Scene {

    enum GEOMETRY_TYPE {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_SPHERE,
        GEO_SPHERE1,
        GEO_SPHERE2,
        GEO_SPHERE3,
        GEO_SPHERE4,
        GEO_SPHERE5,
        GEO_SPHERE6,
        GEO_SPHERE7,
        GEO_SPHERE8,
        GEO_LIGHTBALL,
        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHTENABLED,
        U_TOTAL,
    };

public:
    SceneLight();
    ~SceneLight();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void RenderMesh(Mesh* mesh, bool enableLight);
    virtual void Exit();

private:

    float rotateAngle;
    float translateX;
    float scaleAll;

    Camera2 camera;
    Mesh* meshList[NUM_GEOMETRY];
    MS modelStack, viewStack, projectionStack;
    unsigned m_vertexArrayID;
    unsigned m_parameters[U_TOTAL];
    unsigned m_programID;
    Light light[1];


};

#endif