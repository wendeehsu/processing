"""
Goal:
    Read from microphone, translate to sql, get result, and send to arduino
Prerequisite:
    This file utilizes pyserial library.
    To install, please run `pip install pyserial`
TODO:
    [ ] Microphone speech to text
    [ ] Send query and communicate with database
    [v] Send {result, payment} to arduino
"""

import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()
portNum = 8 # <-------------- arduino port number

serialInst.baudrate = 9600
serialInst.port = "COM" + str(portNum)
serialInst.open()

while True:
    command = input("what do you want to tell ardiuno:")
    serialInst.write(command.encode('utf-8'))

    if command == 'exit':
        exit()