#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler
import sys

class INS_Exit(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		if self.instruction['args']['1']['type'] == 'int':
			if int(self.instruction['args']['1']['value']) >= 0 and int(self.instruction['args']['1']['value']) <= 49:
				sys.exit(int(self.instruction['args']['1']['value']))
			else:
				ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

		elif self.instruction['args']['1']['type'] == 'var':
			
			self.validateVar(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")
			varPath = self.instruction['args']['1']['value'].split('@')
			self.checkVarExistence(self.programMemory, varPath[0], varPath[1])

			if self.programMemory[varPath[0]][varPath[1]]['type'] == '':
				ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()

			if self.programMemory[varPath[0]][varPath[1]]['type'] != 'int':
				ErrorHandler.ERROR_SEMANTIC()

			if int(self.programMemory[varPath[0]][varPath[1]]['value']) >= 0 and int(self.programMemory[varPath[0]][varPath[1]]['value']) <= 49:
				sys.exit(int(self.programMemory[varPath[0]][varPath[1]]['value']))
			else:
				ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()
		
		else:
			ErrorHandler.ERROR_RUNTIME_OPERAND()