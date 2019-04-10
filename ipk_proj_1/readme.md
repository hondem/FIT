__Implementační dokumentace k 1. úloze do IPK 2018/2019__  
__Jméno a příjmení: Jan Demel__  
__Login: xdemel01__  

## Úvod
Úkolem bylo implementovat socket klienta, který komunikoval se serverem OpenWeatherAPI za účelem získat data o počasí.

## Implementace
Program nejdříve prověří správný formát vstupních argumentů (pokud zde program selže, je vrácená návratová hodnota `ERROR_ARGS = -1`), poté vytvoří socket, který se pokusí připojit na:
```
host_name = "api.openweathermap.org"
port = 80
```
Pokud připojení selže, program je ukončen s návratovým kódem `ERROR_SOCKET_CONNECTION = -2`. Následně se zkontroluje, zda request proběhl úspěšně (pokud odpověď má jiný kód, než `200`, jedná se o chybu - program je ukončen s návratovým kódem `ERROR_API_CALL = -4`) a dojde k formátování výsledku na výstup. Zde se může stát, že některé požadované atributy v odpovědi od serveru neexistují. Pokud neexistuje informace o směru větru, je tato informace nahrazena pomlčkou. Pokud ovšem v JSONu chybí jakákoliv jiná informace, jedná se o chybu v odpovědi a program je ukončen s návratovým kódem `ERROR_FORMAT_OUTPUT_DATA = -3`.

### Použité knihovny
V projektu byly použity knihovny `socket` (pro komunikaci se serverem), `json` (pro zpracování odpovědi od serveru) a `sys` (pro zpracování vstupních argumentů a ukončení skriptu).

## Spuštění skriptu
Skript se spouští následujícím způsobem:
```
make run api_key=YOUR_API_KEY city=CITY_NAME
```
Přičemž je třeba validní `API_KEY`.