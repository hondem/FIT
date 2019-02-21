# IPP Přednáška 3
## Principy OO návrhu
- Identifikace objektů/tříd/instancí
- Rozdělení jednotlivých zodpovědností
- Trasovatelnost
- Robustnost a udržovatelnost
- Splnění (ne)funkčních požadavků
- Kvalita služeb (QoS)

Pro návrh používáme **UML**.
_Spousta keců ohledně UML_

## Výhody a nevýhody OOP

### Výhody
- Je jednoduché na pochopení
- Je praktické

### Nevýhody
- Je delší učící křivka
- Generuje pomalejší kód

## Třídní objektově-orientované jazyky a jejich implementace

### Třída
- Je objekt/entita obsahující: 
	- seznam instančních atributů (vč. metadat)
	- data
	- implementace metod

### Instance
= identita + "reference na její třídu" + data

## Třídní dědičnost
### Overloading
Až za běhu se rozhoduje podle konkrétního typu objektu, která metoda se bude invokovat.

### Overriding
Definujeme nové chování metodě potomka.