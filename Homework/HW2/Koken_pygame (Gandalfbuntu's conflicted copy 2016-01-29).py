#Matthew Koken
#Written for python 2.7.9
from Tkinter import *
from random import randint
from time import sleep,time
from math import sqrt

NUM_MINES=0
cur_score=0
mine_list=[]
END=120

#Draw a Canvas for the game
H=600
W=800
window=Tk()
window.title("Submarine Game")
c=Canvas(window, width= W, height=H, bg="#CAE1FF" )
c.pack()
v = StringVar()

#Draw a red submarine
ship_c=c.create_oval(300,400,400,430, outline= "red",  fill="red")
ship_h=c.create_polygon(370,415,425,400,425,430, outline= "red",  fill="red")
ship_p=c.create_rectangle(350,387,360,400, outline= "red",  fill="red")
ship_p2=c.create_rectangle(340,387,350,390, outline= "red",  fill="red")

#move the submarine
#move up
SHIP_SPD=10
def move_ship_up(event):
       x1,y1,x2,y2 =c.coords(ship_c)
       if y1- SHIP_SPD > 0:
                c.move(ship_c,0,-SHIP_SPD)
                c.move(ship_h,0,-SHIP_SPD)
                c.move(ship_p,0,-SHIP_SPD)
                c.move(ship_p2,0,-SHIP_SPD)
window.bind("<Up>", move_ship_up)

#move down
SHIP_SPD1=-10
def move_ship_down(event):
    x1,y1,x2,y2 =c.coords(ship_c)
    if y2- SHIP_SPD1 < 640:
        c.move(ship_c,0,-SHIP_SPD1)
        c.move(ship_h,0,-SHIP_SPD1)
        c.move(ship_p,0,-SHIP_SPD1)
        c.move(ship_p2,0,-SHIP_SPD1)
window.bind("<Down>", move_ship_down)

#move right
SHIP_SPD2=0
def move_ship_right(event):
    x1,y1,x2,y2 =c.coords(ship_c)
    if x1- SHIP_SPD1 < 730:
        c.move(ship_c,10,-SHIP_SPD2)
        c.move(ship_h,10,-SHIP_SPD2)
        c.move(ship_p,10,-SHIP_SPD2)
        c.move(ship_p2,10,-SHIP_SPD2)
window.bind("<Right>", move_ship_right)

#moveleft
SHIP_SPD3=0
def move_ship_left(event):
    x1,y1,x2,y2 =c.coords(ship_c)
    if x2- SHIP_SPD1 > 80:
        c.move(ship_c,-10,-SHIP_SPD3)
        c.move(ship_h,-10,-SHIP_SPD3)
        c.move(ship_p,-10,-SHIP_SPD3)
        c.move(ship_p2,-10,-SHIP_SPD3)
window.bind("<Left>", move_ship_left)

def create_mines():
    NUM_MINES=randint(1,4)
    #add new mines
    for i in range (0, NUM_MINES):
        # use randint function to generate x,y coord and a radius for your mine
        x_coord = randint(0, 800)
        y_coord = randint(500, 600)
        radius = randint(5, 50)
        speed = randint(1, 51-radius)
        #(x1,y1) top left bounding corner
        x1 = x_coord - radius
        y1 = y_coord + radius
        #(x2,y2) bottom right bounding corner
        x2 = x_coord + radius
        y2 = y_coord - radius
        mine_id = c.create_oval(x1,y1,x2,y2, outline= "blue",  fill="white", width="2")
        mine = [mine_id, radius, speed, x_coord, y_coord]
        mine_list.append(mine)
        # draw a round mine with function create_oval
        # add id of the oval above to the list, add rad to list and speed to list als

def mov_mines():  #use a for loop to move all the mines in the list from botton of canvas u
    # move each mine up by its speed
    for mine in mine_list:
        c.move(mine[0], 0, -mine[2]) #top left corner is (0, 0) so need to subtract


def clean_up_mines():
    print "cleaning"
    #for i in range(tot_mines):
    #    mine = mine_list[i]
    #    #if it has a radius of 0 or beyond bounds, delete
    #    if (mine[1] == 0):
    #        c.delete(window, mine[0])
    #        mine_list.__delitem__(i)

def collision():
    print "collision"
    for mine in mine_list:
        x_mine = mine[3] #id, radius, speed, x, y

c.create_text(150,30, text='SCORE', fill="black")
score_text = c.create_text(150, 50, fill='black')
def show_score(score):
    c.itemconfig(score_text, text=str(score))

c.create_text(80, 30, text="TIME", fill="black")
time_text = c.create_text(80, 50, fill="black")
def show_time(time):
    c.itemconfig(time_text, text=str(time))

def end_game():
    print "GAME OVER"

#main game loop
for x in range(0,NUM_MINES):
    create_mines() #you need to create this function
time = 30.0
while time>0:
    mov_mines()  #you need to create this function
    if randint(1,30)==1: #this will create a new bubble every certain amount of time
        create_mines()
    clean_up_mines() #you need to create this function
    collision()#you need to create this function
    window.update()
    sleep(0.1)
    show_score(cur_score)
    time-=.1
    show_time(time)
end_game()
