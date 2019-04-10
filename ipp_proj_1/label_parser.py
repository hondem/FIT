#!/usr/bin/env python3

from instructions.ins_label import INS_Label

class LabelParser:
	"""
		This method finds all labels inside program
		and sotres their instruction pointer to
		program memory
	"""
	@staticmethod
	def parseAll(programMemory, program):

		for instructionPointer in range(1, len(program) + 1):
			if program[instructionPointer]['opcode'] == "LABEL":
				programInstruction = program[instructionPointer].copy()
				programInstruction['instruction_order'] = instructionPointer

				INS_Label(programInstruction, programMemory).eval()
