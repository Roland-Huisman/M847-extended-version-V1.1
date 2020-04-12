// =============================================================================================================  
// Bootloader for Digital PDP8/e PDP8/f PDP8/m computers by Roland Huisman. MIT license
// V1.1 fixed false run state message
// V1.2 changed RX(2)8 boot address for RX(2)8 (RX01/RX02) bootloader
// V1.3 Expanded to currently maximum possible 63 programs, so users can just replace the line with their own boot code
// V1.4 - Added Kaleidoscope. 
//      - Removed delays and Added variable "SlowDown". So you can determine your own loading speed. 
//        It's set to a quite fast but still blinky rate. Search for unsigned long SlowDown which is currently set at 35 milliseconds.
//        You can change it if you want to speed up or slow down the loading. 0 gives the maximum load speed 200 gives a real slow loading.
// V1.5 Added TA8E TU60 bootstrap for Caps-8 and OS/8 setup cassettes
// V1.6 Added program 37, receive charachters on 03/04 serial port and place them into AC
// V1.7 - Updated BIN loader. You don't need to set the switches to 7777 when you want to use the serial port. 
//        It is now permanent set to use the 'low speed reader'. Which actually means that you can use the serial port at high speed.
//      - Besides the BIN loader at 03/04 there is now also a secondary BIN loader at 40/41. So if you have a slow dumb terminal at
//        03/04 you can upload BIN images trough the second serial port at high speed. When you start your program it wil
//        show up on your dumb terminal or TTY.
//      - Changed the order of the bootstraps to a more logical structure
// =============================================================================================================  



// =============================================================================================================  
//                                         Bootload programs
//
// Please note the data format. You can use the octal numbers after 0x....
// Please fill in all the numbers even if they are zero
// 
// The first number is the initial address to deposit from
// The second number is the EMA address (IF and DF)
// Then the complete program can be written
// The last number is the start address of the program
//
// Example: 
// We want a program located at address 200
// The EMA address is 0
// The data to deposit in memory is: 7001, 2300, 5201, 5200
// The startaddress is 200
//
// Should look like this: 
// const PROGMEM word Program_01[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200};  //AC increment program
//
// 
// All Octal values are repesented as HEX numbers, and put as HEX into the MCP23017. 
// Due hardware the bits 15, 11, 7 and 3 are zero and just not used.
// Programnumbers are shown in Octal as well... The highest program number is currently 77 oct (so max 63 programs)
// Program_00 does not exist, this is used to load the selected default 
// 
//
// =============================================================================================================  




// ================================== FROM HERE THE BOOTSTRAPS CAN BE ENTERED =================================

