#!/usr/bin/env python3

def main():
	distance = 0
	p1_depth = 0
	p2_depth = 0
	aim = 0
	with open('inputs/02.txt') as f:
		for line in f:
			direction, clicks = line.strip().split(' ', 1)
			clicks = int(clicks)

			if direction == 'forward':
				distance += clicks
				p2_depth += aim*clicks
			elif direction == 'up':
				p1_depth -= clicks
				aim -= clicks
			elif direction == 'down':
				p1_depth += clicks
				aim += clicks
			else:
				print('You f\'d up')

	print(f'Part 1: {distance*p1_depth=}')
	print(f'Part 2: {distance*p2_depth=}')

if __name__ == '__main__':
	main()