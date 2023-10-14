import argparse
import json
import math
import pandas as pd


def clamp(x):
    if x < 0.0:
        return 0.0
    elif x > 1.0:
        return 1.0
    else:
        return x


def lerp(x, data):
    N = len(data)
    a = clamp(x) * (N - 1)
    i = math.floor(a)
    t = a - i
    c0 = data.loc[int(i)]
    c1 = data.loc[int(math.ceil(a))]
    return (1.0 - t) * c0 + t * c1


def heat(x):
    data = pd.DataFrame([[0.0, 0.0, 1.0],
                         [0.0, 1.0, 1.0],
                         [0.0, 1.0, 0.0],
                         [1.0, 1.0, 0.0],
                         [1.0, 0.0, 0.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def gray(x):
    data = pd.DataFrame([[0.0, 0.0, 0.0],
                         [1.0, 1.0, 1.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def blue(x):
    data = pd.DataFrame([[0.0, 0.0, 0.0],
                         [0.0, 0.0, 1.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def green(x):
    data = pd.DataFrame([[0.0, 0.0, 0.0],
                         [0.0, 1.0, 0.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def red(x):
    data = pd.DataFrame([[0.0, 0.0, 0.0],
                         [1.0, 0.0, 0.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]

def purple(x):
    data = pd.DataFrame([[0.0, 0.0, 0.0],
                         [1.0, 0.0, 1.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]

def bluered(x):
    data = pd.DataFrame([[0.0, 0.0, 0.1],
                         [0.25, 0.0, 0.5],
                         [1.0, 0.0, 0.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def hot(x):
    x = clamp(x)
    if x < 0.4:
        t = x / 0.4
        value = [t, 0.0, 0.0]
    elif x < .8:
        t = (x - 0.4) / (0.8 - 0.4)
        value = [1.0, t, 0.0]
    else:
        t = (x - 0.8) / (1.0 - 0.8)
        value = [1.0, 1.0, t]
    return value


def github(x):
    data = pd.DataFrame([[0.933333, 0.933333, 0.933333],
                         [0.776470, 0.894117, 0.545098],
                         [0.482352, 0.788235, 0.435294],
                         [0.137254, 0.603921, 0.231372],
                         [0.098039, 0.380392, 0.152941]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def jet(x):
    data = pd.DataFrame([[0.0, 0.0, 0.5],
                         [0.0, 0.0, 1.0],
                         [0.0, 0.5, 1.0],
                         [0.0, 1.0, 1.0],
                         [0.5, 1.0, 0.5],
                         [1.0, 1.0, 0.0],
                         [1.0, 0.5, 0.0],
                         [1.0, 0.0, 0.0],
                         [0.5, 0.0, 0.0]], columns=['r', 'g', 'b'])
    color = lerp(x, data)
    return [color['r'], color['g'], color['b']]


def accent(x):
    data = pd.DataFrame([[0x7f, 0xc9, 0x7f],
                         [0xbe, 0xae, 0xd4],
                         [0xfd, 0xc0, 0x86],
                         [0xff, 0xff, 0x99],
                         [0x38, 0x6c, 0xb0],
                         [0xf0, 0x02, 0x7f],
                         [0xbf, 0x5b, 0x17],
                         [0x66, 0x66, 0x66]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]


def sand(x):
    data = pd.DataFrame([[0x60, 0x48, 0x60],
                         [0x78, 0x48, 0x60],
                         [0xa8, 0x60, 0x60],
                         [0xc0, 0x78, 0x60],
                         [0xf0, 0xa8, 0x48],
                         [0xf8, 0xca, 0x8c],
                         [0xfe, 0xec, 0xae],
                         [0xff, 0xf4, 0xc2],
                         [0xff, 0xf7, 0xdb],
                         [0xff, 0xfc, 0xf6]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]


def rdpu(x):
    data = pd.DataFrame([[0xff, 0xf7, 0xf3],
                         [0xfd, 0xe0, 0xdd],
                         [0xfc, 0xc5, 0xc0],
                         [0xfa, 0x9f, 0xb5],
                         [0xf7, 0x68, 0xa1],
                         [0xdd, 0x34, 0x97],
                         [0xae, 0x01, 0x7e],
                         [0x7a, 0x01, 0x77]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]


def gnpu(x):
    data = pd.DataFrame([[0x39, 0x63, 0x53],
                         [0x0d, 0xb1, 0x4b],
                         [0x6d, 0xc0, 0x67],
                         [0xab, 0xd6, 0x9b],
                         [0xda, 0xea, 0xc1],
                         [0xdf, 0xcc, 0xe4],
                         [0xc7, 0xb2, 0xd6],
                         [0x94, 0x74, 0xb4],
                         [0x75, 0x40, 0x98],
                         [0x50, 0x49, 0x71]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]


def set1(x):
    data = pd.DataFrame([[0xE4, 0x1A, 0x1C],
                         [0x37, 0x7E, 0xB8],
                         [0x4D, 0xAF, 0x4A],
                         [0x98, 0x4E, 0xA3],
                         [0xFF, 0x7F, 0x00],
                         [0xFF, 0xFF, 0x33],
                         [0xA6, 0x56, 0x28],
                         [0xF7, 0x81, 0xBF]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]


def paired(x):
    data = pd.DataFrame([[0xA6, 0xCE, 0xE3],
                         [0x1F, 0x78, 0xB4],
                         [0xB2, 0xDF, 0x8A],
                         [0x33, 0xA0, 0x2C],
                         [0xFB, 0x9A, 0x99],
                         [0xE3, 0x1A, 0x1C],
                         [0xFD, 0xBF, 0x6F],
                         [0xFF, 0x7F, 0x00]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]


def rainbow(x):
    data = pd.DataFrame([[0xBE, 0x0A, 0xFF],
                         [0x58, 0x0A, 0xFF],
                         [0x14, 0x7D, 0x85],
                         [0x0A, 0xEF, 0xFF],
                         [0x0A, 0xFF, 0x99],
                         [0xA1, 0xFF, 0x0A],
                         [0xDE, 0xFF, 0x0A],
                         [0xFF, 0xD3, 0x00],
                         [0XFF, 0x87, 0x00],
                         [0XFF, 0x00, 0x00]], columns=['r', 'g', 'b'])
    color = lerp(x, data/255)
    return [color['r'], color['g'], color['b']]

def main():
    parser = argparse.ArgumentParser(
        prog='Generate palette',
        description='Generate paletten based on type')

    parser.add_argument('-t', '--type', required=True,
                        help='type of palettep to generate')
    parser.add_argument('-b', '--brightness', required=False,
                        default=1, type=int, help='Brightness factor')

    args = parser.parse_args()

    colors = []

    for row in range(0, 256):
        x = row / 255.0
        if args.type == 'hot':
            value = hot(x)
        elif args.type == 'heat':
            value = heat(x)
        elif args.type == 'jet':
            value = jet(x)
        elif args.type == 'github':
            value = github(x)
        elif args.type == 'accent':
            value = accent(x)
        elif args.type == 'sand':
            value = sand(x)
        elif args.type == 'rdpu':
            value = rdpu(x)
        elif args.type == 'gnpu':
            value = gnpu(x)
        elif args.type == 'set1':
            value = set1(x)
        elif args.type == 'paired':
            value = paired(x)
        elif args.type == 'gray' or args.type == 'grey':
            value = gray(x)
        elif args.type == 'red':
            value = red(x)
        elif args.type == 'green':
            value = green(x)
        elif args.type == 'blue':
            value = blue(x)
        elif args.type == 'purple':
            value = purple(x)
        elif args.type == 'bluered':
            value = bluered(x)
        elif args.type == 'rainbow':
            value = rainbow(x)
        else:
            value = [x, x, x]

        colors.append(int(value[0]*255))
        colors.append(int(value[1]*255))
        colors.append(int(value[2]*255))

    if len(colors) > 0:
        with open(args.type+'.json', 'w') as json_file:
            json.dump(
                {"colors": colors, "brightness": args.brightness}, json_file)


if __name__ == '__main__':
    main()
