#!/usr/bin/env python3

import sys

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Dprint(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		if self.instruction['args']['1']['type'] == 'var':
			varPath = self.parseVariable(self.programMemory, self.instruction['args']['1'])
			memVar = self.programMemory[varPath[0]][varPath[1]]

			print(memVar['value'], file=sys.stderr)
		
		else:
			data = self.parseConst(self.instruction['args']['1'])
			print(data['value'], file=sys.stderr)