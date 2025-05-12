# IS4310-Modbus-Arduino-Sensor-Example1033

## Description

This example demonstrates how to use the **IS4310 Modbus RTU Slave Chip** with the Arduino platform.

The sketch creates a **Modbus sensor** using the IS4310. The Arduino reads the analog value from a potentiometer connected to pin **A0**, and writes it to **Modbus Holding Register 0x0000** of the IS4310 via I2C.

You can read the Holding Register from your PC using a Modbus master client like [qModMaster](https://sourceforge.net/projects/qmodmaster/).

### Default Modbus Connection Parameters

- **Slave Address:** 1  
- **Baud Rate:** 19200 bps  
- **Parity:** Even  
- **Stop Bits:** 1  

### If you're using the Kappa4310Ard Evaluation Board

- Set the **"I2C Speed Selector"** jumper to **100 kHz**.  
- Set the **"I2C Pull-up Voltage"** according to your microcontroller's logic level.  
  If unsure, use **3.3 V**.

---

For more information, check the [product page](https://www.inacks.com/is4310).
