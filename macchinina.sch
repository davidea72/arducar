EESchema Schematic File Version 4
LIBS:macchinina-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5E347C27
P 5750 3250
F 0 "A1" H 5750 2164 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 5750 2073 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5900 2300 50  0001 L CNN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 5750 2250 50  0001 C CNN
	1    5750 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J4
U 1 1 5E34804B
P 7650 3050
F 0 "J4" H 7756 3528 50  0000 C CNN
F 1 "GY-521" H 7756 3437 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 7650 3050 50  0001 C CNN
F 3 "~" H 7650 3050 50  0001 C CNN
	1    7650 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 5E348110
P 3550 3050
F 0 "J1" H 3656 3428 50  0000 C CNN
F 1 "L298N" H 3656 3337 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 3550 3050 50  0001 C CNN
F 3 "~" H 3550 3050 50  0001 C CNN
	1    3550 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5E348214
P 4550 2200
F 0 "J2" H 4656 2478 50  0000 C CNN
F 1 "HC-06" H 4656 2387 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4550 2200 50  0001 C CNN
F 3 "~" H 4550 2200 50  0001 C CNN
	1    4550 2200
	1    0    0    -1  
$EndComp
Text Label 8150 2750 0    50   ~ 0
VCC
Text Label 8150 2850 0    50   ~ 0
GND
Text Label 8150 2950 0    50   ~ 0
SCL
Text Label 8150 3050 0    50   ~ 0
SDA
Text Label 8150 3150 0    50   ~ 0
XDA
Text Label 8150 3250 0    50   ~ 0
XCL
Text Label 8150 3350 0    50   ~ 0
ADO
Text Label 8150 3450 0    50   ~ 0
INT
Text Label 3950 2850 0    50   ~ 0
EN1
Text Label 3950 2950 0    50   ~ 0
IN1
Text Label 3950 3050 0    50   ~ 0
IN2
Text Label 3950 3150 0    50   ~ 0
IN3
Text Label 3950 3250 0    50   ~ 0
IN4
Text Label 3950 3350 0    50   ~ 0
EN0
Text Label 4950 2100 0    50   ~ 0
+5V
Text Label 4950 2200 0    50   ~ 0
GND
Text Label 4950 2300 0    50   ~ 0
TX
Text Label 4950 2400 0    50   ~ 0
RX
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 5E348846
P 7450 2000
F 0 "J3" H 7556 2278 50  0000 C CNN
F 1 "ALIM" H 7556 2187 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7450 2000 50  0001 C CNN
F 3 "~" H 7450 2000 50  0001 C CNN
	1    7450 2000
	1    0    0    -1  
$EndComp
Text Label 7800 2200 0    50   ~ 0
+5V
Text Label 7800 2100 0    50   ~ 0
VBATT
Text Label 7800 2000 0    50   ~ 0
GND
Wire Wire Line
	7650 2000 7700 2000
Wire Wire Line
	7700 2000 7700 1650
Wire Wire Line
	7700 1650 7250 1650
Wire Wire Line
	5250 1650 5250 2200
Wire Wire Line
	5250 2200 4750 2200
Wire Wire Line
	7700 2000 8500 2000
Wire Wire Line
	8500 2000 8500 2850
Wire Wire Line
	8500 2850 7850 2850
Connection ~ 7700 2000
Wire Wire Line
	4750 2300 5100 2300
Wire Wire Line
	5100 2300 5100 2650
Wire Wire Line
	5100 2650 5250 2650
Wire Wire Line
	4750 2400 4900 2400
Wire Wire Line
	4900 2400 4900 2750
Wire Wire Line
	4900 2750 5250 2750
Wire Wire Line
	5850 2250 5850 2050
Wire Wire Line
	5850 2050 6900 2050
Wire Wire Line
	6900 2050 6900 2750
Wire Wire Line
	6900 2750 6950 2750
Wire Wire Line
	5950 2200 5950 2250
Wire Wire Line
	7150 2200 7150 1750
Wire Wire Line
	7150 1750 5550 1750
Wire Wire Line
	5550 1750 5550 2100
Wire Wire Line
	5550 2100 4750 2100
Wire Wire Line
	5950 2200 7150 2200
Connection ~ 7150 2200
Wire Wire Line
	7150 2200 7650 2200
Wire Wire Line
	6250 3650 7250 3650
Wire Wire Line
	8050 3650 8050 3050
Wire Wire Line
	8050 3050 7850 3050
Wire Wire Line
	7850 2950 7950 2950
Wire Wire Line
	7950 2950 7950 3750
Wire Wire Line
	7850 3450 7850 4500
Wire Wire Line
	7850 4500 4700 4500
Wire Wire Line
	4700 4500 4700 2850
Wire Wire Line
	4700 2850 5250 2850
Wire Wire Line
	5750 4250 5850 4250
Wire Wire Line
	5850 4250 8500 4250
Wire Wire Line
	8500 4250 8500 2850
