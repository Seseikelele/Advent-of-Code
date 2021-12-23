#!/usr/bin/env python3

def load_input(path) -> list[str]:
	with open(path) as f:
		return [line.strip() for line in f]

def count_ones_in_columns(inputs):
	one_count = None
	for line in inputs:
		line = line.strip()
		if not one_count:
			one_count = [0 for _ in line]

		for i, c in enumerate(line):
			one_count[i] += int(c)
	return one_count

def part_1(inputs: list[str]):
	line_count = len(inputs)
	one_count = count_ones_in_columns(inputs)

	gamma_rate = ''
	epsilon_rate = ''
	for column_one_count in one_count:
		if column_one_count > line_count/2:
			gamma_rate += '1'
			epsilon_rate += '0'
		else:
			gamma_rate += '0'
			epsilon_rate += '1'
	gamma_rate = int(gamma_rate, 2)
	epsilon_rate = int(epsilon_rate, 2)

	print(f'Part 1: {gamma_rate*epsilon_rate=}')

def split(inputs, column) -> tuple[list, list]:
	zeros = list()
	ones = list()
	for input in inputs:
		if input[column] == '0':
			zeros.append(input)
		elif input[column] == '1':
			ones.append(input)
		else:
			print('fuck')
	return zeros, ones

def determine_rating(inputs: list[str], most_common_ones=True):
	line_count = len(inputs)
	one_count = count_ones_in_columns(inputs)
	rating = inputs

	for cursor in range(len(inputs[0])):
		zeros, ones = split(rating, cursor)
		if one_count[cursor] >= line_count/2:
			rating = ones if most_common_ones else zeros
		elif one_count[cursor] < line_count/2:
			rating = zeros if most_common_ones else ones
		one_count = count_ones_in_columns(rating)
		line_count = len(rating)
		if len(rating) == 1:
			return int(rating[0], 2)
	raise Exception('Rating not found.')

def part_2(inputs: list[str]):
	oxy_gen_rating = determine_rating(inputs)
	scrubber_rating = determine_rating(inputs, False)
	print(f'Part 2: {oxy_gen_rating*scrubber_rating=}')

def main():
	inputs = load_input('inputs/03.txt')
	part_1(inputs)
	part_2(inputs)


	# print(f'Part 2: {distance*p2_depth=}')

if __name__ == '__main__':
	main()