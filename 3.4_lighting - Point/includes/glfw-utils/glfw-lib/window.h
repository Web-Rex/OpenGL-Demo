#pragma once


class Window
{
private:
    int _buffer_width, _buffer_height;

    static void Handle_Keys(GLFWwindow *window, int key, int code, int action, int mode);
    static void Handle_Resize(GLFWwindow* window, int width, int height);
    static void Handle_Mouse(GLFWwindow* window, double x_posIn, double y_posIn);
    static void Handle_Scroll(GLFWwindow* window, double x_offset, double y_offset);

public:
    Window();
    ~Window();

    bool Get_Window_Should_Close();
    void Swap_Buffers();
    void Set_CallBack();

    void Close_Window();

    float Get_Width() const { return static_cast<float>(_buffer_width); }
    float Get_Height() const { return static_cast<float>(_buffer_height); }
};