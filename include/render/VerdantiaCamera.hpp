#pragma once

#include <raylib.h>

class VerdantiaCamera {
public:
    VerdantiaCamera();
    ~VerdantiaCamera();

    void Update(Vector2 target);

    Camera2D& GetCamera() { return m_Camera;}

private:
    Vector2 m_Position = {0.0f, 0.0f};

    Camera2D m_Camera;

};