## Week of 2-8
#### (my part in Elizabeth's ntbk)

**Agenda:**
- discussed part selection
- began block diagram and proposal

**Todo:**

- RFID Module and RFID tag: Write proposal subsystem section
- Write ethics and safety

GOAL: finish these tasks by midnight wednesday, so we can all review the proposal in full and submit on Thursday

## Week of 2-16
#### (my part in Elizabeth's ntbk)

**Hardware Task:**
- Design Alarm driver board

## Week of 3-6

Finished alarm board and BOM, prep for actual hardware

Consider techical specs and other design details as PCB is prepped

## Week of 4-2

Start looking at Python GUI processing: available options include tkinder

**Objective:** An internal module that would enable for USB connection based on FTDI hardware

Found tutorial online about UART connection of FTDI with internal pyqt5 module for GUI application

## Week of 4-9

Start creating skeleton code for the USB connection with FTDI as trying to figure out I2C connection for data processing
Fully implement the main window for GUI, which consists of vertical layout of buttons with different functions when clicked.

Main window as shown in main.png

Issue: Unable to obtain FTDI in readiness for design, make do with alternative dummy UART serial

## Week of 4-16

While can't fully test with actual data since radio not fully working, it simplifies connection between USB and base station, as python has an internal serial module that would read data from serial port - in this case, demo would utilize dummy data from serial port

Able to obtain data from serial port and have it display statically - example of data window is shown in data.png.

**Issues:**

To display continuously, I suspect multithreading is required so that the data obtaining cannot interfere with the GUI process, haven't been able to figure out

Also, mapping feature is not completely figured out since integration is required, which involves different component as well as possible API integration - gets too complicated and will detract from my focus on the previous issue

