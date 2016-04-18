EESchema Schematic File Version 2
LIBS:Antennas_kl
LIBS:Connectors_kl
LIBS:pcb_details
LIBS:power
LIBS:Power_kl
LIBS:RF ICs
LIBS:st_kl
LIBS:Switches
LIBS:Tittar_kl
LIBS:Transistors_kl
LIBS:GunRadio-cache
EELAYER 25 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Generation Head"
Date "18 apr 2016"
Rev "20160401"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L GND #PWR01
U 1 1 55180E91
P 9050 8250
F 0 "#PWR01" H 9140 8230 30  0001 C CNN
F 1 "GND" H 9050 8170 30  0001 C CNN
F 2 "" H 9050 8250 60  0001 C CNN
F 3 "" H 9050 8250 60  0001 C CNN
	1    9050 8250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 55180E97
P 8800 8250
F 0 "#PWR02" H 8890 8230 30  0001 C CNN
F 1 "GND" H 8800 8170 30  0001 C CNN
F 2 "" H 8800 8250 60  0001 C CNN
F 3 "" H 8800 8250 60  0001 C CNN
	1    8800 8250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 55180E9D
P 8500 8250
F 0 "#PWR03" H 8590 8230 30  0001 C CNN
F 1 "GND" H 8500 8170 30  0001 C CNN
F 2 "" H 8500 8250 60  0001 C CNN
F 3 "" H 8500 8250 60  0001 C CNN
	1    8500 8250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 55180EA3
P 7900 8250
F 0 "#PWR04" H 7990 8230 30  0001 C CNN
F 1 "GND" H 7900 8170 30  0001 C CNN
F 2 "" H 7900 8250 60  0001 C CNN
F 3 "" H 7900 8250 60  0001 C CNN
	1    7900 8250
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 55180EBB
P 7900 7950
F 0 "C8" H 7800 7850 50  0000 L CNN
F 1 "0.1u" H 7800 8050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 8000 7800 28  0001 C BNN
F 3 "" H 7900 7950 60  0001 C CNN
	1    7900 7950
	1    0    0    -1  
$EndComp
$Comp
L C C12
U 1 1 55180EC2
P 8500 7950
F 0 "C12" H 8400 7850 50  0000 L CNN
F 1 "0.1u" H 8400 8050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 8600 7800 28  0001 C BNN
F 3 "" H 8500 7950 60  0001 C CNN
	1    8500 7950
	1    0    0    -1  
$EndComp
$Comp
L C C16
U 1 1 55180EC9
P 9050 7950
F 0 "C16" H 8950 7850 50  0000 L CNN
F 1 "1u" H 8950 8050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 9150 7800 28  0001 C BNN
F 3 "" H 9050 7950 60  0001 C CNN
	1    9050 7950
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 55180ED0
P 8800 7950
F 0 "C14" H 8700 7850 50  0000 L CNN
F 1 "10n" H 8700 8050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 8900 7800 28  0001 C BNN
F 3 "" H 8800 7950 60  0001 C CNN
	1    8800 7950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 55180ED7
P 7600 8250
F 0 "#PWR05" H 7690 8230 30  0001 C CNN
F 1 "GND" H 7600 8170 30  0001 C CNN
F 2 "" H 7600 8250 60  0001 C CNN
F 3 "" H 7600 8250 60  0001 C CNN
	1    7600 8250
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 55180EDD
P 7600 7950
F 0 "C6" H 7500 7850 50  0000 L CNN
F 1 "4.7u" H 7500 8050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 7700 7800 28  0001 C BNN
F 3 "" H 7600 7950 60  0001 C CNN
	1    7600 7950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 55180EE4
P 8200 8250
F 0 "#PWR06" H 8290 8230 30  0001 C CNN
F 1 "GND" H 8200 8170 30  0001 C CNN
F 2 "" H 8200 8250 60  0001 C CNN
F 3 "" H 8200 8250 60  0001 C CNN
	1    8200 8250
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 55180EEA
P 8200 7950
F 0 "C10" H 8100 7850 50  0000 L CNN
F 1 "0.1u" H 8100 8050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 8300 7800 28  0001 C BNN
F 3 "" H 8200 7950 60  0001 C CNN
	1    8200 7950
	1    0    0    -1  
$EndComp
Text Notes 11500 2100 0    60   ~ 0
Radio
$Comp
L CRYSTAL_H XTAL2
U 1 1 5519A89A
P 9650 3850
F 0 "XTAL2" H 9600 4150 60  0000 C CNN
F 1 "27MHz" H 9650 4050 60  0000 C CNN
F 2 "Quartz:03225C4" H 9650 3950 39  0001 C CNN
F 3 "" H 9650 3850 60  0001 C CNN
F 4 "15" H 9650 3850 60  0001 C CNN "Price"
	1    9650 3850
	1    0    0    -1  
$EndComp
$Comp
L C C18
U 1 1 5519A8A1
P 9900 4100
F 0 "C18" H 9800 4000 50  0000 L CNN
F 1 "18pF" H 9800 4200 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 10000 3950 28  0001 C BNN
F 3 "" H 9900 4100 60  0001 C CNN
	1    9900 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 5519A8A8
P 9900 4400
F 0 "#PWR07" H 9990 4380 30  0001 C CNN
F 1 "GND" H 9900 4320 30  0001 C CNN
F 2 "" H 9900 4400 60  0001 C CNN
F 3 "" H 9900 4400 60  0001 C CNN
	1    9900 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 5519A8AE
P 9400 4400
F 0 "#PWR08" H 9490 4380 30  0001 C CNN
F 1 "GND" H 9400 4320 30  0001 C CNN
F 2 "" H 9400 4400 60  0001 C CNN
F 3 "" H 9400 4400 60  0001 C CNN
	1    9400 4400
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 5519A8B4
P 9400 4100
F 0 "C17" H 9300 4000 50  0000 L CNN
F 1 "18pF" H 9300 4200 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 9500 3950 28  0001 C BNN
F 3 "" H 9400 4100 60  0001 C CNN
	1    9400 4100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 5519A8BB
