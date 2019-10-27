DROP TABLE UZIVATEL CASCADE CONSTRAINTS;
DROP TABLE VZTAH CASCADE CONSTRAINTS;
DROP TABLE SKOLA CASCADE CONSTRAINTS;
DROP TABLE ADRESA CASCADE CONSTRAINTS;
DROP TABLE AKCE CASCADE CONSTRAINTS;
DROP TABLE ZAMESTNANI CASCADE CONSTRAINTS;
DROP TABLE ZPRAVA CASCADE CONSTRAINTS;
DROP TABLE FOTKA CASCADE CONSTRAINTS;
DROP TABLE ALBUM CASCADE CONSTRAINTS;
DROP TABLE PRISPEVEK CASCADE CONSTRAINTS;
DROP TABLE KONVERZACE CASCADE CONSTRAINTS;
DROP TABLE UZIVATEL_AKCE CASCADE CONSTRAINTS;
DROP TABLE UZIVATEL_SKOLA CASCADE CONSTRAINTS;
DROP TABLE UZIVATEL_PRISPEVEK CASCADE CONSTRAINTS;
DROP TABLE UZIVATEL_PRATELSTVI CASCADE CONSTRAINTS;
DROP TABLE UZIVATEL_FOTKA CASCADE CONSTRAINTS;
DROP TABLE UZIVATEL_KONVERZACE CASCADE CONSTRAINTS;
DROP SEQUENCE UZIVATEL_ID_GEN;
DROP SEQUENCE VZTAH_ID_GEN;
DROP SEQUENCE SKOLA_ID_GEN;
DROP SEQUENCE ADRESA_ID_GEN;
DROP SEQUENCE AKCE_ID_GEN;
DROP SEQUENCE ZAMESTNANI_ID_GEN;
DROP SEQUENCE ZPRAVA_ID_GEN;
DROP SEQUENCE FOTKA_ID_GEN;
DROP SEQUENCE ALBUM_ID_GEN;
DROP SEQUENCE PRISPEVEK_ID_GEN;
DROP SEQUENCE KONVERZACE_ID_GEN;

-- Sequences for generating UID
CREATE SEQUENCE UZIVATEL_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE VZTAH_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE SKOLA_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE ADRESA_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE AKCE_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE ZAMESTNANI_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE ZPRAVA_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE FOTKA_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE ALBUM_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE PRISPEVEK_ID_GEN START WITH 1 INCREMENT BY 1;
CREATE SEQUENCE KONVERZACE_ID_GEN START WITH 1 INCREMENT BY 1;

-- Tables creations
CREATE TABLE ADRESA(
    id INT DEFAULT ADRESA_ID_GEN.NEXTVAL,
    mesto VARCHAR(50) NOT NULL,
    ulice VARCHAR(50) NOT NULL,
    cp INT NOT NULL,
    psc NUMBER(5) NOT NULL,
    CONSTRAINT adresa_pk PRIMARY KEY(id)
);

CREATE TABLE UZIVATEL(
    id INT,
    jmeno VARCHAR(50) NOT NULL,
    prijmeni VARCHAR(50) NOT NULL,
    tel NUMBER(14) NOT NULL,
    email VARCHAR(50) NOT NULL,
    adresa INT NOT NULL,
    CONSTRAINT uzivatel_pk PRIMARY KEY(id),
    CONSTRAINT uzivatel_adresa_pk FOREIGN KEY (adresa) REFERENCES adresa(id)
);

