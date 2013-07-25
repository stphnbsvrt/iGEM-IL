import serial
import time
import subprocess


ard = serial.Serial()
messages = []
modules = []

def setup():
    try:
        global ard
        ard = serial.Serial('/dev/ttyACM0', 9600, timeout=.01)
        print("CONNECTION SUCCESFUL")
    except:
        print("ERROR: device connection failed")

def getControlModules():
    modStrings = ["practice"]
    global modules
    for mod in modStrings:
        try:
            exec("import " + mod)
            modules.append(eval(mod))
        except Error:
            print "Module " + mod + " does not exist."


def writeln(text):
    global messages
    messages += [text, time.time()]
    text += '\n'
    ard.write(text)

def write(text):
    ard.write(text)

def read(i):
    print(ard.read(i))

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
