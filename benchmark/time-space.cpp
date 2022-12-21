#include "../src/othello/ai.hpp"
#include <chrono>

using namespace std;

int main()
{
    vector<double> time_step(60);
    vector<double> space_step(60);
    vector<int> cnt_step(60);

    ofstream f("time.log");

    int ai_mode_1 = 6;
    int ai_mode_2 = 6;
    int depth = 6;

    auto ai = OthelloAI();

    for (int i = 0; i < 100; i++)
    {
        vector2d board;
        create_2d(board, 8, 8);
        board[3][3] = board[4][4] = 2;
        board[3][4] = board[4][3] = 1;

        string history = "";
        int step = 0;
        int player = 1;

        while (!is_game_over(board))
        {
            if (!is_possible_move(board, player))
            {
                player = 3 - player;
                continue;
            }

            int ai_mode = (player == 1) ? ai_mode_1 : ai_mode_2;

            auto t_start = chrono::high_resolution_clock::now();
            auto [value, x, y] = ai.get_move(board, player, ai_mode, 6, history);
            auto t_end = std::chrono::high_resolution_clock::now();
            double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

            place_disc_and_flip(board, x, y, player);

            auto [c_x, c_y] = point_to_str(x, y, player);
            history += c_x;
            history += c_y;

            player = 3 - player;

            cnt_step[step]++;
            time_step[step] += elapsed_time_ms;
            space_step[step] += ai.cnt_eval;

            step++;
        }
        cout << "Game " << i << " finished\n";
    }

    for (int i = 0; i < 60; i++)
    {
        if (cnt_step[i])
        {
            time_step[i] /= cnt_step[i];
            space_step[i] /= cnt_step[i];
        }
    }

    f << "step,time,space\n";
    for (int i = 0; i < 60; i++)
    {
        if (cnt_step[i])
        {
            f << i << ',' << time_step[i] << ',' << space_step[i] << '\n';
        }
    }
    cout << "Finished\n";
    f.close();
}