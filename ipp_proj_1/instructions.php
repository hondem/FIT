<?php

require_once('error.php');

/**
 * Abstract class that defines interface
 * for classes
 */
abstract class Instruction{
	const KEYWORDS = array(
		'CREATEFRAME', 
		'POPFRAME', 
		'PUSHFRAME',
		'RETURN',
		'BREAK',
		'MOVE',
		'DEFVAR',
		'CALL',
		'PUSHS',
		'POPS',
		'ADD',
		'SUB',
		'MUL',
		'IDIV',
		'LT',
		'GT',
		'EQ',
		'AND',
		'OR',
		'NOT',
		'INT2CHAR',
		'STRI2INT',
		'READ',
		'WRITE',
		'CONCAT',
		'STRLEN',
		'GETCHAR',
		'SETCHAR',
		'TYPE',
		'LABEL',
		'JUMP',
		'JUMPIFEQ',
		'JUMPIFNEQ',
		'EXIT',
		'DPRINT'
	);
	
	/**
	 * Function that generates piece of XML and returns it
	 */
	abstract static function generate(&$xmlEngine, $tokens, $order);

	/**
	 * Validates if label has the right format
	 * @return TRUE/FALSE
	 */
	static function validateLabel($label){
		if(preg_match("/^([a-zA-Z]|[_$&%*!?-])([a-zA-Z]|[_$&%*!?-]|[0-9])*$/", $label)){
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Validates if symb has the right format
	 * @return TRUE/FALSE
	 */
	static function validateSymb($symb){
		if(self::validateConst($symb) || self::validateVar($symb)){
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Validates if var has the right format
	 * @return TRUE/FALSE
	 */
	static function validateVar($var){
		if(preg_match("/^(LF|TF|GF)@([a-zA-Z]|[_$&%*!?-])([a-zA-Z]|[_$&%*!?-]|[0-9])*$/", $var)){
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Validates if const has the right format
	 * @return TRUE/FALSE
	 */
	static function validateConst($const){
		if(
			preg_match("/^bool@(true|false)$/", $const) || //BOOL
			preg_match("/^int@(-{0,1}[1-9][0-9]*|0)$/", $const) || //INT
			preg_match("/^string@(\\[0-9]{3}|[^\\#\s])*$/", $const)){ //STRING
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Validates if type is equeal to int|string|bool
	 * @return TRUE/FALSE
	 */
	static function validateType($type){
		if(preg_match("/^(int|string|bool)$/", $type)){
			return true;
		} else {
			return false;
		}
	}

	/**
	 * Resolves symbol
	 * @return Object
	 */
	static function resolveSymb($symb){
		$object = new stdClass();
		if(self::validateConst($symb)){
			$arg = explode("@", $symb);
			$object->type = $arg[0];
			$object->value = $arg[1];
			return $object;
		} else if(self::validateVar($symb)){
			$object->type = 'var';
			$object->value = $symb;
			return $object;
		}
	}
}

// ====================== 0 PARAMs ======================

class INS_CreateFrame extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(count($tokens) == 1){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'CREATEFRAME');
		} else {
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_PushFrame extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(count($tokens) == 1){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'PUSHFRAME');
		} else {
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_PopFrame extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(count($tokens) == 1){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'POPFRAME');
		} else {
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Return extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(count($tokens) == 1){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'RETURN');
		} else {
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Break extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(count($tokens) == 1){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'BREAK');
		} else {
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

// ====================== 1 PARAM ======================

class INS_DefVar extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateVar($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'DEFVAR');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');
		} else {
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Write extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateSymb($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'WRITE');
			
			$resolvedParam = self::resolveSymb($tokens[1]);
			$param = $instruction->addChild('arg1', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Label extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateLabel($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'LABEL');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'label');
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Jump extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateLabel($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'JUMP');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'label');
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Call extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateLabel($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'CALL');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'label');
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Pushs extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateSymb($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'PUSHS');
			
			$resolvedParam = self::resolveSymb($tokens[1]);
			$param = $instruction->addChild('arg1', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Pops extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateVar($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'POPS');
			
			$resolvedParam = self::resolveSymb($tokens[1]);
			$param = $instruction->addChild('arg1', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Exit extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateSymb($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'EXIT');
			
			$resolvedParam = self::resolveSymb($tokens[1]);
			$param = $instruction->addChild('arg1', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Dprint extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if(self::validateSymb($tokens[1]) && count($tokens) == 2){
			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'DPRINT');
			
			$resolvedParam = self::resolveSymb($tokens[1]);
			$param = $instruction->addChild('arg1', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);
		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

// ====================== 2 PARAMs ======================

class INS_Move extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			count($tokens) == 3){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'MOVE');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');
			

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Int2char extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			count($tokens) == 3){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'INT2CHAR');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Read extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateType($tokens[2]) &&
			count($tokens) == 3){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'READ');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$param = $instruction->addChild('arg2', $tokens[2]);
			$param->addAttribute('type', 'type');

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Strlen extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			count($tokens) == 3){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'STRLEN');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Type extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			count($tokens) == 3){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'TYPE');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

// ====================== 3 PARAMs ======================

class INS_Add extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'ADD');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Sub extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'SUB');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Mul extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'MUL');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Idiv extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'IDIV');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Lt extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'LT');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Gt extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'GT');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Eq extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'EQ');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_And extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'AND');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Or extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'OR');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Not extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'NOT');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Stri2int extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'STRI2INT');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Concat extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'CONCAT');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Getchar extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'GETCHAR');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Setchar extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateVar($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'SETCHAR');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'var');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Jumpifeq extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateLabel($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'JUMPIFEQ');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'label');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}

class INS_Jumpifneq extends Instruction{
	static function generate(&$xmlEngine, $tokens, $order){
		if( self::validateLabel($tokens[1]) &&
			self::validateSymb($tokens[2]) &&
			self::validateSymb($tokens[3]) &&
			count($tokens) == 4){

			$instruction = $xmlEngine->addChild('instruction');
			$instruction->addAttribute('order', $order);
			$instruction->addAttribute('opcode', 'JUMPIFNEQ');
			
			$param = $instruction->addChild('arg1', $tokens[1]);
			$param->addAttribute('type', 'label');

			$resolvedParam = self::resolveSymb($tokens[2]);
			$param = $instruction->addChild('arg2', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

			$resolvedParam = self::resolveSymb($tokens[3]);
			$param = $instruction->addChild('arg3', $resolvedParam->value);
			$param->addAttribute('type', $resolvedParam->type);

		} else { 
			ErrorFunctions::THROW_LEX_SYN_ERROR();
		}
	}
}