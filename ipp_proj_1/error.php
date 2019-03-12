<?php

/**
 * Class that externally defines error codes for project
 */
class ErrorFunctions{
	/**
	 * Error codes
	 */
	const ERROR_PARAM = 10;
	const ERROR_INPUT_FILE = 11;
	const ERROR_OUTPUT_FILE = 12;
	
	const ERROR_HEADER = 21;
	const ERROR_OPCODE = 22;
	const ERROR_LEX_OR_SYN = 23;

	const ERROR_INTERNAL = 99;

	/**
	 * Throws error in parameters
	 */
	static function THROW_PARAM_ERROR(){
		fwrite(STDERR, "Wrong parameters passed\n");
		exit(self::ERROR_PARAM);
	}

	/**
	 * Throws error in input file
	 */
	static function THROW_INPUT_ERROR(){
		fwrite(STDERR, "Damaged input file\n");
		exit(self::ERROR_INPUT_FILE);
	}

	/**
	 * Throws error in input file
	 */
	static function THROW_OUTPUT_ERROR(){
		fwrite(STDERR, "Damaged output file\n");
		exit(self::ERROR_OUTPUT_FILE);
	}

	/**
	 * Throws error in file header
	 */
	static function THROW_HEADER_ERROR(){
		fwrite(STDERR, "Wrong file header\n");
		exit(self::ERROR_HEADER);
	}

	/**
	 * Throws error with opcode
	 */
	static function THROW_OPCODE_ERROR(){
		fwrite(STDERR, "Wrong opcode\n");
		exit(self::ERROR_OPCODE);
	}

	/**
	 * Throws lexical or syntactic error
	 */
	static function THROW_LEX_SYN_ERROR(){
		fwrite(STDERR, "Syntax error: Bad instruction format\n");
		exit(self::ERROR_LEX_OR_SYN);
	}

	/**
	 * Throws internal error
	 */
	static function THROW_INTERNAL_ERROR(){
		fwrite(STDERR, "Syntax error: Internal error\n");
		exit(self::ERROR_INTERNAL);
	}
}
