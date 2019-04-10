#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Strlen(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 2:
			ErrorHandler.ERROR_XML_STRUCTURE()

		targetVariable = self.parseVariable(self.programMemory, self.instruction['args']['1'])
		sourceString = None

		if self.instruction['args']['2']['type'] == 'var':
			varPath = self.parseVariable(self.programMemory, self.instruction['args']['2'])
			sourceString = self.programMemory[varPath[0]][varPath[1]]
		else:
			sourceString = self.parseConst(self.instruction['args']['2'])

		if sourceString['type'] != 'string':
			ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()

		self.programMemory[targetVariable[0]][targetVariable[1]] = {
			"type": "int",
			"value": str(len(sourceString['value']))
		}
