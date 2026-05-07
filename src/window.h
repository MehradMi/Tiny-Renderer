#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>

class Window {
  public:
    Window();
    Window(const char* title, int x, int y, int flags);
    Window(const char* title, int x, int y, int width, int height, int flags);

    int  getWidth()  { return m_width; }          // getter: get window width
    int  getHeight() { return m_height; }         // getter: get window height
    void setShouldClose(bool shouldClose);        // setter: set m_should_close for window
    bool getShouldClose();                        // getter: get m_should_close
    bool getFailBit();                            // getter: get fail_bit status
    SDL_Window* getSDLWindow();                   // getter: get m_window

  private:
    SDL_Window *m_window;                           // pointer to SDL window
    int m_flags;                                    // SDL window flags

    const char* m_win_title;                        // SDL window title
    int m_width, m_height;
    int m_posX,  m_posY;

    bool m_fail_bit;
    bool m_should_close;

    bool initialize_sdl();
    bool create_window();
    void set_fail_bit(bool isFailed);
};

#endif
