# README for Circle Bounce
## A C++ project by Jonathan Jones
### To see source code please visit [https://github.com/kjjejones42/Circle-Bounce](https://github.com/kjjejones42/Circle-Bounce).

This started as a basic attempt to make an elementary executable program for my CS50 Final Project - the idea was to make a program that bounced circles around a window.

Python was originally used with the tk visual library, however the performance was severely lacking. The original Python source code is at the bottom of this file.

I decided to re-write this in C++ in Visual Studio using the popular SFML visual library that is commonly used in games. Once the original idea was achieved, I expanded the program to include;
* User keyboard & mouse input.
* Window loops, and multiple screens.
* Object-oriented programming and classes. 
* Support for window resizing.
* Collision detection with the mouse cursor.

The program now includes two modes - Simulation, and Game.

* Simulation Mode
    - This was the original idea behind the program. This introduces several thousand circle shapes that bounce around the screen in a variety of colours.
    - The user can change the size of the circles with the Up or Down Arrows, or with the mouse wheel.
    - The user can change the opacity of the circles with the Left or Right arrows.
    - The user can also toggle the wall wrapping of the screen with W, and whether the circles draw 'trails' with D.
* Game Mode
    - This basic game gives the user control over a Player object which follows the mouse cursor around the screen. The game loop is similar to Snake.
    - The game begins with the Player, a red Goal object, and one bouncing circle which must be avoided.
    - Each time the Player collides with the Goal; a new circle is added, the Goal moves to a random position, and the score increments by one.
    - The game is over and the score is displayed when the Player collides with any of the bouncing circles.

---
## Original Python Code
```
import tkinter
import time
from random import randint 

def main():

    winHeight = 720
    winWidth = 1280
    rectsize = 10
    numRects = 200

    class Rectangle:
        def __init__(self, a, parent):
            self.int = a
            self.parent = parent
            self.momentum = {"x": randint(-2,2) , "y": randint(-2,2)}
            while (self.momentum["x"] == 0 or self.momentum["y"] == 0):
                self.momentum = {"x": randint(-2,2) , "y": randint(-2,2)}

        def collidesWall(self):
            coords = self.parent.coords(self.int)
            if coords[0] <= 0 or coords[2] >= winWidth:
                self.momentum["x"] *= -1
            if coords[1] <= 0 or coords[3] >= winHeight:
                self.momentum["y"] *= -1

    top = tkinter.Tk()
    C = tkinter.Canvas(
        top,
        bg="black",
        height=winHeight,
        width=winWidth)
    C.pack()

    colors = ["red", "blue", "green", "yellow", "white"]
    rects = [None] * numRects
    for x in range(numRects):
        randX = randint(1, winWidth - rectsize)
        randY = randint(1, winHeight - rectsize)
        rects[x] = Rectangle(
            C.create_oval(
              randX, randY, randX + rectsize, randY + rectsize,
              fill=colors[randint(0, len(colors) - 1)]
            ),
            C)

    while (True):
        for rect in rects:
            rect.collidesWall()
            C.move(rect.int, rect.momentum["x"], rect.momentum["y"])
        top.update()

    top.mainloop()

if __name__ == "__main__":
    main()

```
---
