#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Setchar(BaseInstruction):
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

		if symb1['type'] != 'int' or symb2['type'] != 'string':
			ErrorHandler.ERROR_RUNTIME_OPERAND()

		if len(symb2['value']) == 0:
			ErrorHandler.ERROR_RUNTIME_STRING()

		targetVariableContent = self.programMemory[targetVariable[0]][targetVariable[1]]

		if targetVariableContent['type'] != "string":
			ErrorHandler.ERROR_RUNTIME_OPERAND()

		if int(symb1['value']) < 0 or int(symb1['value']) >= len(targetVariableContent['value']):
			ErrorHandler.ERROR_RUNTIME_STRING()

		try:
			targetVariableContent['value'] = targetVariableContent['value'][:int(symb1['value'])] + symb2['value'][0] + targetVariableContent['value'][int(symb1['value']) + 1:]
			self.programMemory[targetVariable[0]][targetVariable[1]] = targetVariableContent
		except:
			ErrorHandler.ERROR_RUNTIME_STRING()