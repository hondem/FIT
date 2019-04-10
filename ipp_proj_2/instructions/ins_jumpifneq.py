#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Jumpifneq(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory
		#self.callback = callback

	def eval(self):
		if len(self.instruction['args']) != 3:
			ErrorHandler.ERROR_XML_STRUCTURE()

		label = self.instruction['args']['1']
		self.validateLabel(label['value'])

		if label['value'] not in self.programMemory['PROG_LABELS']:
			ErrorHandler.ERROR_SEMANTIC()

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

		if symb1['value'] != symb2['value']:
			return self.programMemory['PROG_LABELS'][label['value']]