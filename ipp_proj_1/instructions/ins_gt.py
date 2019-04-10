#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Gt(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 3:
			ErrorHandler.ERROR_XML_STRUCTURE()

		targetVariable = self.parseVariable(self.programMemory, self.instruction['args']['1'])
		symb1 = None
		symb2 = None

		if self.instruction['args']['2']['type'] == 'var':
			varPath = self.parseVariable(self.programMemory, self.instruction['args']['2'])
			symb1 = self.programMemory[varPath[0]][varPath[1]]
		else:
			symb1 = self.parseConst(self.instruction['args']['2'])

		if self.instruction['args']['3']['type'] == 'var':
			varPath = self.parseVariable(self.programMemory, self.instruction['args']['3'])
			symb2 = self.programMemory[varPath[0]][varPath[1]]
		else:
			symb2 = self.parseConst(self.instruction['args']['3'])

		if symb1['type'] != symb2['type']:
			ErrorHandler.ERROR_RUNTIME_OPERAND()

		boolValue = None

		# we have two strings
		if symb1['type'] == 'string':
			boolValue = symb1['value'] > symb2['value']

		# we have two integers
		elif symb1['type'] == 'int':
			boolValue = int(symb1['value']) > int(symb2['value'])
		
		# we have two bools
		elif symb1['type'] == 'bool':
			boolValue = bool(symb1['value']) > bool(symb2['value'])
		
		# we have something else
		else:
			ErrorHandler.ERROR_RUNTIME_OPERAND()

		self.programMemory[targetVariable[0]][targetVariable[1]] = {
			"type": "bool",
			"value": "true" if boolValue else "false"
		}