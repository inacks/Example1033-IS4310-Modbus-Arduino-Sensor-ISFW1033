/* 
 * Program Title:
 * IS4310_Modbus_Arduino_Sensor (ISFW1033)
 *
 * Description:
 * This example demonstrates how to use the IS4310 Modbus RTU Slave Chip with the 
 * Arduino platform.
 *
 * The sketch creates a Modbus Sensor using the IS4310. The Arduino reads the analog
 * value from a potentiometer connected to pin A0, and writes it to Modbus Holding 
 * Register 0x0000 of the IS4310 via I2C. 
 *
 * You can read the Holding Register from your PC using a Modbus master client
 * like qModMaster: https://sourceforge.net/projects/qmodmaster/
 *
 * Default Modbus connection parameters for your Modbus master client:
 * - Slave Address: 1
 * - Baud Rate: 19200 bps
 * - Parity: Even
 * - Stop Bits: 1
 *
 * If you're using the Kappa4310Ard Evaluation Board:
 * - Set the "I2C Speed Selector" jumper to 100 kHz.
 * - Set the "I2C Pull-up Voltage" according to your microcontroller's logic level.
 *   If unsure, use 3.3 V.
 *
 * For more information check the product page:
 * https://www.inacks.com/is4310
 */



#include <Wire.h>

void writeHoldingRegister(uint16_t holdingRegisterAddress, uint16_t data) {
  Wire.beginTransmission(0x11); // I2C address of the IS4310 (fixed).

  // Send the 16-bit Holding Register address (2 bytes).
  Wire.write((holdingRegisterAddress >> 8) & 0xFF); // High byte.
  Wire.write(holdingRegisterAddress & 0xFF);        // Low byte.

  // Send the 16-bit data (2 bytes).
  Wire.write((data >> 8) & 0xFF); // High byte.
  Wire.write(data & 0xFF);        // Low byte.

  Wire.endTransmission();
}


uint16_t readHoldingRegister(uint16_t holdingRegisterAddress) {
  uint16_t result; // Variable to store the read data.
  
  Wire.beginTransmission(0x11); // I2C address of the IS4310 (fixed).
  
  // Send the 16-bit Holding Register address (2 bytes).
  Wire.write((holdingRegisterAddress >> 8) & 0xFF); // High byte.
  Wire.write(holdingRegisterAddress & 0xFF);        // Low byte.
  Wire.endTransmission(false); // Send a repeated start condition.
  
  // Request 2 bytes from the IS4310 (a full 16-bit Holding Register).
  Wire.requestFrom(0x11, 2);  
  result = Wire.read();        // Read high byte.
  result <<= 8;                // Shift to make space for low byte.
  result |= Wire.read();       // Read and append low byte.

  return result; // Return the full 16-bit value.
}

void setup() {
  uint16_t ModbusSlaveID; // Variable to store the Modbus Slave ID.

  Wire.begin();           // Initialize the I2C interface.
  Serial.begin(9600);     // Initialize the serial port for debug printing.

  // Restore the IS4310's default communication values:
  
  // Set the IS4310 Modbus Slave Address to 1:
  writeHoldingRegister(500, 1);

  // Set the IS4310 Baud Rate to 19200 bps:
  // Value 110 = 1200 bps, 111 = 2400 bps, 112 = 9600 bps, 113 (default) = 19200 bps,
  // 114 = 57600 bps, 115 = 115200 bps.
  writeHoldingRegister(501, 113);

  // Set the IS4310 Parity Bit to Even:
  // Value 120 = No Parity, 121 = Odd Parity, 122 (default) = Even Parity.
  writeHoldingRegister(502, 122);

  // Set the IS4310 Stop Bit configuration to 1 stop bit:
  // Value 131 (default) = 1 Stop Bit, 132 = 2 Stop Bits.
  writeHoldingRegister(503, 131);
}

void loop() {
  /*
   * Main Program: Read the potentiometer and store its value in Holding Register 0x0000.
   */
  uint16_t potentiometerValue = analogRead(A0); // Read the potentiometer connected to pin A0.

  // Print the potentiometer value to the serial terminal:
  Serial.print("Potentiometer value: ");
  Serial.println(potentiometerValue);
  Serial.println();

  // Write the potentiometer value to Holding Register address 0:
  writeHoldingRegister(0, potentiometerValue);

  // Pause briefly:
  delay(500);
}