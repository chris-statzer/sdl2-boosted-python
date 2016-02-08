from random import randint

from sdlapp import SDL2Application


app = SDL2Application()
app.init(1280, 720)

while app.is_running() is True:
    app.update()
    app.clear()
    for y in range(0, 40):
        for x in range(0, 70):
            app.draw_char(x, y, randint(0, 254))
    app.flip()