CREATE TABLE VZTAH(
    id INT DEFAULT VZTAH_ID_GEN.NEXTVAL,
    typ VARCHAR(50) NOT NULL,
    uzivatel1 INT NOT NULL,
    uzivatel2 INT NOT NULL,
    CONSTRAINT vztah_pk PRIMARY KEY(id),
    CONSTRAINT vztah_uzivatel_fk_1 FOREIGN KEY (uzivatel1) REFERENCES uzivatel(id),
    CONSTRAINT vztah_uzivatel_fk_2 FOREIGN KEY (uzivatel2) REFERENCES uzivatel(id)
);
CREATE TABLE SKOLA(
    id INT DEFAULT SKOLA_ID_GEN.NEXTVAL,
    nazev VARCHAR(50) NOT NULL,
    typ VARCHAR(50) NOT NULL,
    adresa INT NOT NULL,
    CONSTRAINT skola_pk PRIMARY KEY(id),
    CONSTRAINT skola_adresa_fk FOREIGN KEY (adresa) REFERENCES adresa(id)
);
CREATE TABLE AKCE(
    id INT DEFAULT AKCE_ID_GEN.NEXTVAL,
    datum TIMESTAMP NOT NULL,
    autor INT NOT NULL,
    adresa INT NOT NULL,
    CONSTRAINT akce_pk PRIMARY KEY(id),
    CONSTRAINT akce_uzivatel_fk FOREIGN KEY (autor) REFERENCES uzivatel(id),
    CONSTRAINT akce_adresa_fk FOREIGN KEY (adresa) REFERENCES adresa(id)
);
CREATE TABLE ZAMESTNANI(
    id INT DEFAULT ZAMESTNANI_ID_GEN.NEXTVAL,
    nazev VARCHAR(50) NOT NULL,
    typ VARCHAR(50) NOT NULL,
    uzivatel INT NOT NULL,
    adresa INT NOT NULL,
    CONSTRAINT zamestnani_pk PRIMARY KEY(id),
    CONSTRAINT zamestnani_uzivatel_fk FOREIGN KEY (uzivatel) REFERENCES uzivatel(id),
    CONSTRAINT zamestnani_adresa_fk FOREIGN KEY (adresa) REFERENCES adresa(id)
);
create table KONVERZACE(
    id INT DEFAULT KONVERZACE_ID_GEN.NEXTVAL,
    nazev VARCHAR(50) NOT NULL,
    anketa NUMBER(1,0) NOT NULL,
    CONSTRAINT konverzace_pk PRIMARY KEY(id)
);
CREATE TABLE ZPRAVA(
    id INT DEFAULT ZPRAVA_ID_GEN.NEXTVAL,
    obsah VARCHAR(4000) NOT NULL,
    datum TIMESTAMP NOT NULL,
    misto VARCHAR(20),
    uzivatel INT NOT NULL,
    konverzace INT NOT NULL,
    CONSTRAINT zprava_pk PRIMARY KEY(id),
    CONSTRAINT zprava_uzivatel_fk FOREIGN KEY (uzivatel) REFERENCES uzivatel(id),
    CONSTRAINT zprava_konverzace_fk FOREIGN KEY (konverzace) REFERENCES konverzace(id)
);
create table ALBUM(
    id INT DEFAULT ALBUM_ID_GEN.NEXTVAL,
    nazev VARCHAR(100) NOT NULL,
    soukromi NUMBER(1,0) NOT NULL,
    popis VARCHAR(120),
    autor INT NOT NULL,
    CONSTRAINT album_pk PRIMARY KEY(id),
    --ID TITULNI FOTKY FK!
    CONSTRAINT album_uzivatel FOREIGN KEY(autor) REFERENCES uzivatel(id)
);

