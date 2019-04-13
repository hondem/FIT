__Implementační dokumentace k 2. úloze do IPP 2018/2019__  
__Jméno a příjmení: Jan Demel__  
__Login: xdemel01__  

## Úvod
Úkolem bylo naimplementovat 2 skripty a to sice `interpret.py` a `test.php`. `interpret.py` na vstupu očekává zparsovanou XML reprezentaci kódu v `.IPPcode19` (výstup skriptu `parse.php` z první úlohy) a postupně vykonává její instrukce. `test.php` pak slouží pro validaci řešení. Jelikož se jedná o 2 samostatné skripty, rozebere tato dokumentace nejdříve `interpret.py` a poté `test.php`. Mé řešení je objektově orientované v případě `interpret.py`.

## `interpret.py`
Tento skript nejdříve zparsuje argumenty, poté ověří, jestli vstupní soubor existuje, načte z něj XML a to zparsuje do podoby, se kterou umí pracovat jednotlivé implementované instrukce. Po všech validačních testech zparsuje návěští, které se v programu vyskytují, vytvoří paměť programu, který bude interpretovat a začne procházet jednotlivé instrukce, které jsou indexovány pomocí indexu `instructionPointer` (dá se nad ním tak uvažovat).  
  
Ukázka vytvoření paměti programu:
```python
programMemory = {
	'GF': {}, # Paměť pro globální rámec
	'LF': None, # Paměť pro lokální rámec
	'TF': None, # Paměť pro dočasný rámec
	'LF_STACK': [], # Odložené lokální rámce
	'PROG_LABELS': {}, # Zparsované labely (dostupné pod klíčem)
	'PROG_STACK': [], # Používán instrukcemi POPS a PUSHS
	'PROG_RETURN_STACK': [] # Používán instrukcemi CALL, RETURN
}
```

### Způsob implementace jednotlivých instrukcí
U předchozí úlohy jsem udělal chybu, že jsem jednotlivé instrukce nerozdělil do jednotlivých souborů - ke konci vývoje se mi v kódu velice špatně orientovalo a jakýkoliv zásah byl složitý. Rozhodl jsem se tedy, že můj interpret bude mít pro každou instrukci samostatný soubor ve složce `./instructions`. Abych se vyhnul nepřehlednému importování instrukcí v samotném `interpret.py`, vytvořil jsem pro ně wrapper `./instructions/instructions.py`, který importuje všechny potřebné instrukce.
```python
from . ins_write 		import INS_Write
from . ins_add 			import INS_Add
from . ins_and 			import INS_And
from . ins_break 		import INS_Break
from . ins_call 		import INS_Call
from . ins_concat 		import INS_Concat
...
```
V hlavním těle programu tedy stačí importovat pouze `./instructions/instructions.py`. Dále je nutno říct, že každá instrukce dědí z třídy `BaseInstruction (./instructions/base_instruction.py)`. V této třídě se nachází statické metody, které potomkům pomáhají s validací vstupních parametrů, validací přístupu do paměti a validací datových typů. Navíc tato třída obsahuje abstraktní metodu `eval()`, což je metoda, která se volá pokaždé, když vyhodnocujeme danou instrukci. Tuto metodu poté jednotliví potomci sami implementují.

### Zachytávání errorů
Jelikož errory mohou vzniknout kdekoliv v kódu, vytvořil jsem pro přehlednější error handling třídu `ErrorHandler`. Ta je importována téměř ve všech skriptech. Třída obsahuje jak jednotlivé chybové kódy, tak i statické metody, které ukončují program s určitou hláškou a návratovým kódem.

### Parsování návěští
Jelikož nemůžeme očekávat, že v programu se návěští objeví dříve, než na něj bude proveden skok, je třeba celý program před samotným spuštěním projít a zaznamenat všechny návěští a jejich "adresy" (jedná se pouze o index do pole). Ty se pak uloží do speciálního místa v paměti programu, aby se s nimi poté dalo pracovat. Implementace je uložena v souboru `./label_parser.py`.

### Parsování argumentů
Tento skript zajišťuje pouze validaci, zda vstupní argumenty odpovídají danému schématu a pokud ano, vrátí je interpretu. Implementováno v `arguments_parser.py`.

## `test.php`
Tento skript má za úkol v závislosti na vstupních argumentech ověřit funkčnost řešení. Podporuje jak validaci výstupu skriptů `parse.php` a `interpret.py`, tak i validaci výstupu obou skriptů spojených.

### Parsování argumentů
K parsování argumentů byla využita metoda `getopt()`, s tím, že její volání vypadalo následovně:
```php
$args = array(
	"help",
	"directory::",
	"recursive",
	"parse-script::",
	"int-script::",
	"parse-only",
	"int-only"
);

$prog_args = getopt('', $args);
``` 
Je vidět, že jsem vynechal místo pro short arguments - ty v naší implementaci nejsou potřeba. Díky tomu, že jsem použil `getopt()`, tak stačilo už jenom ověřit existenci některých vyžadovaných parametrů (případně je doplnit).
```php
if(!array_key_exists("directory", $prog_args)) $prog_args["directory"] = "./";
if(!array_key_exists("parse-script", $prog_args)) $prog_args["parse-script"] = "./parse.php";
if(!array_key_exists("int-script", $prog_args)) $prog_args["int-script"] = "./interpret.py";
```

### Spouštění testů
Jednotlivé testy se spouští pomocí metody `exec()` následujícím způsobem:
#### --int-only
```
exec("python3.6 {$prog_args['int-script']} --source={$test}.src --input={$test}.in > {$test}.myout", $output, $retVal);
```
#### --parse-only
```
exec("php7.3 {$prog_args['parse-script']} < {$test}.src > {$test}.myout", $output, $retVal);
```
#### Parser + Interpret
```
exec("php7.3 {$prog_args['parse-script']} < {$test}.src > {$test}.parseout", $output, $retVal);
exec("python3.6 {$prog_args['int-script']} --source={$test}.parseout --input={$test}.in > {$test}.myout", $output, $retVal);
```

### Validace výstupu
Výstup každého testu je vždy porovnán s očekávaným výstup v souboru `(TESTPATH).out` za pomocí UNIXového `diff`. Výsledek tohoto porovnání je v případě, že není prázdný, zapsán do výstupního HTML. 

### Generování HTML
Každý jednotlivý test, který `test.php` projde, zapisuje informace o úspěchu/neúspěchu do stringu, který obsahuje tělo HTML5 dokumentu. Hlavním elementem výstupního HTML je `<table>`, do kterého jsou vkládány jednotlivé řádky (1 řádek = 1 test). Aby bylo výstupní HTML přehlednější, obsahuje také styly, které definují zbarvení pro řádky tabulky v případě, že obsahují třídu `.failed`, `.success` a nebo `.info`. Tyto styly jsou vloženy do hlavičky HTML a nejsou tudíž získávány z extérních zdrojů.