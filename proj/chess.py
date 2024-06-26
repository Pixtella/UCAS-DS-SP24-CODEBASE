import pygame
import sys
import matplotlib.pyplot as plt
import networkx as nx
import random
import numpy as np
import time
import os

BOARD_SIZE = 8
DIR = [
    (1, 2), (1, -2), (-1, 2), (-1, -2),
    (2, 1), (2, -1), (-2, 1), (-2, -1)
]
DIR_THRESHOLD = 100
NUM_FRAMES = 10
WINDOW_SIZE = 1000

nn = []
succ_seed = None
last_seed = None
sx, sy = 0, 0
successor = None

class Neuron:
    def __init__(self, frm, to, id=None):
        self.frm = frm
        self.to = to
        self.neighbours = []
        self.output = 0
        self.state = random.randint(0, BOARD_SIZE - 1)
        self.output_cache = 0
        self.state_cache = 0
        self.id = id

    def calc_next_state(self):
        sum = 0
        for neighbour in self.neighbours:
            sum += neighbour.output
        self.state_cache = self.state + 4 - sum - self.output * 2
        if self.state_cache > 3:
            self.output_cache = 1
        elif self.state_cache < 0:
            self.output_cache = 0
        else:
            self.output_cache = self.output

    def update(self):
        self.state = self.state_cache
        self.output = self.output_cache


def id2coord(id):
    x = id // BOARD_SIZE
    y = id % BOARD_SIZE
    return x, y

def coord2id(x, y):
    return x * BOARD_SIZE + y

def draw_board(canvas, posx, posy, size):
    COLOR1 = (112, 134, 184)
    COLOR2 = (238, 238, 238)
    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            if (i + j) % 2 == 0:
                color = COLOR1
            else:
                color = COLOR2
            pygame.draw.rect(canvas, color, (posx + i * size, posy + j * size, size, size))

def build_model():
    global nn
    for f in range(BOARD_SIZE * BOARD_SIZE):
        fx, fy = id2coord(f)
        for i in range(8):
            tx = fx + DIR[i][0]
            ty = fy + DIR[i][1]
            if tx < 0 or ty < 0 or tx >= BOARD_SIZE or ty >= BOARD_SIZE:
                continue
            t = coord2id(tx, ty)
            if t < f:
                continue
            nn.append(Neuron(f, t, len(nn)))
    neuron_num = len(nn)
    for i in range(neuron_num):
        for j in range(neuron_num):
            if i == j:
                continue
            if nn[j].frm == nn[i].to or nn[j].frm == nn[i].frm or nn[j].to == nn[i].to or nn[j].to == nn[i].frm:
                nn[i].neighbours.append(nn[j])

def initialize():
    global last_seed, succ_seed
    if succ_seed is not None:
        random.seed(succ_seed)
    else:
        last_seed = time.time()
        random.seed(last_seed)
    for neuron in nn:
        neuron.output = 0
        neuron.state = random.randint(0, BOARD_SIZE - 1)

def check_ans():
    global successor
    edges = [[] for _ in range(BOARD_SIZE * BOARD_SIZE)]
    for neuron in nn:
        if neuron.output == 1:
            edges[neuron.frm].append(neuron.to)
            edges[neuron.to].append(neuron.frm)
    
    if any([len(edges[i]) != 2 for i in range(BOARD_SIZE * BOARD_SIZE)]):
        return False

    vis = np.zeros(BOARD_SIZE * BOARD_SIZE, dtype=bool)
    idx = np.zeros(shape=(BOARD_SIZE, BOARD_SIZE), dtype=int)
    p = 0
    successor = np.zeros(BOARD_SIZE * BOARD_SIZE, dtype=int)
    for i in range(BOARD_SIZE * BOARD_SIZE):
        x, y = id2coord(p)
        idx[x][y] = i
        if vis[p]:
            return False
        vis[p] = True
        if i == BOARD_SIZE * BOARD_SIZE - 1:
            break
        if vis[edges[p][0]]:
            successor[p] = edges[p][1]
            p = edges[p][1]
        else:
            successor[p] = edges[p][0]
            p = edges[p][0]
    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            print(f"{idx[i][j]}\t", end="")
        print()
    return True

def converged():
    return all([neuron.state == neuron.state_cache for neuron in nn])

def calc_next_state():
    for neuron in nn:
        neuron.calc_next_state()

def update():
    for neuron in nn:
        neuron.update()

layout = None

