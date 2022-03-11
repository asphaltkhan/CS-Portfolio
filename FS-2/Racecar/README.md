# FS2-2 CAD Guide

- [FS2-2 CAD Guide](#fs2-2-cad-guide)
  - [Subsystem Abbreviation](#subsystem-abbreviation)
  - [Part Numbering Scheme Documentation](#part-numbering-scheme-documentation)
    - [Custom Part Numbering:](#custom-part-numbering)
    - [Conventional Off The Shelf (COTS) Parts](#conventional-off-the-shelf-cots-parts)
  - [Subsystem Inclusion](#subsystem-inclusion)
    - [Brake System - BR](#brake-system---br)
    - [Electrical - EL](#electrical---el)
    - [Engine and Drivetrain - EN](#engine-and-drivetrain---en)
    - [Frame & Body - FR](#frame--body---fr)
    - [Miscellaneous, Finish and Assembly - MS](#miscellaneous-finish-and-assembly---ms)
    - [Steering System - ST](#steering-system---st)
    - [Suspension System - SU](#suspension-system---su)
    - [Wheels, Wheel Bearings and Tires - WT](#wheels-wheel-bearings-and-tires---wt)

-----

**When creating a new folder inside a subsystem, please add the abberviation for the folder name at the end**

Example: FS-2\Racecar\Miscellaneous, Finish and Assembly - MS\\**Brake Light Holder - BLH**

-----
## Subsystem Abbreviation

- Brake System - BR
- Electrical – EL
- Engine and Drivetrain – EN 
- Frame & Body - FR
- Miscellaneous, Finish and Assembly - MS
- Steering System - ST
- Suspension System – SU
- Wheels, Wheel Bearings and Tires - WT


-----

## Part Numbering Scheme Documentation
### Custom Part Numbering:

**Part Number Template:**

**Car Model - Subsystem Abbr. - Subfolder Abbr. (if applicable) -Type - 4 digit # - Variation - Version, NAME**

**Examples:** 

1. FS2-EN-ACC-A-0002-V54, ACCUMULATOR, ASSEMBLY
2. FS2-BR-P-0034-V2, ROTOR, SHEET METAL
3. FS2-FR-A-0001-V1, CHASSIS, ASSEMBLY 

**General Comments:**

- All letters should be capital letters
- This should be followed for ALL parts in the GrabCAD

**Descriptions:**

- **Car Model**
  - FS2
- **Subsystem**
  - [Subsystem Abbreviation](#subsystem-abbreviation)
- **Type**
  - Part (P)
  - Assembly (A)
  - Drawing (D)
- **4 digit #**
  - A 4 digit value that should be chronologically generated based on the most recent part made
- **Variation**
  - This should be a term that describes which variation of the part it is
  - Only needed if there are multiple variations of a part
  - Ex)
    - WATERJET
    - LASER CUT
    - OUTSOURCE
- **Version**
  - If there are major revisions that have been made to a part it should be renamed to a different version
  - V1, V2, V3...
- **NAME**
  - This should be a descriptive name for whatever part of assembly that is in the file
  - It should be a **noun** followed by some **adjectives**
  - Ex)
    - ENCLOSURE, RIGHT SIDE PANEL
    - ACCUMULATOR
    - PLATE, PEDAL BOX ARM

### Conventional Off The Shelf (COTS) Parts

**COTS Part Name Template:**

NOUN, ADJECTIVE, PART NUMBER, SUPPLIER

Supplier Names Abbreviations:

- McMaster Carr = MMC

Examples:

- BOLT, 0.25-20 X 1" SOCKET HEAD, 91251A542, MMC
- SHOCK, DB Air IL-165X38MM, BAD2060, CANE CREEK

General Comments:

- In the case that a COTS part does not have CAD available you should just create a model that is based off of the part drawings they offer
  
-----

## Subsystem Inclusion

This is taken from FS-2\Series resources\Cost Event\Cost_Event_Rules_Supplement.pdf page 12-14

### Brake System - BR
- BR Brake 
- Fluid 
- Brake Master Cylinder 
- Brake Lines 
- Brake Discs 
- Brake Pads 
- Balance Bar 
- Calipers 
- Proportioning Valve 

### Electrical - EL 
- Brake Light  
- Bulbs 
- Dash Panel 
- Displays 
- Fuses 
- Gages (any) 
- Indicator Lights  
- Relays  
- Solenoids Switches / Buttons / Controls 
- Wire Harness / Connectors

### Engine and Drivetrain - EN 
- Accumulator Container 
- Accumulator Isolation Relays (AIR) 
- Accumulators / Batteries 
- Axles 
- Battery Management System (BMS/AMS) 
- Cell Module 
- Chain / Belt 
- Converter (AC-DC / DC-DC) 
- Coolant 
- Coolant Lines 
- CV Joints / U Joints 
- Differential 
- Differential Mounts 
- ECU 
- Hose Clamps 
- HV Wiring 
- Inertia Switch  
- Isolation Monitoring (IMD) 
- Motor Controller 
- Motor Mounts 
- Motors 
- Overflow Bottles 
- Radiator 
- Radiator Fans 
- Shields 
- Sprockets / Pulleys 
- Tractive System Active Light 
- TSMP 

### Frame & Body - FR
- Aerodynamic Devices (if used- Electrical – EL)  
- Body Attachments 
- Body Material 
- Body Processing Clutch 
- Floor Pan 
- Frame / Frame Tubes  
- Mounts Integral to Frame 
- Pedals 
- Shifter 
- Shifter Cable / Linkage 
- Throttle Controls 
- Tube End Preps 
- Tubes Cuts / Bends 
 
### Miscellaneous, Finish and Assembly - MS
- MS Driver’s Harness  
- Firewall 
- Headrest / Restraints  
- Mirrors 
- Paint – Body 
- Paint – Frame 
- Seats  
- Impact Attenuator 
- Shields 
- Brake Light Housing

### Steering System - ST
- Steering Rack 
- Steering Shaft 
- Steering Wheel 
- Steering Wheel Quick Release 
- Rod Ends / Clevis 
- Tie Rods 
 
### Suspension System - SU 
- Bell Cranks  
- Front A-Arms or Equivalent 
- Front Uprights 
- Pushrods / Pullrods 
- Rear A-Arms or Equivalent 
- Rear Uprights  
- Rod Ends 
- Shocks / Dampers 
- Springs 
- Suspension Mechanism 
 
### Wheels, Wheel Bearings and Tires - WT 
- Front Hubs 
- Lug Nuts 
- Rear Hubs 
- Tires 
- Valve Stems 
- Wheel Bearings 
- Wheel Studs 
- Wheel Weights 
- Wheels
