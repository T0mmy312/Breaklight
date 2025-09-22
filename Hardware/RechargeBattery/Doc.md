\## Charging Circuit Options



Created by: C. Schieszler



In this document we will discuss how we can charge the \*Samsung SDI Li-Ion Cell INR21700-50S (21700, 5000 mAh, 6C)\*.



\### Simple / Low Current (≈1 A)

\- \*\*TP4056 module\*\* (linear CC/CV charger, 4.2 V, up to 1 A).  

\- Very simple, USB-powered, and inexpensive.  

\- Downsides: long charging time (~6–7 h for 5000 mAh) and thermal issues at higher currents.  



\### Medium Current (2–4 A)

\- \*\*TI BQ24133\*\* (switching charger with integrated MOSFETs).  

\- Supports ~3–4 A charging and provides efficient power conversion.  

\- Balanced compromise between charging speed, efficiency, and circuit complexity.  



\### High Current (4–6 A and above)

\- \*\*TI BQ24610 / BQ24617\*\* (switching charger controllers).  

\- Require external MOSFETs and an inductor, but can scale to higher currents (up to 6 A+).  

\- Efficient design, well suited for fast charging and high-power systems.  



\### Important Notes

\- The 50S cell has \*\*no integrated BMS\*\* → it must always be combined with a protection circuit (overvoltage, undervoltage, overcurrent, temperature).  

\- Charging parameters must be set correctly: \*\*4.2 V\*\* cutoff, charge current according to target (2.5 A standard, up to 6 A rated), termination current ~100–250 mA.  

\- For charging above 2–3 A, sufficient thermal management is required.  



---



\### Final Choice for This Project

Since our USB-C port can deliver up to \*\*5 A\*\*, we will use a \*\*high-current charging circuit\*\*.  

The TI BQ24610/BQ24617 family is the best fit, as it supports efficient step-down charging at these currents while allowing proper current control and safety integration.  



Circuit reference: \[example circuit](https://www.circuits-diy.com/nicd-battery-charger-circuit-with-reverse-polarity-protection/)  