create table FOTKA(
    id INT DEFAULT FOTKA_ID_GEN.NEXTVAL,
    url VARCHAR(100) NOT NULL,
    datum_publikovani TIMESTAMP NOT NULL,
    misto_publikovani VARCHAR(120),
    misto_zachyceni VARCHAR(120),
    autor INT NOT NULL,
    album INT NOT NULL,
    akce INT NOT NULL,
    CONSTRAINT fotka_pk PRIMARY KEY(id),
    CONSTRAINT fotka_uzivatel_fk FOREIGN KEY(autor) REFERENCES uzivatel(id),
    CONSTRAINT fotka_album_fk FOREIGN KEY(album) REFERENCES album(id),
    CONSTRAINT fotka_akce_fk FOREIGN KEY(akce) REFERENCES akce(id)
    --- UZIVATEL oznacen FOTKA
);
create table PRISPEVEK(
    id INT DEFAULT PRISPEVEK_ID_GEN.NEXTVAL,
    obsah VARCHAR(100) NOT NULL,
    misto_publikovani VARCHAR(120),
    datum TIMESTAMP NOT NULL,
    autor INT NOT NULL,
    CONSTRAINT prispevek_pk PRIMARY KEY(id),
    CONSTRAINT prispevek_uzivatel_fk FOREIGN KEY(autor) REFERENCES uzivatel(id)
);
CREATE TABLE UZIVATEL_AKCE(
    akce INT NOT NULL,
    uzivatel INT NOT NULL,
    CONSTRAINT uzivatel_akce_pk PRIMARY KEY(akce, uzivatel),
    CONSTRAINT uzivatel_akce_akce_fk FOREIGN KEY(akce) REFERENCES akce(id),
    CONSTRAINT uzivatel_akce_uzivatel_fk FOREIGN KEY(akce) REFERENCES uzivatel(id)
);
CREATE TABLE UZIVATEL_SKOLA(
    skola INT NOT NULL,
    uzivatel INT NOT NULL,
    CONSTRAINT uzivatel_skola_pk PRIMARY KEY(skola, uzivatel),
    CONSTRAINT uzivatel_skola_skola_fk FOREIGN KEY(skola) REFERENCES skola(id),
    CONSTRAINT uzivatel_skola_uzivatel_fk FOREIGN KEY(uzivatel) REFERENCES uzivatel(id)
);
CREATE TABLE UZIVATEL_PRISPEVEK(
    prispevek INT NOT NULL,
    uzivatel INT NOT NULL,
    CONSTRAINT uzivatel_prispevek_pk PRIMARY KEY(prispevek, uzivatel),
    CONSTRAINT uzivatel_prispevek_prispevek_fk FOREIGN KEY(prispevek) REFERENCES prispevek(id),
    CONSTRAINT uzivatel_prispevek_uzivatel_fk FOREIGN KEY(uzivatel) REFERENCES uzivatel(id)
);
CREATE TABLE UZIVATEL_PRATELSTVI(
    uzivatel_1 INT NOT NULL,
    uzivatel_2 INT NOT NULL,
    CONSTRAINT uzivatel_pratelstvi_pk PRIMARY KEY(uzivatel_1, uzivatel_2),
    CONSTRAINT uzivatel_pratelstvi_uzivatel_1_fk FOREIGN KEY(uzivatel_1) REFERENCES uzivatel(id),
    CONSTRAINT uzivatel_pratelstvi_uzivatel_2_fk FOREIGN KEY(uzivatel_2) REFERENCES uzivatel(id)
);
CREATE TABLE UZIVATEL_FOTKA(
    uzivatel INT NOT NULL,
    fotka INT NOT NULL,
    CONSTRAINT uzivatel_fotka_pk PRIMARY KEY(uzivatel, fotka),
    CONSTRAINT uzivatel_fotka_fotka_fk FOREIGN KEY(fotka) REFERENCES fotka(id),
    CONSTRAINT uzivatel_fotka_uzivatel_fk FOREIGN KEY(uzivatel) REFERENCES uzivatel(id)
);
CREATE TABLE UZIVATEL_KONVERZACE(
    uzivatel INT NOT NULL,
    konverzace INT NOT NULL,
    CONSTRAINT uzivatel_konverzace_pk PRIMARY KEY(uzivatel, konverzace),
    CONSTRAINT uzivatel_konverzace_konverzace_fk FOREIGN KEY(konverzace) REFERENCES konverzace(id),
    CONSTRAINT uzivatel_konverzace_uzivatel_fk FOREIGN KEY(uzivatel) REFERENCES uzivatel(id)
);


-- add 4. Ãºloha
CREATE OR REPLACE TRIGGER UZIVATEL_BEFORE_INSERT
    BEFORE INSERT
    ON UZIVATEL
    FOR EACH ROW
BEGIN
    IF :NEW.id is null THEN
        :NEW.id := UZIVATEL_ID_GEN.nextval;
    END IF;
END;
/

