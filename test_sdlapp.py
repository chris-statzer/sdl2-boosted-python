from random import randint

from sdlapp import SDL2Application, KeyboardEvent, keys


class MyApp(SDL2Application):
    def __init__(self):
        super(MyApp, self).__init__()
        self.player_x = 10
        self.player_y = 10

    def draw(self):
        self.clear()
        self.draw_char(self.player_x, self.player_y, 1)
        self.flip()


app = MyApp()
app.init(1280, 720)


while app.is_running() is True:
    app.update()
    for e in app.poll_keys():
        print e.scancode, e.keycode
        if e.scancode == keys.KEY_ESC:
            app.quit()
        elif e.scancode == keys.KEY_UP:
            app.player_y -= 1
        elif e.scancode == keys.KEY_DOWN:
            app.player_y += 1
        elif e.scancode == keys.KEY_LEFT:
            app.player_x -= 1
        elif e.scancode == keys.KEY_RIGHT:
            app.player_x += 1
    app.draw()
