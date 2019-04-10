__Implementační dokumentace k 1. úloze do IPP 2018/2019__  
__Jméno a příjmení: Jan Demel__  
__Login: xdemel01__  

## Úvod
Řešili jsme implementaci skriptu `parse.php`, který převáděl kód ze vstupu ve formátu IPPcode19 na XML formát. Mé řešení je objektově orientované.

## Řešení
Mé řešení kontroluje, zda hodnota konstanty odpovídá typu konstanty - např. `int@302` ANO, `int@test` NE. U instrukcí na vstupu nezáleží na velikosti písmen (stejně, jako v hlavičce - `IPPcode19`). Komentáře začínají vždy od `#` - nezáleží, kde je ve vstupním souboru umístěn. Cokoliv za ním (včetně něj) se zahazuje. Jako oddělovač v instukci MUSÍ být použita mezera. V opačném případě se jedná o lexikální chybu.

### Návrh projektu a tříd
Projekt je rozdělený do 3 souborů - `parse.php`, `error.php` a `instructions.php`.
### `parse.php`
Obsahuje 2 třídy a to sice `Parser` a `Scanner`. `Scanner` posílá parseru pole tokenů, které reprezentují vždy jeden řádek kódu. Rovněž se stará o odstranění komentářů za použití RegExu. `Parser` poté identifikuje instrukci, kterou mu `Scanner` poslal a volá statickou metodu `generate(&$xmlEngine, $tokens, $order)` příslušné třídy instrukce, která do námi zvoleného XML enginu (v mém případě `SimpleXMLElement`) zapíše vygenerované XML.

```php
// $insClass is our determined class
$insClass::generate($xml, $lineOfCode, $xmlInstructionOrder++);
```

Nakonec se vygenerované XML pošle na `STDOUT`.

### `instructions.php`
Obsahuje třídy jednotlivých instrukcí (ty začínají prefixem `INS_`) a abstraktní třídu `Instruction`, ze které tyto třídy dědí. Navíc jsou všechny metody třídy `Instruction` statické, tudíž není třeba vytvářet instanci, abychom je mohli použít. Třída `Instruction` obsahuje tyto metody:
- `abstract static function generate(&$xmlEngine, $tokens, $order)` - Každá odvozená třída si tuto metodu musí definovat sama. V implementaci metody se v zásadě jedná o zkontrolování argumentů instrukce (případnou mutaci argumentů) a vygenerování dílčí části XML.
- `static function resolveSymb($symb)` - Metoda určující, jestli `$symb` obsahuje konstantu, nebo proměnnou.
- Metody pro validaci formátu argumentu (tyto metody vždy používají regex)
	- `static function validateLabel($label)`
	- `static function validateVar($var)`
	- `static function validateSymb($symb)`
	- `static function validateConst($const)`
	- `static function validateType($type)`

### `error.php`
Obsahuje třídu `ErrorFunctions`, která se stará o handling errorů. Je includovaná v obou předchozích souborech a obsahuje metody pro jednotlivé typy errorů, které můžou za běhu programu nastat. Při jakémkoliv typu erroru se vypíše na `STDOUT` příslušná chybová hláška a program se ukončí s příslušným návratovým kódem.