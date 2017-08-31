#include <SimpleModbusMaster.h>
#include <Wire.h>
//////////////////// Comment for Valuable ///////////////
/*
  Fuction Code for Operation
    COIL_OFF, 0x0000                    // Function 5 OFF request is 0x0000
    COIL_ON, 0xFF00                     // Function 5 ON request is 0xFF00
    READ_COIL_STATUS, 0x01, 1           // Reads the ON/OFF status of discrete outputs (0X references, coils) in the slave.
    READ_INPUT_STATUS, 0x02, 2          // Reads the ON/OFF status of discrete inputs (1X references) in the slave.
    READ_HOLDING_REGISTERS, 4x03, 3     // Reads the binary contents of holding registers (4X references) in the slave.
    READ_INPUT_REGISTERS, 4x04,4        // Reads the binary contents of input registers (3X references) in the slave. Not writable.
    FORCE_SINGLE_COIL, 0x05, 5          // Forces a single coil (0X reference) to either ON (0xFF00) or OFF (0x0000).
    PRESET_SINGLE_REGISTER, 4x06, 6     // Presets a value into a single holding register (4X reference).
    FORCE_MULTIPLE_COILS, 0x15, 15      // Forces each coil (0X reference) in a sequence of coils to either ON or OFF.
    PRESET_MULTIPLE_REGISTERS, 4x16, 16 // Presets values into a sequence of holding registers (4X references).

*/
//////////////////// Port information ///////////////////
#define baud 19200
#define timeout 300 // Do everything in 1 loop.
#define polling 200 // the scan rate "200ms For Scanning"
#define retry_count 10
//  used to toggle the receive/transmit pin on the driver rs485
#define TxEnablePin 2
//  The total amount of available memory on the master to store data
#define TOTAL_NO_OF_REGISTERS 3
String val;
//////////////////////////////// This is the easiest way to create new packets ////////////////////////////////////////////
//////////////////////////////// Add as many as you want. TOTAL_NO_OF_PACKETS /////////////////////////////////////////////
/////////////////////////////////////////// is automatically updated. /////////////////////////////////////////////////////
enum
{
  PACKET1,  //  Packet for Stat
  PACKET2  , PACKET3   , //  Packet for M0
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
  // Setthing TTL Serial Communication port and Monitor
  Serial.begin(115200);

  Serial3.begin(115200);

  // Initialize each packet for common negative
  pinMode(22, OUTPUT); digitalWrite(22, HIGH);
  pinMode(24, OUTPUT); digitalWrite(24, HIGH);
  pinMode(26, OUTPUT); digitalWrite(26, HIGH);
  pinMode(28, OUTPUT); digitalWrite(28, HIGH);
  pinMode(30, OUTPUT); digitalWrite(30, HIGH);
  pinMode(32, OUTPUT); digitalWrite(32, HIGH);
  pinMode(34, OUTPUT); digitalWrite(34, HIGH);
  pinMode(36, OUTPUT); digitalWrite(36, HIGH);

  // modbus_construct(&packets[PACKET##], slave_adr, function_code, start_registor_adr, number_of_registor, regs_value_array);


  // Initialize the Modbus Finite State Machine
  modbus_configure(&Serial1, baud, SERIAL_8E1, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS, regs);


}

