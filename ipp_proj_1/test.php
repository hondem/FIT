<?php

/**
 * Supporting functions
 */
function printHelp(){
	print("Use this script to validate your solution.\n");
	print("Usage:\n\tphp test.php --directory=DIRPATH [OPTIONALS]\n");
	print("Optional parameters:\n");
	print("\t--recursive\t- search for tests recousively inside directory\n");
	print("\t--parse-script=SCRIPTPATH\t- specify parse script (default parse.php)\n");
	print("\t--int-script=SCRIPTPATH\t- specify interpret script (default interpret.py)\n");
	print("\t--parse-only\t- evaluate only parse tests (can't be mixed with --int-only)\n");
	print("\t--int-only\t- evaluate only int tests (can't be mixed with --parse-only)\n");
	exit(0);
}

function getTestsFiles($rootDir, &$targetVar, $recursive = false){
	$root = scandir($rootDir);

	foreach($root as $subfile){
		if(is_dir(realpath($rootDir . "/" . $subfile))){
			// Since we don't want to parse current directory and parent directory
			if(!($subfile == "." || $subfile == "..")) {
				if($recursive) getTestsFiles(realpath($rootDir . "/" . $subfile), $targetVar, $recursive);
			}
		} else {
			// We will make sure that no hidden files are being tested
			if (preg_match("/^\..*$/", $subfile) || !preg_match("/^.*\.(src|in|out|rc)$/", $subfile)) continue;
			
			$subfile = preg_replace("/\.(src|in|out|rc)$/", "", $subfile);
			
			if(!in_array($rootDir . "/" . $subfile, $targetVar)) $targetVar[] = $rootDir . "/" . $subfile;
		}
	}
}

/**
 * Parsing arguments
 */
$args = array(
	"help",
	"directory::",
	"recursive",
	"parse-script::",
	"int-script::",
	"parse-only",
	"int-only"
);

/**
 * Fetching arguments
 */
$prog_args = getopt('', $args);

if(!array_key_exists("directory", $prog_args)) $prog_args["directory"] = "./";
if(!array_key_exists("parse-script", $prog_args)) $prog_args["parse-script"] = "./parse.php";
if(!array_key_exists("int-script", $prog_args)) $prog_args["int-script"] = "./interpret.py";

if(array_key_exists("help", $prog_args)) printHelp();

if(array_key_exists("parse-only", $prog_args) && array_key_exists("int-only", $prog_args)){
	fwrite(STDERR, "Error: Please use either --parse-only or --int-only\n");
	exit(-1);
}

$test_files = [];

getTestsFiles($prog_args['directory'], $test_files, array_key_exists("recursive", $prog_args));

// ================== PREPEARING OUTPUT HTML STRING ====================

$outputHTML = '
	<!DOCTYPE html>
	<html lang="en">
	<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<meta http-equiv="X-UA-Compatible" content="ie=edge">
		<title>IPP Tests results</title>
	</head>
	<style>
		body, html{
			padding:0px;
			margin:0px;
		}

		table{
			width:100%;
			padding:0px;
			margin-top:60px;
			border:none;	
		}

		tr{
			width:100%;
			margin:0px;
			padding:20px;
		}

		tr.info{
			background-color:#2c3e50;
			color:white;
			font-weight:bold;
			text-transform:uppercase;
		}

		tr.failed{
			background-color:#c0392b;
			color:white;
			font-weight:bold;
		}

		tr.passed{
			background-color:#27ae60;
		}

		td{
			height:60px;
			padding:0px 20px;
			margin:0px;
			border-top:solid 1px #ffffff;
		}
		
		tr.info td{
			border-top:none;
		}

		tr.diff td{
			border-top:none;	
		}

		.result-info{
			position:absolute;
			top:0px;
			left:0px;
			width:100%;
			height:60px;
			background-color:#2c3e50;
		}

		.result-info p{
			padding:20px;
			margin:0px;
			font-weight:bold;
			color:white;
			text-transform:uppercase;
		}
	</style>
	<body>
';

// =====================================================================

/**
 * Lets run all tests!!!
 */
$passed = 0;
$total = count($test_files);

$outputHTML .= "<table cellspacing='0' cellpading='0'><tr class='info'><td>Expected ret. val</td><td>Got</td><td>Test location</td></tr>";

foreach($test_files as $test){
	$retVal = "";
	$output = "";
	$filesDiffer = "";

	/**
	 * Lets make sure that every single file exist
	 */
	if(!file_exists($test . ".in")) exec("touch {$test}.in");
	if(!file_exists($test . ".out")) exec("touch {$test}.out");
	if(!file_exists($test . ".rc")) exec("touch {$test}.rc && echo 0 > {$test}.rc");

	if(array_key_exists("int-only", $prog_args)){
		// Only interpret
		exec("python3.6 {$prog_args['int-script']} --source={$test}.src --input={$test}.in > {$test}.myout", $output, $retVal);
	} else if(array_key_exists("parse-only", $prog_args)){
		// Only parser
		exec("php7.3 {$prog_args['parse-script']} < {$test}.src > {$test}.myout", $output, $retVal);
	} else {
		// Both
		exec("php7.3 {$prog_args['parse-script']} < {$test}.src > {$test}.parseout", $output, $retVal);
		exec("python3.6 {$prog_args['int-script']} --source={$test}.parseout --input={$test}.in > {$test}.myout", $output, $retVal);
		unlink("{$test}.parseout");
	}

	$retCodeFile = fopen($test . ".rc", "r");
	$expectedValue = fgets($retCodeFile);

	/**
	 * Lets find out if files differ
	 */

	exec("diff {$test}.out {$test}.myout", $filesDiffer);

	if($expectedValue == $retVal && empty($filesDiffer)){
		$outputHTML .= "<tr class='passed'><td>{$expectedValue}</td><td>{$retVal}</td><td>{$test}</td>";
		$passed++;
	} else {
		$outputHTML .= "<tr class='failed'><td>{$expectedValue}</td><td>{$retVal}</td><td>{$test}</td>";
		if(!empty($filesDiffer)){
			$filesDiffer = implode("\n", $filesDiffer);
			$outputHTML .= "</tr><tr class='failed diff'><td colspan='3'>Output files differ<br>{$filesDiffer}</td>";
		}
	}

	$outputHTML .= "</tr>";

	unlink("{$test}.myout");
	fclose($retCodeFile);
}


/**
 * Send generated HTML to STDOUT
 */
$outputHTML .= "<div class='result-info'><p>{$passed}/{$total} tests passed</p></div>";
$outputHTML .= '</table></body></html>';

print($outputHTML);