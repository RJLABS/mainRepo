EESchema Schematic File Version 4
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
L Device:R_US R1
U 1 1 5B98E722
P 6400 2700
F 0 "R1" H 6468 2746 50  0000 L CNN
F 1 "R_US" H 6468 2655 50  0000 L CNN
F 2 "Resistor_SMD:R_1812_4532Metric_Pad1.30x3.40mm_HandSolder" V 6440 2690 50  0001 C CNN
F 3 "~" H 6400 2700 50  0001 C CNN
	1    6400 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5B98E782
P 6600 2700
F 0 "R2" H 6668 2746 50  0000 L CNN
F 1 "R_US" H 6668 2655 50  0000 L CNN
F 2 "Resistor_SMD:R_2010_5025Metric_Pad1.52x2.65mm_HandSolder" V 6640 2690 50  0001 C CNN
F 3 "~" H 6600 2700 50  0001 C CNN
	1    6600 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_Dual_ACA D1
U 1 1 5B98E834
P 6500 3300
F 0 "D1" V 6546 3090 50  0000 R CNN
F 1 "LED_Dual_ACA" V 6455 3090 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6500 3300 50  0001 C CNN
F 3 "~" H 6500 3300 50  0001 C CNN
	1    6500 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6600 3000 6600 2850
Wire Wire Line
	6400 3000 6400 2850
Wire Wire Line
	6600 2550 6600 2400
Wire Wire Line
	6400 2550 6400 2300
Wire Wire Line
	6400 2300 7500 2300
Wire Wire Line
	6600 2400 7200 2400
NoConn ~ 7500 2500
NoConn ~ 7500 2600
$Comp
L Connector:Conn_01x04_Female J1
U 1 1 5B98EBEF
P 7700 2400
F 0 "J1" H 7727 2376 50  0000 L CNN
F 1 "Conn_01x04_Female" H 7727 2285 50  0000 L CNN
F 2 "Connector_Phoenix_GMSTB:PhoenixContact_GMSTBA_2,5_2-G-7,62_1x02_P7.62mm_Horizontal" H 7700 2400 50  0001 C CNN
F 3 "~" H 7700 2400 50  0001 C CNN
	1    7700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3700 7200 2400
Connection ~ 7200 2400
Wire Wire Line
	7200 2400 7500 2400
Wire Wire Line
	6500 3600 6500 3700
Wire Wire Line
	6500 3700 7200 3700
$EndSCHEMATC