CREATE OR REPLACE TRIGGER ALBUM_BEFORE_DELETE
    BEFORE DELETE
    ON ALBUM
    FOR EACH ROW
BEGIN
    DELETE FROM FOTKA WHERE FOTKA.ALBUM = :old.id;
END;
/

CREATE OR REPLACE TRIGGER FOTKA_BEFORE_DELETE
    BEFORE DELETE
    ON FOTKA
    FOR EACH ROW
BEGIN
    DELETE FROM UZIVATEL_FOTKA WHERE UZIVATEL_FOTKA.FOTKA = :old.id;
END;
/

-- /add 4. Ãºloha

INSERT INTO ADRESA(mesto, ulice, cp, psc) VALUES ('Å tramberk', 'ZauliÄ�Ã­', 190, 74266);
INSERT INTO ADRESA(mesto, ulice, cp, psc) VALUES ('KopÅ™ivnice', 'ZahumenÃ­', 124, 74221);
INSERT INTO ADRESA(mesto, ulice, cp, psc) VALUES ('Vostrava', 'Bri Sedlacku', 314, 72120);
INSERT INTO ADRESA(mesto, ulice, cp, psc) VALUES ('Brno-KrÃ¡lovo pole', 'BoÅ¾etÄ›chova', 1, 61200);
INSERT INTO ADRESA(mesto, ulice, cp, psc) VALUES ('KopÅ™ivnice', 'Å tefÃ¡nikova', 142, 74221);
INSERT INTO ADRESA(mesto, ulice, cp, psc) VALUES ('Ostrava', 'TietovÃ¡', 420, 70200);

INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Jan', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('AleÅ¡', 'SedlÃ¡Ä�ek', 00420777979687, 'alesed@gmail.com', 3);

INSERT INTO AKCE(datum, autor, adresa) VALUES (TO_TIMESTAMP('20-05-2019 20:30:00','DD-MM-YYYY HH24:MI:SS'), 1, 2);

INSERT INTO ALBUM(nazev, soukromi, popis, autor) VALUES ('Ostrafski futbal', 0, 'ToÅ¡ takto se Ä�utalo u nÃ¡s.', 2);

INSERT INTO FOTKA(url, datum_publikovani, misto_publikovani, misto_zachyceni, autor, album, akce)
VALUES ('https://www.fit.vutbr.cz/FIT/location/air03.jpg', TO_TIMESTAMP('20-05-2019 21:24:20','DD-MM-YYYY HH24:MI:SS'), 'Koleje', 'Å kola', 2, 1, 1);
INSERT INTO FOTKA(url, datum_publikovani, misto_publikovani, misto_zachyceni, autor, album, akce)
VALUES ('http://www.detskahriste.eu/ew/aacf8691-dc2d-40f6-95d3-1b7c65f04670-cs', TO_TIMESTAMP('21-05-2019 00:01:00','DD-MM-YYYY HH24:MI:SS'), 'Koleje', 'HÅ™iÅ¡tÄ›', 2, 1, 1);

INSERT INTO KONVERZACE(nazev, anketa) VALUES ('NÃ¡Å¡ soukromÃ½ chat..', 0);

INSERT INTO PRISPEVEK(obsah, misto_publikovani, datum, autor)
VALUES ('ToÅ¡ fajnÄ› jsem si dneska s klukma zaÄ�utal!', 'Frantovo ihrisko', TO_TIMESTAMP('23-05-2019 18:21:00','DD-MM-YYYY HH24:MI:SS'), 1);

INSERT INTO SKOLA(nazev, typ, adresa) VALUES ('VUT FIT', 'UniverzitnÃ­ peklo na zemi', 4);

INSERT INTO UZIVATEL_AKCE(akce, uzivatel) VALUES (1, 1);
INSERT INTO UZIVATEL_AKCE(akce, uzivatel) VALUES (1, 2);

INSERT INTO UZIVATEL_FOTKA(uzivatel, fotka) VALUES (1, 1);
INSERT INTO UZIVATEL_FOTKA(uzivatel, fotka) VALUES (2, 1);
INSERT INTO UZIVATEL_FOTKA(uzivatel, fotka) VALUES (1, 2);

INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(1, 1);
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(2, 1);

INSERT INTO UZIVATEL_PRATELSTVI(uzivatel_1, uzivatel_2) VALUES(1, 2);

INSERT INTO UZIVATEL_PRISPEVEK(prispevek, uzivatel) VALUES(1, 2);

INSERT INTO UZIVATEL_SKOLA(skola, uzivatel) VALUES(1, 1);
INSERT INTO UZIVATEL_SKOLA(skola, uzivatel) VALUES(1, 2);

INSERT INTO VZTAH(typ, uzivatel1, uzivatel2) VALUES('KomplikovanÃ½', 1, 2);

INSERT INTO ZAMESTNANI(nazev, typ, uzivatel, adresa) VALUES('ProgramÃ¡tor', 'PlnÃ½ Ãºvazek', 1, 5);
INSERT INTO ZAMESTNANI(nazev, typ, uzivatel, adresa) VALUES('ProgramÃ¡tor', 'StÃ¡Å¾', 2, 6);

INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('AhojQy!', TO_TIMESTAMP('01-01-2012 01:59:00','DD-MM-YYYY HH24:MI:SS'), 'Pivovar v Pilsemu', 2, 1);
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('Na shledanou... nechci se s VÃ¡mi bavit, ozvÄ›te se, prosÃ­m, nÄ›kdy jindy.', TO_TIMESTAMP('01-01-2019 00:00:01','DD-MM-YYYY HH24:MI:SS'), 'OstravarÃ©na', 1, 1);
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('Ach jo... :( Respektuji. RÃ¡d jsem vÃ¡s poznal.', CURRENT_TIMESTAMP, 'Pivovar v Pilsemu', 2, 1);

-- 3. Ãºloha

-- ZjistÃ­, na kolika fotkÃ¡ch jsou jednotlivÃ­ uÅ¾ivatelÃ© oznaÄ�eni
SELECT uzivatel.jmeno, uzivatel.prijmeni, count(*) as pocet_oznaceni
FROM uzivatel
INNER JOIN uzivatel_fotka on uzivatel_fotka.uzivatel = uzivatel.id
GROUP BY uzivatel.jmeno, uzivatel.prijmeni;

-- ZjistÃ­, kolika akcÃ­ se jednotlivÃ­ uÅ¾ivatelÃ© zÃºÄ�astnili
SELECT uzivatel.jmeno, uzivatel.prijmeni, count(*) as pocet_navstivenych_akci
FROM uzivatel
INNER JOIN uzivatel_akce on uzivatel_akce.uzivatel = uzivatel.id
GROUP BY uzivatel.jmeno, uzivatel.prijmeni;

-- ZjistÃ­, kolik zprÃ¡v v jednotlivÃ½ch konverzacÃ­ jednotlivÃ­ uÅ¾ivatelÃ© napsali
SELECT uzivatel.jmeno, uzivatel.prijmeni, konverzace.nazev as nazev_konverzace, count(*) as pocet_zprav_v_konverzaci
FROM uzivatel
INNER JOIN zprava on zprava.uzivatel = uzivatel.id
INNER JOIN konverzace on konverzace.id = zprava.konverzace
GROUP BY uzivatel.jmeno, uzivatel.prijmeni, konverzace.nazev;

-- ZjistÃ­, kteÅ™Ã­ uÅ¾ivatele jsou nÄ›kde zamÄ›stnanÃ­
SELECT uzivatel.jmeno, uzivatel.prijmeni
FROM uzivatel
WHERE EXISTS (
    SELECT * 
    FROM zamestnani 
    WHERE uzivatel.id = zamestnani.uzivatel
);

-- KteÅ™Ã­ uÅ¾ivatele nevytvoÅ™ili Å¾Ã¡dnÃ½ pÅ™Ã­spÄ›vek
SELECT uzivatel.jmeno, uzivatel.prijmeni
FROM uzivatel
WHERE uzivatel.id NOT IN (
    SELECT uzivatel_prispevek.uzivatel
    FROM uzivatel_prispevek
);

