import noise
import numpy as np
from PIL import Image

shape = (1024, 1024)
scale = 150.0
octaves = 6
persistence = 0.4
lacunarity = 4.4

backdrop = np.zeros(shape)
for i in range(shape[0]):
    for j in range(shape[1]):
        backdrop[i][j] = noise.pnoise2(
            i/scale,
            j/scale,
            octaves=octaves,
            persistence=persistence,
            lacunarity=lacunarity,
            repeatx=1024,
            repeaty=1024,
            base=0
        )


sky = [
    [53, 81, 92],
    [135, 206, 235],
]

cloud = [
    [246, 246, 246],
    [204, 204, 204],
    [171, 171, 171],
    [144, 144, 144],
    [116, 116, 116],
]


def add_color(image):
    color = np.zeros(image.shape+(3,))
    for i in range(shape[0]):
        for j in range(shape[1]):
            if image[i][j] < 0.18:
                diff = np.array(sky[1]) - np.array(sky[0])
                rand = np.random.randint(20, size=3)
                color[i][j] = np.array(sky[0]) + diff * i / shape[0] + rand
            elif image[i][j] < 0.22:
                color[i][j] = cloud[2]
            elif image[i][j] < 0.3:
                color[i][j] = cloud[1]
            elif image[i][j] < 1.0:
                color[i][j] = cloud[0]

    return color


backdrop = add_color(backdrop).astype(np.uint8)
Image.fromarray(backdrop, 'RGB').save("imgs/backdrop4.jpg")
