import speech_recognition as sr
import pygame as pg


def main_loop(screen: pg.Surface, source: sr.Microphone, recognizer: sr.Recognizer):
    while True:
        # Go through pygame events
        for event in pg.event.get():
            # Check quit event
            if event.type == pg.QUIT:
                pg.quit()
                exit()
            # Check keydown event
            elif event.type == pg.KEYDOWN:
                pass

        # Update display
        screen.fill("black")
        pg.display.update()


if __name__ == "__main__":
    recognizer = sr.Recognizer()
    pg.init()
    screen = pg.display.set_mode((500, 100))

    with sr.Microphone() as source:
        main_loop(screen, source, recognizer)
