import threading
import sys
import queue
import time
from math import inf
from src.error import prout

# AI = 1, Opponent = 2

def protocolPrint(str):
    print(str, end="\r\n", flush=True)

def check_map(map, player_one, player_two):
    equivalent = [[0, 0, 0, 0, 0, inf], [0, 1, 4, 16, 64, inf], [0, 2, 8, 32, 1000, inf]]
    map_width = len(map[0])
    map_heigh = len(map)
    res = 0

    def check_direction(x, y, dx, dy):
        nonlocal res
        multiplier = 0
        size = 1
        if (0 <= x - dx < map_heigh and 0 <= y - dy < map_width and map[x - dx][y - dy] not in [player_two, player_one]):
            multiplier += 1
        for i in range(1, 6):
            size = i
            if not (0 <= x + i * dx < map_heigh and 0 <= y + i * dy < map_width) or map[x + i * dx][y + i * dy] != player_one:
                break
        if (0 <= x + size * dx < map_heigh and 0 <= y + size * dy < map_width and map[x + size * dx][y + size * dy] != player_two):
            multiplier += 1
        if (0 <= x - dx < map_heigh and 0 <= y - dy < map_width and map[x - dx][y - dy] == player_one):
            multiplier = 0
        if equivalent[multiplier][size] == inf:
            return inf
        res += equivalent[multiplier][size]
        return res

    try:
        for y in range(map_width):
            for x in range(map_heigh):
                if map[x][y] == player_one:
                    if check_direction(x, y, 0, 1) == inf:
                        return inf
                    if check_direction(x, y, 1, 0) == inf:
                        return inf
                    if check_direction(x, y, -1, 1) == inf:
                        return inf
                    if check_direction(x, y, 1, 1) == inf:
                        return inf
    except Exception as err:
        print(f"ERROR error = {err}", flush=True)
    return res

