#pragma once

#include <vector>
#include <iostream>

using namespace std;

using vector2d = vector<vector<int>>;

const vector<pair<int, int>> dirs = {{1, 1}, {1, -1}, {1, 0}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};

const double INF = 1e15;

void create_2d(vector2d &a, int h, int w)
{
    a.resize(h);
    for (auto &r : a)
    {
        r.resize(w);
    }
}

void print_2d(const vector2d &a)
{
    for (auto &r : a)
    {
        for (auto &c : r)
        {
            cout << c << ' ';
        }
        cout << '\n';
    }
}

void load_board(vector2d &a)
{
    create_2d(a, 8, 8);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cin >> a[i][j];
        }
    }
}

int count_disc(const vector2d &a)
{
    int res = 0;

    for (auto &r : a)
    {
        for (auto &c : r)
        {
            if (c != 0)
            {
                res++;
            }
        }
    }

    return res;
}

int count_disc(const vector2d &a, int player)
{
    int res = 0;

    for (auto &r : a)
    {
        for (auto &c : r)
        {
            if (c == player)
            {
                res++;
            }
        }
    }

    return res;
}

int count_disc_corner(const vector2d &board, int player)
{
    int res = 0;

    if (board[0][0] == player)
    {
        res++;
    }

    if (board[0][7] == player)
    {
        res++;
    }

    if (board[7][0] == player)
    {
        res++;
    }

    if (board[7][7] == player)
    {
        res++;
    }

    return res;
}

bool is_possible_move(const vector2d &board, int player)
{
    int opp = 3 - player;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != 0)
            {
                continue;
            }

            bool flag = 0;
            for (auto [dx, dy] : dirs)
            {
                int _i = i + dx;
                int _j = j + dy;

                while (0 <= _i && _i < 8 && 0 <= _j && _j < 8 && board[_i][_j] == opp)
                {
                    _i += dx;
                    _j += dy;
                }

                int tmp = max(abs(_i - i) - 1, abs(_j - j) - 1);
                if (0 <= _i && _i < 8 && 0 <= _j && _j < 8 && board[_i][_j] == player && tmp > 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int count_possible_move(const vector2d &board, int player)
{
    int opp = 3 - player;
    int res = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != 0)
            {
                continue;
            }

            bool flag = 0;
            for (auto [dx, dy] : dirs)
            {
                int _i = i + dx;
                int _j = j + dy;

                while (0 <= _i && _i < 8 && 0 <= _j && _j < 8 && board[_i][_j] == opp)
                {
                    _i += dx;
                    _j += dy;
                }

                int tmp = max(abs(_i - i) - 1, abs(_j - j) - 1);
                if (0 <= _i && _i < 8 && 0 <= _j && _j < 8 && board[_i][_j] == player && tmp > 0)
                {
                    res++;
                    break;
                }
            }
        }
    }
    return res;
}

bool is_game_over(const vector2d &board)
{
    if (!is_possible_move(board, 1) && !is_possible_move(board, 2))
    {
        return true;
    }
    return false;
}

int count_disc(const int *a, int player)
{
    int res = 0;
    for (int i = 0; i < 8; i++)
    {
        if (a[i] == player)
        {
            res++;
        }
    }
    return res;
}

pair<char, char> point_to_str(int x, int y, int player)
{
    char _x;
    char _y;
    if (player == 1)
    {
        _x = char(y + 'A');
    }
    else
    {
        _x = char(y + 'a');
    }

    _y = char(x + '1');
    return {_x, _y};
}

pair<int, int> str_to_point(char x, char y)
{
    return {y - '1', tolower(x) - 'a'};
}

void place_disc_and_flip(vector2d &boards, int i, int j, int player)
{
    int opp = 3 - player;
    char flip_nums[] = {0, 0, 0, 0, 0, 0, 0, 0};
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
            flip_nums[d] = tmp;
        }
        else
        {
            flip_nums[d] = 0;
        }
    }
    boards[i][j] = player;

    for (int d = 0; d < 8; d++)
    {
        auto [dx, dy] = dirs[d];
        for (int t = 1; t <= flip_nums[d]; t++)
        {
            boards[i + t * dx][j + t * dy] = player;
        }
    }
}