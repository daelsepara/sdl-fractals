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
