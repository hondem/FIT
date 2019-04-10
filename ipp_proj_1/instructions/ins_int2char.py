#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Int2char(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 2:
			ErrorHandler.ERROR_XML_STRUCTURE()

		# Ensuring variables existance etc...
		
		self.validateVar(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")
		target = self.instruction['args']['1']['value'].split('@')
		self.checkVarExistence(self.programMemory, target[0], target[1])

		source = None

		if self.instruction['args']['2']['type'] == 'var':
			self.validateVar(f"{self.instruction['args']['2']['type']}@{self.instruction['args']['2']['value']}")
			source = self.instruction['args']['2']['value'].split('@')
			self.checkVarExistence(self.programMemory, source[0], source[1])
			source = self.programMemory[source[0]][source[1]]

		elif self.instruction['args']['2']['type'] == 'int':
			self.validateConst(f"{self.instruction['args']['2']['type']}@{self.instruction['args']['2']['value']}")
			source = self.instruction['args']['2']
		else:
			ErrorHandler.ERROR_RUNTIME_OPERAND_VALUE()

		if source['type'] != 'int':
			ErrorHandler.ERROR_RUNTIME_OPERAND()

		try:
			self.programMemory[target[0]][target[1]] = {
				"type": "string",
				"value": chr(int(source['value']))
			}
		except:
			ErrorHandler.ERROR_RUNTIME_STRING()
			