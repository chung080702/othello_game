#pragma once

#include <sstream>
#include <fstream>
#include "evaluate.hpp"
#include <ctime>
using namespace std;

struct Move
{
    double value;
    int x;
    int y;
};

class OthelloAI
{
public:
    OthelloAI()
    {
        srand(time(NULL));

        ifstream f("openbook.txt");
        string s;
        int len = 0;
        while (getline(f, s))
        {
            stringstream ss(s);
            string t;
            ss >> t;
            openbooks.push_back(t);
        }
        f.close();
    }

    Move get_move(const vector2d &boards, int player, int eval_mode, int depth)
    {

        int turn_num = count_disc(boards);
        if (turn_num >= 52)
        {
            depth = 15;
        }

        this->boards = boards;
        this->player = player;
        this->eval_mode = eval_mode;
        this->cnt_eval = 0;
        return minimax(depth, -INF, INF, true);
    }

    Move get_move(const vector2d &boards, int player, int eval_mode, int depth, const string &history)
    {

        if (history.size() / 2 <= 25)
        {
            auto [x, y] = search_in_openbook(history);
            if (x != -1 && y != -1)
            {
                return {INF, x, y};
            }
        }

        return get_move(boards, player, eval_mode, depth);
    }

    pair<int, int> search_in_openbook(const string &history)
    {
        vector<int> possible_opens;
        for (int i = 0; i < openbooks.size(); i++)
        {
            if (openbooks[i].size() > history.size() && openbooks[i].find(history) == 0)
            {
                possible_opens.push_back(i);
            }
        }
        if (possible_opens.size() > 0)
        {
            string open = openbooks[possible_opens[1LL * rand() * rand() % possible_opens.size()]];
            return str_to_point(open[history.size()], open[history.size() + 1]);
        }
        return {-1, -1};
    }

    Move minimax(int depth, double alpha, double beta, bool is_max_player)
    {
        if (depth == 0)
        {
            return {evaluate(is_game_over(boards)), -1, -1};
        }

        int player = is_max_player ? this->player : 3 - this->player;
        int opp = 3 - player;

        if (!is_possible_move(boards, player))
        {
            if (is_possible_move(boards, opp))
            {
                return minimax(depth - 1, alpha, beta, !is_max_player);
            }
            else
            {
                return {evaluate(true), -1, -1};
            }
        }

        double res = is_max_player ? -INF : INF;

        bool is_no_move = true;

        char flip_nums[] = {0, 0, 0, 0, 0, 0, 0, 0};

        int best_i = 0;
        int best_j = 0;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (boards[i][j] != 0)
                {
                    continue;
                }

                bool flag = 0;
                for (int d = 0; d < 8; d++)
                {
                    auto [dx, dy] = dirs[d];
                    int _i = i + dx;
                    int _j = j + dy;

                    while (0 <= _i && _i < 8 && 0 <= _j && _j < 8 && boards[_i][_j] == opp)
                    {
                        _i += dx;
                        _j += dy;
                    }

                    int tmp = max(abs(_i - i) - 1, abs(_j - j) - 1);
                    if (0 <= _i && _i < 8 && 0 <= _j && _j < 8 && boards[_i][_j] == player && tmp > 0)
                    {
                        flag = true;
                        flip_nums[d] = tmp;
                    }
                    else
                    {
                        flip_nums[d] = 0;
                    }
                }
                if (!flag)
                {
                    continue;
                }
                is_no_move = false;
                boards[i][j] = player;

                for (int d = 0; d < 8; d++)
                {
                    auto [dx, dy] = dirs[d];
                    for (int t = 1; t <= flip_nums[d]; t++)
                    {
                        boards[i + t * dx][j + t * dy] = player;
                    }
                }

                double tmp = minimax(depth - 1, alpha, beta, !is_max_player).value;

                boards[i][j] = 0;

                for (int d = 0; d < 8; d++)
                {
                    auto [dx, dy] = dirs[d];
                    for (int t = 1; t <= flip_nums[d]; t++)
                    {
                        boards[i + t * dx][j + t * dy] = opp;
                    }
                }

                if (is_max_player)
                {
                    if (res < tmp)
                    {
                        res = tmp;
                        best_i = i;
                        best_j = j;
                    }
                    alpha = max(alpha, tmp);
                }
                else
                {
                    if (res > tmp)
                    {
                        res = tmp;
                        best_i = i;
                        best_j = j;
                    }
                    beta = min(beta, tmp);
                }

                if (beta <= alpha)
                {
                    break;
                }
            }
        }

        return {res, best_i, best_j};
    }

    double evaluate(bool is_over = false)
    {
        cnt_eval++;

        if (is_over)
        {
            return 10000 * disc_diff(boards, player);
        }

        switch (eval_mode)
        {
        case 1:
            return evaluate1(boards, player);
        case 2:
            return evaluate2(boards, player);
        case 3:
            return evaluate3(boards, player);
        case 4:
            return evaluate4(boards, player);
        case 5:
            return evaluate5(boards, player);
        case 6:
            return evaluate6(boards, player);
        default:
            return evaluate6(boards, player);
        }
    }

    int player;
    int eval_mode;
    int cnt_eval = 0;
    Move move;
    vector<vector<int>> boards;
    vector<string> openbooks;
};
