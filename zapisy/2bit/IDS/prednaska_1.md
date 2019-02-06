# IDS Přednáška č.1

**Referenční integrita** - Je to to, co propojuje řádky tabulek (na základě čeho spojujeme řádky tabulek)

## Příklady SQL
### Select
```sql
SELECT místnost
FROM Oddělení, Zaměstnanci
WHERE odděnení = zkratka and přijmení = ’Nováková’
```

### Vložení
```sql
INSERT INTO Oddělení
VALUES (‘PER’, ‘Personální oddělení’, ‘Personální záležitosti’, NULL, ‘B-020’, 125)
```

### Aktualizace
```sql
UPDATE Zaměstnanci
SET oddělení = ‘PER’
WHERE os_cislo = 20
```

### Zrušení
```sql
DELETE FROM Zaměstnanci WHERE os_cislo = 20
```

## Jaké problémy řeší databáze?
Řeší [redundanci](#redundance-dat) a [integritu](#integrita-dat) dat.

## Základní pojmy
### Databáze
Perzistentní data, využívaná aplikačními systémy dané instituce

### Perzistentní data
Data s dobou života překračující běh aplikačního programu i vypnutí počítače.

### Vlastnosti dat databáze
- **Integrovaná** - Lze chápat jako sjednocení několika datových souborů s odstraněním redundance. (Data tvoří jakýsi celek, který je určitým
způsobem kompaktní)

- **Sdílená** - K datům může přistupovat více aplikací, více uživatelů.

- **Bezpečná** - Snadněji se realizují přístupová práva

### Redundance dat
Vzniká v momentě, kdy na různých místech v databázi máme napsanou stejnou informaci. Vznikají _nekonzistentní_ data.
Právě redundance dat byla jedním z prvních podnětů pro vytvoření databází.

### Integrita dat
Soulad s realitou, kterou data reprezentují. To znamená, že pokud máme v databázi informace o platu nějaké osoby, tak
plat nemůže být záporný (logicky, ne?).

### Systém řízení báze dat
Je to programová vrstva, která poskytuje databázové služby, které databázi zaobalují a prostřednictvím těch služeb aplikace přistupujou k datům.

### Databázový systém
V užším smyslu jim můžeme rozumět databázi a [systém řizení báze dat](#system-rizeni-baze-dat).  
V širším smyslu jim označujeme:
- technické prostředby
- data - DB
- programové vybavení - [SŘBD](#system-rizeni-baze-dat) + aplikační programy, vývojové prostředky, knihovny
- uživatelé DB

## Úrovně pohledu na data
- **Úroveň pohledů (externí)** - Popisuje, jak data vnímají jednotliví uživatelé. Obecně vidí každý uživatel (role) je část databáze, která představuje data reprezentující objekty reálného světa.

- **Konceptuální (logická) úroveň** - Popisuje, jaká data jsou skutečně uložena v databázi a jaké vztahy mezi nimi existují.

- **Fyzická (interní úroveň)** - Popisuje data, jak jsou skutečně uložena.

## Datové modely
Souvisí s [úrovněmi pohledu na data](#urovne-pohledu-na-data). Je to souhrn (kolekce) nástrojů, která nám pomáhají
popisovat data na jednotlivých úrovních (jejich strukturu, vztahy, sémantiky apod...).  
Rozdělujeme je na:
- **Logické modely** - Popisují data na úrovni konceptuální a pohledů modelů. Jsou to modely pro modelování
objektů reálného světa (ER model, OO model, funkcionální model, ...)
	- **Databázové modely** - Definující logickou organizaci dat v databázi (relační, síťové, hierarchický, OO, objektově relační apod, ...)
- **Fyzické modely** - Popisují data na fyzické úrovni

_Někdy se v souvislosti s návrhem relační databáze logickým modele označuje ER diagram a fyzickým modelem podobný diagram ukazující tabulky a vztahy mezi nimi._

## Databázové modely
### Hierarchický model
- nebyl se schopný vypořádat se vztahy 1:N

### Síťový model
- **Struktura dat** - Množina záznamů + pojmenování vazeb  
- **Manipulace s daty** - Navigační - První záznam s danou hodnotou pole, nastavení na první členský záznam, na další vytvoření/zrušení/modifikace záznamu apod...
- **Standardizace** - Standard DBTG CODASYL (nějaké datum...)

### Relační model
- **Struktura dat** - Na logické úrovni jsou data strukturována do tabulek (tzv. normalizovaných - hodnoty v tabulce musí být z hlediska významu atomické (skalární)).
- **Manipulace s daty** - Výběr z tabulky, vložení/změna/zrušení řádků, jednoduchá navigace po řádcích tabulky.

## Schéma databáze
V podstatě říká, jak jsou data v databázi organizována, jaká existují integritní omezení atd... Jedná se o _metainformace_

## Datová nezávislost
Schopnost modifikovat schéma bez vlivu na schéma na vyšší úrovni.
Úrovně nezávislosti: 
- **Fyzická nezávislost** - Schopnost modifikace fyzického schématu bez nutnosti přepsat aplikační programy  
_Například vytvoření efektivnější přístupové metody_
- **Logická nezávislost** - Schopnost modifikovat logické schéma bez nutnosti přepsat aplikační programy  
_Například přidání sloupce tabulky_  
Snazší je dosažení fyzické nezávislosti dat

## Databázové jazyky
Je to jazyk, kterému rozumí [systém řizení báze dat](#system-rizeni-baze-dat) - někdy jej označujeme jako dotazovací (byť neslouží pouze k dotazování). U relačních systémů je to typicky SQL.
Můžeme rozlišit 2 skupiny těchto jazyků
- **Jazyk pro definici dat (DDL)** - Skupina příkazů, které slouží pro vytvoření, upravení a smazání objektů (tabulek). V podstatě upravují strukturu databáze.
- **Jazyk pro manipulaci s daty (DML)** - Patří zde především SELECT, INSERT, DELETE, UPDATE
- **Jazyk pro žízení dat (DCL)** - Řízení přístupu k datům