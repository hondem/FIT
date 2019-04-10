#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Pushs(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		sourceSymb = None

		if self.instruction['args']['1']['type'] == 'var':
			varPath = self.parseVariable(self.programMemory, self.instruction['args']['1'])
			sourceSymb = self.programMemory[varPath[0]][varPath[1]]
		else:
			sourceSymb = self.parseConst(self.instruction['args']['1'])

		if sourceSymb['type'] == "":
			ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()

		self.programMemory['PROG_STACK'] = [sourceSymb.copy()] + self.programMemory['PROG_STACK']