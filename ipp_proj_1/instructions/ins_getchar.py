#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Getchar(BaseInstruction):
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


		# ALL SYMBOLS ARE NOW LOADED

		if symb1['type'] == "" or symb2['type'] == "":
			ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()

		if symb1['type'] != 'string' or symb2['type'] != 'int':
			ErrorHandler.ERROR_RUNTIME_OPERAND()

		try:
			self.programMemory[targetVariable[0]][targetVariable[1]] = {
				"type": "string",
				"value": symb1['value'][int(symb2['value'])]
			}
		except:
			ErrorHandler.ERROR_RUNTIME_STRING()