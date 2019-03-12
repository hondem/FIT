<?php

require_once("error.php");
require_once("instructions.php");

/**
 * Class that ensures returning tokens
 */
class Scanner{

	/**
	 * Explodes command to array of elements
	 */
	private function explodeCommand($command){
		$command = trim($command);
		if(strpos($command, " ")){
			$command = explode(" ", $command);
			return $command;
		} else {
			return array($command);
		}
	}

	/**
	 * Removes comments from command
	 * Returns false if there is ONLY comment
	 */
	private function removeComments($command){
		if($command[0][0] == '#') return false;
		$commentBeginningIndex = null;

		for($i = 0; $i < count($command); $i++){
			if($command[$i][0] == '#'){
				$commentBeginningIndex = $i;
			}
		}

		if($commentBeginningIndex != null){
			$command = array_slice($command, 0, $commentBeginningIndex);
		}
		return $command;
	}

	/**
	 * Returns next instruction as an array of tokens
	 */
	public function getNextInstruction(){
		$line = fgets(STDIN);
		$command = $this->removeComments($this->explodeCommand($line));
		if(!$command){
			return $this->getNextInstruction(); // If entire line is comment, we can skip it!
		} else {
			return $command;
		}
	}
}

/**
 * Class that ensures parsing IPPCode19 input
 */
class Parser{
	// Scanner instance is made inside constructor
	private $scannerInstance = null;
	
	/**
	 * Parser's constuctor - we will use it only for
	 * creating new instance of scanner
	 */
	function __construct(){
		$this->scannerInstance = new Scanner();
	}

	/**
	 * Parse source code
	 */
	public function parse(){
		
		// Lets make sure that file has correct header
		$line = fgets(STDIN);

		if(strcmp($line, ".IPPcode19\n") != 0) ErrorFunctions::THROW_HEADER_ERROR();

		// Creating XML container
		$xml = new SimpleXMLElement('<?xml version="1.0" encoding="utf-8"?><program language="IPPcode19"/>');
		$xmlInstructionOrder = 1;

		// Now we can parse everything!
		while(($lineOfCode = $this->scannerInstance->getNextInstruction()) && strcmp($lineOfCode[0], "") != 0){

			$insClass = null;

			// We must determine which instruction to parse
			switch($lineOfCode[0]){
				case 'CREATEFRAME':	$insClass = INS_CreateFrame; break;
				case 'POPFRAME': 	$insClass = INS_PopFrame; break;
				case 'PUSHFRAME': 	$insClass = INS_PushFrame; break;
				case 'RETURN':		$insClass = INS_Return; break;
				case 'BREAK':		$insClass = INS_Break; break;
				case 'DEFVAR':		$insClass = INS_DefVar; break;
				case 'WRITE':		$insClass = INS_Write; break;
				case 'LABEL':		$insClass = INS_Label; break;
				case 'JUMP':		$insClass = INS_Jump; break;
				case 'CALL':		$insClass = INS_Call; break;
				case 'PUSHS':		$insClass = INS_Pushs; break;
				case 'POPS':		$insClass = INS_Pops; break;
				case 'EXIT':		$insClass = INS_Exit; break;
				case 'DPRINT':		$insClass = INS_Dprint; break;
				case 'MOVE':		$insClass = INS_Move; break;
				case 'INT2CHAR':	$insClass = INS_Int2char; break;
				case 'READ':		$insClass = INS_Read; break;
				case 'STRLEN':		$insClass = INS_Strlen; break;
				case 'TYPE':		$insClass = INS_Type; break;
				case 'ADD':			$insClass = INS_Add; break;
				case 'SUB':			$insClass = INS_Sub; break;
				case 'MUL':			$insClass = INS_Mul; break;
				case 'IDIV':		$insClass = INS_Idiv; break;
				case 'LT':			$insClass = INS_Lt; break;
				case 'GT':			$insClass = INS_Gt; break;
				case 'EQ':			$insClass = INS_Eq; break;
				case 'AND':			$insClass = INS_And; break;
				case 'OR':			$insClass = INS_Or; break;
				case 'NOT':			$insClass = INS_Not; break;
				case 'STRI2INT':	$insClass = INS_Stri2int; break;
				case 'CONCAT':		$insClass = INS_Concat; break;
				case 'GETCHAR':		$insClass = INS_Getchar; break;
				case 'SETCHAR':		$insClass = INS_Setchar; break;
				case 'JUMPIFEQ':	$insClass = INS_Jumpifeq; break;
				case 'JUMPIFNEQ':	$insClass = INS_Jumpifneq; break;
				default:
					ErrorFunctions::THROW_OPCODE_ERROR();
			}

			// Lets generate our code!
			$insClass::generate($xml, $lineOfCode, $xmlInstructionOrder++);
		}

		return $xml->asXML();
	}
}

$parserInstance = new Parser();
$program = $parserInstance->parse();

$xmlDocument = new DOMDocument('1.0');
$xmlDocument->preserveWhiteSpace = false;
$xmlDocument->formatOutput = true;
$xmlDocument->loadXML($program);

$program = $xmlDocument->saveXML();
	
fwrite(STDOUT, $program);