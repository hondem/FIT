# IPK Přednáška 2
## ISP
- **Lokální ISP** - Připojují koncové uživatele
- **Regional ISP** - Od nich si lokální ISP kupují konektivitu
- **NSP** - V podstatě páteř sítě

NSP se propojují v IXP (International exchange point). Je zde vytvořená lokální síť, která propojuje NSP (musí být rychlá).  

### Cesnet 2 
Je to poskytovatel založený spojením několika univerzit. V podstatě hlavní poskytovatel v Česku. V americe je to *VERIZON* (tam se ale bavíme o skutečné páteři internetu).

## Zpoždění, ztráta a propustnost
Víme, že paket musí skákat mezi jednotlivými směrovači.  

### Zpoždění
V každém prvku můžeme rozeznat 4 prvky zpoždění
- Zpoždění na přepínání paketů
- Né vždy je možné packet hned odeslat (takže je odeslán do fronty - opět nějaká doba potřebná. Doba ve frontě se hodně mění v závislosti na vytížení sítě)
- Doba, než je paket odeslán (závisí na rychlosti linky)
- Propagation delay - závisí na délky spoje

Intenzita provozu = délka paketu * průměrná rychlost / šířka pásma

Provideři se snaží pohybovat někde uprostřed té intenzity provozu (podobný graf jako x^4, x náleží R+)

`tracert URL` - analyzujeme kudy všudy proudí paket, jak dlouho to trvá tam i zpět. Funguje tak, že se snaží zaslat packet na cílovou adresu. Nastavuje packetům TTL tak, že ho jednotlivé routery vždy zahazují (inkrementuje jej o 1). U některých routerů to ale vyhodí `Request timed out`. To je kvůli bezpečnosti a nějaké optimalizaci, nebo tak něco. 

## Vrstvy TCP/IP
- Aplikační (emailový klient etc...)
- Transportní (rozkouskuje na segmenty)
- Síťová (router)
- Linková (switch)
- Fyzická (kabely, hub)

Z vyšších vrstev níž se data zapouzřujou (každá vrstva přidává svou hlavičku).

## Protokoly
- **TCP** - Potvrzovaný přenos (3-way handshaking apod...)
- **UDP** - Nepotvrzovaný přenos (použití třeba pro streamy)
