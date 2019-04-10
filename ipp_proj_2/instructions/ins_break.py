#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

import json

class INS_Break(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 0:
			ErrorHandler.ERROR_XML_STRUCTURE()

		ErrorHandler.eprint("PROGRAM MEMORY: ", json.dumps(self.programMemory, indent=2))