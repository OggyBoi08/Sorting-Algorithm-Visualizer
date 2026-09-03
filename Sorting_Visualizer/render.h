#include <string>
#include <cstdint>
#include <vector>
#ifndef RENDER_H
#define RENDER_H


struct SDL_Renderer;
struct SDL_Window;
struct SDL_Surface;

struct Bounds
{
    int window_w, window_h;
};

struct Rectangle
{
    float x,y,w,h;
};

class Renderer
{
public:
    SDL_Renderer* renderer;
    SDL_Window* window;

    Renderer(const char* name, int window_width, int window_height);

    uint64_t counter();
    uint64_t frequency();
    bool ProcessEvents();
    void clearBG(std::string hexColor);
    void present(int delay_ms);
    void setIcon(const char* icon);

    //drawing
    void draw_rectangle(Rectangle rectangle, const std::string& hex_color);
    void draw_sorted_graph(Bounds bound, int num_bars, const std::string& hex_color);
    void draw_array(Bounds bound,
                          const std::vector<int>& arr,
                          const std::string& hex_color1 = "#FFFFFF",
                          const std::string& hex_color2 = "#000000",
                          const std::string& hex_color3 = "#000000",
                          bool fill_solid = false,
                          const std::vector<bool>& sorted = {},
                          int cur_j = -1);
};




#endif // RENDER_H