Connection ~ 5850 4250
Connection ~ 8500 2850
$Comp
L Device:R R3
U 1 1 5E34AA0C
P 7250 3200
F 0 "R3" H 7320 3246 50  0000 L CNN
F 1 "R" H 7320 3155 50  0000 L CNN
F 2 "Resistor_THT:R_Bare_Metal_Element_L12.4mm_W4.8mm_P11.40mm" V 7180 3200 50  0001 C CNN
F 3 "~" H 7250 3200 50  0001 C CNN
	1    7250 3200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5E34AA6E
P 6950 3200
F 0 "R1" H 7020 3246 50  0000 L CNN
F 1 "R" H 7020 3155 50  0000 L CNN
F 2 "Resistor_THT:R_Bare_Metal_Element_L12.4mm_W4.8mm_P11.40mm" V 6880 3200 50  0001 C CNN
F 3 "~" H 6950 3200 50  0001 C CNN
	1    6950 3200
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 3050 6950 3050
Connection ~ 6950 2750
Wire Wire Line
	6950 2750 7850 2750
$Comp
L Device:R R4
U 1 1 5E34E21E
P 7500 2350
F 0 "R4" V 7293 2350 50  0000 C CNN
F 1 "R" V 7384 2350 50  0000 C CNN
F 2 "Resistor_THT:R_Bare_Metal_Element_L12.4mm_W4.8mm_P11.40mm" V 7430 2350 50  0001 C CNN
F 3 "~" H 7500 2350 50  0001 C CNN
	1    7500 2350
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5E34E27D
P 7250 1950
F 0 "R2" H 7320 1996 50  0000 L CNN
F 1 "R" H 7320 1905 50  0000 L CNN
F 2 "Resistor_THT:R_Bare_Metal_Element_L12.4mm_W4.8mm_P11.40mm" V 7180 1950 50  0001 C CNN
F 3 "~" H 7250 1950 50  0001 C CNN
	1    7250 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2100 7750 2100
Wire Wire Line
	7750 2100 7750 2350
Wire Wire Line
	7750 2350 7650 2350
Wire Wire Line
	7350 2350 7250 2350
Wire Wire Line
	7250 2350 7250 2100
Wire Wire Line
	7250 1800 7250 1650
Connection ~ 7250 1650
Wire Wire Line
	7250 1650 5250 1650
Wire Wire Line
	7250 2350 6650 2350
Wire Wire Line
	6650 2350 6650 3250
Wire Wire Line
	6650 3250 6250 3250
Connection ~ 7250 2350
Text Label 6350 3200 0    50   ~ 0
Vbatt
Wire Wire Line
	6950 2750 6950 3050
Connection ~ 6950 3050
Wire Wire Line
	7250 3350 7250 3650
Connection ~ 7250 3650
Wire Wire Line
	7250 3650 8050 3650
Wire Wire Line
	6950 3350 6950 3750
Wire Wire Line
	6250 3750 6950 3750
Connection ~ 6950 3750
Wire Wire Line
	6950 3750 7950 3750
Wire Wire Line
	5250 3250 4450 3250
Wire Wire Line
	4450 3250 4450 3350
Wire Wire Line
	4450 3350 3750 3350
Wire Wire Line
	5250 2950 4550 2950
Wire Wire Line
	4550 2950 4550 2850
Wire Wire Line
	4550 2850 3750 2850
Text Label 4350 2800 0    50   ~ 0
PWM
Text Label 4300 3450 0    50   ~ 0
PWM
Wire Wire Line
	4250 3850 4250 3250
Wire Wire Line
	4250 3250 3750 3250
Wire Wire Line
	4250 3850 5250 3850
Wire Wire Line
	4350 3750 4350 3150
Wire Wire Line
	4350 3150 3750 3150
Wire Wire Line
	4350 3750 5250 3750
Wire Wire Line
	4850 3650 4850 3100
Wire Wire Line
	4850 3100 4450 3100
Wire Wire Line
	4450 3100 4450 3050
Wire Wire Line
	4450 3050 3750 3050
Wire Wire Line
	4850 3650 5250 3650
Wire Wire Line
	5250 3550 4950 3550
Wire Wire Line
	4950 3550 4950 3000
Wire Wire Line
	4950 3000 4250 3000
Wire Wire Line
	4250 3000 4250 2950
Wire Wire Line
	4250 2950 3750 2950
NoConn ~ 5250 3050
NoConn ~ 5250 3150
NoConn ~ 5250 3350
NoConn ~ 5250 3450
NoConn ~ 5250 3950
NoConn ~ 6250 3950
NoConn ~ 6250 3850
NoConn ~ 6250 3550
NoConn ~ 6250 3450
NoConn ~ 6250 3350
NoConn ~ 6250 2750
NoConn ~ 6250 2650
NoConn ~ 5650 2250
NoConn ~ 7650 1900
NoConn ~ 7850 3150
NoConn ~ 7850 3250
NoConn ~ 7850 3350
NoConn ~ 6250 3050
$EndSCHEMATC
