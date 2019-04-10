#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Defvar(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 1:
			ErrorHandler.ERROR_XML_STRUCTURE()

		self.validateVar(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")

		varPath = self.instruction['args']['1']['value'].split('@')

		self.checkFrameExistence(self.programMemory, varPath[0])

		# NOW LETS DEFINE THE VARIABLE IN CERTAIN FRAME!
		self.programMemory[varPath[0]][varPath[1]] = {
			"type": "",
			"value": ""
		}