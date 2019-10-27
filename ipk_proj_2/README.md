# IPK Projekt - Scanner síťových služeb
### Autor - Jan Demel (xdemel01)

## Obsah
### [Úvod](#úvod-1)
### [Řešení](#řešení-1)
### [Obecně známý open-source port scanner](#obecně-známý-open-source-port-scanner-1)

## Úvod
Úkolem bylo naimplementovat jednoduchý scanner síťových služeb za pomocí C/C++, socketů a knihovny libpcap.

## Řešení
Mé řešení umí zparsovat argumenty, získat adresu cílového zařízení a adresu zdrojového zařízení. K dalším částem projektu jsem se bohužel z důvodu časové vytíženosti nedostal. 

## Obecně známý open-source port scanner
Rozhodl jsem se otestovat nástroj `nmap`. Tento nástroj je volně ke stažení například pomocí nástroje Homebrew. Ze zajímavosti jsem si zkusil zjistit, které porty do 1024 jsou na mém zařízení otevřené. 
```
🔥 jandemel@Jan-Air-2:~ $ nmap -p 1-1024 localhost
Starting Nmap 7.70 ( https://nmap.org ) at 2019-04-21 21:38 CEST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.0016s latency).
Other addresses for localhost (not scanned): ::1
rDNS record for 127.0.0.1: mcpneu
Not shown: 524 filtered ports, 499 closed ports
PORT   STATE SERVICE
80/tcp open  http

Nmap done: 1 IP address (1 host up) scanned in 2.57 seconds
```
Zjistil jsem, že pouze jeden port je otevřený a to sice HTTP server na portu 80.