# IDS Přednáška 2

Přístup k relační databázi z aplikačních programů (v čem programujeme)
## Použití specializovaných databázových jazyků
- Například PL/SQL (jedná se o úplné proramovací jazyky...)  

## Použití obecných programovacích jazyků
Musíme využít nějaké knihovny, nebo rozhraní pro přístup k databázi. Knihovny můžou být nativní. Existují i standardizovaná rohraní a k nim příslušné knihovny. 
Příklady knihoven:
- **Nativní**
	- OCI - Oracle Call Interface
	- ADO - ActiveX Data Objects
- **Standardizované**
	- ODBC - Open database connectivity
	- JDBC - Java database connectivity

## Role uživatelů databázového systému
### Administrátor databáze
V podstatě "vládce", který rozhoduje o všem - typicky někdo z vyššího managementu. Rozděluje práva ostatním uživatelům, spravuje databázi.

### Aplikační programátor
Očekává se znalost SQL, používá knihovny, snaží se programovat.

### Znalý uživatel
Zná SQL na takové úrovni, že je schopen použitím SQL konzole udělat ad-hoc dotaz a získat informace.

### Naivní uživatel
Pracuje s databází jedině prostřednictvím vytvořených programů, vůbec nemá páru, co to je SQL a je odkázán jenom na to, co mu aplikace dovolí.

_Podle toho frajera budeme po absolvování kurzu všichni minimálně znalí uživatelé... Worth it_

## Architektura databázových systémů a aplikací
Teď budeme pod pojmem databázová aplikace chápat i tu vrstvu systému řízení báze dat. Pokud to takto budeme chápat, tak můžeme u každé aplikace rozlišit 2 základní části **frontend** a **backend**.
- **Frontend** - To, co vidíme (využívá SŘBD)
- **Backend** - Realizuje všechny základní funkce SŘBD + nějaké další funkce

### Architektura klient-server
Na PC musí být nainstalovaná i vrstva zajišťující komunikaci se serverem. Vhodná pro komunikaci uvnitř firem (intranet). Nevýhodou je, že lze s databází pracovat přes aplikace pouze tam, kde je aplikace nainstalovaná.

### Vícevrstvá architektura
Klientem (tenkým) je například webový prohlížeč. Objevuje se vrstva aplikačního serveru. Tam je soustředěno gró aplikační logiky. Defacto připraví a naformátuje příslušnou stránku s daty z databáze.  
Aplikační server obsahuje především aplikační logiku, kontrolu dat apod..  
Motivací a hlavní výhodou této architektury je, že tady aplikace můžeme spouštět z libovolného PC, na kterém je standardní vybavení (zde například webový prohlížeč).

### Distribuovaný databázový systém
O takovém systému hovoříme tehdy, když to je architektura pro nikoliv lokální síť, ale pro rozlehlou síť, kde existuje řada uzlů propojených počítačovou sítí (například firma, která má řadu poboček v různých městech - v jednotlivých pobočkách jsou uzly, data jsou distribuována po uzlech). Každý uzel může současně plnit roli klienta a serveru.

**Vertikální škálování** - Zvětšujeme kapacitu úložišť  
**Horizontální škálování** - Přidáváme stroje - preferované

### Aplikace pro počítání v cloudu
Výhodou je, že infrastruktura se dá přizpůsobovat požadavkům aplikací (je velice pružná). Existují zde databáze relační, nerelační, zátěž se rozkládá apod...

V dnešní době se můžeme setkat v prostředí intranetu s dvouvrstvou architekturou klient-server, u rozlehlých sítí s distribuovanými databázemi a nebo i s cloudem.

Můžeme rozlišit následující kategorie SŘBD a odpovídající aplikace:
- Stolní (desktop) - orientované na jednouživatelské aplikace, často původně pro architekturu file server (Microsoft Access, FoxPro,...)
- Serverové - orientované na víceuživatelské klient/server a vícevrstvé aplikace
- Cloudové - orientované na hostování u poskytovatele cloudových služeb přístupných prostřednictvím internetu

### Typy DBS
- **Předrelační** - IMS, IDMS
- **Relační**
	- architektura "mainframe"
	- architektura "PC file-server" - dBASE, FoxBase
	- architektura klient-server - IBM DB2, Oracle, Microsoft SQL Server, Informix
- **Postrelační** - Objektově orientované, objektově-relační, deduktivní, NoSQL, MongoDB etc...

### Projekt
Nebudeme vyvíjet žádnou kompletní aplikaci. Budeme vytvářet pouze skripty (na dvouvrstvé architektuře).  
Můžeme použít Oracle SQL Developer, ale dá se použít i jakákoliv jiná SQL konzole. Ale musí být spustitelné i na finálním serveru.

_... nějaké nesmysly, co už dávno víme z IUS_

## Relační model databáze
