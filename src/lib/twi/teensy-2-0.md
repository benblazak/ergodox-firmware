# Documentation : I&sup2;C : Teensy 2.0

## I&sup2;C Status Codes (for Master modes)

### Master Transmitter (datasheet section 20.8.1, table 20-3)

* `0x08`  A START condition has been transmitted 
* `0x10`  A repeated START condition has been transmitted
* `0x18`  SLA+W has been transmitted; ACK has been received
* `0x20`  SLA+W has been transmitted; NOT ACK has been received
* `0x28`  Data byte has been transmitted; ACK has been received
* `0x30`  Data byte has been transmitted; NOT ACK has been received
* `0x38`  Arbitration lost in SLA+W or data bytes

### Master Receiver (datasheet section 20.8.2, table 20-4)

* `0x08`  A START condition has been transmitted
* `0x10`  A repeated START condition has been transmitted
* `0x38`  Arbitration lost in SLA+R or NOT ACK bit
* `0x40`  SLA+R has been transmitted; ACK has been received
* `0x48`  SLA+R has been transmitted; NOT ACK has been received
* `0x50`  Data byte has been received; ACK has been returned
* `0x58`  Data byte has been received; NOT ACK has been returned

-------------------------------------------------------------------------------

Copyright &copy; 2012 Ben Blazak <benblazak.dev@gmail.com>  
Released under The MIT License (MIT) (see "license.md")  
Project located at <https://github.com/benblazak/ergodox-firmware>

