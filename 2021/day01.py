#!/usr/bin/env python3


def main():
	measurements = None
	with open('inputs/01.txt') as f:
		measurements = [int(line.strip()) for line in f]

	measurement_increases = 0
	measurement_window_increases = 0
	previous_measurement = None
	previous_measurement_window_sum = None
	measurement_1 = None
	measurement_2 = None
	for measurement_3 in measurements:
		# Part 1 - increases in single measurements
		if measurement_2 and measurement_2 < measurement_3:
			measurement_increases += 1
		# Part 2 - increases in measurement window of three measurements
		if measurement_1 and measurement_2:
			measurement_window_sum = measurement_1 + measurement_2 + measurement_3
			if previous_measurement_window_sum and previous_measurement_window_sum < measurement_window_sum:
				measurement_window_increases += 1
			previous_measurement_window_sum = measurement_window_sum

		measurement_1 = measurement_2
		measurement_2 = measurement_3

	print(f'{measurement_increases=}')
	print(f'{measurement_window_increases=}')

if __name__ == '__main__':
	main()