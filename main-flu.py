#!/home/mzamith/Apps/anaconda3/bin/python
import pygame
from pylibcaflu import CellularAutomata
import matplotlib.pyplot as plt




width  = 1024
height = 768
FPS    = 60
CA_X   = 100
CA_Y   = 100

pygame.init()
gameDisplay = pygame.display.set_mode((width,height))
pygame.display.set_caption('Autômato Celular')
gameDisplay.fill((0, 0, 0))

btn    = pygame.Rect(0, 0, 100, 30)
rect1  = pygame.Rect(0, 30, 100, 100)
clock  = pygame.time.Clock()

running = True



ca = CellularAutomata(CA_X, CA_Y)
ca.setProb(ca.P_INFECT, 0.25)
ca.setProb(ca.P_RECOVER, 0.0001)
ca.setProb(ca.P_DIE, 0.03)
ca.setDays2R(28)
#ca.setProb(ca.P_DIE, 0.10)
ca.random()
deltaX =  (width / CA_X)
deltaY =  (height / CA_Y)
day = 0
days = []
S = []
I = []
R = []
D = []
domain = CA_X * CA_Y

days.append(day)
S.append(ca.getStatistic(ca.SUSCEPTIBLE) / domain)
I.append(ca.getStatistic(ca.INFECT) / domain)
R.append(ca.getStatistic(ca.RECOVER) / domain)
D.append(ca.getStatistic(ca.DIE) / domain)

while running:
    clock.tick(FPS)
    gameDisplay.fill((0, 0, 0))
    for j in range(0, CA_Y):
        for i in range(0, CA_X):
            s = ca.getState(i, j)
            if s == ca.SUSCEPTIBLE:
                x = i  * deltaX
                y = j  * deltaY
                pygame.draw.rect(gameDisplay, (255, 255, 255), (x + 1, y + 1, deltaX - 2, deltaY - 2), 0)

            if s == ca.INFECT:
                x = i  * deltaX
                y = j  * deltaY
                pygame.draw.rect(gameDisplay, (0, 0, 255), (x + 1, y + 1, deltaX - 2, deltaY - 2), 0)

            if s == ca.RECOVER:
                x = i  * deltaX
                y = j  * deltaY
                pygame.draw.rect(gameDisplay, (0, 255, 0), (x + 1, y + 1, deltaX - 2, deltaY - 2), 0)

            if s == ca.DIE:
                x = i * deltaX
                y = j * deltaY
                pygame.draw.rect(gameDisplay, (255, 0, 0), (x + 1, y + 1, deltaX - 2, deltaY - 2), 0)

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
                day = day + 1
                days.append(day)
                S.append(ca.getStatistic(ca.SUSCEPTIBLE) / domain)
                I.append(ca.getStatistic(ca.INFECT) / domain)
                R.append(ca.getStatistic(ca.RECOVER) / domain)
                D.append(ca.getStatistic(ca.DIE) / domain)
                # ax.scatter([0.3, 3.8, 1.2, 2.5], [11, 25, 9, 26], color='darkgreen', marker='^')
                #    ax.set_xlim(0, 100)
            if e.key == pygame.K_p:
                pygame.image.save(gameDisplay, "screenshot-CA.jpg")

            if e.key == pygame.K_s:
                print("Day: ", day)
                print("S: ", ca.getStatistic(ca.SUSCEPTIBLE))
                print("I: ", ca.getStatistic(ca.INFECT))
                print("R: ", ca.getStatistic(ca.RECOVER))
                print("D: ", ca.getStatistic(ca.DIE))
                fig = plt.figure()
                ax = fig.add_subplot(111)
                ax.plot(days, S, color='black', linewidth=3)
                ax.plot(days, I, color='blue', linewidth=3)
                ax.plot(days, R, color='green', linewidth=3)
                ax.plot(days, D, color='red', linewidth=3)
                ax.legend(['Suscetível', 'Infectado', 'Recuperado', 'Morto'])
                plt.show()


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

