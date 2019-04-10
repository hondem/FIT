#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Write(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		if self.instruction['args']['1']['type'] in ['string', 'int', 'bool', 'nil']:
			# Type is const, so we can directly print it!
			self.validateConst(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")

			if self.instruction['args']['1']['type'] != 'nil':
				print(self.instruction['args']['1']['value'], end="")
		else:
			# We want to print something from programMemory
			
			self.validateVar(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")
			
			varPath = self.instruction['args']['1']['value'].split('@')

			self.checkVarExistence(self.programMemory, varPath[0], varPath[1])
			
			if self.programMemory[varPath[0]][varPath[1]]['type'] == "":
				ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()

			if self.programMemory[varPath[0]][varPath[1]]['type'] != 'nil':
				print(self.programMemory[varPath[0]][varPath[1]]['value'], end="")