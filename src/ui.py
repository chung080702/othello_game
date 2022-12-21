import enum
import itertools
import socket
import threading
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import sys
import time


class GameMode(enum.Enum):
    HUMAN_VS_HUMAN = (0,)
    HUMAN_VS_AI = (1,)
    AI_VS_HUMAN = (2,)
    AI_VS_AI = 3


class Othello:
    def __init__(self, mode, socket, ai1, ai2, board=None) -> None:

        self.window = Tk()
        self.window.title("Othello-AI")
        self.window.option_add("*Dialog.msg.font", "Helvetica 14")
        self.window.option_add("*Dialog.msg.width", 20)
        self.window.geometry("512x552")

        self.bg_color = "#009067"

        self.canvas = Canvas(
            self.window, background=self.bg_color, height=512, width=512
        )
        self.canvas.pack()

        for i in range(1, 8):
            self.canvas.create_line(64 * i, 0, 64 * i, 512)
            self.canvas.create_line(0, 64 * i, 512, 64 * i)

        self.board_ui = [
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
            [0, 0, 0, 0, 0, 0, 0, 0],
        ]

        if board is None:
            self.board = [
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0, 0, 0],
            ]
            self.place_disc(3, 4, 1)
            self.place_disc(4, 3, 1)
            self.place_disc(3, 3, 2)
            self.place_disc(4, 4, 2)
        else:
            self.board = board
            for i in range(8):
                for j in range(8):
                    self.place_disc(i, j, self.board[i][j])

        self.dx = [1, 0, -1, 1, -1, 1, 0, -1]
        self.dy = [-1, -1, -1, 0, 0, 1, 1, 1]

        self.player = 1
        self.history = ""
        self.moves = []
        self.last_move = (-1, -1)

        self.mode = mode
        self.ai1 = ai1
        self.ai2 = ai2
        self.socket = socket

        panel = Frame(self.window, height=60)
        self.player1_label = ttk.Label(panel, text="Player 1: x0")
        self.player2_label = ttk.Label(panel, text="Player 2: x0")
        self.player1_label.pack(side=LEFT, padx=10, pady=10)
        self.player2_label.pack(side=RIGHT, padx=10, pady=10)
        panel.pack(fill=BOTH)

        self.init_turn()
        self.window.mainloop()

    def draw_disc(self, x, y, state):
        y, x = x, y
        if state == 0:
            return self.canvas.create_rectangle(
                x * 64 + 1,
                y * 64 + 1,
                (x + 1) * 64 - 1,
                (y + 1) * 64 - 1,
                fill=self.bg_color,
                width=0,
            )
        elif state == 1:
            return self.canvas.create_oval(
                x * 64 + 5,
                y * 64 + 5,
                (x + 1) * 64 - 5,
                (y + 1) * 64 - 5,
                fill="black",
            )
        elif state == 2:
            return self.canvas.create_oval(
                x * 64 + 5,
                y * 64 + 5,
                (x + 1) * 64 - 5,
                (y + 1) * 64 - 5,
                fill="white",
            )
        elif state == 3:
            return self.canvas.create_oval(
                x * 64 + 5,
                y * 64 + 5,
                (x + 1) * 64 - 5,
                (y + 1) * 64 - 5,
                fill=self.bg_color,
                width=1,
            )
        elif state == 4:
            return self.canvas.create_oval(
                x * 64 + 25,
                y * 64 + 25,
                (x + 1) * 64 - 25,
                (y + 1) * 64 - 25,
                fill="red",
            )
        elif state == 1.25:
            return self.canvas.create_oval(
                x * 64 + 5,
                y * 64 + 20,
                (x + 1) * 64 - 5,
                (y + 1) * 64 - 20,
                fill="white",
            )
        elif state == 1.5:
            return self.canvas.create_oval(
                x * 64 + 5,
                y * 64 + 31,
                (x + 1) * 64 - 5,
                (y + 1) * 64 - 31,
                width=2,
                fill="black",
            )
        elif state == 1.75:
            return self.canvas.create_oval(
                x * 64 + 5,
                y * 64 + 20,
                (x + 1) * 64 - 5,
                (y + 1) * 64 - 20,
                fill="black",
            )

    def find_possible_moves(self):
        opp = 3 - self.player
        self.moves.clear()

        for i in range(8):
            for j in range(8):
                if self.board[i][j] != 0:
                    continue
                for d in range(8):
                    _i = i + self.dx[d]
                    _j = j + self.dy[d]

                    while (
                        0 <= _i
                        and _i < 8
                        and 0 <= _j
                        and _j < 8
                        and self.board[_i][_j] == opp
                    ):
                        _i += self.dx[d]
                        _j += self.dy[d]

                    if (
                        0 <= _i
                        and _i < 8
                        and 0 <= _j
                        and _j < 8
                        and self.board[_i][_j] == self.player
                        and max(abs(_i - i) - 1, abs(_j - j) - 1) > 0
                    ):
                        self.moves.append((i, j))
                        break

    def flip_disc(self, i, j):
        opp = 3 - self.player
        array_move = []
        for d in range(8):
            _i = i + self.dx[d]
            _j = j + self.dy[d]

            while (
                0 <= _i and _i < 8 and 0 <= _j and _j < 8 and self.board[_i][_j] == opp
            ):
                _i += self.dx[d]
                _j += self.dy[d]

            num_flip = max(abs(_i - i) - 1, abs(_j - j) - 1)
            if (
                0 <= _i
                and _i < 8
                and 0 <= _j
                and _j < 8
                and self.board[_i][_j] == self.player
                and num_flip > 0
            ):
                for t in range(num_flip):
                    array_move.append(
                        [i + self.dx[d] * (t + 1), j + self.dy[d] * (t + 1)]
                    )
                    # self.place_disc(
                    #     i + self.dx[d] * (t + 1), j + self.dy[d] * (t + 1), self.player
                    # )
        state = 3 - self.player
        d = self.player - state

        for [x, y] in array_move:
            self.board[x][y] = self.player

        self.window.after(
            100,
            lambda: self.change_state(array_move, state + d * 0.25 * 1),
        )
        self.window.after(
            200,
            lambda: self.change_state(array_move, state + d * 0.25 * 2),
        )
        self.window.after(
            300,
            lambda: self.change_state(array_move, state + d * 0.25 * 3),
        )
        self.window.after(
            400,
            lambda: self.change_state(array_move, state + d * 0.25 * 4),
        )

    def change_state(self, array_move, state):
        for [x, y] in array_move:
            self.draw_disc(x, y, 0)
            self.draw_disc(x, y, state)

    def init_turn(self):
        if self.player == 1:
            print("--------------")
        else:
            print("************")
        self.update_panel()
        self.find_possible_moves()
        if len(self.moves) == 0:
            print(self.player, "pass")
            self.change_player()
            self.update_panel()
            self.find_possible_moves()

            if len(self.moves) == 0:
                cnt_1, cnt_2 = self.count_num_disc()
                if cnt_1 > cnt_2:
                    messagebox.showinfo(
                        "Player 1 win",
                        message=f"Player 1: {cnt_1}\n\nPlayer 2: {cnt_2}\n",
                    )
                elif cnt_1 < cnt_2:
                    messagebox.showinfo(
                        "Player 2 win",
                        message=f"Player 1: {cnt_1}\n\nPlayer 2: {cnt_2}\n",
                    )
                else:
                    messagebox.showinfo(
                        "Draw", message=f"Player 1: {cnt_1}\n\nPlayer 2: {cnt_2}\n"
                    )
                return

        if self.is_human_turn():
            for (x, y) in self.moves:
                self.board_ui[x][y] = self.draw_disc(x, y, 3)
                self.canvas.tag_bind(
                    self.board_ui[x][y], "<Button-1>", self.handle_place_disc
                )
        else:
            self.get_ai_turn()
            # threading.Thread(target=self.get_ai_turn).start()

    def handle_place_disc(self, event):
        id, *_ = event.widget.find_closest(event.x, event.y)
        for (i, j) in self.moves:
            self.canvas.tag_unbind(self.board_ui[i][j], "<Button-1>")
            self.draw_disc(i, j, 0)

        for (i, j) in self.moves:
            if self.board_ui[i][j] == id:
                self.place_disc(i, j, self.player)
                self.flip_disc(i, j)
                self.update_last_move(i, j)

        self.change_player()
        self.window.after(
            800,
            lambda: self.init_turn(),
        )

    def get_ai_turn(self):
        print(100)
        ai = 1
        if self.mode == GameMode.AI_VS_HUMAN or self.mode == GameMode.HUMAN_VS_AI:
            ai = self.ai1
        elif self.mode == GameMode.AI_VS_AI:
            ai = self.ai1 if self.player == 1 else self.ai2

        board_arr = (
            list(itertools.chain.from_iterable(self.board))
            + [
                self.player,
                ai,
                len(self.history),
            ]
            + list(map(lambda x: ord(x), self.history))
        )

        board_bytes = bytes(board_arr)
        self.socket.send(board_bytes)
        msg = self.socket.recv(2)
        x, y = msg[0], msg[1]

        self.place_disc(x, y, self.player)
        self.flip_disc(x, y)
        self.update_last_move(x, y)
        self.change_player()
        self.window.after(
            800,
            lambda: self.init_turn(),
        )

    def place_disc(self, i, j, player):
        self.board[i][j] = player
        self.draw_disc(i, j, player)

    def change_player(self):
        self.player = 3 - self.player

    def is_human_turn(self):
        if self.mode == GameMode.HUMAN_VS_HUMAN:
            return True

        if self.player == 1 and self.mode == GameMode.HUMAN_VS_AI:
            return True

        if self.player == 2 and self.mode == GameMode.AI_VS_HUMAN:
            return True

        return False

    def update_last_move(self, x, y):
        if self.last_move != (-1, -1):
            _x, _y = self.last_move
            self.draw_disc(_x, _y, self.board[_x][_y])

        self.last_move = x, y

        self.history += chr(y + ord("A" if self.player == 1 else "a"))
        self.history += chr(x + ord("1"))

        self.draw_disc(x, y, 4)
        print(self.player, "-->", x, y)

    def update_panel(self):
        if self.player == 1:
            self.player1_label.config(foreground="red")
            self.player2_label.config(foreground="black")
        else:
            self.player1_label.config(foreground="black")
            self.player2_label.config(foreground="red")

        cnt_1, cnt_2 = self.count_num_disc()
        self.player1_label.config(text=f"Player 1: x{cnt_1}")
        self.player2_label.config(text=f"Player 2: x{cnt_2}")

    def count_num_disc(self):
        cnt_1, cnt_2 = 0, 0
        for i in range(8):
            for j in range(8):
                if self.board[i][j] == 1:
                    cnt_1 += 1
                elif self.board[i][j] == 2:
                    cnt_2 += 1
        return cnt_1, cnt_2


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    # s.connect(("localhost", 6666))
    id = 1
    ai1 = 6
    ai2 = 6
    if len(sys.argv) >= 2:
        id = int(sys.argv[1])
    if len(sys.argv) >= 3:
        ai1 = int(sys.argv[2])
    if len(sys.argv) >= 4:
        ai2 = int(sys.argv[3])

    if id == 0:
        mode = GameMode.HUMAN_VS_HUMAN
    elif id == 1:
        mode = GameMode.HUMAN_VS_AI
    elif id == 2:
        mode = GameMode.AI_VS_HUMAN
    else:
        mode = GameMode.AI_VS_AI
    othello = Othello(mode, s, ai1, ai2)
