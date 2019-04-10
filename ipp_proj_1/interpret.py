#!/usr/bin/env python3

import json
import sys
import re
import xml.etree.ElementTree as ET

from instructions.base_instruction import BaseInstruction
from instructions.instructions import *
from error_handler import ErrorHandler
from arguments_parser import ArgumentsParser
from label_parser import LabelParser

# ====== Defining usefull methods =====

def printHelp():
	print('This script interprets programm written in .IPPCode19')
	print('Usage: python3 interpret.py [--help, [--source=file, --input=file]]')
	sys.exit(0)

def removeEscapeSeq(inputString):
	escapeSequences = re.findall("\\\\[0-9]{3}", inputString)
	
	for escape in escapeSequences:
		inputString = inputString.replace(escape, chr(int(escape.replace("\\", ""))))
	return inputString

# ====== Parsing arguments ======

args = ArgumentsParser.parse()

if '--help' in args:
	printHelp()
elif '--source' not in args and '--input' not in args:
	ErrorHandler.ERROR_PARAM()
elif '--source' in args and '--input' not in args:
	args['--input'] = 'STDIN'
elif '--source' not in args and '--input' in args:
	args['--source'] = 'STDIN'

# ====== Loading source XML and input =====

sourceFile = None
inputFile = None

try:
	if args['--source'] == "STDIN":
		sourceFile = sys.stdin
	else:
		sourceFile = open(args['--source'], 'r')

	if args['--input'] == "STDIN":
		inputFile = "STDIN"
	else:
		inputFile = open(args['--input'], 'r')
except:
	ErrorHandler.ERROR_INPUT_FILE()

parsedSource = ""

for line in sourceFile:

	if (
		re.search("^\\s*<.*>\\s*$", line) or
		re.search("^\\s*$", line)
	):
		parsedSource += line
	else:
		ErrorHandler.ERROR_XML_STRUCTURE()

# Converting string to XML
try:
	program = ET.fromstring(parsedSource)
except:
	ErrorHandler.ERROR_XML_STRUCTURE()

# Source code must be IPPcode19 - case sensitive!!!
if program.attrib['language'] != "IPPcode19":
	ErrorHandler.ERROR_XML_STRUCTURE()

parsedProgram = {}

for instruction in program:
	# Instructions can have only 2 attributes sooo... ->
	if len(instruction.attrib) != 2:
		ErrorHandler.ERROR_XML_STRUCTURE()

	# Making sure that opcode and order are lowercase
	if (
		"opcode" not in instruction.attrib or
		"order" not in instruction.attrib
	):
		ErrorHandler.ERROR_XML_STRUCTURE()

	# This is basic body of parsed instruction
	parsedInstruction = {
		"opcode": instruction.attrib["opcode"], # Opcode of instruction
		"args": {} # Arguments of instruction
	}

	for arg in instruction:
		
		# Childrens must have certain schema
		if not re.search("arg[1-9]+[0-9]*", arg.tag):
			ErrorHandler.ERROR_XML_STRUCTURE()

		if (
			"type" not in arg.attrib or
			len(arg.attrib) != 1
		):
			ErrorHandler.ERROR_XML_STRUCTURE()

		# Arguments must be lower cased... So lets check it!
		if arg.attrib["type"] != arg.attrib["type"].lower():
			ErrorHandler.ERROR_XML_STRUCTURE()

		parsedInstruction['args'][arg.tag.replace('arg', '')] = {
			"type": arg.attrib["type"],
			"value": arg.text if arg.text != None else ""
		}

		# No subelements are allowed in argument
		if len(arg) != 0:
			ErrorHandler.ERROR_XML_STRUCTURE()

	# If len(parsed_args) != len(given_args) -- PARSING WENT WRONG!
	if len(parsedInstruction['args']) != len(instruction):
		ErrorHandler.ERROR_XML_STRUCTURE()

	# We will place that instruction on the specific position in final DICT
	parsedProgram[int(instruction.attrib["order"])] = parsedInstruction


