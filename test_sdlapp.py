from random import randint

from sdlapp import SDL2Application


class MyApp(SDL2Application):
    def draw(self):
        for y in range(0, 45):
            for x in range(0, 80):
                self.draw_char(x, y, randint(0, 254))

    def on_keypress(self, key):
        print 'MyApp::on_keypress({})'.format(key)

app = MyApp()
app.init(1280, 720)

while app.is_running() is True:
    app.update()
    app.clear()
    app.draw()
    app.flip()
