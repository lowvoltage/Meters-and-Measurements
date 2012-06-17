EESchema Schematic File Version 2  date 17/06/2012 20:40:51
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:AVR-Electrolytic-C-Meter-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "17 jun 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Connection ~ 2000 2550
Wire Wire Line
	2800 2550 2000 2550
Wire Wire Line
	2000 2550 1800 2550
Wire Wire Line
	1800 2550 1700 2550
Wire Wire Line
	1700 2550 1600 2550
Wire Wire Line
	1600 2550 1400 2550
Wire Wire Line
	2300 2850 2400 2850
Connection ~ 1800 3150
Wire Wire Line
	2000 3050 2000 3150
Wire Wire Line
	1800 3150 1800 3050
Wire Wire Line
	1600 3150 1600 3050
Connection ~ 1700 2550
Wire Wire Line
	1800 2550 1800 2650
Wire Wire Line
	1400 2550 1400 2650
Wire Wire Line
	2700 2250 2800 2250
Wire Wire Line
	2000 2250 2100 2250
Wire Wire Line
	2100 2250 2200 2250
Wire Wire Line
	1700 1450 1700 1350
Wire Wire Line
	2100 1350 2100 1500
Wire Wire Line
	1700 1950 1700 2050
Wire Wire Line
	2100 1900 2100 2250
Connection ~ 2100 2250
Wire Wire Line
	1700 2550 1700 2450
Wire Wire Line
	1600 2550 1600 2650
Connection ~ 1600 2550
Wire Wire Line
	2000 2550 2000 2650
Connection ~ 1800 2550
Wire Wire Line
	1700 3150 1700 3250
Connection ~ 1700 3150
Wire Wire Line
	2000 3150 1800 3150
Wire Wire Line
	1800 3150 1700 3150
Wire Wire Line
	1700 3150 1600 3150
Wire Wire Line
	1600 3150 1400 3150
Wire Wire Line
	1400 3150 1400 3050
Connection ~ 1600 3150
Wire Wire Line
	3000 2850 2900 2850
Text GLabel 2800 2550 2    60   Output ~ 0
VOLTAGE
Text GLabel 3000 2850 2    60   Input ~ 0
DISCHARGE
$Comp
L R R3
U 1 1 4FD62EDD
P 2650 2850
F 0 "R3" V 2750 2850 50  0000 C CNN
F 1 "270R" V 2550 2850 50  0000 C CNN
	1    2650 2850
	0    1    1    0   
$EndComp
$Comp
L C CX1
U 1 1 4FD62EC0
P 1400 2850
F 0 "CX1" H 1250 2950 50  0000 L CNN
F 1 "CX" H 1250 2950 50  0000 L CNN
	1    1400 2850
	1    0    0    -1  
$EndComp
Text GLabel 2800 2250 2    60   Input ~ 0
CHARGE
$Comp
L +5V #PWR?
U 1 1 4FD62E37
P 2100 1350
AR Path="/4FD62E30" Ref="#PWR?"  Part="1" 
AR Path="/4FD62E37" Ref="#PWR2"  Part="1" 
F 0 "#PWR2" H 2100 1440 20  0001 C CNN
F 1 "+5V" H 2100 1440 30  0000 C CNN
	1    2100 1350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 4FD62E30
P 1700 1350
F 0 "#PWR1" H 1700 1440 20  0001 C CNN
F 1 "+5V" H 1700 1440 30  0000 C CNN
	1    1700 1350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 4FD62E26
P 1700 3250
F 0 "#PWR3" H 1700 3250 30  0001 C CNN
F 1 "GND" H 1700 3180 30  0001 C CNN
	1    1700 3250
	1    0    0    -1  
$EndComp
$Comp
L MOSFET_N Q2
U 1 1 4FD62E03
P 2100 2850
F 0 "Q2" H 2050 3000 60  0000 R CNN
F 1 "MOSFET_N" H 2150 2650 60  0000 R CNN
	1    2100 2850
	-1   0    0    -1  
$EndComp
$Comp
L PNP Q1
U 1 1 4FD62DD4
P 1800 2250
F 0 "Q1" H 1800 2100 60  0000 R CNN
F 1 "PNP" H 1800 2400 60  0000 R CNN
	1    1800 2250
	-1   0    0    1   
$EndComp
$Comp
L DIODE D?
U 1 1 4FD62DC4
P 1800 2850
AR Path="/4FD62DBC" Ref="D?"  Part="1" 
AR Path="/4FD62DC4" Ref="D2"  Part="1" 
F 0 "D2" V 1700 2900 40  0000 C CNN
F 1 "1N4001" H 1800 2750 40  0000 C CNN
	1    1800 2850
	0    1    1    0   
$EndComp
$Comp
L DIODE D1
U 1 1 4FD62DBC
P 1600 2850
F 0 "D1" V 1700 2900 40  0000 C CNN
F 1 "1N4001" H 1600 2750 40  0000 C CNN
	1    1600 2850
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 4FD62D8C
P 1700 1700
F 0 "R1" H 1800 1650 50  0000 C CNN
F 1 "680R" H 1850 1750 50  0000 C CNN
	1    1700 1700
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4FD62D83
P 2450 2250
F 0 "R2" V 2550 2250 50  0000 C CNN
F 1 "10k" V 2350 2250 50  0000 C CNN
	1    2450 2250
	0    1    1    0   
$EndComp
$Comp
L LED D3
U 1 1 4FD62D6D
P 2100 1700
F 0 "D3" V 2150 1850 50  0000 C CNN
F 1 "LED" V 2050 1850 50  0000 C CNN
	1    2100 1700
	0    1    1    0   
$EndComp
$EndSCHEMATC
