# BMS-Design – BQ2972 + IPD090N03LG für Samsung INR21700-50S

## Ziel
Das Ziel war, eine **einfache, zuverlässige Schutzschaltung (BMS)** für eine einzelne Samsung INR21700-50S Zelle zu realisieren – ohne Overengineering, aber mit sauberer technischer Reserve bei Strom und Spannung.

---

## Bauteilübersicht

| Komponente | Typ | Funktion | Begründung |
|-------------|-----|-----------|-------------|
| **BQ2972** | Protection-IC | Überwacht Zellspannung & Strom | Schutz gegen Overcharge, Overdischarge, Kurzschluss |
| **IPD090N03LG** | N-Kanal Logic-Level MOSFET | Trennt Lade- und Entladepfad | Niedriger R_DS(on), hohe Effizienz, ideal für 3–4 V Systeme |
| **Shunt (z. B. 10 mΩ)** | Präziser Messwiderstand | Strommessung für Schutzlogik | Definiert Overcurrent-Schwelle |

---

## Warum **BQ2972**
Der **Texas Instruments BQ2972** ist ein **klassischer 1-Zellen Li-Ion Schutzcontroller**.  
Er ist kein volles Smart-BMS, sondern eine **rein analoge, hardwarebasierte Sicherheitsstufe** – genau das, was du für eine einzelne 21700-Zelle brauchst.

### Vorteile
- Unterstützt externe FETs → hohe Strombelastbarkeit möglich.  
- Sehr geringe Ruheströme (<1 µA).  
- Präzise Schutzschwellen:
  - **Overvoltage:** ~4.3 V → sicher unterhalb 4.35 V absolute maximum der Samsung 50S.  
  - **Undervoltage:** ~2.5–2.7 V → schützt vor Tiefentladung.  
  - **Overcurrent:** typ. 100 mV @ Sense-Resistor.  
- Interne **Ladungspumpe** sorgt für ausreichendes Gate-Drive (+V_GS) der externen MOSFETs.
- Kein µC nötig – funktioniert autark und sofort nach Anschluss.

Damit bietet der BQ2972 **Zellschutz auf Hardwareebene**, ohne dass dein Ladecontroller (BQ25895M) das übernehmen muss.

---

## Warum **IPD090N03LG**
Der **Infineon IPD090N03LG** ist ein **30 V Logic-Level N-MOSFET** aus der OptiMOS-Serie.

### Technische Eigenschaften
| Parameter | Wert | Bedeutung |
|------------|-------|------------|
| **V_DS max** | 30 V | 5× über Zellspannung – hohe Reserve |
| **R_DS(on)** | 7.5 – 9 mΩ @ 4.5 V Gate | Minimaler Spannungsabfall, kaum Verlustwärme |
| **I_D max** | 40 A | locker über 30 A Dauerlast der Zelle |
| **Gate Threshold** | 1 – 2.2 V | Schaltet zuverlässig schon bei niedrigen Gate-Spannungen |
| **P_tot** | 42 W | ausreichend thermische Reserve im DPAK-Gehäuse |

Damit passt der MOSFET **perfekt zur Samsung 50S**, deren maximale Dauerlast 30 A beträgt.  
Bei 9 mΩ R_DS(on) ergibt das nur:
\[
P = I^2 \cdot R = (30A)^2 \cdot 0.009Ω = 8.1 W
\]
→ gut beherrschbar mit kleiner Kupferfläche oder Kühlpad.

---

## Zusammenspiel BQ2972 + IPD090N03LG

Die Kombination funktioniert ideal:
- BQ2972 steuert **zwei externe MOSFETs** (Charge & Discharge-Pfad).
- IPD090N03LG ist **logic-level-fähig**, also voll kompatibel mit der Gate-Spannung des BQ2972 (~4.5 V).  
- Schutz reagiert schnell auf:
  - Überspannung (abschalten Lade-FET)
  - Unterspannung (abschalten Entlade-FET)
  - Überstrom oder Kurzschluss (abschalten beider FETs)
- Sehr geringer Eigenverbrauch – perfekt für Einzelzellenanwendungen wie Powerbanks, Werkzeuge oder Eigenbau-Akkupacks.

---

## Fazit
Diese Kombination ist:
- **Effizient:** niedriger Spannungsabfall und kaum Eigenverbrauch  
- **Sicher:** hardwarebasierter Schutz mit klaren Schwellen  
- **Einfach:** keine Firmware, kein MCU, kein I²C nötig  
- **Skalierbar:** funktioniert für jede 3.6 – 4.2 V Einzelzelle, auch in Serien-BMS-Systemen

Damit ist **BQ2972 + IPD090N03LG** das **technisch und wirtschaftlich optimale Duo** für deine Samsung INR21700-50S.

---

**Autor:** C. Schieszler  
**Datum:** 2025-10-16  
