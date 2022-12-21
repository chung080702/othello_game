#include <assert.h>

#include "../src/othello/heuristic.hpp"

void test_disc_diff()
{
    cout << "\nTest disc diff evaluation\n";
    vector2d a = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 2, 2, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};

    assert(disc_diff(a, 1) == 0.4);
    assert(disc_diff(a, 2) == -0.4);
    cout << "Pass\n";
}

void test_mobility_diff()
{
    cout << "\nTest mobility diff evaluation\n";
    vector2d a = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 2, 2, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}};
    assert(mobility_diff(a, 1) == -4.0 / 17);
    assert(mobility_diff(a, 2) == 4.0 / 17);
    cout << "Pass\n";
}

void test_corner_diff()
{
    cout << "\nTest corner diff evaluation\n";
    vector2d a = {
        {1, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 2, 2, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2}};

    assert(corner_diff(a, 1) == 0.25);
    assert(corner_diff(a, 2) == -0.25);

    vector2d b = {
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 2, 2, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0}};

    assert(corner_diff(b, 1) == 2.0 / 3);
    assert(corner_diff(b, 2) == -2.0 / 3);

    cout << "Pass\n";
}

void test_parity()
{
    cout << "\nTest parity\n";
    vector2d a = {{
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 0, 0},
    }};

    assert(parity(a) == -1);

    vector2d b = {{
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 1},
        {1, 1, 1, 1, 2, 2, 1, 0},
        {1, 1, 1, 1, 2, 2, 0, 0},
    }};

    assert(parity(b) == 1);

    cout << "Pass\n";
}

void test_disc_weight_diff()
{
    cout << "\nTest disc weight\n";
    vector2d a = {{0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 1, 0, 0},
                  {0, 0, 0, 1, 1, 1, 0, 0},
                  {0, 0, 0, 1, 2, 2, 0, 0},
                  {0, 0, 0, 0, 1, 1, 0, 0},
                  {0, 0, 0, 0, 0, 2, 2, 0},
                  {0, 0, 0, 0, 0, 1, 2, 0}};

    assert(disc_weight_diff(a, 1) == 650.0 / 9951);
    assert(disc_weight_diff(a, 2) == -650.0 / 9951);

    vector2d b = {{0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 0, 0, 0},
                  {0, 0, 0, 0, 0, 1, 0, 0},
                  {0, 0, 0, 1, 1, 1, 0, 0},
                  {0, 0, 0, 1, 2, 2, 0, 0},
                  {0, 0, 0, 0, 1, 1, 0, 0},
                  {0, 0, 0, 0, 0, 2, 2, 0},
                  {0, 0, 0, 0, 0, 1, 2, 1}};

    assert(disc_weight_diff(b, 1) == 100.0 / 10101);
    assert(disc_weight_diff(b, 2) == -100.0 / 10101);

    cout << "Pass\n";
}

void test_stability_diff()
{
    cout << "\nTest stablility diff\n";
    vector2d a = {
        {1, 1, 1, 0, 2, 2, 2, 2},
        {1, 0, 0, 0, 0, 0, 0, 2},
        {1, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 2},
        {1, 1, 0, 0, 0, 0, 2, 2}};

    assert(stability_diff(a, 1) == -5.0 / 20);
    assert(stability_diff(a, 2) == 5.0 / 20);
    cout << "Pass\n";
}

int main()
{
    cout << "Test heruistic function\n";
    test_disc_diff();
    test_mobility_diff();
    test_corner_diff();
    test_parity();
    test_disc_weight_diff();
    test_stability_diff();
    cout << "\nFinish\n";
}