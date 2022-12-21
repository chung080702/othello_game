#include "heuristic.hpp"

// độ chênh lệch số lượng quân
double evaluate1(const vector2d &boards, int player)
{
    return disc_diff(boards, player);
}

// độ chênh lệch số lượng quân và góc
double evaluate2(const vector2d &boards, int player)
{
    int turn_num = count_disc(boards);
    if (turn_num < 25)
    {
        return corner_diff(boards, player);
    }
    else if (turn_num < 50)
    {
        return (disc_diff(boards, player) + 1000 * corner_diff(boards, player)) / 1001;
    }
    else
    {
        return (50 * disc_diff(boards, player) + 1000 * corner_diff(boards, player)) / 1050;
    }
}

// độ chệnh lệch số lượng quân, góc và trọng số bảng
double evaluate3(const vector2d &boards, int player)
{
    int turn_num = count_disc(boards);

    if (turn_num < 25)
    {
        return (50 * disc_weight_diff(boards, player) + 1000 * corner_diff(boards, player)) / 1050;
    }
    else if (turn_num < 50)
    {
        return (disc_diff(boards, player) + 1000 * corner_diff(boards, player) + 10 * disc_weight_diff(boards, player)) / 1011;
    }
    else
    {
        return (50 * disc_diff(boards, player) + 1000 * corner_diff(boards, player)) / 1050;
    }
}

// độ chệnh lệch số lượng quân, góc, trọng số bảng và quân ổn định
double evaluate4(const vector2d &boards, int player)
{
    int turn_num = count_disc(boards);

    if (turn_num < 25)
    {
        return (50 * disc_weight_diff(boards, player) + 1000 * corner_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2050;
    }
    else if (turn_num < 50)
    {
        return (disc_diff(boards, player) + 1000 * corner_diff(boards, player) + 10 * disc_weight_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2011;
    }
    else
    {
        return (50 * disc_diff(boards, player) + 1000 * corner_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2050;
    }
}

// độ chệnh lệch số lượng quân, góc, trọng số bảng, quân ổn định và độ cơ động
double evaluate5(const vector2d &boards, int player)
{
    int turn_num = count_disc(boards);

    if (turn_num < 25)
    {
        return (10 * mobility_diff(boards, player) + 50 * disc_weight_diff(boards, player) + 1000 * corner_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2060;
    }
    else if (turn_num < 50)
    {
        return (disc_diff(boards, player) + 5 * mobility_diff(boards, player) + 1000 * corner_diff(boards, player) + 10 * disc_weight_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2016;
    }
    else
    {
        return (50 * disc_diff(boards, player) + 1000 * corner_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2050;
    }
}

// độ chệnh lệch số lượng quân, góc, trọng số bảng, quân ổn định, độ cơ động và lượt cuối
double evaluate6(const vector2d &boards, int player)
{
    int turn_num = count_disc(boards);

    if (turn_num < 25)
    {
        return (10 * mobility_diff(boards, player) + 50 * disc_weight_diff(boards, player) + 1000 * corner_diff(boards, player) + 1000 * stability_diff(boards, player)) / 2060;
    }
    else if (turn_num < 50)
    {
        return (disc_diff(boards, player) + 5 * mobility_diff(boards, player) + 1000 * corner_diff(boards, player) + 10 * disc_weight_diff(boards, player) + 1000 * stability_diff(boards, player) + 5 * parity(boards)) / 2021;
    }
    else
    {
        return (50 * disc_diff(boards, player) + 1000 * corner_diff(boards, player) + 1000 * stability_diff(boards, player) + 50 * parity(boards)) / 2100;
    }
}