#include <SimpleModbusMaster.h>
//////////////////// Comment for Valuable ///////////////
/*
    regs  = "Registor/Coil value in Array Block"
    FC#   = "Fuction Code for Operation   COIL_OFF, 0x0000                    // Function 5 OFF request is 0x0000
                                          COIL_ON, 0xFF00                     // Function 5 ON request is 0xFF00
                                          READ_COIL_STATUS, 0x01, 1           // Reads the ON/OFF status of discrete outputs (0X references, coils) in the slave.
                                          READ_INPUT_STATUS, 0x02, 2          // Reads the ON/OFF status of discrete inputs (1X references) in the slave.
                                          READ_HOLDING_REGISTERS, 4x03, 3     // Reads the binary contents of holding registers (4X references) in the slave.
                                          READ_INPUT_REGISTERS, 4x04,4        // Reads the binary contents of input registers (3X references) in the slave. Not writable.
                                          FORCE_SINGLE_COIL, 0x05, 5          // Forces a single coil (0X reference) to either ON (0xFF00) or OFF (0x0000).
                                          PRESET_SINGLE_REGISTER, 4x06, 6     // Presets a value into a single holding register (4X reference).
                                          FORCE_MULTIPLE_COILS, 0x15, 15      // Forces each coil (0X reference) in a sequence of coils to either ON or OFF.
                                          PRESET_MULTIPLE_REGISTERS, 4x16, 16 // Presets values into a sequence of holding registers (4X references).
    REGP# = "Registor/Coil Position/Taget"
    TNRR# = "Total Number of Registor/Coil in Rage on Taget"
    ARY#  = "Array to Keep/Write regitors/coil value"
*/
//////////////////// Port information ///////////////////
#define baud 19200
#define timeout 1000 // Do everything in 1 loop.
#define polling 200 // the scan rate "200ms For Scanning"
#define retry_count 10
#define slave_adr 1
//  used to toggle the receive/transmit pin on the driver rs485
#define TxEnablePin 2
#define LED 9
//  The total amount of available memory on the master to store data
#define TOTAL_NO_OF_REGISTERS 3
int count = 0;
//////////////////////////////// This is the easiest way to create new packets ////////////////////////////////////////////
//////////////////////////////// Add as many as you want. TOTAL_NO_OF_PACKETS /////////////////////////////////////////////
/////////////////////////////////////////// is automatically updated. /////////////////////////////////////////////////////

enum
{
  PACKET100,
  PACKET0,  //  Packet for M0
  PACKET1,  //  Packet for M1
  TOTAL_NO_OF_PACKETS // leave this last entry
};

// Create an array of Packets to be configured
Packet packets[TOTAL_NO_OF_PACKETS];
// Masters register array
unsigned int regs[TOTAL_NO_OF_REGISTERS];

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////SETUP/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  // Print Port
  Serial1.begin(19200);
  Serial2.begin(19200);
  // INPUT From ESP8266
  Serial3.begin(19200);


  // Array Value for Setting
  regs[0] = 0x0000; // Function 0X05 OFF request is 0x0000
  regs[1] = 0xFF00; // Function 0X05 ON request is 0xFF00

  // Setup to read Registor/Coil form Modbus Slave 1 and keep in Array regs 2
//  modbus_construct(&packets[PACKET100], slave_adr, 1, 0, 1, 2);


  // Initialize the Modbus Finite State Machine
  modbus_configure(&Serial1, baud, SERIAL_8N2, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);
  
  pinMode(LED, OUTPUT);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////MAIN/////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  // Main loop Fuction to Rx value

  if (Serial3.available()) {
    //
    String val = Serial3.readString();
    if (val == "1") {

      do  {
        count++;
        delay(50);
        m0_0(); //M0 state "0" Fuction call
        delay(50);
      } while (count == 10);
    } else if (val == "2") {
      do  {
        count++;
        delay(50);
        m0_1(); //M0 state "1" Fuction call
        delay(50);
      } while (count == 10);
    } else if (val == "3") {
      delay(50);
      m1_0(); //M1 state "0" Fuction call
      delay(50);

    } else if (val == "4") {

      delay(50);
      m1_1(); //M1 state "1" Fuction call
      delay(50);
    } else {
      //Nothing
    }

  } else {

    // Do Read or Write Form "void setup()" Fuction
    modbus_update();
    // Print Array value 2
    Serial2.print(regs[2]);
    // Update every 1 second
    delay(150);

  }
  delay(500);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////FUNCTION//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void m0_0() {
  word FC0, REGP0, TNRR0, ARY0;
  FC0 = 0x05;
  REGP0 = 0;
  TNRR0 = 1;
  ARY0 = 0x0000;
  modbus_construct(&packets[PACKET0], slave_adr, FC0, REGP0, TNRR0, ARY0);

  modbus_update();
}

void m0_1() {
  word FC0_1, REGP0_1, TNRR0_1, ARY0_1;

  FC0_1 = 0x05;
  REGP0_1 = 0;
  TNRR0_1 = 1;
  ARY0_1 = 0x0001;
  modbus_construct(&packets[PACKET0], slave_adr, FC0_1, REGP0_1, TNRR0_1, ARY0_1);

  modbus_update();
}
void m1_0() {
  word FC1, REGP1, TNRR1, ARY1;

  FC1 = 0x05;
  REGP1 = 1;
  TNRR1 = 1;
  ARY1 = 0x0000;
  modbus_construct(&packets[PACKET1], slave_adr, FC1, REGP1, TNRR1, ARY1);

  modbus_update();
}

void m1_1() {
  word FC1_1, REGP1_1, TNRR1_1, ARY1_1;

  FC1_1 = 0x05;
  REGP1_1 = 1;
  TNRR1_1 = 1;
  ARY1_1 = 0x0001;
  modbus_construct(&packets[PACKET1], slave_adr, FC1_1, REGP1_1, TNRR1_1, ARY1_1);

  modbus_update();
}