# There might be some escape seq in strings... LET'S RESOLVE THEM!
for instructionPointer in parsedProgram:
	for argIndex in parsedProgram[instructionPointer]['args']:
		if parsedProgram[instructionPointer]['args'][argIndex]['type'] == "string":
			parsedProgram[instructionPointer]['args'][argIndex]['value'] = removeEscapeSeq(parsedProgram[instructionPointer]['args'][argIndex]['value'])

# Lets check if there are not any duplicates or missing instructions
for index in range(1, len(program) + 1):
	if index not in parsedProgram:
		ErrorHandler.ERROR_XML_STRUCTURE()

# NOW WHOLE LOADED PROGRAM IS STORED INSIDE parsedProgram
# VARIABLE. WE CAN DO AMAZING STUFF WITH IT!

# ... but we will need some MEMORY!

programMemory = {
	'GF': {},
	'LF': None,
	'TF': None,
	'LF_STACK': [],
	'PROG_LABELS': {},
	'PROG_STACK': [],
	'PROG_RETURN_STACK': []
}

# Because there might be some labels inside our program
# we have to keep record of them before program starts interpretation
LabelParser.parseAll(programMemory, parsedProgram)

# We need to determine which instruction we should run...
# Thanks python amazing-be-like-developers for not implementing 'switch'... -_-
instructionPointer = 1

while instructionPointer < len(parsedProgram) + 1:
	instructionHandler = None

	parsedProgram[instructionPointer]["instruction_order"] = instructionPointer

	if parsedProgram[instructionPointer]['opcode'] == 'WRITE':
		instructionHandler = INS_Write(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'ADD':
		instructionHandler = INS_Add(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'AND':
		instructionHandler = INS_And(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'BREAK':
		instructionHandler = INS_Break(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'CALL':
		instructionHandler = INS_Call(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'CONCAT':
		instructionHandler = INS_Concat(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'CREATEFRAME':
		instructionHandler = INS_CreateFrame(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'DEFVAR':
		instructionHandler = INS_Defvar(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'DPRINT':
		instructionHandler = INS_Dprint(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'EQ':
		instructionHandler = INS_Eq(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'EXIT':
		instructionHandler = INS_Exit(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'GETCHAR':
		instructionHandler = INS_Getchar(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'GT':
		instructionHandler = INS_Gt(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'IDIV':
		instructionHandler = INS_Idiv(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'INT2CHAR':
		instructionHandler = INS_Int2char(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'JUMP':
		instructionHandler = INS_Jump(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'JUMPIFEQ':
		instructionHandler = INS_Jumpifeq(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'JUMPIFNEQ':
		instructionHandler = INS_Jumpifneq(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'LABEL':
		instructionPointer = instructionPointer + 1
		continue
	elif parsedProgram[instructionPointer]['opcode'] == 'LT':
		instructionHandler = INS_Lt(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'MOVE':
		instructionHandler = INS_Move(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'MUL':
		instructionHandler = INS_Mul(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'NOT':
		instructionHandler = INS_Not(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'OR':
		instructionHandler = INS_Or(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'POPFRAME':
		instructionHandler = INS_PopFrame(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'POPS':
		instructionHandler = INS_Pops(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'PUSHFRAME':
		instructionHandler = INS_PushFrame(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'PUSHS':
		instructionHandler = INS_Pushs(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'READ':
		instructionHandler = INS_Read(parsedProgram[instructionPointer], programMemory, inputFile)
	elif parsedProgram[instructionPointer]['opcode'] == 'RETURN':
		instructionHandler = INS_Return(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'SETCHAR':
		instructionHandler = INS_Setchar(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'STRI2INT':
		instructionHandler = INS_Stri2int(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'STRLEN':
		instructionHandler = INS_Strlen(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'SUB':
		instructionHandler = INS_Sub(parsedProgram[instructionPointer], programMemory)
	elif parsedProgram[instructionPointer]['opcode'] == 'TYPE':
		instructionHandler = INS_Type(parsedProgram[instructionPointer], programMemory)
	else:
		ErrorHandler.ERROR_XML_STRUCTURE()

	# Let's evaluate our instruction and see, what happens!
	evaluation_result = instructionHandler.eval()

	if evaluation_result != None:
		instructionPointer = evaluation_result
	else:	
		instructionPointer = instructionPointer + 1