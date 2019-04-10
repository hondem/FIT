#!/usr/bin/env python3

# Base class for instruction
# Every single instruction inherits from this class

import abc
import re
from error_handler import ErrorHandler

class BaseInstruction:

	@abc.abstractmethod
	def eval(self):
		pass

	"""
		This method helps other classes to find out if
		variable they are trying to manipulate with exists
	"""
	@staticmethod
	def checkVarExistence(programMemory, frame, variable):
		if frame == 'GF':
			if variable not in programMemory['GF']:
				ErrorHandler.ERROR_RUNTIME_UNDEFINED_VARIABLE()
		
		else:
			BaseInstruction.checkFrameExistence(programMemory, frame)

			if variable not in programMemory[frame]:
				ErrorHandler.ERROR_RUNTIME_UNDEFINED_VARIABLE()

	"""
		This method checks for existence of frame
	"""
	@staticmethod
	def checkFrameExistence(programMemory, frame):
		if(
			(frame == 'TF' and programMemory['TF'] == None) or
			(frame == 'LF' and programMemory['LF'] == None) or
			(frame == 'LF_STACK' and programMemory['LF_STACK'] == [])
		): 
			ErrorHandler.ERROR_RUNTIME_UNDEFINED_FRAME()

	"""
		This method checks for label existence
	"""
	@staticmethod
	def checkLabelExistence(programMemory, label):
		return True if (label in programMemory['PROG_LABELS']) else False

	"""
		This method ensures that label has the right lexical structure
	"""
	@staticmethod
	def validateLabel(label):
		if not re.search("^([a-zA-Z]|[_$&%*!?-])([a-zA-Z]|[_$&%*!?-]|[0-9])*$", label):
			ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

	"""
		This method ensures that var has the right lexical structure
	"""
	@staticmethod
	def validateVar(var):
		if not re.search("^var@(LF|TF|GF)@([a-zA-Z]|[_$&%*!?-])([a-zA-Z]|[_$&%*!?-]|[0-9])*$", var):
			ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

	"""
		This method validates string with escape seq
	"""
	@staticmethod
	def validateStringWithEscapeSeq(string):
		if not re.search("^string@(\\\\\d{3,}|[^\\\\\s])*$", string):
			ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

	"""
		This method ensures that const has the right lexical structure
	"""
	@staticmethod
	def validateConst(const):
		if not ( 
			re.search("^nil@nil$", const) or
			re.search("^bool@(true|false)$", const) or
			re.search("^int@(-{0,1}[1-9][0-9]*|0)$", const) or
			re.search("^string@.*$", const)
		):
			ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

	"""
		This method ensures type has the right lexical structure
	"""
	@staticmethod
	def validateType(type):
		if not re.search("^type@(int|string|bool)$", type):
			ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

	"""
		This helps parsing variable
	"""
	@staticmethod
	def parseVariable(programMemory, arg):
		if arg['type'] != 'var':
			ErrorHandler.ERROR_XML_STRUCTURE()

		BaseInstruction.validateVar(f"{arg['type']}@{arg['value']}")
		varPath = arg['value'].split('@')
		BaseInstruction.checkVarExistence(programMemory, varPath[0], varPath[1])
		return varPath

	"""
		This helps parsing const
	"""
	@staticmethod
	def parseConst(arg):
		BaseInstruction.validateConst(f"{arg['type']}@{arg['value']}")
		return arg

	"""
		This helps parsing type
	"""
	@staticmethod
	def parseType(arg):
		BaseInstruction.validateType(f"{arg['type']}@{arg['value']}")
		return arg