P 9650 4400
F 0 "#PWR09" H 9740 4380 30  0001 C CNN
F 1 "GND" H 9650 4320 30  0001 C CNN
F 2 "" H 9650 4400 60  0001 C CNN
F 3 "" H 9650 4400 60  0001 C CNN
	1    9650 4400
	1    0    0    -1  
$EndComp
Text Label 10000 3200 0    60   ~ 0
CC_GDO2
Text Label 10000 3100 0    60   ~ 0
CC_GDO0
Text Label 10000 2900 0    60   ~ 0
CC_CS
Text Label 10000 2600 0    60   ~ 0
CC_SCK
Text Label 10000 2800 0    60   ~ 0
CC_MISO
Text Label 10000 2700 0    60   ~ 0
CC_MOSI
$Comp
L CC1101 DD2
U 1 1 5519A8EB
P 11250 3250
F 0 "DD2" H 10800 4050 60  0000 C CNN
F 1 "CC1101" H 11550 4050 60  0000 C CNN
F 2 "QFN_DFN:QFN20" H 11250 3250 60  0001 C CNN
F 3 "" H 11250 3250 60  0001 C CNN
F 4 "140" H 11250 3250 60  0001 C CNN "Price"
	1    11250 3250
	1    0    0    -1  
$EndComp
Text Label 11950 2800 0    60   ~ 0
RF2
Text Label 11950 2600 0    60   ~ 0
RF1
$Comp
L GND #PWR010
U 1 1 5519A8F4
P 9000 9600
F 0 "#PWR010" H 9090 9580 30  0001 C CNN
F 1 "GND" H 9000 9520 30  0001 C CNN
F 2 "" H 9000 9600 60  0001 C CNN
F 3 "" H 9000 9600 60  0001 C CNN
	1    9000 9600
	1    0    0    -1  
$EndComp
$Comp
L C C15
U 1 1 5519A8FA
P 9000 9300
F 0 "C15" H 8900 9400 50  0000 L CNN
F 1 "220pF" H 8900 9200 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 9000 9300 60  0001 C CNN
F 3 "" H 9000 9300 60  0001 C CNN
	1    9000 9300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 5519A901
P 8400 9600
F 0 "#PWR011" H 8490 9580 30  0001 C CNN
F 1 "GND" H 8400 9520 30  0001 C CNN
F 2 "" H 8400 9600 60  0001 C CNN
F 3 "" H 8400 9600 60  0001 C CNN
	1    8400 9600
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 5519A907
P 8400 9300
F 0 "C11" H 8300 9400 50  0000 L CNN
F 1 "10n" H 8300 9150 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 8400 9300 60  0001 C CNN
F 3 "" H 8400 9300 60  0001 C CNN
	1    8400 9300
	1    0    0    -1  
$EndComp
$Comp
L C C13
U 1 1 5519A90E
P 8700 9300
F 0 "C13" H 8600 9400 50  0000 L CNN
F 1 "0.1u" H 8600 9200 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 8700 9300 60  0001 C CNN
F 3 "" H 8700 9300 60  0001 C CNN
	1    8700 9300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5519A915
P 8700 9600
F 0 "#PWR012" H 8790 9580 30  0001 C CNN
F 1 "GND" H 8700 9520 30  0001 C CNN
F 2 "" H 8700 9600 60  0001 C CNN
F 3 "" H 8700 9600 60  0001 C CNN
	1    8700 9600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5519A91B
P 8100 9600
F 0 "#PWR013" H 8190 9580 30  0001 C CNN
F 1 "GND" H 8100 9520 30  0001 C CNN
F 2 "" H 8100 9600 60  0001 C CNN
F 3 "" H 8100 9600 60  0001 C CNN
	1    8100 9600
	1    0    0    -1  
$EndComp
$Comp
L C C9
U 1 1 5519A921
P 8100 9300
F 0 "C9" H 8000 9400 50  0000 L CNN
F 1 "3.3pF" H 8000 9200 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 8100 9300 60  0001 C CNN
F 3 "" H 8100 9300 60  0001 C CNN
	1    8100 9300
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5519A928
P 7800 9300
F 0 "C7" H 7700 9400 50  0000 L CNN
F 1 "10n" H 7700 9150 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 7800 9300 60  0001 C CNN
F 3 "" H 7800 9300 60  0001 C CNN
	1    7800 9300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 5519A92F
P 7800 9600
F 0 "#PWR014" H 7890 9580 30  0001 C CNN
F 1 "GND" H 7800 9520 30  0001 C CNN
F 2 "" H 7800 9600 60  0001 C CNN
F 3 "" H 7800 9600 60  0001 C CNN
	1    7800 9600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 5519A935
P 7500 9600
F 0 "#PWR015" H 7590 9580 30  0001 C CNN
F 1 "GND" H 7500 9520 30  0001 C CNN
F 2 "" H 7500 9600 60  0001 C CNN
F 3 "" H 7500 9600 60  0001 C CNN
	1    7500 9600
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 5519A93B
P 7500 9300
F 0 "C5" H 7400 9400 50  0000 L CNN
F 1 "220pF" H 7400 9200 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 7500 9300 60  0001 C CNN
F 3 "" H 7500 9300 60  0001 C CNN
	1    7500 9300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 5519A942
P 11900 4000
F 0 "#PWR016" H 11990 3980 30  0001 C CNN
F 1 "GND" H 11900 3920 30  0001 C CNN
F 2 "" H 11900 4000 60  0001 C CNN
F 3 "" H 11900 4000 60  0001 C CNN
	1    11900 4000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 5519A956
P 11200 4400
F 0 "#PWR017" H 11290 4380 30  0001 C CNN
F 1 "GND" H 11200 4320 30  0001 C CNN
F 2 "" H 11200 4400 60  0001 C CNN
F 3 "" H 11200 4400 60  0001 C CNN
	1    11200 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 5519A95C