void loop()
{
  regs[1] = COIL_ON;
  regs[0] = COIL_OFF;
  if ( Serial3.available())
  {
    //////////////////////////////////////////////////////////////////////////////////
    val = Serial3.readString();

    Serial.print(val);
    ///////////////////WetBlue////////////////////
    if (val == "lp01") {
      digitalWrite(22, LOW);
      M0();
      delay(500);
      digitalWrite(22, HIGH);
    } else if (val == "lp03") {
      digitalWrite(24, LOW);
      M0();
      delay(500);
      digitalWrite(24 , HIGH);
    }  if (val == "lp05") {
      digitalWrite(26, LOW);
      M0();
      delay(500);
      digitalWrite(26, HIGH);
    } else if (val == "lp07") {
      digitalWrite(28, LOW);
      M0();
      delay(500);
      digitalWrite(28, HIGH);
    } else if (val == "lp09") {
      digitalWrite(30, LOW);
      M0();
      delay(500);
      digitalWrite(30, HIGH);
    } else if (val == "lp11") {
      digitalWrite(32, LOW);
      M0();
      delay(500);
      digitalWrite(32, HIGH);
    } else if (val == "lp13") {
      digitalWrite(34, LOW);
      M0();
      delay(500);
      digitalWrite(34, HIGH);
    } else if (val == "lp15") {
      digitalWrite(36, LOW);
      M0();
      delay(500);
      digitalWrite(36, HIGH);
    } else  if (val == "lp17") {
      digitalWrite(22, LOW);
      M1();
      delay(500);
      digitalWrite(22, HIGH);
    } else if (val == "lp19") {
      digitalWrite(24, LOW);
      M1();
      delay(500);
      digitalWrite(24 , HIGH);
    } else if (val == "ep27") {
      digitalWrite(26, LOW);
      M4();
      delay(500);
      digitalWrite(26, HIGH);
    } else if (val == "ep29") {
      digitalWrite(28, LOW);
      M4();
      delay(500);
      digitalWrite(28, HIGH);
    } else
      /////////////////Crust////////////////////////
      if (val == "lp02") {
        digitalWrite(26, LOW);
        M1();
        delay(500);
        digitalWrite(26, HIGH);
      } else if (val == "lp04") {
        digitalWrite(28, LOW);
        M1();
        delay(500);
        digitalWrite(28, HIGH);
      } else if (val == "lp06") {
        digitalWrite(30, LOW);
        M1();
        delay(500);
        digitalWrite(30, HIGH);
      } else if (val == "lp08") {
        digitalWrite(32, LOW);
        M1();
        delay(500);
        digitalWrite(32, HIGH);
      } else if (val == "lp10") {
        digitalWrite(34, LOW);
        M1();
        delay(500);
        digitalWrite(34, HIGH);
      } else if (val == "lp12") {
        digitalWrite(36, LOW);
        M1();
        delay(500);
        digitalWrite(36, HIGH);
      } else if (val == "lp14") {
        digitalWrite(22, LOW);
        M2();
        delay(500);
        digitalWrite(22, HIGH);
      } else if (val == "lp16") {
        digitalWrite(24, LOW);
        M2();
        delay(500);
        digitalWrite(24, HIGH);
      } else if (val == "lp18") {
        digitalWrite(26, LOW);
        M2();
        delay(500);
        digitalWrite(26, HIGH);
      } else if (val == "lp28") {
        digitalWrite(28, LOW);
        M2();
        delay(500);
        digitalWrite(28, HIGH);
      } else if (val == "lp32") {
        digitalWrite(30, LOW);
        M2();
        delay(500);
        digitalWrite(30, HIGH);
      } else if (val == "lp38") {
        digitalWrite(32, LOW);
        M2();
        delay(500);
        digitalWrite(32, HIGH);
      } else if (val == "lp41") {
        digitalWrite(34, LOW);
        M2();
        delay(500);
        digitalWrite(34, HIGH);
      } else if (val == "ep02") {
        digitalWrite(30, LOW);
        M4();
        delay(500);
        digitalWrite(30, HIGH);
      } else if (val == "ep25") {
        digitalWrite(32, LOW);
        M4();
        delay(500);
        digitalWrite(32, HIGH);
      } else
        //////////////////Finishing///////////////////
        if (val == "lp21") {
          digitalWrite(36, LOW);
          M2();
          delay(500);
          digitalWrite(36, HIGH);
        } else if (val == "lp23") {
          digitalWrite(22, LOW);
          M3();
          delay(500);
          digitalWrite(22, HIGH);
        } else if (val == "lp25") {
          digitalWrite(24, LOW);
          M3();
          delay(500);
          digitalWrite(24, HIGH);
        } else if (val == "lp27") {
          digitalWrite(26, LOW);
          M3();
          delay(500);
          digitalWrite(26, HIGH);
        } else if (val == "lp29") {
          digitalWrite(28, LOW);
          M3();
          delay(500);
          digitalWrite(28, HIGH);
        } else if (val == "lp31") {
          digitalWrite(30, LOW);
          M3();
          delay(500);
          digitalWrite(30, HIGH);
        } else if (val == "lp33") {
          digitalWrite(32, LOW);
          M3();
          delay(500);
          digitalWrite(32, HIGH);
        } else if (val == "lp35") {
          digitalWrite(34, LOW);
          M3();
          delay(500);
          digitalWrite(34, HIGH);
        } else if (val == "lp37") {
          digitalWrite(36, LOW);
          M3();
          delay(500);
          digitalWrite(36, HIGH);
        } else if (val == "lp39") {
          digitalWrite(22, LOW);
          M4();
          delay(500);
          digitalWrite(22, HIGH);
        } else if (val == "lp40") {
          digitalWrite(24, LOW);
          M4();
          delay(500);
          digitalWrite(24, HIGH);
        } else if (val == "ep04") {
          digitalWrite(34, LOW);
          M4();
          delay(500);
          digitalWrite(34, HIGH);
        } else if (val == "ep06") {
          digitalWrite(36, LOW);
          M4();
          delay(500);
          digitalWrite(36, HIGH);
        } else if (val == "ep18") {
          digitalWrite(22, LOW);
          M5();
          delay(500);
          digitalWrite(22, HIGH);
        } else
          ///////////////////Retanning//////////////////
          if (val == "ep15") {
            digitalWrite(24, LOW);
            M5();
            delay(500);
            digitalWrite(24, HIGH);
          } else if (val == "ep17") {
            digitalWrite(26, LOW);
            M5();
            delay(500);
            digitalWrite(26, HIGH);
          } else if (val == "ep19") {
            digitalWrite(28, LOW);
            M5();
            delay(500);
            digitalWrite(28, HIGH);
          } else if (val == "ep21") {
            digitalWrite(30, LOW);
            M5();
            delay(500);
            digitalWrite(30, HIGH);
          } else if (val == "ep23") {
            digitalWrite(32, LOW);
            M5();
            delay(500);
            digitalWrite(32, HIGH);
          } else if (val == "ep28") {
            digitalWrite(34, LOW);
            M5();
            delay(500);
            digitalWrite(34, HIGH);
          } else if (val == "ep31") {
            digitalWrite(36, LOW);
            M5();
            delay(500);
            digitalWrite(36, HIGH);
          } else if (val == "ep33") {
            digitalWrite(22, LOW);
            M6();
            delay(500);
            digitalWrite(22, HIGH);
          } 
            /////////////////Ending LOOP//////////////////
            else {}
  }
}
void modbus_update10() {
  modbus_update();
  delay(10);
  modbus_update();
  delay(10);
  modbus_update();
  delay(10);
  modbus_update();
  delay(10);
  modbus_update();
  delay(10);
  modbus_update();
  delay(10);

}

void modbus_update40() {
  modbus_update();
  delay(40);
  modbus_update();
  delay(40);
  modbus_update();
  delay(40);
  modbus_update();
  delay(40);
  modbus_update();
  delay(40);
  modbus_update();
  delay(40);
}
//////////////// Triker Signal for scan time///////////////
void M0()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 0, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 0, 1, 0);

  modbus_update40();
}

void M1()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 1, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 1, 1, 0);
  modbus_update40();
}
void M2()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 2, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 2, 1, 0);
  modbus_update40();
}

void M3()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 3, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 3, 1, 0);
  modbus_update40();
}

void M4()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 4, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 4, 1, 0);
  modbus_update40();
}

void M5()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 5, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 5, 1, 0);
  modbus_update40();
}
void M6()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 6, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 6, 1, 0);
  modbus_update40();
}

void M7()
{
  modbus_construct(&packets[PACKET3], 1, FORCE_SINGLE_COIL, 7, 1, 1);
  modbus_update10();
  delay(50);
  modbus_construct(&packets[PACKET2], 1, FORCE_SINGLE_COIL, 7, 1, 0);
  modbus_update40();
}

