#!/usr/bin/env python3

# Class for parsing arguments
# from command line

# Allowed arguments are
# --help
# --source=file
# --source="file"
# --input=file
# --input="file"

import sys
import re

class ArgumentsParser:

	"""
		Parses input arguments into objects and return them
	"""
	@staticmethod
	def parse():
		args = {}

		for argument in sys.argv[1:]:
			# Search for --something=file pattern
			if re.search("^--[a-zA-Z]*=.+$", argument):
				splitedArg = argument.split("=")
				args[splitedArg[0]] = splitedArg[1]
			elif argument == '--help':
				args[argument] = None

		return args
