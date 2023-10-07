import argparse
import pandas as pd
import os
import json


def main():
    parser = argparse.ArgumentParser(
        prog='Convert palette',
        description='Converts csv to palette json')

    parser.add_argument('-f', '--file', required=True,
                        help='csv file to convert')
    parser.add_argument('-o', '--output', required=True,
                        help='output filename')
    parser.add_argument('-b', '--brightness', required=False,
                        default=1, type=int, help='Brightness factor')

    args = parser.parse_args()

    if os.path.exists(args.file):
        colors = []
        palette = pd.read_csv(args.file, sep=',')
        for row in palette.itertuples():
            colors.append(int(row.r*255))
            colors.append(int(row.g*255))
            colors.append(int(row.b*255))

        with open(args.output, 'w') as json_file:
            json.dump({"colors": colors, "brightness": args.brightness}, json_file)


if __name__ == '__main__':
    main()
