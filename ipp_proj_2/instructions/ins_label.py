#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Label(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		if self.checkLabelExistence(self.programMemory, self.instruction['args']['1']['value']):
			ErrorHandler.ERROR_SEMANTIC()

		self.validateLabel(self.instruction['args']['1']['value'])

		self.programMemory['PROG_LABELS'][self.instruction['args']['1']['value']] = self.instruction['instruction_order'] + 1