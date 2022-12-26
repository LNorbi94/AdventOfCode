def get_pixel_coordinates(pixel):
    #print(cycle)
    x = (pixel - 1) % 40
    y = int((pixel - 1) / 40)
    return (y, x)

def sprite_pixels(sprite):
    return [
        (sprite),
        (sprite - 1),
        (sprite + 1)
    ]

with open('day_10.txt') as f:
    sprite = 1
    cycle = 1
    pixels = []
    for i in range(0, 6):
        for j in range(0, 40):
            if len(pixels) < i + 1:
                pixels.append([])
            pixels[i].append('.')

    for line in f.readlines():
        #print(cycle)
        coords = get_pixel_coordinates(cycle)
        if coords[1] in sprite_pixels(sprite):
            pixels[coords[0]][coords[1]] = '#'
        if coords[1] + 1 in sprite_pixels(sprite):
            pixels[coords[0]][coords[1] + 1] = '#'
        if 'noop' in line:
            cycle += 1
            continue
        to_add = int(line.split(' ')[1])
        cycle += 2
        sprite += to_add
        #print(sprite)

    for i in range(0, 6):
        line = ' '.join(pixels[i])
        print(line)