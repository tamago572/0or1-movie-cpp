import cv2
import sys
import pygame

args = sys.argv

videoPath = args[1]
audio = args[2]

cap = cv2.VideoCapture(videoPath)

if (cap.isOpened() == False):
    print("Error opening video stream or file")
    sys.exit()

maxFrames = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
fps = cap.get(cv2.CAP_PROP_FPS)
img_h = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
img_w = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))

ret, img = None, None


clock = pygame.time.Clock()


pygame.mixer.init()
pygame.mixer.music.load(audio)
pygame.mixer.music.play(1)

for i in range(maxFrames):
    ret, img = cap.read()

    if not ret:
        print("ERROR!! フレームが読み込まれませんでした！")
        break


    for y in range(img_h):
        for x in range(img_w):
            B = img[y, x, 0]
            G = img[y, x, 1]
            R = img[y, x, 2]

            text = 0
            if (B > 36):
                text = 1;

            print("\x1b[38;2;" + str(R) + ";" + str(G) + ";" + str(B) + "m" + str(text), end="")
        print("\x1b[0m")

    print(f"frame: {i}")

    print("\033[" + str(img_h+2) + "A")

    clock.tick_busy_loop(fps)
