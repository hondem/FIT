# IPK Přednáška 3
## Protokoly používané pro email
- SMTP
- POP3
- IMAP
- HTTP (pokud chceme přistupovat přes nějaké webové rozhraní)

### SMTP
Některé SMTP umí i autentifikaci.

### POP3
Umí pouze získat seznam zpráv, získat zprávu a smazat zprávu. V podstatě triviální protokol.

### IMAP
Umí navíc od POP3 i uložit zprávy.

## DNS
Je to v podstatě pomůcka pro uživatele. Překládá doménové jméno na IP adresu (www.seznam.cz -> 192.154.238.2 (např.)). Aplikace požádá, aby OS přeložila doménové jméno na IP adresu. Ten zavolá resolver, který se spojí s lokálním DNS server a ten v komunikaci s ostatními DNS servery získá IP adresu odpovídající doménovému jménu. DNS je v podstatě velká distribuovaná databáze. Občas se musí provést několit výměn dat mezi jednotlivými DNS servery. Každý ví jenom kousek nějaké informace a odkazuje se na další DNS server. Komunikace mezi DNS je jednoduchá, takže větší množství dotazů ani moc nevadí. Dotaz má pouze několik bajtů.

Ukázkový dotaz:
```
www.someserver.com: typeA, classIN
```
Do dotazu můžeme specifikovat i jiné parametry:
- **AAAA** - chceme převést doménové jméno na IPv6 adresu
- **MX** - definuje, na jaký server se má doručit email pro uživatele nějaké @ domény
- **CNAME** - jedná se o alias k určitým jménům

### DNS servery
Tyto servery obsahují informace o serverech .com, .org, .edu apod... (o tzv. top-level domény). Ty dále obsahují informace o například DNS serveru yahoo.com, amazon.com.

### DNS rezoluce
#### Jak se to nedělá
Do prohlížeče jsem napsal cis.poly.edu. Pošle se to lokálnímu DNS serveru. Ten se zeptá Root DNS serveru -> top level dns server -> authoritative DNS server (a ten už zná cílový počítač). Následně se data vrací zpátky stejnou cestou. Problém je, že jednotlivé servery si musí pamatovat, se kterým DNS serverem komunikovali (tedy musí vědět, kam musí data poslat zpátky).

#### Jak se to dělá
Veškerý workflow se přesouvá na lokální DNS server. Komunikuje přímo s root dns serverem, nebo s top level domain dns serverem, nebo s authoritativním dns serverem. Navíc u sebe může mít nějakou paměť a může si pamatovat IP adresy jednotlivých doménových jmén. 

#### Zónové soubory
Má několiv částí (hlavičku, kde specifikuju zónu - example.com). Potom informace důležité pro činnost serveru, informace o DNS serverech, MX záznamy (informace o tom, jaké jsou poštovní servery), A záznamy (mapování na IP adresy), (kanonické jména pro ftp servery).

_Spousta keců o socketech_