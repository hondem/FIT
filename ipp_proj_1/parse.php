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
		return preg_replace("/#.*/", "", $command);
	}

	/**
	 * Returns next instruction as an array of tokens
	 */
	public function getNextInstruction(){
		if(feof(STDIN)) return false;
		$line = fgets(STDIN);

		if(preg_match("/^#.*$/", $line)){
			return $this->getNextInstruction(); // If entire line is comment, we can skip it!
		} else {
			return $this->explodeCommand($this->removeComments($line));
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

		if(!preg_match("/^.ippcode19([\s]*#.*){0,1}$/i", $line)) ErrorFunctions::THROW_HEADER_ERROR();

		// Creating XML container
		$xml = new SimpleXMLElement('<?xml version="1.0" encoding="utf-8"?><program language="IPPcode19"/>');
		$xmlInstructionOrder = 1;

		// Now we can parse everything!
		while(($lineOfCode = $this->scannerInstance->getNextInstruction())){
			if($lineOfCode[0] == "") continue;
			
			$insClass = null;

			// We must determine which instruction to parse
			switch(strtoupper($lineOfCode[0])){
				case 'CREATEFRAME':	$insClass = new INS_CreateFrame(); break;
				case 'POPFRAME': 	$insClass = new INS_PopFrame(); break;
				case 'PUSHFRAME': 	$insClass = new INS_PushFrame(); break;
				case 'RETURN':		$insClass = new INS_Return(); break;
				case 'BREAK':		$insClass = new INS_Break(); break;
				case 'DEFVAR':		$insClass = new INS_DefVar(); break;
				case 'WRITE':		$insClass = new INS_Write(); break;
				case 'LABEL':		$insClass = new INS_Label(); break;
				case 'JUMP':		$insClass = new INS_Jump(); break;
				case 'CALL':		$insClass = new INS_Call(); break;
				case 'PUSHS':		$insClass = new INS_Pushs(); break;
				case 'POPS':		$insClass = new INS_Pops(); break;
				case 'EXIT':		$insClass = new INS_Exit(); break;
				case 'DPRINT':		$insClass = new INS_Dprint(); break;
				case 'MOVE':		$insClass = new INS_Move(); break;
				case 'INT2CHAR':	$insClass = new INS_Int2char(); break;
				case 'READ':		$insClass = new INS_Read(); break;
				case 'STRLEN':		$insClass = new INS_Strlen(); break;
				case 'TYPE':		$insClass = new INS_Type(); break;
				case 'ADD':			$insClass = new INS_Add(); break;
				case 'SUB':			$insClass = new INS_Sub(); break;
				case 'MUL':			$insClass = new INS_Mul(); break;
				case 'IDIV':		$insClass = new INS_Idiv(); break;
				case 'LT':			$insClass = new INS_Lt(); break;
				case 'GT':			$insClass = new INS_Gt(); break;
				case 'EQ':			$insClass = new INS_Eq(); break;
				case 'AND':			$insClass = new INS_And(); break;
				case 'OR':			$insClass = new INS_Or(); break;
				case 'NOT':			$insClass = new INS_Not(); break;
				case 'STRI2INT':	$insClass = new INS_Stri2int(); break;
				case 'CONCAT':		$insClass = new INS_Concat(); break;
				case 'GETCHAR':		$insClass = new INS_Getchar(); break;
				case 'SETCHAR':		$insClass = new INS_Setchar(); break;
				case 'JUMPIFEQ':	$insClass = new INS_Jumpifeq(); break;
				case 'JUMPIFNEQ':	$insClass = new INS_Jumpifneq(); break;
				default:
					ErrorFunctions::THROW_OPCODE_ERROR();
			}

			// Lets generate our code!
			$insClass::generate($xml, $lineOfCode, $xmlInstructionOrder++);
		}

		return $xml->asXML();
	}
}

switch(count($argv)){
	case 1:
		$parserInstance = new Parser();
		$program = $parserInstance->parse();
		
		$xmlDocument = new DOMDocument('1.0');
		$xmlDocument->preserveWhiteSpace = false;
		$xmlDocument->formatOutput = true;
		$xmlDocument->loadXML($program);
		
		$program = $xmlDocument->saveXML();
			
		fwrite(STDOUT, $program);
	break;

	case 2:
		if(strcmp($argv[1], "--help") == 0){
			print("Loads source code in IPPcode19 and transform it into XML format.\n");
			print("Usage: php parse.php < INPUT_FILE\n");
		}
	break;

	default:
		ErrorFunctions::THROW_PARAM_ERROR();
}