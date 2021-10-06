import sys
import argparse

size = (50, 50)

room_sizes = [
    (5, 5),
    (4, 5),
    (4, 4),
    (3, 4),
    (3, 3),
]


def generate_level() -> str:
    level = [['w' for i in range(size[0])] for j in range(size[1])]

    return '\n'.join([''.join([i for i in row]) for row in level])


parser = argparse.ArgumentParser(description='Generate Procedural Dungeon')
parser.add_argument("template", help="template level file")
parser.add_argument("output", help="output level file")
args = parser.parse_args()

with open(args.template, 'r') as template, open(args.output, 'w') as output:
    for line in template:
        output.write(line)
        if 'World' in line:
            break

    output.write(generate_level())
