#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Jump(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory
		#self.callback = callback

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		label = self.instruction['args']['1']
		self.validateLabel(label['value'])

		if label['value'] not in self.programMemory['PROG_LABELS']:
			ErrorHandler.ERROR_SEMANTIC()

		return self.programMemory['PROG_LABELS'][label['value']]