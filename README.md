# Autonomous Solar Panel Cleaning Robot

Design and engineering analysis of an autonomous robot for cleaning dust and dirt off solar panels, developed as a Design of Machine Elements course project (Department of Mechanical Engineering, Group 10).

## Overview

Dust and dirt accumulation on solar panels significantly reduces their efficiency and power output, and manual cleaning is time-consuming, labor-intensive, and impractical at scale. This project presents the design and engineering analysis of an **autonomous solar panel cleaning robot** — a motorized, sensor-guided system that moves across a panel's surface and cleans it with minimal human intervention.

The robot combines a motorized cleaning mechanism, a drive system, an Arduino-based control unit, and a lightweight mechanical chassis. To validate the design, the team carried out Center of Mass (COM) analysis, static and dynamic force analysis, stress/stress-concentration analysis, and fatigue (S-N curve) analysis, alongside CAD modeling and simulation .

## Key Contributions

- Design and development of an autonomous solar panel cleaning robot
- Integration of a motorized cleaning and drive mechanism for efficient cleaning operation
- Performance evaluation using COM, static, dynamic, and stress analysis
- A cost-effective, automated cleaning solution for solar panel maintenance

## Components Used

| Component | Quantity | Function |
|---|---|---|
| Arduino Uno R3 | 1 | ATmega328P microcontroller, 5V operating voltage — main controller |
| IR Obstacle Sensors | 4 | Infrared detection / obstacle sensing module |
| L298N Motor Driver | 1 | Dual H-Bridge motor control module |
| 2-Channel Relay | 1 | Electromagnetic switching module, 5V relay |
| 18650 Batteries | 4 | Rechargeable Li-ion battery, 3.7V |
| LM2596 Buck Converter | 1 | DC-DC step-down voltage regulator |
| 12V Water Pump | 1 | Compact DC water circulation pump |
| BO Motors & Wheels | 4 | High-torque geared motor with wheel assembly |
| Jumper Wires (60pk) | 1 | Electrical connection wires for circuit interfacing |

The Arduino Uno R3 acts as the main controller, the IR sensors handle obstacle/edge detection, the L298N motor driver controls motor movement, and the relay module handles switching. Power comes from 18650 Li-ion batteries, regulated to a stable supply via the LM2596 buck converter.

## Design

### Chassis / Body

The chassis forms the main structural body, supporting all mechanical and electronic components. It was developed using CAD modeling with dimensions sized for mounting the motors, batteries, cleaning mechanism, and control unit, prioritizing a lightweight, stable structure.

**Physical properties:**

| Property | Value |
|---|---|
| Area | 43200 mm² |
| Density | 1.24 g/cm³ |
| Mass | 294 g |
| Bounding box | 240.00 mm (L) × 180.00 mm (W) × 3.00 mm (thickness) |

## Engineering Analysis

Analysis was performed with the robot operating on a solar panel surface inclined at **21°**.

**System parameters:**

| Parameter | Symbol | Value |
|---|---|---|
| Total Mass | m | 0.7 kg |
| Gravity Acceleration | g | 9.81 m/s² |
| Inclination Angle | θ | 21° |
| Center of Gravity Height | h | 111 mm |
| Center of Mass | X, Y | 121 mm, 90 mm |
| Track Width (Wheelbase) | w | 180 mm |
| Wheel Radius | r | 65 mm |
| Motor Efficiency | η | 60% |
| Rolling Resistance Coeff. | Crr | 0.02 |
| Brush Drag Force | F_brush | 0.50 N |
| Brush Reaction Torque | τb | 0.05 Nm (estimated) |

### Analyses performed

- **Inclined-plane force analysis** — total weight, normal force, downslope force, and resulting factor of safety against sliding/tipping on the 21° incline
- **Traction / slip analysis** — minimum coefficient of friction required (≈0.42) versus the ~0.60 typically available from rubber wheels, confirming adequate traction
- **Dynamic analysis** — driving force, rolling resistance, and acceleration behavior
- **Stress and stress-concentration analysis** — bending and shear stress at critical chassis features (arm roots, fillets, cutouts), including stress concentration factor (Kt)
- **Fatigue (S-N curve) analysis** — using the PLA chassis material's ultimate tensile strength (58 MPa) and endurance limit, a fatigue-strength equation `S = 628.88(N)^-0.3603 MPa` was derived, giving an estimated fatigue life of **~15,570 cycles** under the calculated alternating stress (±19.41 MPa)

### Key results

- Factor of safety (static): close to **3**, indicating the structure is statically safe
- The chassis can develop fatigue cracks under repeated cyclic loading (wheel vibration, brush rotation), particularly at the front arm roots

### Demonstration
  - https://drive.google.com/file/d/1xpPIq0E5DjK2kI-ZSmbF67O1mccolGd0/view?usp=drivesdk

### Engineering recommendations

- Increase the fillet radius from 1 mm to 3–5 mm to reduce stress concentration
- Add triangular support ribs (gussets) near the arm roots for better load distribution and rigidity
- Use stronger or reinforced materials for improved fatigue resistance and long-term durability

## Applications

- Industrial solar power plants — automated, continuous cleaning of large-scale solar farms
- Smart cities / smart energy systems — integration into renewable energy management systems
- Agricultural solar systems — solar-powered irrigation and agricultural energy setups
- Educational and research institutions — robotics, automation, and renewable energy research
- Industrial automation — adaptable to other automated surface cleaning/maintenance systems

## Future Scope

- Integration of AI for intelligent, automated cleaning decisions
- IoT-based monitoring for remote control and real-time performance tracking
- Automatic dust detection to trigger cleaning only when needed
- Water-efficient, self-adjustable cleaning brushes
- Solar-powered charging for sustainable, self-sufficient operation
- Further COM and structural optimization for improved stability

## Team

**Group 10 — Department of Mechanical Engineering**
Course: Design of Machine Elements
Faculty Guide: Prof. Krishna Mohan Kumar

| S.No | Name | Roll Number |
|---|---|---|
| 1 | Ch. Prajay Verma | 230003018 |
| 2 | B. Samith Lal | 230003013 |
| 3 | B. Santhosh | 230003014 |
| 4 | M. Naveen | 230003042 |
| 5 | R. Manthru Naik | 230003055 |
| 6 | R. Yogendhra Babu | 230003056 |
| 7 | S. Manjunatha | 230003067 |
| 8 | S. Praveen | 230003063 |
| 9 | Y. Akshay | 230003087 |

## License

None.