P 10200 4400
F 0 "#PWR018" H 10290 4380 30  0001 C CNN
F 1 "GND" H 10200 4320 30  0001 C CNN
F 2 "" H 10200 4400 60  0001 C CNN
F 3 "" H 10200 4400 60  0001 C CNN
	1    10200 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5519A962
P 10450 4400
F 0 "#PWR019" H 10540 4380 30  0001 C CNN
F 1 "GND" H 10450 4320 30  0001 C CNN
F 2 "" H 10450 4400 60  0001 C CNN
F 3 "" H 10450 4400 60  0001 C CNN
	1    10450 4400
	1    0    0    -1  
$EndComp
$Comp
L C C19
U 1 1 5519A968
P 10200 4100
F 0 "C19" H 10200 4200 50  0000 L CNN
F 1 "0.1u" H 10200 4000 50  0000 L CNN
F 2 "Capacitors:CAP_0603" H 10200 4100 60  0001 C CNN
F 3 "" H 10200 4100 60  0001 C CNN
	1    10200 4100
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5519A96F
P 10450 4100
F 0 "R4" V 10530 4100 50  0000 C CNN
F 1 "56k" V 10450 4100 50  0000 C CNN
F 2 "Resistors:RES_0603" H 10450 4100 60  0001 C CNN
F 3 "" H 10450 4100 60  0001 C CNN
	1    10450 4100
	1    0    0    -1  
$EndComp
$Comp
L C C20
U 1 1 5519A976
P 13350 3100
F 0 "C20" H 13400 3200 50  0000 L CNN
F 1 "*" H 13400 3000 50  0000 L CNN
F 2 "Capacitors:CAP_0402" H 13350 3100 60  0001 C CNN
F 3 "" H 13350 3100 60  0001 C CNN
	1    13350 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 5519A97D
P 13350 3350
F 0 "#PWR020" H 13440 3330 30  0001 C CNN
F 1 "GND" H 13350 3270 30  0001 C CNN
F 2 "" H 13350 3350 60  0001 C CNN
F 3 "" H 13350 3350 60  0001 C CNN
	1    13350 3350
	1    0    0    -1  
$EndComp
Text Notes 13350 2250 0    60   ~ 0
Matching circuit
$Comp
L GND #PWR021
U 1 1 5519A98B
P 12850 3150
F 0 "#PWR021" H 12940 3130 30  0001 C CNN
F 1 "GND" H 12850 3070 30  0001 C CNN
F 2 "" H 12850 3150 60  0001 C CNN
F 3 "" H 12850 3150 60  0001 C CNN
	1    12850 3150
	1    0    0    -1  
$EndComp
$Comp
L L L1
U 1 1 5519A991
P 13700 2600
F 0 "L1" V 13600 2460 40  0000 C CNN
F 1 "*" V 13600 2600 40  0000 C CNN
F 2 "Inductors:IND_0402" V 13760 2610 40  0000 C CNN
F 3 "~" H 13700 2600 60  0000 C CNN
	1    13700 2600
	0    1    1    0   
$EndComp
Text Label 6300 3750 0    60   ~ 0
SWCLK
Text Label 6300 3650 0    60   ~ 0
SWDIO
$Comp
L GND #PWR022
U 1 1 551AB282
P 4700 5200
F 0 "#PWR022" H 4790 5180 30  0001 C CNN
F 1 "GND" H 4700 5120 30  0001 C CNN
F 2 "" H 4700 5200 60  0001 C CNN
F 3 "" H 4700 5200 60  0001 C CNN
	1    4700 5200
	1    0    0    -1  
$EndComp
Text Label 6300 3250 0    60   ~ 0
UART_TX
Text Label 6200 2550 0    60   ~ 0
CC_GDO2
Text Label 6200 2650 0    60   ~ 0
CC_GDO0
Text Label 6200 2450 0    60   ~ 0
CC_CS
Text Label 6200 2850 0    60   ~ 0
CC_SCK
Text Label 6200 2950 0    60   ~ 0
CC_MISO
Text Label 6200 3050 0    60   ~ 0
CC_MOSI
Text Label 6300 3350 0    60   ~ 0
UART_RX
Text Label 13300 2600 0    60   ~ 0
ANT1
$Comp
L R R3
U 1 1 55207E31
P 9100 2750
F 0 "R3" V 9050 2500 50  0000 C CNN
F 1 "20k" V 9100 2750 50  0000 C CNN
F 2 "Resistors:RES_0603" V 9000 2750 28  0001 C CNN
F 3 "" H 9100 2750 60  0000 C CNN
	1    9100 2750
	0    1    -1   0   
$EndComp
Entry Wire Line
	6900 2550 7000 2650
Entry Wire Line
	6900 2650 7000 2750
Entry Wire Line
	6900 2450 7000 2550
Entry Wire Line
	6900 2850 7000 2950
Entry Wire Line
	6900 2950 7000 3050
Entry Wire Line
	6900 3050 7000 3150
Entry Wire Line
	9850 2500 9950 2600
Entry Wire Line
	9850 2600 9950 2700
Entry Wire Line
	9850 2700 9950 2800
Entry Wire Line
	9850 2800 9950 2900
Entry Wire Line
	9850 3000 9950 3100
Entry Wire Line
	9850 3100 9950 3200
Entry Wire Line
	9750 2950 9850 3050
Entry Wire Line
	9750 3050 9850 3150
Text Label 9250 3050 0    60   ~ 0
CC_GDO2
Text Label 9250 2950 0    60   ~ 0
CC_GDO0
$Comp
L C C21
U 1 1 552947E8
P 14050 3100
F 0 "C21" H 14100 3200 50  0000 L CNN
F 1 "*" H 14100 3000 50  0000 L CNN
F 2 "Capacitors:CAP_0402" H 14050 3100 60  0001 C CNN
F 3 "" H 14050 3100 60  0001 C CNN
	1    14050 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 552947EE
