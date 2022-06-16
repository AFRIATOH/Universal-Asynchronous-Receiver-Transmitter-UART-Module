import sys
import serial as ser
import time

state = '8'

def transmit_data(scom, enableTX, delay=0.30):       #TX
    while scom.out_waiting or enableTX:  # while the output buffer isn't empty
        global state
        enableTX = True
        state = input(" enter menu option: ")
        scom.write(bytes(state, 'ascii'))
        time.sleep(delay)  # delay for accurate read/write operations on both
        if state == '4':
            x = input(" enter new delay: ")
            x = bytes(x + '\0', 'ascii')
            scom.write(x)
            time.sleep(delay)  # delay for accurate read/write operations on both ends
        if(scom.out_waiting == 0 and (state == '5' or state == '7')):
            return False
    return enableTX

def receive_data(scom, enableTX, delay=0.30):      # RX
    global state
    while scom.in_waiting:  # while the input buffer isn't empty
        if state != '5':
            menu = scom.read_until('\r').decode("ascii")
            print(menu)
            enableTX = True
        else:
            pot = scom.read(size=5).decode("ascii")  # read 3 byte from the input buffer
            pot = pot.replace('\0', '')
            volt = (str(3.3 * int(pot) / 1024))
            print(" Potentiometer value: " + volt[:5] + " [Volt]")
            state = '8'
            enableTX = False
        time.sleep(delay)  # delay for accurate read/write operations on both ends
    return enableTX


def reset_com():
    scom = ser.Serial('COM4', baudrate=9600, bytesize=ser.EIGHTBITS,
                             parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                             timeout=1)
    scom.reset_input_buffer()
    scom.reset_output_buffer()
    return scom


def main():
    scom = reset_com()   #reset the buffers
    enableTX = False
    while 1:
        # RX
        enableTX = receive_data(scom, enableTX)
        # TX
        enableTX = transmit_data(scom, enableTX)


if __name__ == "__main__":
    main()
