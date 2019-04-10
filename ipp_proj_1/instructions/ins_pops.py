#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Pops(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		targetVariable = self.parseVariable(self.programMemory, self.instruction['args']['1'])

		if self.programMemory['PROG_STACK'] == []:
			ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()
		
		self.programMemory[targetVariable[0]][targetVariable[1]] = self.programMemory['PROG_STACK'].pop(0)
		