P 14050 3350
F 0 "#PWR023" H 14140 3330 30  0001 C CNN
F 1 "GND" H 14050 3270 30  0001 C CNN
F 2 "" H 14050 3350 60  0001 C CNN
F 3 "" H 14050 3350 60  0001 C CNN
	1    14050 3350
	1    0    0    -1  
$EndComp
Text Notes 12550 2200 0    60   ~ 0
Balun
Text Label 14100 2600 0    60   ~ 0
ANT2
Text Notes 7750 7350 0    60   ~ 0
MCU Power Filter
Text Notes 7500 7500 0    60   ~ 0
Pins   24,    36,   48,     1+9
Text Notes 7600 8700 0    60   ~ 0
CC Power Filter
Text Notes 7150 8850 0    60   ~ 0
Pins  15,   14,    11,    9,     4,    18
Text Label 9700 2750 2    60   ~ 0
CC_CS
Entry Wire Line
	9850 2850 9750 2750
Text Notes 8950 2650 0    60   ~ 0
Keep CS High\nwhen sleeping
$Comp
L ANT_PCB_MONO ANT1
U 1 1 569A2ECB
P 14650 2600
F 0 "ANT1" H 14450 2850 60  0000 C CNN
F 1 "ANT_PCB_MONO" H 14700 2750 60  0000 C CNN
F 2 "Radio:ANT_868_MEANDER_4HOR_35mm" H 14650 2600 60  0001 C CNN
F 3 "" H 14650 2600 60  0000 C CNN
F 4 "0" H 14650 2600 60  0001 C CNN "Price"
	1    14650 2600
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR025
U 1 1 56F54380
P 7300 7650
F 0 "#PWR025" H 7300 7610 30  0001 C CNN
F 1 "+3.3V" H 7380 7680 30  0000 C CNN
F 2 "" H 7300 7650 60  0000 C CNN
F 3 "" H 7300 7650 60  0000 C CNN
	1    7300 7650
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR026
U 1 1 56F54464
P 7000 9000
F 0 "#PWR026" H 7000 8960 30  0001 C CNN
F 1 "+3.3V" H 7080 9030 30  0000 C CNN
F 2 "" H 7000 9000 60  0000 C CNN
F 3 "" H 7000 9000 60  0000 C CNN
	1    7000 9000
	-1   0    0    -1  
$EndComp
Text Notes 3350 6650 0    60   ~ 0
Power
$Comp
L STM32L151CxTx DD1
U 1 1 56F9A59B
P 4750 3550
F 0 "DD1" H 4250 4900 60  0000 C CNN
F 1 "STM32L151C8T6" H 4900 4900 60  0000 C CNN
F 2 "LQFP_TQFP:LQFP48" H 4750 3550 60  0001 C CNN
F 3 "" H 4750 3550 60  0000 C CNN
F 4 "http://onelec.ru/products/stm32l151cbt6a-33e1fab7-da8a-4e30-8f35-29930f502330" H 4750 3550 60  0001 C CNN "URL"
	1    4750 3550
	1    0    0    -1  
$EndComp
Text Notes 7850 7100 0    60   ~ 0
Power Filters
$Comp
L R R2
U 1 1 56FADB37
P 6750 4350
F 0 "R2" V 6830 4200 50  0000 C CNN
F 1 "220R" V 6750 4350 50  0000 C CNN
F 2 "Resistors:RES_0603" V 6830 4450 28  0001 C CNN
F 3 "" H 6750 4350 60  0001 C CNN
	1    6750 4350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR027
U 1 1 56FADB3E
P 7000 5200
F 0 "#PWR027" H 7090 5180 30  0001 C CNN
F 1 "GND" H 7000 5120 30  0001 C CNN
F 2 "" H 7000 5200 60  0001 C CNN
F 3 "" H 7000 5200 60  0001 C CNN
	1    7000 5200
	-1   0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 56FADB44
P 7250 4950
F 0 "C4" H 7150 4850 50  0000 L CNN
F 1 "20pF" H 7150 5050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 7350 4800 28  0001 C BNN
F 3 "" H 7250 4950 60  0001 C CNN
	1    7250 4950
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 56FADB4B
P 7250 5200
F 0 "#PWR028" H 7340 5180 30  0001 C CNN
F 1 "GND" H 7250 5120 30  0001 C CNN
F 2 "" H 7250 5200 60  0001 C CNN
F 3 "" H 7250 5200 60  0001 C CNN
	1    7250 5200
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 56FADB51
P 6750 5200
F 0 "#PWR029" H 6840 5180 30  0001 C CNN
F 1 "GND" H 6750 5120 30  0001 C CNN
F 2 "" H 6750 5200 60  0001 C CNN
F 3 "" H 6750 5200 60  0001 C CNN
	1    6750 5200
	-1   0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 56FADB57
P 6750 4950
F 0 "C3" H 6650 4850 50  0000 L CNN
F 1 "20pF" H 6650 5050 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 6850 4800 28  0001 C BNN
F 3 "" H 6750 4950 60  0001 C CNN
	1    6750 4950
	-1   0    0    -1  
$EndComp
$Comp
L CRYSTAL_H XTAL1
U 1 1 56FADB5E
P 7000 4700
F 0 "XTAL1" H 6400 4650 60  0000 C CNN
F 1 "12.0MHz" H 6350 4550 60  0000 C CNN
F 2 "Quartz:0503x4-4" H 7150 4750 39  0001 C CNN
F 3 "" H 7000 4700 60  0001 C CNN
F 4 "http://www.quartz1.com/price/model.php?akt=2214.09" H 7000 4700 60  0001 C CNN "URL"
F 5 "15" H 7000 4700 60  0001 C CNN "Price"
	1    7000 4700
	1    0    0    -1  
