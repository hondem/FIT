#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Move(BaseInstruction):
	def __init__(self, instruction, programMemory):
		self.instruction = instruction
		self.programMemory = programMemory

	def eval(self):
		if len(self.instruction['args']) != 2:
			ErrorHandler.ERROR_XML_STRUCTURE()

		self.validateVar(f"{self.instruction['args']['1']['type']}@{self.instruction['args']['1']['value']}")
		
		targetVariable = self.instruction['args']['1']['value'].split('@')

		self.checkVarExistence(self.programMemory, targetVariable[0], targetVariable[1])

		if self.instruction['args']['2']['type'] == 'var':
			
			self.validateVar(f"{self.instruction['args']['2']['type']}@{self.instruction['args']['2']['value']}")

			sourceVariable = self.instruction['args']['2']['value'].split('@')
			self.checkVarExistence(self.programMemory, sourceVariable[0], sourceVariable[1])

			# WE HAVE SUCCESSFULLY VALIDATED ALL INPUTS, NOW WE CAN MOVE ARGUMENT TO ANOTHER ARGUMENT... EYAAAA
			
			self.programMemory[targetVariable[0]][targetVariable[1]] = self.programMemory[sourceVariable[0]][sourceVariable[1]]
		else:

			self.validateConst(self.instruction['args']['2']['type'] + "@" + self.instruction['args']['2']['value'])
			
			# WE HAVE SUCCESSFULLY VALIDATED ALL INPUTS, NOW WE CAN MOVE ARGUMENT TO ANOTHER ARGUMENT... EYAAAAA!

			self.programMemory[targetVariable[0]][targetVariable[1]] = {
				"type": self.instruction['args']['2']['type'],
				"value": self.instruction['args']['2']['value']
			}
