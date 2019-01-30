import sys, pygame
import numpy as np
import os
import time


pygame.init()

size = width, height = 500, 500
black = 0, 0, 0

def load_image(name):
    image = pygame.image.load(name)
    return image

class FireSprite(pygame.sprite.Sprite):
    def __init__(self,  a, b):
        super(FireSprite, self).__init__()
        self.images = []
        self.images.append(load_image('flames/flame1.gif'))
        self.images.append(load_image('flames/flame2.gif'))
        self.images.append(load_image('flames/flame3.gif'))
        self.images.append(load_image('flames/flame4.gif'))
        self.images.append(load_image('flames/flame5.gif'))
        self.images.append(load_image('flames/flame6.gif'))
        self.images.append(load_image('flames/flame7.gif'))
        self.images.append(load_image('flames/flame8.gif'))
        self.images.append(load_image('flames/flame9.gif'))
        self.images.append(load_image('flames/flame10.gif'))
        self.index = 0
        self.image = self.images[self.index]
        self.rect = pygame.Rect(a, b, 50, 50)

    def update(self):
        self.time = 0
        self.index += 1
        if self.index >= len(self.images):
            self.index = 0
        self.image = self.images[self.index]

def get_file_and_draw(screen, filename, x, y):
    exit = pygame.image.load(filename)
    exit = pygame.transform.scale(exit, (50, 50))
    exitrect = exit.get_rect()
    exitrect.x = x
    exitrect.y = y  
    screen.blit(exit, exitrect)

fires = []

def fire_and_draw(screen, x, y):
    global fires
    my_sprite = FireSprite(x, y)
    my_group = pygame.sprite.Group(my_sprite)
    fires.append(my_group)
    my_group.draw(screen)

def draw_sur(screen, data, x, y):
    get_file_and_draw(screen, 'white.jpg', x, y)
    font = pygame.font.SysFont('Arial', 20)
    screen.blit(font.render(str(int(data-82)), True, (0,128,0)), (x+18, y+15))


screen = pygame.display.set_mode(size)

tile = pygame.image.load("tile.jpg")
tilerect = tile.get_rect()

data = np.genfromtxt('test.txt', delimiter=' ')
dim = np.shape(data)[0]
## generate grid of fires
for x in range(0,10):
    for y in range(0,10):
        fire_and_draw(screen, x*50, y*50)        
# print(data)

pygame.display.set_caption('Fire Escape')

def run_move():
    global data
    # print("Herre")
    os.system('./a.out 0')
    data = np.genfromtxt('test.txt', delimiter=' ')

def run_fire_move():
    global data
    # print("Herre")
    os.system('./a.out 1')
    data = np.genfromtxt('test.txt', delimiter=' ')


start = time.time()
k = 0

while 1:
    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()
    
    end = time.time()
    if(int(end - start) == 1):
        start = time.time()
        k = k + 1
        if k % 2 == 0:
            run_move()
        else:
            run_fire_move()

    screen.fill(black)
    for fire in fires:
        fire.update()
        fire.draw(screen)

    for x in range(0,10):
        for y in range(0,10):
            if data[y][x] == 69:
                get_file_and_draw(screen, 'exit.png', x*50, y*50)
            if data[y][x] == 0:
                get_file_and_draw(screen, 'tile.jpg', x*50, y*50)    
            if data[y][x] == 12:
                continue
            if data[y][x] == 1:
                get_file_and_draw(screen, 'brick.jpg', x*50, y*50)
            if data[y][x] >= 83:
                draw_sur(screen, data[y][x], x*50, y*50) 
                continue                                             

    pygame.display.flip()