$EndComp
$Comp
L BALUN868ST BLN1
U 1 1 56F89154
P 12650 2700
F 0 "BLN1" H 12300 3050 60  0000 C CNN
F 1 "BALUN868ST" H 12650 2950 60  0000 C CNN
F 2 "Radio:BALUN868_ST" H 12200 2950 60  0001 C CNN
F 3 "" H 12300 3050 60  0000 C CNN
F 4 "BAL-CC1101-01D3" H 12400 3150 60  0001 C CNN "PN"
F 5 "https://www.terraelectronica.ru/catalog.php?ID=1469&search=balcc110101d3" H 12500 3250 60  0001 C CNN "URL"
F 6 "31" H 12650 2700 60  0001 C CNN "Price"
	1    12650 2700
	1    0    0    -1  
$EndComp
NoConn ~ 6100 3850
NoConn ~ 6100 4250
NoConn ~ 6100 4350
NoConn ~ 6100 4450
Text Notes 1850 3150 0    60   ~ 0
Just pins
NoConn ~ 3450 2850
$Comp
L GND #PWR030
U 1 1 5704284A
P 3400 9400
F 0 "#PWR030" H 3490 9380 30  0001 C CNN
F 1 "GND" H 3400 9320 30  0001 C CNN
F 2 "" H 3400 9400 60  0001 C CNN
F 3 "" H 3400 9400 60  0001 C CNN
	1    3400 9400
	0    1    -1   0   
$EndComp
$Comp
L +5V #PWR031
U 1 1 57042995
P 3400 9300
F 0 "#PWR031" H 3400 9260 30  0001 C CNN
F 1 "+5V" H 3480 9330 30  0000 C CNN
F 2 "" H 3400 9300 60  0000 C CNN
F 3 "" H 3400 9300 60  0000 C CNN
	1    3400 9300
	1    0    0    -1  
$EndComp
Text Notes 2950 9100 0    60   ~ 0
Power connector
$Comp
L CONN_2 XL3
U 1 1 5711F8EB
P 6600 1650
F 0 "XL3" V 6550 1650 40  0000 C CNN
F 1 "CONN_2" V 6650 1650 40  0000 C CNN
F 2 "Connectors:PLS-2" H 6600 1650 60  0001 C CNN
F 3 "" H 6600 1650 60  0001 C CNN
F 4 "0" V 6600 1650 60  0001 C CNN "Price"
F 5 "0" V 6600 1650 60  0001 C CNN "SolderPointsDIP"
	1    6600 1650
	0    -1   -1   0   
$EndComp
$Comp
L TESTPOINT TP1
U 1 1 570F1026
P 3350 4050
F 0 "TP1" H 3125 4050 60  0000 C CNN
F 1 "TESTPOINT" H 3325 4275 60  0001 C CNN
F 2 "PCB:TESTPOINT_1MM" H 3250 4100 60  0001 C CNN
F 3 "" H 3350 4200 60  0001 C CNN
F 4 "0" H 3450 4300 60  0001 C CNN "Price"
F 5 "0" H 3550 4400 60  0001 C CNN "SolderPoints"
	1    3350 4050
	1    0    0    -1  
$EndComp
$Comp
L TESTPOINT TP2
U 1 1 570FB316
P 9150 2950
F 0 "TP2" H 8925 2950 60  0000 C CNN
F 1 "TESTPOINT" H 9125 3175 60  0001 C CNN
F 2 "PCB:TESTPOINT_1MM" H 9050 3000 60  0001 C CNN
F 3 "" H 9150 3100 60  0001 C CNN
F 4 "0" H 9250 3200 60  0001 C CNN "Price"
F 5 "0" H 9350 3300 60  0001 C CNN "SolderPoints"
	1    9150 2950
	1    0    0    -1  
$EndComp
$Comp
L TESTPOINT TP3
U 1 1 570FB3FB
P 9200 3050
F 0 "TP3" H 8975 3050 60  0000 C CNN
F 1 "TESTPOINT" H 9175 3275 60  0001 C CNN
F 2 "PCB:TESTPOINT_1MM" H 9100 3100 60  0001 C CNN
F 3 "" H 9200 3200 60  0001 C CNN
F 4 "0" H 9300 3300 60  0001 C CNN "Price"
F 5 "0" H 9400 3400 60  0001 C CNN "SolderPoints"
	1    9200 3050
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR032
U 1 1 570FD5AD
P 3150 4700
F 0 "#PWR032" H 3150 4660 30  0001 C CNN
F 1 "+3.3V" H 3230 4730 30  0000 C CNN
F 2 "" H 3150 4700 60  0000 C CNN
F 3 "" H 3150 4700 60  0000 C CNN
	1    3150 4700
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR033
U 1 1 570FDFAF
P 7000 1850
F 0 "#PWR033" H 7000 1810 30  0001 C CNN
F 1 "+3.3V" H 7080 1880 30  0000 C CNN
F 2 "" H 7000 1850 60  0000 C CNN
F 3 "" H 7000 1850 60  0000 C CNN
	1    7000 1850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR034
U 1 1 570FE7C6
P 8800 2750
F 0 "#PWR034" H 8800 2710 30  0001 C CNN
F 1 "+3.3V" H 8880 2780 30  0000 C CNN
F 2 "" H 8800 2750 60  0000 C CNN
F 3 "" H 8800 2750 60  0000 C CNN
	1    8800 2750
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR035
U 1 1 570FECA9
P 12100 3500
F 0 "#PWR035" H 12100 3460 30  0001 C CNN
F 1 "+3.3V" H 12180 3530 30  0000 C CNN
F 2 "" H 12100 3500 60  0000 C CNN
F 3 "" H 12100 3500 60  0000 C CNN
	1    12100 3500
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 57102BD9
P 3100 2350
F 0 "R1" V 3180 2200 50  0000 C CNN
F 1 "100R" V 3100 2350 50  0000 C CNN
F 2 "Resistors:RES_0603" V 3180 2450 28  0001 C CNN
F 3 "" V 3180 2200 60  0000 C CNN
F 4 "0.5" V 3280 2300 60  0001 C CNN "Price"
F 5 "2" V 3380 2400 60  0001 C CNN "SolderPoints"
	1    3100 2350
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 57102F4D
P 2550 2350
F 0 "D1" H 2650 2490 50  0000 C CNN
F 1 "LED" H 2470 2490 50  0000 C CNN
F 2 "LEDs:LED_0603" H 2550 2390 60  0001 C CNN
F 3 "" H 2650 2490 60  0001 C CNN
F 4 "4" H 2750 2590 60  0001 C CNN "Price"
F 5 "2" H 2850 2690 60  0001 C CNN "SolderPoints"
	1    2550 2350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 57103126