-- 4. Ãºloha
-- UkÃ¡zka, Å¾e nenÃ­ tÅ™eba zadÃ¡vat ID uÅ¾ivatele -> automaticky se vygeneruje v triggeru
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Jan', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(id, jmeno, prijmeni, tel, email, adresa) VALUES (500,'Jan', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);

-- UkÃ¡zka smazÃ¡nÃ­ alba (smaÅ¾ou se i vÅ¡echny fotky, kterÃ© v danÃ©m albu jsou)
DELETE FROM ALBUM WHERE ALBUM.ID = 1;

-- new uzivatele
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Alda', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Boris', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Honza', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Adam', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Pavel', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Marek', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Bro', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Barney', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Ted', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
INSERT INTO UZIVATEL(jmeno, prijmeni, tel, email, adresa) VALUES ('Robert', 'Demel', 00420777979686, 'jandemel98@gmail.com', 1);
-- new konverzace
INSERT INTO KONVERZACE(nazev, anketa) VALUES ('Testovaci chat1', 0);
INSERT INTO KONVERZACE(nazev, anketa) VALUES ('Testovaci chat2', 0);
INSERT INTO KONVERZACE(nazev, anketa) VALUES ('Testovaci chat3', 0);
INSERT INTO KONVERZACE(nazev, anketa) VALUES ('Testovaci chat4', 0);
-- uzivatele v konverzaci 1
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(3, 2);
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(4, 2);
-- uzivatele v konverzaci 2
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(5, 3);
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(6, 3);
-- uzivatele v konverzaci 3
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(7, 4);
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(8, 4);
-- uzivatele v konverzaci 4
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(9, 5);
INSERT INTO UZIVATEL_KONVERZACE(uzivatel, konverzace) VALUES(10, 5);
-- insert zpravy
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('AhojQy!', TO_TIMESTAMP('01-01-2012 01:59:00','DD-MM-YYYY HH24:MI:SS'), 'Pivovar v Pilsemu', 3, 2);
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('Na shledanou...', TO_TIMESTAMP('01-01-2019 00:00:01','DD-MM-YYYY HH24:MI:SS'), 'OstravarÃ©na', 4, 2);

INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('AhojQy!', TO_TIMESTAMP('01-01-2012 01:59:00','DD-MM-YYYY HH24:MI:SS'), 'Pivovar v Pilsemu', 5, 3);
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('Na shledanou...', TO_TIMESTAMP('01-01-2019 00:00:01','DD-MM-YYYY HH24:MI:SS'), 'OstravarÃ©na', 6, 3);

INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('AhojQy!', TO_TIMESTAMP('01-01-2012 01:59:00','DD-MM-YYYY HH24:MI:SS'), 'Pivovar v Pilsemu', 7, 4);
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('Na shledanou...', TO_TIMESTAMP('01-01-2019 00:00:01','DD-MM-YYYY HH24:MI:SS'), 'OstravarÃ©na', 8, 4);

INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('AhojQy!', TO_TIMESTAMP('01-01-2012 01:59:00','DD-MM-YYYY HH24:MI:SS'), 'Pivovar v Pilsemu', 9, 5);
INSERT INTO ZPRAVA(obsah, datum, misto, uzivatel, konverzace)
VALUES('Na shledanou...', TO_TIMESTAMP('01-01-2019 00:00:01','DD-MM-YYYY HH24:MI:SS'), 'OstravarÃ©na', 10, 5);

-- Explain plan ukol
-- ZjistÃ­, kolik zprÃ¡v v jednotlivÃ½ch konverzacÃ­ jednotlivÃ­ uÅ¾ivatelÃ© napsali
EXPLAIN PLAN FOR 
    SELECT uzivatel.jmeno, uzivatel.prijmeni, konverzace.nazev as nazev_konverzace, count(*) as pocet_zprav_v_konverzaci
    FROM uzivatel
    INNER JOIN zprava on zprava.uzivatel = uzivatel.id
    INNER JOIN konverzace on konverzace.id = zprava.konverzace
    GROUP BY uzivatel.jmeno, uzivatel.prijmeni, konverzace.nazev;
