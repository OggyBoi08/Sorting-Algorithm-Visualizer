#include <iostream>

#include "render.h"
#include "update.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600



int main()
{
    Renderer renderer("Sort Visualizer", WINDOW_WIDTH, WINDOW_HEIGHT);

    //Creating an Icon
    renderer.setIcon("bar-chart.png");

    //delta time
    uint64_t last = renderer.counter();
    uint64_t freq = renderer.frequency();

    //Variables
    Rectangle new_rect = {100,100,200,400};
    Bounds bound = {WINDOW_WIDTH, WINDOW_HEIGHT};
    std::vector<int> arr = {27, 81, 10, 5, 61, 40, 93, 72, 58, 4,
    13, 68, 86, 2, 90, 41, 30, 76, 14, 84, 19, 69, 66, 37, 20, 98,
    23, 62, 59, 89, 44, 82, 17, 54, 9, 87, 7, 47, 73, 94, 48, 8,
    29, 80, 42, 6, 71, 52, 36, 78, 56, 88, 83, 55, 49, 51, 16, 31,
    65, 38, 64, 91, 46, 75, 25, 15, 32, 99, 24, 28, 43, 33, 57, 67,
    85, 21, 100, 74, 34, 92, 35, 53, 96, 3, 18, 95, 12, 45, 22, 77,
    60, 97, 79, 11, 39, 1, 26, 70, 50, 63};
    SortState state = CreateShellSortState(arr);
    std::string colour1 = "#FF0000";   //unsorted colour
    std::string colour2 = "#00FF00";   //sorted colour
    std::string colour3 = "#0000FF";   //focus element colour

    //Create a main loop
    bool running = true;

    while (running)
    {
        running = renderer.ProcessEvents();
        renderer.clearBG("#000000");

        //update
        shell_sort_step(state);

        //draw
        if (!state.finished)
        {
            renderer.draw_array(bound, state.arr, colour1, colour2, colour3, true, state.sorted, state.j);
        }
        else
        {
            renderer.draw_sorted_graph(bound, arr.size(), colour2);
        }


        //delta time
        uint64_t now = renderer.counter();
        float dt = (now - last)/(float)freq;
        last = now;

        //Update
        renderer.present(16);   //around 60fps
    }

    return 0;
}
