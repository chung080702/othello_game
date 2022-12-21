#include <iostream>
#include <chrono>
#include "./othello/ai.hpp"
using namespace std;

int main()
{
    vector2d a;
    load_board(a);

    auto ai = OthelloAI();
    auto t_start = chrono::high_resolution_clock::now();
    auto [value, x, y] = ai.get_move(a, 1, 6, 6);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    cout << elapsed_time_ms << '\n';
    cout << value << ' ' << x << ' ' << y << '\n';
}