class Protocol:
    def __init__(self):
        self.size = None
        self.width = None
        self.heigh = None
        self.map = None
        self.map_lenght = None
        self.timeout_turn = None
        self.timeout_match = None
        self.max_memory = None
        self.time_left = None
        self.game_type = None
        self.rule = None
        self.evaluate = None
        self.folder = None

    def pos_to_mid(self, x, y):
        return abs(x - (len(self.map[0]) // 2)) + abs(y - (self.map_lenght // 2))

    def check_neighbour(self, x, y):
        map_heigh = len(self.map[y])

        if ((x and self.map[y][x - 1]) or
            (y and self.map[y - 1][x]) or
            (map_heigh - 1 != x and self.map[y][x + 1]) or
            (self.map_lenght - 1 != y and self.map[y + 1][x]) or
            (x and y and self.map[y - 1][x - 1]) or
            (x and self.map_lenght - 1 != y and self.map[y + 1][x - 1]) or
            (map_heigh - 1 != x and self.map_lenght - 1 != y and self.map[y + 1][x + 1]) or
            (map_heigh - 1 != x and y and self.map[y - 1][x + 1])):
            return True
        return False

    def alpha_beta_prunning(self, depth, brain, alpha, beta, start_stamp):
        if depth == 0:
            return (check_map(self.map, 1, 2) - check_map(self.map, 2, 1))
        for y in range(self.map_lenght):
            for x in range(len(self.map[y])):
                if self.map[y][x] == 0 and self.check_neighbour(x, y):
                    self.map[y][x] = 1 if brain else 2
                    value = self.alpha_beta_prunning(depth - 1, not brain, alpha, beta, start_stamp)
                    if brain:
                        alpha = max(alpha, value)
                    else:
                        beta = min(beta, value)
                    self.map[y][x] = 0
                    if alpha >= beta or int(time.time()) * 1000 - start_stamp > 5000 * 0.9:
                        return alpha if brain else beta
        return alpha if brain else beta

    def get_subboard(self, x, y):
        subboard = [
            [
                self.map[x + i][y + j] if 0 <= x + i < self.map_lenght and 0 <= y + j < len(self.map[0]) else 0
                for j in range(-2, 3)
            ]
            for i in range(-2, 3)
        ]
        return subboard

    def minimax(self):
        actual_time = int(time.time() * 1000)
        best_move = (len(self.map[0]) // 2, self.map_lenght // 2)
        found = False
        neg_inf = -inf
        for x in range(self.size):
            for y in range(self.size):
                if (self.map[x][y] == 0):
                    occupied_lines_count = 0
                    closest = self.get_subboard(x, y)
                    occupied_lines_count = sum(1 for row in closest if any(cell in [1, 2] for cell in row))
                    if (occupied_lines_count):
                        self.map[x][y] = 1
                        actual_value = self.alpha_beta_prunning(1, False, neg_inf, inf, actual_time)
                        self.map[x][y] = 0
                        distance_of_actual = self.pos_to_mid(x, y)
                        distance_of_best = self.pos_to_mid(best_move[0], best_move[1])
                        if (actual_value > neg_inf or (actual_value == neg_inf and distance_of_actual < distance_of_best) or found == False):
                            neg_inf = actual_value
                            best_move = (x, y)
                            found = True
        protocolPrint(f"{best_move[0]},{best_move[1]}")
        self.map[best_move[0]][best_move[1]] = 1
        return True

    def about(self):
        protocolPrint("name=\"BassemBrain\", version=\"1.0\", author=\"Bassem\", country=\"Tunisia\"")
        return

    def start(self, size):
        if (size < 5):
            protocolPrint("ERROR message - unsupported size or other error")
            return
        self.size = size
        self.map = [[0 for i in range(size)] for j in range(size)]
        self.map_lenght = len(self.map)
        protocolPrint("OK")
        return

    def get_map(self):
        return self.map
    
    def get_size(self):
        return self.size
    
    def display(self):
        for i in range(self.size):
            protocolPrint(self.map[i])

    def end(self):
        sys.exit(0)

    def best_move(self, depth):
        self.max_depth = depth
        return self.minimax(depth, True)

    def rectStart(self, width, heigh):
        if (width <= 1 or heigh <= 1):
            protocolPrint("ERROR message - rectangular board is not supported or other error")
            return
        self.width = width
        self.heigh = heigh
        self.map = [[0 for i in range(width)] for j in range(heigh)]
        protocolPrint("OK")
        return

    def restart(self):
        if (self.size != None):
            self.map = [[0 for i in range(self.size)] for j in range(self.size)]
        elif (self.width != None and self.heigh != None):
            self.map = [[0 for i in range(self.width)] for j in range(self.heigh)]
        protocolPrint("OK")

    def takeback(self, x, y):
        self.map[x][y] = 0
        protocolPrint("OK")

    def play(self, x, y):
        self.map[x][y] = 1
        protocolPrint(f"{x},{y}")

    def turn(self, player_x, player_y):
        if player_x < 0 or player_x >= self.size or player_y < 0 or player_y >= self.size or self.map[player_x][player_y] != 0:
            protocolPrint("ERROR message - invalid turn move")
            return
        self.map[player_x][player_y] = 2
        self.minimax()

    def info(self, key, value):
        if key == "timeout_turn":
            self.timeout_turn = value
        elif key == "timeout_match":
            self.timeout_match = value
        elif key == "max_memory":
            self.max_memory = value
        elif key == "time_left":
            self.time_left = value
        elif key == "game_type":
            self.game_type = value
        elif key == "rule":
            self.rule = value
        elif key == "evaluate":
            self.evaluate = value
        elif key == "folder":
            self.folder = value
        return

    def begin(self):
        self.minimax()

    def boardUpdate(self, x, y, field):
        if (field == 1):
            self.map[x][y] = 1
        elif (field == 2):
            self.map[x][y] = 2
    
    def boardBrain(self, x, y):
        self.map[x][y] = 1
        protocolPrint(f"{x},{y}")

class BrainThreadManager:
    def __init__(self):
        self.protocol = Protocol()
        self.command_queue = queue.Queue()
        self.command_event = threading.Event()
        self.stop_event = threading.Event()
        self.running = True
        self.reader_thread = threading.Thread(target=self.command_reader)
        self.thinker_thread = threading.Thread(target=self.command_thinker)
        self.reader_thread.start()
        self.thinker_thread.start()

    def command_reader(self):
        while self.running:
            try:
                command = input()
                if not self.running:
                    break
                if command == "END":
                    self.end_handler()
                if (command.startswith("BOARD")):
                    while (True):
                        input_string = input()
                        command = command + "|" + input_string
                        if (input_string.startswith("DONE")):
                            break

                self.command_queue.put(command)
                self.command_event.set()
            except Exception as e:
                return 84
    
    def command_thinker(self):
        try:
            while self.running:
                if self.stop_event.is_set():
                    break
                self.command_event.wait()
                
                if not self.running:
                    break

                while not self.command_queue.empty():
                    command = self.command_queue.get()
                    if command.startswith("PLAY"):
                        self.play_handler(command)
                    elif command.startswith("START"):
                        self.start_handler(command)
                    elif command == "display":
                        self.display_handler()
                    elif command.startswith("TURN"):
                        self.turn_handler(command)
                    elif command.startswith("INFO"):
                        self.info_handler(command)
                    elif command.startswith("BEGIN"):
                        self.begin_handler(command)
                    elif command.startswith("ABOUT"):
                        self.about_handler()
                    elif command.startswith("RECTSTART"):
                        self.rectStart_handler(command)
                    elif command.startswith("RESTART"):
                        self.restart_handler()
                    elif command.startswith("TAKEBACK"):
                        self.takeback_handler(command)
                    elif command.startswith("BOARD"):
                        self.board_handler(command)
                    else:
                        print("UNKNOWN command unidentified", command)
                self.command_event.clear()
        except Exception as e:
            return 84
    
    def start_handler(self, command):
        _, size = command.split()
        size = int(size)
        self.protocol.start(size)

    def play_handler(self, command):
        _, x, y = command.split()
        x, y = int(x), int(y)
        self.protocol.play(x, y)

    def display_handler(self):
        self.protocol.display()

    def turn_handler(self, command):
        player_x, player_y = command.split()[1].split(",")
        player_x, player_y = int(player_x), int(player_y)
        self.protocol.turn(player_x, player_y)

    def info_handler(self, command):
        _, key, value = command.split()
        self.protocol.info(key, value)
    
    def begin_handler(self, command):
        self.protocol.begin()
    
    def end_handler(self):
        self.stop_event.set()
        self.running = False
    
    def about_handler(self):
        self.protocol.about()
    
    def rectStart_handler(self, command):
        _, width, heigh = command.split()
        width, heigh = int(width), int(heigh)
        self.protocol.rectStart(width, heigh)

    def restart_handler(self):
        self.protocol.restart()

    def takeback_handler(self, command):
        _, x, y = command.split()
        x, y = int(x), int(y)
        self.protocol.takeback(x, y)

    def board_handler(self, command):
        commands = command.split("|")
        for command in commands:
            if command.startswith("DONE"):
                break
            if command.startswith("BOARD"):
                continue
            x, y, field = command.split(",")
            x, y, field = int(x), int(y), int(field)
            self.protocol.boardUpdate(x, y, field)
        self.protocol.minimax()

    def stop(self):
        self.running = False
        self.command_event.set()
        with self.command_queue.mutex:
            self.command_queue.queue.clear()
        self.reader_thread.join()
        self.thinker_thread.join()
