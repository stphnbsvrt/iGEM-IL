import serial

ard = serial.Serial()

def setup():
    try:
        global ard
        ard = serial.Serial('/dev/ttyACM0', 9600)
        print("CONNECTION SUCCESFUL")
    except:
        print("ERROR: device connection failed")

def writeln(text):
    text += '\n'
    ard.write(text)

def write(text):
    ard.write(text)

def readln():
    print(ard.readline())

def readAnalog(pin):
    writeln("analogRead::" + str(pin))

def writeAnalog(pin, value):
    writeln("analogWrite::" + str(pin) + "::" + str(value))

def readDigital(pin):
    writeln("digitalRead::" + str(pin))

def writeDigital(pin, ):
    writeln("digitalWrite::" + str(pin) + "::" + str(value))

def loopRead():
    ln = ard.readline();
    if(len(ln) > 0):
        print(ln)
