import speech_recognition as sr
import pygame as pg
from enum import Enum, auto
from sys import argv


DEBUGGING = True


class PlaybackState(Enum):
    PLAYING = auto()
    PAUSED = auto()
    STOPPED = auto()


def main_loop(
    screen: pg.Surface,
    font: pg.font.Font,
    source: sr.Microphone,
    recognizer: sr.Recognizer,
):
    playback_state = PlaybackState.PAUSED
    t = 0.0

    begin = pg.time.get_ticks()
    end = begin
    dt = 0.0
    while True:
        # Go through pygame events
        for event in pg.event.get():
            # Check quit event
            if event.type == pg.QUIT:
                pg.quit()
                exit()
            # Check keydown event
            elif event.type == pg.KEYDOWN:
                if event.key == pg.K_SPACE:
                    if playback_state == PlaybackState.PAUSED:
                        playback_state = PlaybackState.PLAYING
                    elif playback_state == PlaybackState.PLAYING:
                        playback_state = PlaybackState.PAUSED
                    elif playback_state == PlaybackState.STOPPED:
                        playback_state = PlaybackState.PLAYING

        # Update display
        screen.fill("black")
        pg.display.update()
        # Update clock
        end = pg.time.get_ticks()
        dt = end - begin
        begin = end


if __name__ == "__main__":
    if len(argv) != 2:
        print(f"Usage: {argv[0]} <source>")
        exit(1)
    recognizer = sr.Recognizer()
    pg.init()
    font = pg.font.Font("freesansbold.ttf", 32)
    screen = pg.display.set_mode((500, 100))

    with sr.Microphone() as source:
        main_loop(screen, font, source, recognizer)
