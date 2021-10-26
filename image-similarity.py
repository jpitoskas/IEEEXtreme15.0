# a simple parser for python. use get_number() and get_word() to read
def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)

input_parser = parser()

def get_word():
    global input_parser
    return next(input_parser)

def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)


import numpy as np
from numpy.lib.stride_tricks import as_strided


def max_overlap(a, b):
    b_p = np.pad(b, ((a.shape[0]-1, a.shape[0]-1), (a.shape[1]-1, a.shape[1]-1)), 'constant', constant_values=0)
    output_shape = (b_p.shape[0] - a.shape[0] + 1, b_p.shape[1] - a.shape[1] + 1)
    b_w = as_strided(b_p, shape=output_shape + a.shape,
                          strides=b_p.strides*2)
    c = (b_w * a).sum(axis=(2,3))
    return c.max()

def map_pixel(pxl):
    return 1 if pxl == "#" else 0


T = get_number()

for _ in range(T):

    R1 = get_number()
    C1 = get_number()
    image1 = []
    for r in range(R1):
        row = []
        row_syms = get_word()
        for c in range(C1):
            row.append(map_pixel(row_syms[c]))
        image1.append(row)

    R2 = get_number()
    C2 = get_number()
    image2 = []
    for r in range(R2):
        row = []
        row_syms = get_word()
        for c in range(C2):
            row.append(map_pixel(row_syms[c]))
        image2.append(row)

    image1 = np.array(image1)
    image2 = np.array(image2)

    im1 = image1
    im2 = np.fliplr(image1)
    im3 = np.flipud(image1)
    im4 = np.flipud(im2)
    im5 = np.rot90(image1)
    im6 = np.fliplr(im5)
    im7 = np.flipud(im5)
    im8 = np.fliplr(im7)
    im9 = np.rot90(im5)
    im10 = np.flipud(im9)
    im11 = np.fliplr(im9)
    im12 = np.fliplr(im10)
    im13 = np.rot90(im10)

    images = [image1, im1, im2, im3, im4, im5, im6, im7, im8, im9, im10, im11, im12, im13]
    max_val = 0
    for image in images:
        max_val = max(max_val, max_overlap(image, image2))
    print(max_val)
