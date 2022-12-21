#include <assert.h>
#include "../src/othello/helper.hpp"

void test_create_2d()
{
    cout << "\nTesting create 2d" << '\n';
    vector2d a;
    create_2d(a, 8, 8);
    assert(a.size() == 8);
    for (auto &r : a)
    {
        assert(r.size() == 8);
        for (auto &c : r)
        {
            assert(c == 0);
        }
    }
    cout << "Pass\n";
}

void test_count_disc()
{
    cout << "\nTesting count disc\n";
    int a[8] = {1, 1, 0, 2, 2, 1, 1, 0};
    assert(count_disc(a, 1) == 4);
    assert(count_disc(a, 2) == 2);

    vector2d b = {
        {0, 0, 1, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 2}};

    assert(count_disc(b) == 7);
    assert(count_disc(b, 1) == 3);
    assert(count_disc(b, 2) == 4);

    cout << "Pass\n";
}

void test_count_disc_corner()
{
    cout << "\nTest count disc corner\n";
    vector2d b = {
        {0, 0, 1, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 2}};

    assert(count_disc_corner(b, 1) == 1);
    assert(count_disc_corner(b, 2) == 2);

    cout << "Pass\n";
}

void test_is_game_over()
{
    cout << "\nTest game is over\n";
    vector2d a = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    assert(is_game_over(a) == true);

    vector2d b = {
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
    };

    assert(is_game_over(b) == true);

    vector2d c = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 2, 2, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    assert(is_game_over(c) == false);

    cout << "Pass\n";
}

void test_is_possible_move()
{
    cout << "\nTest there is possible move\n";
    vector2d a = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0}};

    assert(is_possible_move(a, 1) == false);
    assert(is_possible_move(a, 2) == true);

    cout << "Pass\n";
}

void test_count_possible_move()
{
    cout << "\nTest count possible move\n";
    int x = 0;
    vector2d a = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 2, 2, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    assert(count_possible_move(a, 1) == 6);
    assert(count_possible_move(a, 2) == 10);
    cout << "Pass\n";
}

void test_point_to_str()
{
    cout << "\nTest point to str\n";
    auto [x, y] = point_to_str(0, 3, 1);
    assert(x == 'D');
    assert(y == '1');

    auto [x2, y2] = point_to_str(0, 3, 2);
    assert(x2 == 'd');
    assert(y2 == '1');
    cout << "Pass\n";
}

void test_str_to_point()
{
    cout << "\nTest str to point\n";
    auto [x, y] = str_to_point('D', '1');
    assert(x == 0);
    assert(y == 3);

    auto [x2, y2] = str_to_point('d', '1');
    assert(x2 == 0);
    assert(y2 == 3);
    cout << "Pass\n";
}

void test_place_disc_and_flip()
{
    cout << "\nTest place disc and flip\n";
    vector2d a = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 2, 2, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    place_disc_and_flip(a, 4, 6, 1);
    vector2d b = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            assert(a[i][j] == b[i][j]);
        }
    }
    cout << "Pass\n";
}

int main()
{
    cout << "\nTest helper function\n";
    test_create_2d();
    test_count_disc();
    test_count_disc_corner();
    test_is_game_over();
    test_is_possible_move();
    test_count_possible_move();
    test_point_to_str();
    test_str_to_point();
    test_place_disc_and_flip();
    cout << "\nFinsih\n";
}