#include <winsock2.h>
#include <netinet/in.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include "othello/ai.hpp"

using namespace std;

int main()
{

    vector2d boards;
    create_2d(boards, 8, 8);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << "Failed to create socket. errno: " << errno << '\n';
        exit(EXIT_FAILURE);
    }

    sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(6666);

    if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
    {
        cout << "Failed to bind to port 6666. errno: " << errno << '\n';
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 10);

    auto addrlen = sizeof(sockaddr);

    char buffer[1024];

    auto ai = OthelloAI();

    while (true)
    {
        int connection = accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

        if (connection < 0)
        {
            cout << "Failed to grab connection. errno: " << errno << '\n';
            exit(EXIT_FAILURE);
        }
        while (true)
        {

            auto bytesRead = read(connection, buffer, 1024);
            if (bytesRead != 0)
            {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        boards[i][j] = buffer[i * 8 + j];
                    }
                }
                int player = buffer[64];
                int eval_mode = buffer[65];
                int history_len = buffer[66];
                string history;
                for (int i = 0; i < history_len; i++)
                {
                    history += buffer[67 + i];
                }
                cout << "\n==============\n";
                cout << "Board\n";
                print_2d(boards);
                cout << "Player: " << player << '\n';
                cout << "Evaluation mode: " << eval_mode << '\n';
                cout << "History: " << history << '\n';
                auto t_start = chrono::high_resolution_clock::now();
                auto [value, x, y] = ai.get_move(boards, player, eval_mode, 6, history);
                auto t_end = std::chrono::high_resolution_clock::now();
                double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
                cout << "Estimate time: " << elapsed_time_ms << " ms\n";
                cout << "Evaluation value: " << value << '\n';
                cout << "Move: " << x << ' ' << y << '\n';
                char res[] = {char(x), char(y)};
                send(connection, res, 2, 0);
            }
            else
            {
                close(connection);
                break;
            }
        }
    }

    close(sockfd);
}