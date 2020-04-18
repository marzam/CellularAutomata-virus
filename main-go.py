#!/home/mzamith/Apps/anaconda3/bin/python
import pygame
from pylibcaflu import CellularAutomata

width  = 800
height = 600
FPS    = 60
CA_X   = 12
CA_Y   = 8

pygame.init()
gameDisplay = pygame.display.set_mode((width,height))
pygame.display.set_caption('Autômato Celular')
gameDisplay.fill((0, 0, 0))

btn    = pygame.Rect(0, 0, 100, 30)
rect1  = pygame.Rect(0, 30, 100, 100)
clock  = pygame.time.Clock()

running = True

ca = CellularAutomata(CA_X, CA_Y)
ca.setProb(0.25)
ca.random()
deltaX =  (width / CA_X)
deltaY =  (height / CA_Y)

while running:
    clock.tick(FPS)
    gameDisplay.fill((0, 0, 0))
    for j in range(0, CA_Y):
        for i in range(0, CA_X):
            s = ca.getState(i, j)
            if s == 1:
                x = i  * deltaX
                y = j  * deltaY
                pygame.draw.rect(gameDisplay, (255, 255, 255), (x + 1, y + 1, deltaX - 2, deltaY - 2), 0)

    for j in range(1, CA_Y):
        pygame.draw.line(gameDisplay, (255, 0, 0), (0, j * deltaY), (width, j * deltaY))

    for i in range(1, CA_X):
        pygame.draw.line(gameDisplay, (255, 0, 0), (i * deltaX, 0), (i * deltaX, height))
        #for i in range(0, CA_X - 1):

    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            running = False
        if e.type == pygame.KEYDOWN:
            if e.key == pygame.K_ESCAPE:
                running = False
            if e.key == pygame.K_r:
                ca.random()
            if e.key == pygame.K_u:
                ca.update()

    pygame.display.flip()

'''
    
        if e.type == pygame.MOUSEBUTTONDOWN:
            (mouseX, mouseY) = pygame.mouse.get_pos()
            if(btn.collidepoint((mouseX, mouseY))):
                move_it = not move_it

        if e.type == pygame.QUIT:
            running = False
    #end event handling

    if move_it:
        rect1.move_ip(move_direction * 5, 0)
        if not gameDisplay.get_rect().contains(rect1):
            move_direction = move_direction * -1
            rect1.move_ip(move_direction * 5, 0)

    pygame.draw.rect(gameDisplay, (255, 0, 255), rect1, 1)
    pygame.draw.rect(gameDisplay, (255, 0, 0) if move_it else (0, 255, 255), btn)
'''


#end main loop
pygame.quit()