P 2250 2350
F 0 "#PWR036" H 2340 2330 30  0001 C CNN
F 1 "GND" H 2250 2270 30  0001 C CNN
F 2 "" H 2250 2350 60  0000 C CNN
F 3 "" H 2250 2350 60  0000 C CNN
	1    2250 2350
	0    1    1    0   
$EndComp
NoConn ~ 3450 2450
NoConn ~ 3450 2550
NoConn ~ 3450 2650
NoConn ~ 3450 2750
NoConn ~ 3450 2950
NoConn ~ 3450 3050
NoConn ~ 3450 3150
NoConn ~ 3450 3250
NoConn ~ 6100 2750
NoConn ~ 6100 3450
NoConn ~ 6100 3550
$Comp
L NCP583SQ DA1
U 1 1 570EC396
P 3500 7450
F 0 "DA1" H 3350 7800 50  0000 C CNN
F 1 "NCP583SQ" H 3500 7700 50  0000 C CNN
F 2 "SOT:SC82AB" H 3250 7700 60  0001 C CNN
F 3 "" H 3350 7800 60  0001 C CNN
F 4 "4" H 3450 7900 60  0001 C CNN "SolderPoints"
F 5 "17,18rub" H 3550 8000 60  0001 C CNN "Price"
F 6 "https://www.terraelectronica.ru/catalog_info.php?CODE=363262" H 3650 8100 60  0001 C CNN "URL"
F 7 "NCP583SQ33T1G" H 3750 8200 60  0001 C CNN "PN"
	1    3500 7450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 570EC462
P 4050 7550
F 0 "#PWR037" H 4140 7530 30  0001 C CNN
F 1 "GND" H 4050 7470 30  0001 C CNN
F 2 "" H 4050 7550 60  0000 C CNN
F 3 "" H 4050 7550 60  0000 C CNN
	1    4050 7550
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 570EC614
P 4400 7550
F 0 "C2" H 4300 7450 50  0000 L CNN
F 1 "0.1u" H 4300 7650 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 4500 7400 28  0001 C BNN
F 3 "" H 4300 7450 60  0001 C CNN
F 4 "0.5" H 4400 7550 60  0001 C CNN "Price"
F 5 "2" H 4500 7650 60  0001 C CNN "SolderPoints"
	1    4400 7550
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR038
U 1 1 570EC708
P 4700 7350
F 0 "#PWR038" H 4700 7310 30  0001 C CNN
F 1 "+3.3V" H 4780 7380 30  0000 C CNN
F 2 "" H 4700 7350 60  0000 C CNN
F 3 "" H 4700 7350 60  0000 C CNN
	1    4700 7350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 570EC88F
P 4400 7900
F 0 "#PWR039" H 4490 7880 30  0001 C CNN
F 1 "GND" H 4400 7820 30  0001 C CNN
F 2 "" H 4400 7900 60  0000 C CNN
F 3 "" H 4400 7900 60  0000 C CNN
	1    4400 7900
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 570ECAAB
P 2650 7550
F 0 "C1" H 2550 7450 50  0000 L CNN
F 1 "1u" H 2550 7650 50  0000 L CNN
F 2 "Capacitors:CAP_0603" V 2750 7400 28  0001 C BNN
F 3 "" H 2550 7450 60  0001 C CNN
F 4 "0.5" H 2650 7550 60  0001 C CNN "Price"
F 5 "2" H 2750 7650 60  0001 C CNN "SolderPoints"
	1    2650 7550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR040
U 1 1 570ECB72
P 2650 7900
F 0 "#PWR040" H 2740 7880 30  0001 C CNN
F 1 "GND" H 2650 7820 30  0001 C CNN
F 2 "" H 2650 7900 60  0000 C CNN
F 3 "" H 2650 7900 60  0000 C CNN
	1    2650 7900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR041
U 1 1 570ED48A
P 2350 7350
F 0 "#PWR041" H 2350 7310 30  0001 C CNN
F 1 "+5V" H 2430 7380 30  0000 C CNN
F 2 "" H 2350 7350 60  0000 C CNN
F 3 "" H 2350 7350 60  0000 C CNN
	1    2350 7350
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR042
U 1 1 5714DC60
P 12150 8050
F 0 "#PWR042" H 12240 8030 30  0001 C CNN
F 1 "GND" H 12150 7970 30  0001 C CNN
F 2 "" H 12150 8050 60  0001 C CNN
F 3 "" H 12150 8050 60  0001 C CNN
	1    12150 8050
	0    1    1    0   
$EndComp
Text Label 11700 7950 0    60   ~ 0
SWCLK
Text Label 11700 8150 0    60   ~ 0
SWDIO
Text Label 11850 8250 0    60   ~ 0
UART_TX
Text Label 11850 8350 0    60   ~ 0
UART_RX
$Comp
L PwrMCU #PWR043
U 1 1 5714DC6A
P 12050 7850
F 0 "#PWR043" H 12050 7900 30  0001 C CNN
F 1 "PwrMCU" H 12120 7880 30  0000 C CNN
F 2 "" H 12050 7850 60  0000 C CNN
F 3 "" H 12050 7850 60  0000 C CNN
	1    12050 7850
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 XL4
U 1 1 5714DC76
P 11400 8100
F 0 "XL4" V 11350 8100 50  0000 C CNN
F 1 "CONN_6" V 11450 8100 50  0000 C CNN
F 2 "Connectors:PLS-6" H 11400 8100 60  0001 C CNN
F 3 "" H 11400 8100 60  0000 C CNN
F 4 "6" V 11400 8100 60  0001 C CNN "SolderPointsDIP"
	1    11400 8100
	-1   0    0    -1  
