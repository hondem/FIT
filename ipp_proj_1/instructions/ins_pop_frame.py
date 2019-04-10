#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_PopFrame(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 0:
			ErrorHandler.ERROR_XML_STRUCTURE()

		self.checkFrameExistence(self.programMemory, 'LF')
		
		self.programMemory['TF'] = self.programMemory['LF']
		self.programMemory['LF'] = self.programMemory['LF_STACK'].pop(0) if self.programMemory['LF_STACK'] != [] else {}
		