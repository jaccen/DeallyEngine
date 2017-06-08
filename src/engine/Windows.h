#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "FrameBuffer.h"

class Window
{
public:
    Window(const char* name, int width = 1024, int height = 768);
    virtual ~Window();
    void update(float dt);
    void render();
    void clear();
    bool closed();
    void close();

    void setfbo(bool isfbo);
    int GetWidth()
    {
        return _width;
    }
    int GetHeight()
    {
        return _height;
    }
    //将结构化数据封装
    //
private:
    bool init();
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void resizeHandler(GLFWwindow *window, int width, int height);
private:
    const char* _name = nullptr;
    int _width, _height;
    GLFWwindow* _window = nullptr;
    FrameBuffer m_fbo;
    bool m_isfbo;//是否开启fbo
    int m_fps = 0;
};



#endif //ENGINE_WINDOW_H
