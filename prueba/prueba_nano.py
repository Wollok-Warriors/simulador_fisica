##El goat va a ir aprendiendo como todo en la vida
##Por eso es que se crea este archivo, para que mientras se aprende
##todos puedan ver que fue lo que hizo, y quizas.... inspirarse.
##Nazareno José Rodriguez Moyano    17/04/2026

import numpy as np
import pygame

#pygame setup
pygame.init()
screen = pygame.display.set_mode((1280,720))
clock = pygame.time.Clock()
running = True
dt = 0

height = screen.get_height()
width = screen.get_width()
g=10

#Atributos de la particula 
player_pos = pygame.Vector2(width/2, 150) #vector posicion 
player_vel = pygame.Vector2(0, 0) #vector velocidad 
player_acc = pygame.Vector2(100, g) #vector aceleración 
time_acc = 10 #implementacipon temproal. Cuanto tiempo está la aceleración. Por ahora solo va a afectar a la aceleración en x
t = 0 #tiempo total del programa. Implementación temporal


while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    #Fondo
    screen.fill("white")
    radio = 30
    max_height = height - radio
    min_height =  radio
    max_width = width - radio
    min_width = radio
    #Particula y sus movimientos
    pygame.draw.circle(screen, "red", player_pos,radio)
    keys = pygame.key.get_pressed()
    if keys[pygame.K_w] and player_pos.y > min_height:
        player_pos.y -= 300 * dt
    if keys[pygame.K_s] and player_pos.y < max_height:
        player_pos.y += 300 * dt
    if keys[pygame.K_a] and player_pos.x > min_width:
        player_pos.x -= 300 * dt
    if keys[pygame.K_d] and player_pos.x < max_width:
        player_pos.x += 300 * dt 
    if keys[pygame.K_q]:
        pygame.quit()    
    #velocidad en funcion del tiempo
    player_vel.y += player_acc.y * dt
    if (t < time_acc):
        player_vel.x += player_acc.x * dt
    #Posicion en funcion del tiempo
    player_pos.y += player_vel.y*dt
    player_pos.x += player_vel.x*dt
    if (player_pos.y >= max_height and player_vel.y>0) or (player_pos.y <= min_height and player_vel.y < 0):
        player_vel.y = -player_vel.y
    if (player_pos.x >= max_width and player_vel.x>0)  or (player_pos.x <= min_width and player_vel.x<0):
        player_vel.x = -player_vel.x
    #Poner el trabajo en la pantalla
    pygame.display.flip()
    #Delta t mide cuanto tiempo pasa entre cada frame
    dt = clock.tick(60) / 1000
    t += dt
pygame.quit()

