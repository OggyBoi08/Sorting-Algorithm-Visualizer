#include <cstdint>   //for uint_64
#include <string>
#include <vector>
#include <algorithm>
#include "utility.h"   //for hexToColour
#include "render.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

//SDL_Window* window = nullptr;
//SDL_Renderer* renderer = nullptr;

Renderer::Renderer(const char* name, int window_width, int window_height)
{
    window = SDL_CreateWindow(name,window_width,window_height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
}

bool Renderer::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            return false;
    }

    return true;
}

uint64_t Renderer::counter()
{
    return SDL_GetPerformanceCounter();
}
uint64_t Renderer::frequency()
{
    return SDL_GetPerformanceFrequency();
}
void Renderer::clearBG(std::string hexColor)
{
    Colour rgb = hexToColour(hexColor);
    SDL_SetRenderDrawColor(renderer,rgb.r, rgb.g, rgb.b, 255);  //background colour
    SDL_RenderClear(renderer);
}
void Renderer::present(int delay_ms)
{
    SDL_RenderPresent(renderer);
    SDL_Delay(delay_ms);
}
void Renderer::setIcon(const char* icon_address)
{
    SDL_Surface* icon = IMG_Load(icon_address);
    if (icon == nullptr)
    {
        SDL_Log("Failed to load icon: %s", SDL_GetError());
    }
    else
    {
        SDL_SetWindowIcon(window, icon);
        SDL_DestroySurface(icon);
    }
}

void Renderer::draw_rectangle(Rectangle rectangle, const std::string& hex_color)
{
    SDL_FRect rect = {rectangle.x, rectangle.y, rectangle.w, rectangle.h};
    Colour colour = hexToColour(hex_color);
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
    SDL_RenderRect(renderer, &rect);
}

void Renderer::draw_sorted_graph(Bounds bound, int num_bars, const std::string& hex_color)
{
    Colour colour = hexToColour(hex_color);
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);
    float height_chunk = bound.window_h/static_cast<float>(num_bars);
    float width_chunk = bound.window_w/static_cast<float>(num_bars);

    for (int i=0; i<num_bars; i++)
    {
        float x = i*width_chunk;
        float height = (i+1)*height_chunk;
        float y = bound.window_h - height;
        SDL_FRect rect = {x,y,width_chunk,height};
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Renderer::draw_array(Bounds bound,
                          const std::vector<int>& arr,
                          const std::string& hex_color1,
                          const std::string& hex_color2,
                          const std::string& hex_color3,
                          bool fill_solid,
                          const std::vector<bool>& sorted,
                          int cur_j)   //default argument only on declaration in render.h
{
    if (arr.empty())
        return;
    int max_num = *std::max_element(arr.begin(), arr.end());  //max_element returns a reference (use *)
    if (max_num<=0)
        return;
    int arr_len = static_cast<int>(arr.size());    //only works if size does not surpass INT_MAX
    Colour colour1 = hexToColour(hex_color1);
    Colour colour2 = hexToColour(hex_color2);
    Colour colour3 = hexToColour(hex_color3);
    float height_chunk = bound.window_h/static_cast<float>(max_num);
    float width_chunk = bound.window_w/static_cast<float>(arr_len);

    for (int i=0; i<arr_len; i++)
    {
        Colour colour = colour1;

        if (sorted[i])
        {
            colour = colour2;
        }

        if (cur_j!=-1 && i==cur_j)
            colour = colour3;

        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, 255);

        float x = i*width_chunk;
        float height = arr[i]*height_chunk;
        float y = bound.window_h - height;
        SDL_FRect rect = {x,y,width_chunk,height};
        if (fill_solid)
        {
            SDL_RenderFillRect(renderer, &rect);
        }
        else
        {
            SDL_RenderRect(renderer, &rect);
        }
    }
}

