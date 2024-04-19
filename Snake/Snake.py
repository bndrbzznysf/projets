import pygame
import PIL.Image
import random


#Game setup
running = True
game_over = pause = False
window_width = window_height = 550
menu_height = 50
player_pos = pygame.Vector2(window_width/2, (window_height)/2)
snake_size = apple_size = 25
score = high_score = 0

top_border = menu_height
bottom_border = window_height + menu_height - snake_size
left_border = 0
right_border = window_width - snake_size
position = ""



#Window setup
pygame.init()
Icon = PIL.Image.open("Waluigi.ico")
Icon = Icon.tobytes(), Icon.size, Icon.mode
pygame.display.set_icon(pygame.image.frombytes(*Icon))
pygame.display.set_caption("SNAAAKE!!")
window = pygame.display.set_mode((window_width, window_height+menu_height))
pygame.font.init()
font = pygame.font.Font("Roboto-Light.ttf", 20)
clock = pygame.time.Clock()



#Snake and apple
snake = pygame.Rect(player_pos, (snake_size, snake_size))
snake_body = [snake]
apple = pygame.Rect((random.randrange(0, window_width, apple_size), random.randrange(menu_height, window_height, apple_size)), (apple_size, apple_size))



#Game loop
while running:
    #Quit game
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False


    #Game Over
    game_over = player_pos.x<left_border or player_pos.x>right_border or player_pos.y<top_border or player_pos.y>bottom_border or snake.collideobjects(snake_body[1:])
    if game_over:
        pygame.mixer.music.load("game_over.mp3")
        pygame.mixer.music.play()
        pygame.time.wait(1550)
        window = pygame.display.set_mode((window_width, window_height+menu_height)) 
        window.fill("gray14")
        player_pos = pygame.Vector2(window_width/2, (window_height)/2)
        apple = pygame.Rect((random.randrange(0, window_width, apple_size), random.randrange(menu_height, window_height, apple_size)), (apple_size, apple_size))
        position = ""
        snake_body = [snake]
        score = 0


    #Eating apple
    appleEaten = pygame.Rect.colliderect(snake, apple)
    if appleEaten:
        score+=1
        apple_coordinates = (random.randrange(0, window_width, apple_size), random.randrange(menu_height, window_height, apple_size))
        apple = pygame.Rect(apple_coordinates, (apple_size, apple_size))
        pygame.mixer.music.load("eat.mp3")
        pygame.mixer.music.play()
        if score>high_score:
            high_score=score
        
        if position == "UP":
            snake_body.append(pygame.Rect((player_pos.x, player_pos.y + snake_size), (snake_size, snake_size)))
        elif position == "DOWN":
            snake_body.append(pygame.Rect((player_pos.x, player_pos.y - snake_size), (snake_size, snake_size)))
        elif position == "LEFT":
            snake_body.append(pygame.Rect((player_pos.x + snake_size, player_pos.y), (snake_size, snake_size)))
        elif position == "RIGHT":
            snake_body.append(pygame.Rect((player_pos.x - snake_size, player_pos.y), (snake_size, snake_size)))
        
        

    #Fill the window with a color to wipe away anything from last frame
    window.fill("gray14")
    pygame.draw.rect(window, "grey10", (0, 0, 550, 50))


    #Snake
    pygame.draw.rect(window, "red", apple)
    snake = pygame.Rect(player_pos, (snake_size, snake_size))

    if not pause:
        snake_body=snake_body[:-1]
        snake_body.insert(0, snake)
    
    for i in range(len(snake_body)):
        pygame.draw.rect(window, "green", snake_body[i])


    #Score display
    score_text = font.render(f"Score : {score}", True, "white")
    high_score_text = font.render(f"High Score : {high_score}", True, "white")
    window.blit(score_text, (20, 14))
    window.blit(high_score_text, (130, 14))


    #Keys
    keys = pygame.key.get_pressed()
    if keys[pygame.K_UP] and position != "DOWN" and not pause:
        position = "UP"

    elif keys[pygame.K_DOWN] and position != "UP" and not pause:
        position = "DOWN"

    elif keys[pygame.K_LEFT] and position != "RIGHT" and not pause:
        position = "LEFT"

    elif keys[pygame.K_RIGHT] and position != "LEFT" and not pause:
        position = "RIGHT"


    elif keys[pygame.K_SPACE]:
        if not pause:
            pause = True
            position_before_pause = position
            position = ""
        else:
            pause = False
            position = position_before_pause


    #Snake movement
    if position == "UP":
        player_pos.y -= snake_size 
    elif position == "DOWN":
        player_pos.y += snake_size 
    elif position == "LEFT":
        player_pos.x -= snake_size
    elif position == "RIGHT":
        player_pos.x += snake_size


    # flip() the display to put work on window (update)
    pygame.display.flip()
    clock.tick(7.5)

pygame.quit()


#python3 -m PyInstaller --onefile --add-data=eat.mp3;. --add-data=game_over.mp3;. --add-data=Roboto-Light.ttf;. --icon=Waluigi.ico --noconsole Snake.py