$EndComp
$Comp
L CONN_8 XL1
U 1 1 5714DC06
P 2050 3700
F 0 "XL1" V 2000 3700 50  0000 C CNN
F 1 "CONN_8" V 2100 3700 50  0000 C CNN
F 2 "Connectors:PLS-8" H 2050 3700 60  0001 C CNN
F 3 "" H 2050 3700 60  0000 C CNN
	1    2050 3700
	-1   0    0    -1  
$EndComp
$Comp
L +3.3V #PWR044
U 1 1 5714DDD0
P 2350 3950
F 0 "#PWR044" H 2350 3910 30  0001 C CNN
F 1 "+3.3V" H 2430 3980 30  0000 C CNN
F 2 "" H 2350 3950 60  0000 C CNN
F 3 "" H 2350 3950 60  0000 C CNN
	1    2350 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR045
U 1 1 5714DF2E
P 2400 4050
F 0 "#PWR045" H 2490 4030 30  0001 C CNN
F 1 "GND" H 2400 3970 30  0001 C CNN
F 2 "" H 2400 4050 60  0000 C CNN
F 3 "" H 2400 4050 60  0000 C CNN
	1    2400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 2750 8850 2750
Wire Wire Line
	9750 2750 9350 2750
Wire Wire Line
	6200 2350 6100 2350
Wire Wire Line
	3150 4700 3450 4700
Wire Notes Line
	8850 8750 8850 9600
Wire Notes Line
	8550 9600 8550 8750
Wire Notes Line
	8250 8750 8250 9600
Wire Notes Line
	7950 9600 7950 8750
Wire Notes Line
	7650 8750 7650 9600
Connection ~ 8700 9000
Wire Wire Line
	8700 9100 8700 9000
Connection ~ 8400 9000
Wire Wire Line
	8400 9100 8400 9000
Connection ~ 8100 9000
Wire Wire Line
	8100 9100 8100 9000
Connection ~ 7800 9000
Wire Wire Line
	7800 9100 7800 9000
Connection ~ 7500 9000
Wire Wire Line
	7500 9100 7500 9000
Wire Wire Line
	9000 9100 9000 9000
Connection ~ 11950 3500
Connection ~ 11950 3100
Wire Wire Line
	11850 3100 11950 3100
Connection ~ 11950 3200
Wire Wire Line
	11850 3200 11950 3200
Connection ~ 11950 3300
Wire Wire Line
	11850 3300 11950 3300
Connection ~ 11950 3400
Wire Wire Line
	11850 3400 11950 3400
Wire Wire Line
	11850 3500 12100 3500
Wire Wire Line
	11950 3000 11950 3500
Wire Wire Line
	11850 3000 11950 3000
Wire Wire Line
	12200 2800 11850 2800
Wire Wire Line
	11850 2600 12200 2600
Wire Notes Line
	8350 8250 8350 7400
Wire Notes Line
	8050 8250 8050 7400
Wire Notes Line
	7750 8250 7750 7400
Wire Notes Line
	8650 8250 8650 7400
Connection ~ 3350 4300
Wire Wire Line
	3350 4200 3450 4200
Connection ~ 3350 4400
Wire Wire Line
	3350 4300 3450 4300
Connection ~ 3350 4550
Wire Wire Line
	3350 4400 3450 4400
Connection ~ 3350 4700
Wire Wire Line
	3350 4550 3450 4550
Wire Wire Line
	3350 4200 3350 4700
Connection ~ 8800 7650
Wire Wire Line
	8800 7750 8800 7650
Connection ~ 8500 7650
Wire Wire Line
	8500 7750 8500 7650
Connection ~ 8200 7650
Wire Wire Line
	8200 7750 8200 7650
Connection ~ 7900 7650
Wire Wire Line
	7900 7750 7900 7650
Connection ~ 7600 7650
Wire Wire Line
	7600 7750 7600 7650
Wire Wire Line
	9050 7650 9050 7750
Wire Wire Line
	7300 7650 9050 7650
Wire Wire Line
	13100 2600 13500 2600
Connection ~ 13350 2600
Wire Wire Line
	14050 3300 14050 3350
Wire Wire Line
	14050 2600 14050 2900
Wire Bus Line
	7000 3150 7000 2450
Wire Wire Line
	9750 3050 9200 3050
Wire Wire Line
	9150 2950 9700 2950
Wire Bus Line
	9850 2450 9850 3200
Wire Wire Line
	10500 3200 9950 3200
Wire Wire Line
	9950 3100 10500 3100
Wire Wire Line
	6300 3350 6100 3350
Wire Wire Line
	6100 2550 6900 2550
Wire Wire Line
	6100 3050 6900 3050
Wire Wire Line
	6100 2950 6900 2950
Wire Wire Line
	6100 2850 6900 2850
Wire Wire Line
	6100 2450 6900 2450
Wire Wire Line
	6100 2650 6900 2650
Wire Wire Line
	6100 3750 6300 3750
Wire Wire Line
	6100 3250 6300 3250
Wire Wire Line
	6100 3650 6300 3650
Connection ~ 14050 2600
Wire Wire Line
	13900 2600 14450 2600
Wire Wire Line
	13350 3300 13350 3350
Wire Wire Line
	13350 2600 13350 2900
Wire Wire Line
	9800 3850 9900 3850
Wire Wire Line
	9650 4000 9650 4400
Wire Wire Line
	9400 4300 9400 4400
Wire Wire Line
	9950 2800 10500 2800
Wire Wire Line
	9950 2600 10500 2600
Wire Wire Line
	7500 9500 7500 9600
Wire Wire Line
	11900 3700 11850 3700
