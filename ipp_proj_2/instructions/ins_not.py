#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Not(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 2:
			ErrorHandler.ERROR_XML_STRUCTURE()

		symb1 = None

		# Loading of input data

		if self.instruction['args']['2']['type'] == 'var':
			self.validateVar(f"{self.instruction['args']['2']['type']}@{self.instruction['args']['2']['value']}")
			varPath = self.instruction['args']['2']['value'].split('@')
			self.checkVarExistence(self.programMemory, varPath[0], varPath[1])
			symb1 = self.programMemory[varPath[0]][varPath[1]] if self.programMemory[varPath[0]][varPath[1]]['type'] == 'bool' else ErrorHandler.ERROR_RUNTIME_OPERAND()
		else:
			symb1 = self.instruction['args']['2'] if self.instruction['args']['2']['type'] == 'bool' else ErrorHandler.ERROR_RUNTIME_OPERAND()

		# Target variable

		self.validateVar(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")
		varPath = self.instruction['args']['1']['value'].split('@')
		self.checkVarExistence(self.programMemory, varPath[0], varPath[1])

		self.programMemory[varPath[0]][varPath[1]] = {
			"type": "bool",
			"value": "true" if not (symb1['value'] == 'true') else "false"
		}