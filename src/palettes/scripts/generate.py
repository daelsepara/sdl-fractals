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


def main():
    parser = argparse.ArgumentParser(
        prog='Convert palette',
        description='Converts csv to palette json')

    parser.add_argument('-t', '--type', required=True,
                        help='csv file to convert')
    parser.add_argument('-o', '--output', required=True,
                        help='output filename')
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