def draw_graph(canvas, iter, posx, posy):
    global layout
    g = nx.Graph()
    node_color = {}
    for neuron in nn:
        g.add_node(neuron.id)
    for neuron in nn:
        if neuron.output == 1:
            node_color[neuron.id] = 'red'
        else:
            node_color[neuron.id] = 'blue'

    for neuron in nn:
        for neighbour in neuron.neighbours:
            g.add_edge(neuron.id, neighbour.id)
    fig, ax = plt.subplots(figsize=(10, 10))
    if layout is None:
        layout = nx.spring_layout(g)
    nx.draw(g, ax=ax, pos=layout, node_color=[node_color[i] for i in g.nodes])
    ax.set_title(f"Iteration {iter}")
    fig.canvas.draw()
    img = np.frombuffer(fig.canvas.tostring_rgb(), dtype=np.uint8)

    w, h = fig.canvas.get_width_height()
    img = img.reshape(h, w, 3)
    img = np.transpose(img, (1, 0, 2))
    sur = pygame.surfarray.make_surface(img)
    canvas.blit(sur, (posx, posy))
    plt.close(fig)

def draw_arrows(canvas, posx, posy, size):
    for neuron in nn:
        if neuron.output == 0:
            continue
        fx, fy = id2coord(neuron.frm)
        tx, ty = id2coord(neuron.to)
        pygame.draw.line(canvas, (78, 204, 181), (posx + fx * size + size // 2, posy + fy * size + size // 2), 
                                                 (posx + tx * size + size // 2, posy + ty * size + size // 2), 5)

def draw_num(canvas, posx, posy, size, num):
    font = pygame.font.Font(None, size)
    text = font.render(str(num), True, (78, 204, 181))
    if num < 10:
        text = pygame.transform.scale(text, (size // 2, size))
        canvas.blit(text, (posx + size // 4, posy))
    else:
        text = pygame.transform.scale(text, (size, size))
        canvas.blit(text, (posx, posy))

def draw_horse(canvas, horse, posx, posy, size):
    horse = pygame.transform.scale(horse, (size, size))
    canvas.blit(horse, (posx, posy))

def solve():
    global succ_seed, last_seed
    assert len(nn) > 0, "Model not built"
    initialize()
    t = 0
    while True:
        calc_next_state()
        t += 1
        if converged():
            print(f"Converged in {t} iterations")
            if check_ans():
                print("Hamiltonian path found")
                succ_seed = last_seed
                break
            else:
                print("Non-Hamiltonian path found")
                t = 0
                initialize()
                continue
        if t > DIR_THRESHOLD:
            print("Divergent")
            initialize()
            t = 0
            continue
        update()



if __name__ == "__main__":
    build_model()
    solve()
    os.environ['SDL_VIDEO_WINDOW_POS'] = "%d,%d" % (100,100)
    pygame.init()
    canvas = pygame.display.set_mode((WINDOW_SIZE * 2, WINDOW_SIZE))
    
    pygame.display.set_caption("Chess")

    exit_iter = False
    solution_found = False

    initialize()
    t = 0
    while not exit_iter:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit_iter = True
            if event.type == pygame.KEYDOWN and solution_found:
                exit_iter = True
        if not solution_found:
            t += 1
            calc_next_state()
            if converged():
                solution_found = True
            update()

            draw_board(canvas, 0, 0, WINDOW_SIZE//BOARD_SIZE)
            draw_graph(canvas, iter=t, posx=WINDOW_SIZE, posy=0)
            draw_arrows(canvas, 0, 0, WINDOW_SIZE//BOARD_SIZE)
            pygame.display.update()
    print(successor)
    exit_visit = False
    vt = 1
    horse = pygame.image.load("horse.png")
    p = coord2id(sx, sy)
    num2cor = {}
    for i in range(1, BOARD_SIZE * BOARD_SIZE + 1):
        fx, fy = id2coord(p)
        num2cor[i] = (fx, fy)
        p = successor[p]
        tx, ty = id2coord(p)
        for j in range(NUM_FRAMES):
            draw_board(canvas, 0, 0, WINDOW_SIZE//BOARD_SIZE)
            draw_graph(canvas, iter=t, posx=WINDOW_SIZE, posy=0)
            for num in range(1, i + 1):
                x, y = num2cor[num]
                draw_num(canvas, x * WINDOW_SIZE//BOARD_SIZE, y * WINDOW_SIZE//BOARD_SIZE, WINDOW_SIZE//BOARD_SIZE, num)
            draw_horse(canvas, horse, fx * WINDOW_SIZE//BOARD_SIZE + (tx - fx) * j * WINDOW_SIZE//BOARD_SIZE//NUM_FRAMES, 
                       fy * WINDOW_SIZE//BOARD_SIZE + (ty - fy) * j * WINDOW_SIZE//BOARD_SIZE//NUM_FRAMES,
                         WINDOW_SIZE//BOARD_SIZE)
            
            pygame.display.update()
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    exit_visit = True
            if exit_visit:
                break
        if exit_visit:
            break

    exit = False
    while not exit:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit = True
    pygame.quit()