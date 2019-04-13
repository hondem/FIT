#!/usr/bin/env python3


# Simple class to ensure
# handling errors


import sys

class ErrorHandler:
	# ===== ERROR CODES =====
	CODE_PARAM_ERROR = 10
	CODE_INPUT_FILE_ERROR = 11
	CODE_OUTPUT_FILE_ERROR = 12

	CODE_INPUT_XML = 31
	CODE_XML_STRUCTURE = 32

	CODE_SEMANTIC = 52
	CODE_RUNTIME_OPERAND = 53
	CODE_RUNTIME_UNDEFINED_VARIABLE = 54
	CODE_RUNTIME_UNDEFINED_FRAME = 55
	CODE_RUNTIME_MISSING_VALUE = 56
	CODE_RUNTIME_OPERAND_VALUE = 57
	CODE_RUNTIME_STRING = 58

	CODE_INTERNAL_ERROR = 99

	"""
		Prints a message to STDERR
	"""
	@staticmethod
	def eprint(*args, **kwargs):
		sys.stdout.flush()
		print("", file=sys.stderr)
		print(*args, file=sys.stderr, **kwargs)

	"""
		Throws param error
	"""
	@staticmethod
	def ERROR_PARAM():
		ErrorHandler.eprint("\033[31mERROR: Bad or forbidden use of parameters\033[39m")
		sys.exit(ErrorHandler.CODE_PARAM_ERROR)

	"""
		Throws input file error
	"""
	@staticmethod
	def ERROR_INPUT_FILE():
		ErrorHandler.eprint("\033[31mERROR: Bad or damaged input file\033[39m")
		sys.exit(ErrorHandler.CODE_INPUT_FILE_ERROR)

	"""
		Throws output file error
	"""
	@staticmethod
	def ERROR_OUTPUT_FILE():
		ErrorHandler.eprint("\033[31mERROR: Bad or damaged output file\033[39m")
		sys.exit(ErrorHandler.CODE_OUTPUT_FILE_ERROR)

	"""
		Throws semantic error
	"""
	@staticmethod
	def ERROR_SEMANTIC():
		ErrorHandler.eprint("\033[31mERROR: Semantic or syntactic error\033[39m")
		sys.exit(ErrorHandler.CODE_SEMANTIC)

	"""
		Throws runtime error with operand
	"""
	@staticmethod
	def ERROR_RUNTIME_OPERAND():
		ErrorHandler.eprint("\033[31mERROR: Runtime error - forbidden use of operand\033[39m")
		sys.exit(ErrorHandler.CODE_RUNTIME_OPERAND)

	"""
		Throws runtime error undefined variable
	"""
	@staticmethod
	def ERROR_RUNTIME_UNDEFINED_VARIABLE():
		ErrorHandler.eprint("\033[31mERROR: Runtime error - Use of undefined variable\033[39m")
		sys.exit(ErrorHandler.CODE_RUNTIME_UNDEFINED_VARIABLE)

	"""
		Throws runtime error undefined frame
	"""
	@staticmethod
	def ERROR_RUNTIME_UNDEFINED_FRAME():
		ErrorHandler.eprint("\033[31mERROR: Runtime error - Use of undefined frame\033[39m")
		sys.exit(ErrorHandler.CODE_RUNTIME_UNDEFINED_FRAME)

	"""
		Throws runtime error missing value
	"""
	@staticmethod
	def ERROR_RUNTIME_MISSING_VALUE():
		ErrorHandler.eprint("\033[31mERROR: Runtime error - Missing value\033[39m")
		sys.exit(ErrorHandler.CODE_RUNTIME_MISSING_VALUE)

	"""
		Throws runtime error missing value
	"""
	@staticmethod
	def ERROR_RUNTIME_OPERAND_VALUE():
		ErrorHandler.eprint("\033[31mERROR: Runtime error - Bad or forbidden operand value\033[39m")
		sys.exit(ErrorHandler.CODE_RUNTIME_OPERAND_VALUE)

	"""
		Throws runtime error with string
	"""
	@staticmethod
	def ERROR_RUNTIME_STRING():
		ErrorHandler.eprint("\033[31mERROR: Runtime error - Bad string\033[39m")
		sys.exit(ErrorHandler.CODE_RUNTIME_STRING)

	"""
		Throws internal error
	"""
	@staticmethod
	def ERROR_INTERNAL():
		ErrorHandler.eprint("\033[31mERROR: Internal error\033[39m")
		sys.exit(ErrorHandler.CODE_INTERNAL_ERROR)

	"""
		Throws XML format error
	"""
	@staticmethod
	def ERROR_XML_INPUT():
		ErrorHandler.eprint("\033[31mERROR: Error parsing input XML\033[39m")
		sys.exit(ErrorHandler.CODE_INPUT_XML)

	"""
		Throws internal error
	"""
	@staticmethod
	def ERROR_XML_STRUCTURE():
		ErrorHandler.eprint("\033[31mERROR: Bad XML structure or unknown opcode\033[39m")
		sys.exit(ErrorHandler.CODE_XML_STRUCTURE)