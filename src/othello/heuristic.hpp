#pragma once

#include "helper.hpp"

int board_weights[8][8] = {
    {200, -100, 100, 50, 50, 100, -100, 200},
    {-100, -200, -50, -50, -50, -50, -200, -100},
    {100, -50, 100, 0, 0, 100, -50, 100},
    {50, -50, 0, 0, 0, 0, -50, 50},
    {50, -50, 0, 0, 0, 0, -50, 50},
    {100, -50, 100, 0, 0, 100, -50, 100},
    {-100, -200, -50, -50, -50, -50, -200, -100},
    {200, -100, 100, 50, 50, 100, -100, 200},
};

double disc_diff(const vector2d &board, int player)
{
    double cnt_player = count_disc(board, player);
    double cnt_opp = count_disc(board, 3 - player);

    return (cnt_player - cnt_opp) / (cnt_player + cnt_opp);
}

double mobility_diff(const vector2d &board, int player)
{
    double cnt_player = count_possible_move(board, player);
    double cnt_opp = count_possible_move(board, 3 - player);

    return (cnt_player - cnt_opp) / (cnt_player + cnt_opp + 1);
}

double corner_diff(const vector2d &board, int player)
{
    double cnt_player = count_disc_corner(board, player);
    double cnt_opp = count_disc_corner(board, 3 - player);

    return (cnt_player - cnt_opp) / (cnt_player + cnt_opp + 1);
}

double parity(const vector2d &board)
{
    if ((64 - count_disc(board)) % 2)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

double disc_weight_diff(const vector2d &board, int player)
{
    double sum_player = 5000; // to make value sum possitive
    double sum_opp = 5000;
    int opp = 3 - player;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i <= 3 && j <= 3 && board[0][0] != 0)
            {
                continue;
            }

            if (i <= 3 && j >= 4 && board[0][7] != 0)
            {
                continue;
            }

            if (i >= 4 && j <= 3 && board[7][0] != 0)
            {
                continue;
            }

            if (i >= 4 && j >= 4 && board[7][7] != 0)
            {
                continue;
            }

            if (board[i][j] == player)
            {
                sum_player += board_weights[i][j];
            }
            else if (board[i][j] == opp)
            {
                sum_opp += board_weights[i][j];
            }
        }
    }

    return (sum_player - sum_opp) / (sum_player + sum_opp + 1);
}

double stability_diff(const vector2d &board, int player)
{
    int r0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int r7[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int c0[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int c7[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    if (board[0][0])
    {
        for (int i = 0; i < 8; i++)
        {
            if (board[0][i] == board[0][0])
            {
                r0[i] = board[0][0];
            }
            else
            {
                break;
            }
        }
        for (int i = 1; i < 7; i++)
        {
            if (board[i][0] == board[0][0])
            {
                c0[i] = board[0][0];
            }
            else
            {
                break;
            }
        }
    }

    if (board[0][7])
    {
        for (int i = 7; i >= 0; i--)
        {
            if (board[0][i] == board[0][7])
            {
                r0[i] = board[0][7];
            }
            else
            {
                break;
            }
        }
        for (int i = 1; i < 7; i++)
        {
            if (board[i][7] == board[0][7])
            {
                c7[i] = board[0][7];
            }
            else
            {
                break;
            }
        }
    }

    if (board[7][0])
    {
        for (int i = 0; i < 8; i++)
        {
            if (board[7][i] == board[7][0])
            {
                r7[i] = board[7][0];
            }
            else
            {
                break;
            }
        }
        for (int i = 6; i > 0; i--)
        {
            if (board[i][0] == board[7][0])
            {
                c0[i] = board[7][0];
            }
            else
            {
                break;
            }
        }
    }

    if (board[7][7])
    {
        for (int i = 7; i >= 0; i--)
        {
            if (board[7][i] == board[7][7])
            {
                r7[i] = board[7][7];
            }
            else
            {
                break;
            }
        }
        for (int i = 6; i > 0; i++)
        {
            if (board[i][0] == board[7][7])
            {
                c7[i] = board[7][7];
            }
            else
            {
                break;
            }
        }
    }

    int opp = 3 - player;

    double cnt_player = count_disc(r0, player) + count_disc(r7, player) + count_disc(c0, player) + count_disc(c7, player);
    double cnt_opp = count_disc(r0, opp) + count_disc(r7, opp) + count_disc(c0, opp) + count_disc(c7, opp);

    return (cnt_player - cnt_opp) / (cnt_player + cnt_opp + 1);
}