#!/usr/bin/env python3


def main():
	measurements = None
	with open('inputs/01.txt') as f:
		measurements = [int(line.strip()) for line in f]

	single_increases = 0
	sum_increases = 0
	prev_sum = None
	measurement_1 = None
	measurement_2 = None
	for measurement_3 in measurements:
		# Part 1 - increases in single measurements
		if measurement_2 and measurement_2 < measurement_3:
			single_increases += 1
		# Part 2 - increases in measurement window of three measurements
		if measurement_1 and measurement_2:
			curr_sum = measurement_1 + measurement_2 + measurement_3
			if prev_sum and prev_sum < curr_sum:
				sum_increases += 1
			prev_sum = curr_sum

		measurement_1 = measurement_2
		measurement_2 = measurement_3

	print(f'{single_increases=}')
	print(f'{sum_increases=}')

if __name__ == '__main__':
	main()