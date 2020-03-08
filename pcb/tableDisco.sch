EESchema Schematic File Version 4
EELAYER 30 0
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
L MCU_Module:WeMos_D1_mini U1
U 1 1 5E63D8B8
P 2250 2100
F 0 "U1" H 2250 1211 50  0000 C CNN
F 1 "WeMos_D1_mini" H 2250 1120 50  0000 C CNN
F 2 "Module:WEMOS_D1_mini_light" H 2250 950 50  0001 C CNN
F 3 "https://wiki.wemos.cc/products:d1:d1_mini#documentation" H 400 950 50  0001 C CNN
	1    2250 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 5E64B664
P 3450 2950
F 0 "J5" H 3530 2942 50  0000 L CNN
F 1 "Power Connection" H 3530 2851 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x02_P3.81mm_Drill0.8mm" H 3450 2950 50  0001 C CNN
F 3 "~" H 3450 2950 50  0001 C CNN
	1    3450 2950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 5E64FB5C
P 3450 1500
F 0 "J3" H 3530 1492 50  0000 L CNN
F 1 "Mode Switch" H 3530 1401 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x02_P3.81mm_Drill0.8mm" H 3450 1500 50  0001 C CNN
F 3 "~" H 3450 1500 50  0001 C CNN
	1    3450 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5E650CB8
P 3100 1900
F 0 "R1" V 3307 1900 50  0000 C CNN
F 1 "R" V 3216 1900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3030 1900 50  0001 C CNN
F 3 "~" H 3100 1900 50  0001 C CNN
	1    3100 1900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2250 2900 2250 3350
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5E641D60
P 3450 2400
F 0 "J2" H 3530 2442 50  0000 L CNN
F 1 "LED Connection" H 3530 2351 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x03_P3.81mm_Drill1.2mm" H 3450 2400 50  0001 C CNN
F 3 "~" H 3450 2400 50  0001 C CNN
	1    3450 2400
	1    0    0    -1  
$EndComp
Text Label 2250 3350 0    50   ~ 0
Ground
Text Label 3000 3050 0    50   ~ 0
Ground
Wire Wire Line
	3000 3050 3250 3050
Wire Wire Line
	2650 1900 2950 1900
Wire Wire Line
	2950 1900 2950 1600
Wire Wire Line
	2950 1600 3250 1600
Connection ~ 2950 1900
Wire Wire Line
	3250 1900 3450 1900
Wire Wire Line
	3450 1900 3450 2000
Wire Wire Line
	3250 1500 2950 1500
Wire Wire Line
	2950 1500 2950 1400
Text Label 3450 2000 0    50   ~ 0
Ground
Text Label 2950 1400 0    50   ~ 0
VCC
Wire Wire Line
	2350 1300 2350 1100
Text Label 2350 1100 0    50   ~ 0
VCC
Wire Wire Line
	3250 2300 3150 2300
Wire Wire Line
	3250 2500 3150 2500
Wire Wire Line
	2950 2400 2950 2000
Wire Wire Line
	2950 2000 2650 2000
Wire Wire Line
	2950 2400 3250 2400
Wire Wire Line
	3150 2300 3150 2150
Wire Wire Line
	3150 2500 3150 2650
Text Label 3150 2150 0    50   ~ 0
VCC
Text Label 3150 2650 0    50   ~ 0
Ground
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5E640D45
P 3450 950
F 0 "J1" H 3530 992 50  0000 L CNN
F 1 "Mic Connection" H 3530 901 50  0000 L CNN
F 2 "Connector_Wire:SolderWirePad_1x03_P3.81mm_Drill1.2mm" H 3450 950 50  0001 C CNN
F 3 "~" H 3450 950 50  0001 C CNN
	1    3450 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5E65FE79
P 4350 950
F 0 "C1" H 4468 996 50  0000 L CNN
F 1 "CP470uF" H 4468 905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 4388 800 50  0001 C CNN
F 3 "~" H 4350 950 50  0001 C CNN
	1    4350 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 1050 3250 1150
Wire Wire Line
	3250 1150 4350 1150
Wire Wire Line
	4350 1150 4350 1100
Wire Wire Line
	4350 1150 4350 1250
Connection ~ 4350 1150
Wire Wire Line
	3250 850  3250 750 
Wire Wire Line
	3250 750  4350 750 
Connection ~ 4350 750 
Wire Wire Line
	4350 750  4350 800 
Wire Wire Line
	4350 650  4350 750 
Text Label 4350 650  0    50   ~ 0
VCC
Text Label 4350 1250 0    50   ~ 0
Ground
Wire Wire Line
	3250 950  2650 950 
Wire Wire Line
	2650 950  2650 1600
Wire Wire Line
	3250 2950 3000 2950
Text Label 3000 2950 0    50   ~ 0
VCC
$EndSCHEMATC
