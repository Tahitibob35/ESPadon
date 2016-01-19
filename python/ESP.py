import pySerialComm
import time

ssid = "TahitibobNetwork"
password = "calimeroestgentil"

arduino = pySerialComm.SerialComm('/dev/ttyUSB0', baudrate=115200)



while True:
    print("Status")
    resp = arduino.sendmessage(2, ack=True)
    values = arduino.parsedata("i", resp)
    print(values)
    if values[0] == 3:
        break
    time.sleep(2)

while True:    
    resp = arduino.sendmessage(6, ack=True)
    print(arduino.parsedata("s", resp))


"""print("Status")
resp = arduino.sendmessage(2, ack=True)
values = arduino.parsedata("i", resp)
print(values)

time.sleep(2)

print("disconnect")
resp = arduino.sendmessage(3)

time.sleep(2)

print("connect")
resp = arduino.sendmessage(4, (ssid, password), ack=True)
print (resp)
time.sleep(2)

resp = arduino.sendmessage(5, ack=True)
print(arduino.parsedata("s", resp))
"""
