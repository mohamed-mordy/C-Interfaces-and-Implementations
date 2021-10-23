#!/usr/bin/env python3

import os

def main():
	print(count_lines("."))

def count_lines(directory):
	count = 0
	for obj in os.listdir(directory):
		fullpath = os.path.join(directory, obj)
		if os.path.isdir(fullpath):
			count += count_lines(fullpath)
		elif obj.endswith(".c") or obj.endswith(".h"):
			nlines = 0
			with open(fullpath) as file:
				for line in file:
					nlines += 1
			print(fullpath, f"\tno of lines:{nlines}")
			count += nlines
	return count

if __name__ == "__main__":
	exit(main())
    