Wire Wire Line
	10450 4350 10450 4400
Wire Wire Line
	10450 3800 10500 3800
Wire Wire Line
	10450 3850 10450 3800
Wire Wire Line
	10200 3700 10200 3900
Wire Wire Line
	10500 3700 10200 3700
Wire Wire Line
	10200 4300 10200 4400
Wire Wire Line
	11200 4250 11200 4400
Wire Wire Line
	11850 3800 11900 3800
Connection ~ 11900 3800
Wire Wire Line
	11900 4000 11900 3700
Wire Wire Line
	7800 9500 7800 9600
Wire Wire Line
	8100 9500 8100 9600
Wire Wire Line
	8700 9500 8700 9600
Wire Wire Line
	8400 9500 8400 9600
Wire Wire Line
	9000 9500 9000 9600
Wire Wire Line
	9950 2700 10500 2700
Wire Wire Line
	9950 2900 10500 2900
Connection ~ 9400 3850
Wire Wire Line
	9500 3850 9400 3850
Connection ~ 9900 3850
Wire Wire Line
	9900 4300 9900 4400
Wire Wire Line
	9400 3400 9400 3900
Wire Wire Line
	10500 3400 9400 3400
Wire Wire Line
	9900 3500 10500 3500
Wire Wire Line
	9900 3900 9900 3500
Wire Wire Line
	8200 8150 8200 8250
Wire Wire Line
	7600 8150 7600 8250
Wire Wire Line
	8800 8150 8800 8250
Wire Wire Line
	8500 8150 8500 8250
Wire Wire Line
	7900 8150 7900 8250
Wire Wire Line
	9050 8150 9050 8250
Wire Wire Line
	3350 4050 3450 4050
Wire Wire Line
	6200 1850 6200 2350
Wire Bus Line
	7000 2450 9850 2450
Wire Wire Line
	4700 5200 4700 5000
Wire Wire Line
	4500 5000 4500 5100
Wire Wire Line
	4500 5100 4950 5100
Connection ~ 4700 5100
Wire Wire Line
	4600 5000 4600 5100
Connection ~ 4600 5100
Wire Wire Line
	4800 5100 4800 5000
Wire Wire Line
	4950 5100 4950 5000
Connection ~ 4800 5100
Connection ~ 7250 4700
Wire Wire Line
	7150 4700 7250 4700
Connection ~ 6750 4700
Wire Wire Line
	6750 4600 6750 4750
Wire Wire Line
	7250 5150 7250 5200
Wire Wire Line
	6750 5150 6750 5200
Wire Wire Line
	7000 5200 7000 4850
Wire Wire Line
	6850 4700 6750 4700
Wire Wire Line
	7250 4000 7250 4750
Wire Wire Line
	6100 4100 6750 4100
Wire Wire Line
	6100 4000 7250 4000
Wire Wire Line
	12850 3150 12850 3050
Wire Wire Line
	2250 3350 3450 3350
Wire Wire Line
	3450 3450 2250 3450
Wire Wire Line
	3300 9400 3400 9400
Wire Wire Line
	3400 9300 3300 9300
Wire Wire Line
	6500 1850 6200 1850
Wire Wire Line
	6700 1850 7000 1850
Wire Wire Line
	9000 9000 7000 9000
Wire Wire Line
	2250 3550 3450 3550
Wire Wire Line
	2250 3650 3450 3650
Wire Wire Line
	2250 3750 3450 3750
Wire Wire Line
	2250 3850 3450 3850
Wire Wire Line
	3450 2350 3350 2350
Wire Wire Line
	2750 2350 2850 2350
Wire Wire Line
	2250 2350 2350 2350
Wire Wire Line
	3900 7550 4050 7550
Connection ~ 4400 7350
Wire Wire Line
	3900 7350 4700 7350
Wire Wire Line
	4400 7750 4400 7900
Wire Wire Line
	2650 7750 2650 7900
Wire Wire Line
	2350 7350 3100 7350
Connection ~ 3000 7350
Wire Wire Line
	3000 7350 3000 7550
Wire Wire Line
	3000 7550 3100 7550
Connection ~ 2650 7350
Wire Bus Line
	500  6350 16050 6350
Wire Bus Line
	550  6350 450  6350
Wire Bus Line
	5800 6350 5800 11200
Wire Bus Line
	10550 6350 10550 11200
Wire Bus Line
	10550 11200 10750 11200
Wire Bus Line
	5800 8500 500  8500
Wire Bus Line
	500  8500 500  8550
Wire Bus Line
	13550 6350 13550 9950
Wire Bus Line
	13550 9950 13750 9950
Wire Bus Line
	13550 8250 13550 8200
Wire Wire Line
	11850 8250 11600 8250
Wire Wire Line
	11600 8350 11850 8350
Wire Wire Line
	11600 7850 12050 7850
Wire Wire Line
	11600 8150 11700 8150
Wire Wire Line
	11700 7950 11600 7950
Wire Wire Line
	11600 8050 12150 8050
Wire Wire Line
	2350 3950 2250 3950
$Comp
L CONN_5 XL2
U 1 1 5714F763
P 3100 9400
F 0 "XL2" V 3050 9400 50  0000 C CNN
F 1 "CONN_5" V 3150 9400 50  0000 C CNN
F 2 "Connectors:PLS-5" H 3100 9400 60  0001 C CNN
F 3 "" H 3100 9400 60  0000 C CNN
	1    3100 9400
	-1   0    0    -1  
$EndComp
Text Label 3550 9600 0    60   ~ 0
UART_TX
Text Label 3550 9500 0    60   ~ 0
UART_RX
Wire Wire Line
	3550 9600 3300 9600
Wire Wire Line
	3300 9500 3550 9500
Text Label 6300 3150 0    60   ~ 0
Trigger
Wire Wire Line
	6300 3150 6100 3150
Text Label 3500 9200 0    60   ~ 0
Trigger
Wire Wire Line
	3500 9200 3300 9200
$EndSCHEMATC