-- Vypis Explain plan do konzole    
SELECT plan_table_output  
FROM TABLE(DBMS_XPLAN.DISPLAY('plan_table' ,null,'typical'));

-- Grant privileges to another user
GRANT ALL ON UZIVATEL TO xdemel01;
GRANT ALL ON VZTAH TO xdemel01;
GRANT ALL ON ADRESA TO xdemel01;
GRANT ALL ON AKCE TO xdemel01;
GRANT SELECT ON ZAMESTNANI TO xdemel01;
GRANT INSERT ON ZPRAVA TO xdemel01;
GRANT UPDATE ON SKOLA TO xdemel01;
GRANT DELETE ON FOTKA TO xdemel01;

-- Index
CREATE INDEX test_index1 ON uzivatel(prijmeni);
--DROP INDEX test_index1;

-- Explain plan ukol with index
-- ZjistÃ­, kolik zprÃ¡v v jednotlivÃ½ch konverzacÃ­ jednotlivÃ­ uÅ¾ivatelÃ© napsali
EXPLAIN PLAN FOR 
    SELECT uzivatel.jmeno, uzivatel.prijmeni, konverzace.nazev as nazev_konverzace, count(*) as pocet_zprav_v_konverzaci
    FROM uzivatel
    INNER JOIN zprava on zprava.uzivatel = uzivatel.id
    INNER JOIN konverzace on konverzace.id = zprava.konverzace
    WHERE uzivatel.prijmeni = 'SedlÃ¡Ä�ek'
    GROUP BY uzivatel.jmeno, uzivatel.prijmeni, konverzace.nazev;
-- Vypis Explain plan do konzole    
SELECT plan_table_output  
FROM TABLE(DBMS_XPLAN.DISPLAY('plan_table' ,null,'typical'));

-- Vytvoreni instance AKCE
CREATE MATERIALIZED VIEW akce_new
CACHE
BUILD IMMEDIATE
REFRESH ON COMMIT AS
   SELECT xsedla1c.AKCE.ID, xsedla1c.AKCE.autor, xsedla1c.AKCE.adresa FROM AKCE
   INNER JOIN xsedla1c.uzivatel on xsedla1c.uzivatel.id = xsedla1c.akce.autor;

-- Remove materialized view in case of needed
-- DROP MATERIALIZED VIEW akce_new;

-- Test aktualniho stavu
SELECT * FROM AKCE;
-- Insert akce
INSERT INTO xsedla1c.AKCE(datum, autor, adresa) VALUES (TO_TIMESTAMP('02-05-2019 12:00:00','DD-MM-YYYY HH24:MI:SS'), 2, 3);
-- Kontrola, ze stale v tabulce neni novy prvek
SELECT * FROM AKCE;
-- Potvrzeni zmen materialized view
COMMIT;
-- Kontrola, ze je tabulka AKCE aktualizovana
SELECT * FROM AKCE;

-- PROCEDURA 1
CREATE OR REPLACE PROCEDURE how_many_people_live_at_address (addressId in INT) 
IS
    CURSOR UZIVATEL_CURSOR IS SELECT * FROM UZIVATEL WHERE UZIVATEL.ADRESA = addressId;
    currentUzivatel UZIVATEL%ROWTYPE;
    finalCount INT;
BEGIN
    finalCount := 0;
    
    OPEN UZIVATEL_CURSOR;
    LOOP
        FETCH UZIVATEL_CURSOR INTO currentUzivatel;
        EXIT WHEN UZIVATEL_CURSOR%NOTFOUND;
        finalCount := finalCount + 1;
    END LOOP;
    CLOSE UZIVATEL_CURSOR;
    
    dbms_output.put_line(finalCount);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
      RAISE_APPLICATION_ERROR(-20000, 'No data found');
    WHEN OTHERS THEN
      RAISE_APPLICATION_ERROR(-20001, 'Unexpected procedure error');
END;
/

EXEC how_many_people_live_at_address (1);