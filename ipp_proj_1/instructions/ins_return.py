#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Return(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 0:
			ErrorHandler.ERROR_XML_STRUCTURE()

		if self.programMemory['PROG_RETURN_STACK'] == []:
			ErrorHandler.ERROR_RUNTIME_MISSING_VALUE()

		return self.programMemory['PROG_RETURN_STACK'].pop(0)