// The program numbers in group 0x and 1x can be set by the dipstitches as default bootloader.
// This means, when you toggle the SW switch just once down and up again, the delected default is loaded.
// If an other program is desired to load, just toggle the SW switch more often and watch the address lights for the program number.
  
  //group 0x
  // Program 0 does not exist, this is preseved to load a default trough the dip switches
  const PROGMEM word Program_01[] = {0x0017, 0x0000, 0x0017, 0x7240, 0x3017, 0x1045, 0x6416, 0x6411, 0x5024, 0x6402, 0x6401, 0x5027, 0x6406, 0x7106, 0x7006, 0x7510, 0x5000, 0x7006, 0x6401, 0x5037, 0x6404, 0x3417, 0x5026, 0x7605, 0x0100, 0x0020}; // OS8 disk server 40/41
  const PROGMEM word Program_02[] = {0x0024, 0x0000, 0x7126, 0x1060, 0x6751, 0x7201, 0x4053, 0x4053, 0x7104, 0x6755, 0x5054, 0x6754, 0x7450, 0x7610, 0x5046, 0x1060, 0x7041, 0x1061, 0x3060, 0x5024, 0x6751, 0x4053, 0x3002, 0x2050, 0x5047, 0x0000, 0x6753, 0x5033, 0x6752, 0x5453, 0x7024, 0x6030, 0x0033}; //RX8 RX01 bootloader (M8357 RX8E card at 675x)
  const PROGMEM word Program_03[] = {0x0020, 0x0000, 0x1061, 0x1046, 0x0060, 0x3061, 0x7327, 0x1061, 0x6751, 0x7301, 0x4053, 0x4053, 0x7004, 0x6755, 0x5054, 0x6754, 0x7450, 0x5020, 0x1061, 0x6751, 0x1061, 0x0046, 0x1032, 0x3060, 0x0360, 0x4053, 0x3002, 0x2050, 0x5047, 0x0000, 0x6753, 0x5033, 0x6752, 0x5453, 0x0420, 0x0020, 0x0033}; //RX28 RX02 bootloader (M8357 RX8E card at 675x)
  const PROGMEM word Program_04[] = {0x0023, 0x0000, 0x6007, 0x6751, 0x6745, 0x5025, 0x7200, 0x6733, 0x5031, 0x0023}; // RK05 (RK8E) bootloader MI8-ED RK8
  const PROGMEM word Program_05[] = {0x7300, 0x0000, 0x1312, 0x4312, 0x4312, 0x6773, 0x5303, 0x6777, 0x3726, 0x2326, 0x5303, 0x5732, 0x2000, 0x1300, 0x6774, 0x6771, 0x5315, 0x6776, 0x0331, 0x1327, 0x7640, 0x5315, 0x2321, 0x5712, 0x7354, 0x7756, 0x7747, 0x0077, 0x7400, 0x7300}; //TU56 (TD8E) MI8-EH
  const PROGMEM word Program_06[] = {0x7554, 0x0000, 0x7600, 0x6774, 0x1374, 0x6766, 0x6771, 0x5360, 0x7240, 0x1354, 0x3773, 0x1354, 0x3772, 0x1375, 0x6766, 0x5376, 0x7754, 0x7755, 0x0600, 0x0220, 0x6771, 0x5376, 0x7777, 0x7554}; // TU56 TC08 dec tape MI8-EC
  const PROGMEM word Program_07[] = {0x4000, 0x0000, 0x1237, 0x1206, 0x6704, 0x6706, 0x6703, 0x5204, 0x7264, 0x6702, 0x7610, 0x3211, 0x3636, 0x1205, 0x6704, 0x6706, 0x6701, 0x5216, 0x7002, 0x7430, 0x1636, 0x7022, 0x3636, 0x7420, 0x2236
                                    , 0x2235, 0x5215, 0x7346, 0x7002, 0x3235, 0x5201, 0x7737, 0x3557, 0x7730, 0x4000}; //  TU60 (TA8E) CAPS-8 or OS/8 setup cassettes


  //group 1x
  const PROGMEM word Program_10[] = {0x7737, 0x0000, 0x6014, 0x0776, 0x7326, 0x1337, 0x2376, 0x5340, 0x6011, 0x5356, 0x3361, 0x1361, 0x3371, 0x1345, 0x3357, 0x1345, 0x3367, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510, 0x5374, 0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x0000, 0x7737}; // PC04 PC8E papertape MI8-EA
  const PROGMEM word Program_11[] = {0x7756, 0x0000, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510, 0x5357, 0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x7756}; // RIM loader  03/04
  const PROGMEM word Program_12[] = {0x7612, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3212, 0x4260, 0x1300, 0x7750, 0x5237, 0x2212, 0x7040, 0x5227
                                    ,0x1212, 0x7640, 0x5230, 0x1214, 0x0274, 0x1341, 0x7510, 0x2226, 0x7750, 0x5626, 0x1214, 0x0256, 0x1257, 0x3213, 0x5230, 0x0070, 0x6201, 0x0000, 0x0000, 0x6031, 0x5262, 0x6036, 0x3214, 0x1214
                                    ,0x5660, 0x6011, 0x5270, 0x6016, 0x5265, 0x0300, 0x4343, 0x7041, 0x1215, 0x7402, 0x6032, 0x6014, 0x6214, 0x1257, 0x3213, 0x7240, 0x7700, 0x1353, 0x1352, 0x3261, 0x4226, 0x5313, 0x3215, 0x1213
                                    ,0x3336, 0x1214, 0x3376, 0x4260, 0x3355, 0x4226, 0x5275, 0x4343, 0x7420, 0x5336, 0x3216, 0x1376, 0x1355, 0x1215, 0x5315, 0x6201, 0x3616, 0x2216, 0x7600, 0x5332, 0x0000, 0x1376, 0x7106, 0x7006
                                    ,0x7006, 0x1355, 0x5743, 0x5262, 0x0006, 0x0000, 0x0000, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510, 0x5357, 0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x7776, 0x5301, 0x7777}; //BIN LOADER 03/04
  const PROGMEM word Program_13[] = {0x7612, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3212, 0x4260, 0x1300, 0x7750, 0x5237, 0x2212, 0x7040, 0x5227
                                    ,0x1212, 0x7640, 0x5230, 0x1214, 0x0274, 0x1341, 0x7510, 0x2226, 0x7750, 0x5626, 0x1214, 0x0256, 0x1257, 0x3213, 0x5230, 0x0070, 0x6201, 0x0000, 0x0000, 0x6401, 0x5262, 0x6406, 0x3214, 0x1214
                                    ,0x5660, 0x6011, 0x5270, 0x6016, 0x5265, 0x0300, 0x4343, 0x7041, 0x1215, 0x7402, 0x6402, 0x6014, 0x6214, 0x1257, 0x3213, 0x7240, 0x7700, 0x1353, 0x1352, 0x3261, 0x4226, 0x5313, 0x3215, 0x1213
                                    ,0x3336, 0x1214, 0x3376, 0x4260, 0x3355, 0x4226, 0x5275, 0x4343, 0x7420, 0x5336, 0x3216, 0x1376, 0x1355, 0x1215, 0x5315, 0x6201, 0x3616, 0x2216, 0x7600, 0x5332, 0x0000, 0x1376, 0x7106, 0x7006
                                    ,0x7006, 0x1355, 0x5743, 0x5262, 0x0006, 0x0000, 0x0000, 0x6402, 0x6401, 0x5357, 0x6406, 0x7106, 0x7006, 0x7510, 0x5357, 0x7006, 0x6401, 0x5367, 0x6404, 0x7420, 0x3776, 0x3376, 0x5356, 0x7776, 0x5301, 0x7777}; //BIN LOADER 40/41
  const PROGMEM word Program_14[] = {0x0200, 0x0000, 0x1220, 0x4221, 0x7040, 0x1217, 0x3217, 0x1217, 0x6053, 0x4221, 0x1220, 0x6054, 0x6052, 0x5212, 0x6055, 0x3220, 0x5200, 0x3777, 0x0006, 0x0000
                                    ,0x3236, 0x7404, 0x7041, 0x3237, 0x1236, 0x7100, 0x7510, 0x7020, 0x7010, 0x2237, 0x5227, 0x5621, 0x0000, 0x0000, 0x6144, 0x5240, 0x0200}; // Kaleidoscope
  const PROGMEM word Program_15[] = {0x7756, 0x0000, 0x7771, 0x6014, 0x6011, 0x5360, 0x7106, 0x7106, 0x6012, 0x7420, 0x5357, 0x5756, 0x4356, 0x3373, 0x4356, 0x7770}; //MI8-EE Typeset
  const PROGMEM word Program_16[] = {0x7737, 0x0000, 0x6007, 0x7604, 0x7510, 0x3343, 0x6766, 0x6771, 0x5344, 0x1376, 0x5343, 0x7600, 0x6603, 0x6622, 0x5352, 0x5752, 0x7577, 0x6032, 0x6031, 0x5357, 0x6036, 0x7106, 0x7006, 0x7510, 0x5357, 0x7006, 0x6031, 0x5367, 0x6034, 0x7420, 0x3776, 0x3376, 0x5356, 0x0200, 0x7737}; //MI8-EF Edu sys low
  const PROGMEM word Program_17[] = {0x7737, 0x0000, 0x6007, 0x7604, 0x7510, 0x3343, 0x6766, 0x6771, 0x5344, 0x1376, 0x5343, 0x7600, 0x6603, 0x6622, 0x5352, 0x5752, 0x7577, 0x6014, 0x6011, 0x5357, 0x6016, 0x7106, 0x7006, 0x7510, 0x5374, 0x7006, 0x6011, 0x5367, 0x6016, 0x7420, 0x3776, 0x3376, 0x5357, 0x0220, 0x7737}; //MI8-EG Edu sys high


                                    
  // from here programs are not selectable by the dipswitches. These can be loaded by toggeling the SW switch or pushbutton on the PCB only.
  //group 2x
  const PROGMEM word Program_20[] = {0x0200, 0x0000, 0x7200, 0x7100, 0x7040, 0x7020, 0x7020, 0x7010, 0x7004, 0x7012, 0x7006, 0x7001, 0x7001, 0x7002, 0x7402, 0x0200}; //group 1 microinstructions
  const PROGMEM word Program_21[] = {0x0200, 0x0000, 0x7300, 0x7440, 0x7402, 0x7430, 0x7402, 0x7020, 0x7420, 0x7402, 0x7001, 0x7450, 0x7402, 0x7510, 0x7402, 0x7410, 0x7402, 0x7012, 0x7500, 0x7402, 0x7404, 0x7402, 0x0200}; //group 1 microinstructions
  const PROGMEM word Program_22[] = {0x0200, 0x0000, 0x7240, 0x7001, 0x7640, 0x7402, 0x7120, 0x7010, 0x7510, 0x7410, 0x7402, 0x7001, 0x7002, 0x1202, 0x7420, 0x7402, 0x7402, 0x0200}; // Operate instructions
  const PROGMEM word Program_23[] = {0x0200, 0x0000, 0x7500, 0x3300, 0x7001, 0x2300, 0x5202, 0x7440, 0x7402, 0x7402, 0x0200}; // ISZ instructions
  const PROGMEM word Program_24[] = {0x0200, 0x0000, 0x7300, 0x3300, 0x3204, 0x4204, 0x0000, 0x1204, 0x7041, 0x1215, 0x7440, 0x7402, 0x2300, 0x5202, 0x7402, 0x0204, 0x0200}; // JMS instruction
  const PROGMEM word Program_25[] = {0x0200, 0x0000, 0x5210, 0x7402, 0x5206, 0x7402, 0x5212, 0x7402, 0x5204, 0x7402, 0x5204, 0x7402, 0x2300, 0x5200, 0x7402, 0x0200}; // JMP instruction
  const PROGMEM word Program_26[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment
  const PROGMEM word Program_27[] = {0x7777, 0x0000, 0x0000, 0x7300, 0x1007, 0x7040, 0x3007, 0x1007, 0x3410, 0x5000, 0x0000, 0x0011, 0x7777}; //checker board runs endless MD alters between 0000 and 7777

  // group 3x
  const PROGMEM word Program_30[] = {0x0020, 0x0000, 0x7300, 0x7020, 0x7420, 0x5025, 0x5027, 0x1032, 0x7410, 0x1033, 0x3410, 0x5021, 0x5252, 0x2525, 0x0035, 0x0020}; //checker board runs endless MD alters between 5252 and 2525
  const PROGMEM word Program_31[] = {0x0000, 0x0000, 0x7604, 0x6046, 0x6041, 0x5002, 0x5000, 0x0000}; // print character in switch register
  const PROGMEM word Program_32[] = {0x0000, 0x0000, 0x7001, 0x6046, 0x6041, 0x5002, 0x5000, 0x0000}; // console print test 03/04
  const PROGMEM word Program_33[] = {0x0000, 0x0000, 0x6032, 0x6031, 0x5001, 0x6036, 0x6046, 0x6041, 0x5005, 0x5001, 0x0000}; // Echo test for one terminal at 03/04
  const PROGMEM word Program_34[] = {0x0200, 0x0000, 0x7300, 0x1205, 0x6412, 0x6401, 0x5203, 0x0210, 0x6406, 0x5203, 0x7000, 0x7000, 0x7000, 0x5206, 0x7000, 0x7000, 0x7000, 0x6405, 0x6404, 0x5203, 0x0200}; // echo 1-4 terminals
  const PROGMEM word Program_35[] = {0x0200, 0x0000, 0x7001, 0x6026, 0x6021, 0x5202, 0x5200, 0x0200}; // PC04 Punch alternating 1's and 0's
  const PROGMEM word Program_36[] = {0x0200, 0x0000, 0x7300, 0x6016, 0x6011, 0x5202, 0x5200, 0x0200}; // PC04 read the papertape (doesn't load to core, just for test purposes)
  const PROGMEM word Program_37[] = {0x0000, 0x0000, 0x6032, 0x6031, 0x5001, 0x6036, 0x5001, 0x0000}; // Place received character into AC from terminal at 03/04

  // group 4x
  const PROGMEM word Program_40[] = {0x3000, 0x0000, 0x0016, 0x3015, 0x3601, 0x2201, 0x2200, 0x5202, 0x3203, 0x3204, 0x3205, 0x1201, 0x3014, 0x3212, 0x3414, 0x3000}; // memory wipe field 0 Vince
  const PROGMEM word Program_41[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_42[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_43[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_44[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_45[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_46[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_47[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.

  // group 5x
  const PROGMEM word Program_50[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_51[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_52[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_53[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_54[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_55[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_56[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_57[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.

  // group 6x
  const PROGMEM word Program_60[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_61[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_62[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_63[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_64[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_65[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_66[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_67[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.

  // group 7x
  const PROGMEM word Program_70[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_71[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_72[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_73[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_74[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_75[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_76[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.
  const PROGMEM word Program_77[] = {0x0200, 0x0000, 0x7001, 0x2300, 0x5201, 0x5200, 0x0200}; //AC increment. REPLACE THIS CODE WITH YOUR OWN BOOTSTRAP IF YOU WANT TO.

// ====================================== END OF BOOTSTRAPLIST =================================================





// =============================================================================================================  
//                                         Includes
  #include <Wire.h>                             // I2C handler




// =============================================================================================================  
//                                         Variables  
  const    byte GPIOA                     = 0x12;  // GPIOA adres in 16-bit mode, 2x 8 I/O ports.
  const    byte IOCON                     = 0x0A;  // IOCON adres in 16-bit mode, I/O Expander Configuration Register.
  const    byte IODIRA                    = 0x00;  // IODIRA adres in 16-bit mode, is het I/O Direction Register voor PortA.  
  volatile byte ProgramNumber             = 0x00;  // program to run
  volatile byte pulseState                = 0x00;  // Previous state of switch
  volatile unsigned long SwitchTimeOut    = 3000;  // This is the wait time (ms) after the last toggle. Then the program loads.
  volatile word ProgramLength             = 0x0000;// To calculate the amount of words in the programs
  volatile byte RunOnce                   = 0x00;  // just run Kitt once at turn on

  unsigned long SlowDown                  = 5;     // Blink delay in milli seconds. This slows down the loading of a bootstrap to give it a nice blinking effect.
                                                   // Placing a 0 loads the program at full speed, you can't really see a program to be loaded.
                                                   // Placing 50 will give a nice blinking effect but it slows down the program loading.

  
void setup ()
{
// =============================================================================================================  
//                                         Pin definitions
  #define r_RUN                   8           // PB0
  #define r_SW                    9           // PB1
  #define Dip_1                   10          // PB2
  #define Dip_2                   11          // PB3
  #define Dip_3                   12          // PB4
  #define Dip_4                   13          // PB5

  #define w_INITIALIZE_H          A0          // PC0 for 400nS pulse
  #define w_PULSE_LA_H            A1          // PC1 for 400nS pulse
  #define w_MEM_START             A2          // PC2 for 400nS pulse
  #define w_STOP                  A3          // PC3
  
  #define Set_Flip_Flop           2           // PD2 
  #define Show_Data               3           // PD3 
  #define Exam                    4           // PD4 
  #define w_LA_ENABLE             5           // PD5
  #define w_MS_IR_DISABLE         6           // PD6
  #define w_KEY_CONTROL           7           // PD7

  pinMode (r_RUN                  , INPUT)  ; // read RUN signal from Omnibus
  pinMode (r_SW                   , INPUT)  ; // read SW signal from Omnibus
  pinMode (Dip_1                  , INPUT)  ; // Default bootprogam select for one time toggeling SW
  pinMode (Dip_2                  , INPUT)  ; // Default bootprogam select for one time toggeling SW 
  pinMode (Dip_3                  , INPUT)  ; // Default bootprogam select for one time toggeling SW
  pinMode (Dip_4                  , INPUT)  ; // Default bootprogam select for one time toggeling SW

  digitalWrite (r_RUN             , HIGH)   ; // turn on pull up
  digitalWrite (r_SW              , HIGH)   ; // turn on pull up
  digitalWrite (Dip_1             , HIGH)   ; // turn on pull up
  digitalWrite (Dip_2             , HIGH)   ; // turn on pull up
  digitalWrite (Dip_3             , HIGH)   ; // turn on pull up
  digitalWrite (Dip_4             , HIGH)   ; // turn on pull up

  digitalWrite (w_INITIALIZE_H    , LOW)    ; // Write zero before initializing output
  digitalWrite (w_PULSE_LA_H      , LOW)    ; // Write zero before initializing output
  digitalWrite (w_MEM_START       , LOW)    ; // Write zero before initializing output
  digitalWrite (w_STOP            , LOW)    ; // Write zero before initializing output

  pinMode (w_INITIALIZE_H         , OUTPUT) ; // Set to output mode
  pinMode (w_PULSE_LA_H           , OUTPUT) ; // Set to output mode
  pinMode (w_MEM_START            , OUTPUT) ; // Set to output mode
  pinMode (w_STOP                 , OUTPUT) ; // Set to output mode

  digitalWrite (Set_Flip_Flop     , LOW)    ; // Write zero before initializing output
  digitalWrite (Show_Data         , LOW)    ; // Write zero before initializing output
  digitalWrite (Exam              , LOW)    ; // Write zero before initializing output
  digitalWrite (w_LA_ENABLE       , LOW)    ; // Write zero before initializing output
  digitalWrite (w_MS_IR_DISABLE   , LOW)    ; // Write zero before initializing output
  digitalWrite (w_KEY_CONTROL     , LOW)    ; // Write zero before initializing output

  pinMode (Set_Flip_Flop          , OUTPUT) ; // Set to output mode
  pinMode (Show_Data              , OUTPUT) ; // Set to output mode
  pinMode (Exam                   , OUTPUT) ; // Set to output mode
  pinMode (w_LA_ENABLE            , OUTPUT) ; // Set to output mode
  pinMode (w_MS_IR_DISABLE        , OUTPUT) ; // Set to output mode
  pinMode (w_KEY_CONTROL          , OUTPUT) ; // Set to output mode




// =============================================================================================================
//                                          Start I2C bus
  Wire.begin();                               // start Wire library as I2C-Bus Master

  Wire.beginTransmission(0x20);               // MCP23017 Address
  Wire.write(IOCON);                          // IOCON register
  Wire.write(byte(B01000000));                // Enable sequential addresses
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(IODIRA);                         // IODIRA register
  Wire.write(byte(0x00));                     // Write zeto's to outputs A
  Wire.write(byte(0x00));                     // Write zeto's to outputs B
  Wire.endTransmission();
 
 
// =============================================================================================================
//                                          Setup serial port for debugging
  Serial.begin (115200);
  digitalWrite (0                 , HIGH)   ; // turn on pull up on RX line
}
//                                                  End setup
// =============================================================================================================




// =============================================================================================================
//                                                 Main loop
void loop ()
{
  if (RunOnce==0x00){Kitt();}
  Serial.println   ("PDP8/E, PDP8/F, PDP8/M bootloader by Roland Huisman V1.6");
  Serial.println   ();
  Serial.print     ("Default program number by dipswitch ");
  Serial.println   (ReadDefaultProgramNumber(),HEX);

  Serial.print   ("Use SW switch to select program number please... ");
  ProgramNumber=(GetProgramNumber());
  Serial.println (ProgramNumber,HEX);
  Serial.println();

  if (ProgramNumber==0x00)
    {
      ProgramNumber = ReadDefaultProgramNumber();
        if (ProgramNumber == 0x00)
          {
            Serial.print("No default selected, no program will be loaded !");    
            Serial.println();  
          }
        if (ProgramNumber != 0x00)
        {
            Serial.print("Default program ");
            Serial.print(ProgramNumber,HEX);
            Serial.println(" will be loaded !");
            Serial.println();
        }
    }


  if (ProgramNumber==0x01) {LoadProgram(Program_01, sizeof(Program_01));}
  if (ProgramNumber==0x02) {LoadProgram(Program_02, sizeof(Program_02));}
  if (ProgramNumber==0x03) {LoadProgram(Program_03, sizeof(Program_03));}
  if (ProgramNumber==0x04) {LoadProgram(Program_04, sizeof(Program_04));}
  if (ProgramNumber==0x05) {LoadProgram(Program_05, sizeof(Program_05));}
  if (ProgramNumber==0x06) {LoadProgram(Program_06, sizeof(Program_06));}
  if (ProgramNumber==0x07) {LoadProgram(Program_07, sizeof(Program_07));}

  if (ProgramNumber==0x10) {LoadProgram(Program_10, sizeof(Program_10));}
  if (ProgramNumber==0x11) {LoadProgram(Program_11, sizeof(Program_11));}
  if (ProgramNumber==0x12) {LoadProgram(Program_12, sizeof(Program_12));}
  if (ProgramNumber==0x13) {LoadProgram(Program_13, sizeof(Program_13));}  
  if (ProgramNumber==0x14) {LoadProgram(Program_14, sizeof(Program_14));}
  if (ProgramNumber==0x15) {LoadProgram(Program_15, sizeof(Program_15));}
  if (ProgramNumber==0x16) {LoadProgram(Program_16, sizeof(Program_16));}  
  if (ProgramNumber==0x17) {LoadProgram(Program_17, sizeof(Program_17));}

  if (ProgramNumber==0x20) {LoadProgram(Program_20, sizeof(Program_20));}
  if (ProgramNumber==0x21) {LoadProgram(Program_21, sizeof(Program_21));}
  if (ProgramNumber==0x22) {LoadProgram(Program_22, sizeof(Program_22));}
  if (ProgramNumber==0x23) {LoadProgram(Program_23, sizeof(Program_23));}
  if (ProgramNumber==0x24) {LoadProgram(Program_24, sizeof(Program_24));}
  if (ProgramNumber==0x25) {LoadProgram(Program_25, sizeof(Program_25));}
  if (ProgramNumber==0x26) {LoadProgram(Program_26, sizeof(Program_26));}
  if (ProgramNumber==0x27) {LoadProgram(Program_27, sizeof(Program_27));}

  if (ProgramNumber==0x30) {LoadProgram(Program_30, sizeof(Program_30));}
  if (ProgramNumber==0x31) {LoadProgram(Program_31, sizeof(Program_31));}
  if (ProgramNumber==0x32) {LoadProgram(Program_32, sizeof(Program_32));}
  if (ProgramNumber==0x33) {LoadProgram(Program_33, sizeof(Program_33));}
  if (ProgramNumber==0x34) {LoadProgram(Program_34, sizeof(Program_34));}
  if (ProgramNumber==0x35) {LoadProgram(Program_35, sizeof(Program_35));}
  if (ProgramNumber==0x36) {LoadProgram(Program_36, sizeof(Program_36));}
  if (ProgramNumber==0x37) {LoadProgram(Program_37, sizeof(Program_37));}

  if (ProgramNumber==0x40) {LoadProgram(Program_40, sizeof(Program_40));}
  if (ProgramNumber==0x41) {LoadProgram(Program_41, sizeof(Program_41));}
  if (ProgramNumber==0x42) {LoadProgram(Program_42, sizeof(Program_42));}
  if (ProgramNumber==0x43) {LoadProgram(Program_43, sizeof(Program_43));}
  if (ProgramNumber==0x44) {LoadProgram(Program_44, sizeof(Program_44));}
  if (ProgramNumber==0x45) {LoadProgram(Program_45, sizeof(Program_45));}
  if (ProgramNumber==0x46) {LoadProgram(Program_46, sizeof(Program_46));}
  if (ProgramNumber==0x47) {LoadProgram(Program_47, sizeof(Program_47));}

  if (ProgramNumber==0x50) {LoadProgram(Program_50, sizeof(Program_50));}
  if (ProgramNumber==0x51) {LoadProgram(Program_51, sizeof(Program_51));}
  if (ProgramNumber==0x52) {LoadProgram(Program_52, sizeof(Program_52));}
  if (ProgramNumber==0x53) {LoadProgram(Program_53, sizeof(Program_53));}
  if (ProgramNumber==0x54) {LoadProgram(Program_54, sizeof(Program_54));}
  if (ProgramNumber==0x55) {LoadProgram(Program_55, sizeof(Program_55));}
  if (ProgramNumber==0x56) {LoadProgram(Program_56, sizeof(Program_56));}
  if (ProgramNumber==0x57) {LoadProgram(Program_57, sizeof(Program_57));}

  if (ProgramNumber==0x60) {LoadProgram(Program_60, sizeof(Program_60));}
  if (ProgramNumber==0x61) {LoadProgram(Program_61, sizeof(Program_61));}
  if (ProgramNumber==0x62) {LoadProgram(Program_62, sizeof(Program_62));}
  if (ProgramNumber==0x63) {LoadProgram(Program_63, sizeof(Program_63));}
  if (ProgramNumber==0x64) {LoadProgram(Program_64, sizeof(Program_64));}
  if (ProgramNumber==0x65) {LoadProgram(Program_65, sizeof(Program_65));}
  if (ProgramNumber==0x66) {LoadProgram(Program_66, sizeof(Program_66));}
  if (ProgramNumber==0x67) {LoadProgram(Program_67, sizeof(Program_67));}

  if (ProgramNumber==0x70) {LoadProgram(Program_70, sizeof(Program_70));}
  if (ProgramNumber==0x71) {LoadProgram(Program_71, sizeof(Program_71));}
  if (ProgramNumber==0x72) {LoadProgram(Program_72, sizeof(Program_72));}
  if (ProgramNumber==0x73) {LoadProgram(Program_73, sizeof(Program_73));}
  if (ProgramNumber==0x74) {LoadProgram(Program_74, sizeof(Program_74));}
  if (ProgramNumber==0x75) {LoadProgram(Program_75, sizeof(Program_75));}
  if (ProgramNumber==0x76) {LoadProgram(Program_76, sizeof(Program_76));}
  if (ProgramNumber==0x77) {LoadProgram(Program_77, sizeof(Program_77));}
  



// etc...


  Serial.println();

}
//                                                End of main loop
// =============================================================================================================






// =============================================================================================================
//                  Count amount of switch pulses for program number and show in address LEDs
byte GetProgramNumber()
{
  byte ToggledProgramNumber    = 0x00;
  byte OctalProgramNumber      = 0x00; // highest valid program number is 0x77
  unsigned long currentMillis  = millis();
  unsigned long previousMillis = millis();
  
  while( (ToggledProgramNumber==0) | (currentMillis-previousMillis<SwitchTimeOut) )
    {
    if ((digitalRead(r_SW) == LOW) && (pulseState == false))
      {
        pulseState = true;
        ToggledProgramNumber++;
        currentMillis = millis();
        previousMillis = millis();
        
        if(ToggledProgramNumber>1)
          {
            OctalProgramNumber = ToggledProgramNumber-1;
            OctalProgramNumber = ((OctalProgramNumber<<1)&0x70) | (OctalProgramNumber & 0x07); // ToggledProgramNumber transfer to octal
            SingleStep();
            SwitchRegister(OctalProgramNumber);
            AddresLoad();
          }
      } 
    
    else if (digitalRead(r_SW) == HIGH) 
      {
        pulseState = false;
        currentMillis = millis();        
      }
      delay(20);
    }
  SwitchRegister(0x0000);
  Serial.println();
  UndoSingleStep();
  Serial.println();
  return (OctalProgramNumber);
}











// =============================================================================================================
//                             Read dipswitches for the default boot loader to load
byte ReadDefaultProgramNumber ()
{
  byte DefaultProgramNumber = PINB;
  DefaultProgramNumber = DefaultProgramNumber >> 2;       // move bits to the right
  DefaultProgramNumber = ~DefaultProgramNumber & 0x0F;    // invert reading and wipe out extra bits
  DefaultProgramNumber = ((DefaultProgramNumber<<1)&0x70) | (DefaultProgramNumber & 0x07); // dipswitch transfer to octal
  return DefaultProgramNumber;
}





// =============================================================================================================
//                                            Load program
void LoadProgram(const word TheProgram[], int ProgramLength)
  {
  SingleStep();
  Serial.println();
  int i=0;
  ProgramLength = ProgramLength/2;         // calculate programlength in words
  for (i = 0; i < ProgramLength; i = i + 1) 
    {
      //Serial.println(pgm_read_word_near(TheProgram+i),HEX);
      SwitchRegister(pgm_read_word_near(TheProgram+i));   
      if (i==0){AddresLoad();}
      if (i==1){ExtendedAddressLoad();}
      if (i==ProgramLength-1) {AddresLoad();}
      if ((i!=0)&(i!=1)&(i!=ProgramLength-1)) {Deposit();}
      delay(SlowDown);
    }
  SwitchRegister(0x0000);
  Serial.println();
  Serial.println();
  UndoSingleStep();
  Clear();
  Continue();
  }



// =============================================================================================================
//                       Transfer the switchregisterdata to the MC23017 to deposit or load address
void SwitchRegister(word LoadData)
{
  Serial.print ("Set Switch Register to ");  
  Serial.print (LoadData,HEX);
  Serial.print (" "); 
  word WordA = (LoadData)      & 0x00FF;
  word WordB = (LoadData >> 8) & 0x00FF;
  //Serial.println (WordA, HEX);
  //Serial.println (WordB, HEX);
  Wire.beginTransmission(0x20);
  Wire.write(GPIOA);                                  // gpioa
  Wire.write(byte(WordA)& 0xFF);                      // set A outputs to WordA
  Wire.write(byte(WordB)& 0xFF);                      // set B outputs to WordA
  Wire.endTransmission();
}


// =============================================================================================================
//                                          Put PDP into Single Step mode
void SingleStep()
  {
    Serial.println("Go into Single Step mode");
    digitalWrite (w_STOP , HIGH);                     // Places the machine in Single step mode
  }


// =============================================================================================================
//                                          Get PDP out of Single Step mode
void UndoSingleStep()
  {
    Serial.println("Undo Single Step mode");
    digitalWrite (w_STOP , LOW);                     // Get the machine out of Single step mode
  }



// =============================================================================================================
//                                                Deposit
void Deposit()
  {
    Serial.println("Deposit");
    digitalWrite (Set_Flip_Flop     , HIGH)    ;
    digitalWrite (w_KEY_CONTROL     , HIGH)    ; 
    digitalWrite (Show_Data         , HIGH)    ; 
    digitalWrite (w_MS_IR_DISABLE   , HIGH)    ;
    Trigger_Mem_Start ();
    digitalWrite (Set_Flip_Flop     , LOW)     ; 
    digitalWrite (w_KEY_CONTROL     , LOW)     ;
    digitalWrite (Show_Data         , LOW)     ;
    digitalWrite (w_MS_IR_DISABLE   , LOW)     ;
    
  }



// =============================================================================================================
//                                               Address Load
void AddresLoad()
  {
    Serial.println("Addres Load");
    digitalWrite (w_LA_ENABLE       , HIGH)    ; // get machine ready to receive an address 
    digitalWrite (w_MS_IR_DISABLE   , HIGH)    ; // get machine ready to receive an address 
    digitalWrite (Set_Flip_Flop     , HIGH)    ; // get machine ready to receive an address 
    digitalWrite (Show_Data         , HIGH)    ;                                            
    digitalWrite (Exam              , HIGH)    ;                                            
    Trigger_Adres_Latch ();
    digitalWrite (w_LA_ENABLE       , LOW)     ; // get machine out of address latch mode
    digitalWrite (w_MS_IR_DISABLE   , LOW)     ; // get machine out of address latch mode
    digitalWrite (Set_Flip_Flop     , LOW)     ; // get machine out of address latch mode
    digitalWrite (Show_Data         , LOW)     ;
    digitalWrite (Exam              , LOW)     ;
  }




// =============================================================================================================
//                                       Extended Memory Address Load
void ExtendedAddressLoad()
  {
    Serial.println("Extended Memory Address Load");
    digitalWrite (w_LA_ENABLE       , HIGH)    ; // get machine ready to receive an extended address  
    digitalWrite (w_KEY_CONTROL     , HIGH)    ; // get machine ready to receive an extended address  
    digitalWrite (Set_Flip_Flop     , HIGH)    ; // get machine ready to receive an extended address  
    digitalWrite (Show_Data         , HIGH)    ;                                                      
    Trigger_Adres_Latch ();
    digitalWrite (w_LA_ENABLE       , LOW)     ; // get machine out of extended address latch mode
    digitalWrite (w_KEY_CONTROL     , LOW)     ; // get machine out of extended address latch mode
    digitalWrite (Set_Flip_Flop     , LOW)     ; // get machine out of extended address latch mode
    digitalWrite (Show_Data         , LOW)     ;
  }




// =============================================================================================================
//                                                 Clear
void Clear()
  {
    Serial.print("Clear machine");
    if (digitalRead(r_RUN) == HIGH)         // check if machine is not running
      {
        Trigger_Initialize ();              // give 400ns positive pulse on Initialize_H
        Serial.print(" >> Machine cleared");
      }
    if (digitalRead(r_RUN) == LOW)          // Warning, machine seems to run ! Not cleared
      {
        Serial.print(" >> ERROR !! Machine not cleared due RUN state !");
      }
    Serial.println();  
  }

  


// =============================================================================================================
//                                      Continue, set machine in RUN mode
void Continue()
  {
    Serial.print("Continue, set machine in RUN mode");
    if (digitalRead(r_RUN) == LOW)          // Warning, machine seems to run ! Not started
      {
        Serial.print(" >> ERROR !! Machine not started due RUN state !");
      }
    if (digitalRead(r_RUN) == HIGH)         // check if machine is not running
      {
        Trigger_Mem_Start ();               // give 400ns positive pulse on Initialize_H
        Serial.print(" >> Running");
      }
    Serial.println();  
  }


// =============================================================================================================
//                                      400nS pulse to Initialize
void Trigger_Initialize ()
  {
    PORTC |= B00000001 ; // Turn on PC0
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  // Wait for 400nS
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  //
    PORTC &= B11111110 ; // Turn off PC0
  }


// =============================================================================================================
//                                      400nS pulse to Latch in address
void Trigger_Adres_Latch ()
  {
    PORTC |= B00000010 ; // Turn on PC1
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  // Wait for 400ns
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  //
    __asm__("nop\n\t");  //
    PORTC &= B11111101 ; // Turn off PC1
  }


// =============================================================================================================
//                                      400nS pulse to start memorycycle
void Trigger_Mem_Start ()
  {
    PORTC |= B00000100; // Turn on PC2
    __asm__("nop\n\t"); //
    __asm__("nop\n\t"); //
    __asm__("nop\n\t"); // Wait for 400ns
    __asm__("nop\n\t"); //
    __asm__("nop\n\t"); //
    __asm__("nop\n\t"); //
    PORTC &= B11111011; // Turn on PC2
  }



// =============================================================================================================
//                                           Kitt scanner at turn on PDP
void Kitt()
  {
    SingleStep();
    RunOnce++;
    unsigned long scanspeed = 35;

        SwitchRegister(0x0001);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0003);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0007);
        AddresLoad();
        delay(scanspeed);    
        SwitchRegister(0x0016);
        AddresLoad();
        delay(scanspeed);        
        SwitchRegister(0x0034);
        AddresLoad();
        delay(scanspeed);    
        SwitchRegister(0x0070);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0160);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0340);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0700);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x1600);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x3400);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x7000);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x6000);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x4000);
        AddresLoad();
        delay(scanspeed);
          // and back
        SwitchRegister(0x6000);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x7000);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x3400);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x1600);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0700);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0340);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0160);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0070);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0034);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0016);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0007);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0003);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0001);
        AddresLoad();
        delay(scanspeed);
        SwitchRegister(0x0000);
        AddresLoad();
        delay(scanspeed);
    UndoSingleStep();
  }
