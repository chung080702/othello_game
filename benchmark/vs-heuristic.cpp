#include "../src/othello/ai.hpp"

using namespace std;

int main()
{
    ofstream log("vs-heuristic.log");
    log << "ai_mode_1,ai_mode_2,cnt_win_1,cnt_win_2,cnt_tie\n";
    auto ai = OthelloAI();

    for (int ai_mode_1 = 1; ai_mode_1 <= 6; ai_mode_1++)
    {
        for (int ai_mode_2 = 1; ai_mode_2 <= 6; ai_mode_2++)
        {
            int cnt_win_1 = 0;
            int cnt_win_2 = 0;
            int cnt_tie = 0;

            for (int i = 0; i < 100; i++)
            {
                cout << "[" << ai_mode_1 << " vs " << ai_mode_2 << "] game " << i << ' ';
                vector2d board;
                create_2d(board, 8, 8);
                board[3][3] = board[4][4] = 2;
                board[3][4] = board[4][3] = 1;

                string history = "";
                int player = 1;
                while (!is_game_over(board))
                {
                    if (!is_possible_move(board, player))
                    {
                        player = 3 - player;
                        continue;
                    }

                    int ai_mode = (player == 1) ? ai_mode_1 : ai_mode_2;
                    auto [value, x, y] = ai.get_move(board, player, ai_mode, 6, history);

                    place_disc_and_flip(board, x, y, player);

                    auto [c_x, c_y] = point_to_str(x, y, player);
                    history += c_x;
                    history += c_y;

                    player = 3 - player;
                }

                int cnt_1 = count_disc(board, 1);
                int cnt_2 = count_disc(board, 2);
                if (cnt_1 > cnt_2)
                {
                    cnt_win_1++;

                    cout << "player 1 win\n";
                }
                else if (cnt_1 < cnt_2)
                {
                    cnt_win_2++;
                    cout << "player 2 win\n";
                }
                else
                {
                    cnt_tie++;
                    cout << "tie\n";
                }
            }

            log << ai_mode_1 << ',' << ai_mode_2 << ',' << cnt_win_1 << ',' << cnt_win_2 << ',' << cnt_tie << '\n';
        }
    }

    log.close();
}