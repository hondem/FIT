#!/usr/bin/env python3

from . base_instruction import BaseInstruction
from error_handler import ErrorHandler

class INS_Read(BaseInstruction):
	def __init__(self, instruction, programMemory, inputFile):
		self.instruction = instruction
		self.programMemory = programMemory
		self.inputFile = inputFile

	def eval(self):
		if len(self.instruction['args']) != 2:
			ErrorHandler.ERROR_XML_STRUCTURE()

		targetVariable = self.parseVariable(self.programMemory, self.instruction['args']['1'])
		readType = self.parseType(self.instruction['args']['2'])
		finalData = {
			"type": None,
			"value": None
		}

		try:
			if self.inputFile == "STDIN":
				inputLine = input()
			else:
				inputLine = self.inputFile.readline().rstrip("\r\n")

		except:
			if readType['value'] == "int":
				finalData = {
					"type": "int",
					"value": "0"
				}
			elif readType['value'] == "bool":
				finalData = {
					"type": "bool",
					"value": "false"
				}
			elif readType['value'] == "string":
				finalData = {
					"type": "string",
					"value": ""
				}

			self.programMemory[targetVariable[0]][targetVariable[1]] = finalData
			return

		if readType['value'] == "int":
			finalData['type'] = 'int'

			try:
				finalData['value'] = int(inputLine)
			except:
				finalData['value'] = 0
		
		elif readType['value'] == "bool":
			finalData['type'] = 'bool'

			if inputLine.lower() == "true":
				finalData['value'] = "true"
			else:
				finalData['value'] = "false"

		elif readType['value'] == "string":
			finalData = {
				"type": "string",
				"value": inputLine
			}

		self.programMemory[targetVariable[0]][targetVariable[1]] = finalData
