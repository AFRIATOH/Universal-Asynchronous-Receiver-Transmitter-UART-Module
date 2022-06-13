import serial as ser
import time

state = '7'

def receive_data(serial_comm, enableTX, delay=0.25):
    global state
    # RX
    while serial_comm.in_waiting:  # while the input buffer isn't empty
        if state != '5':
            menu = serial_comm.read_until('\r').decode("ascii")
            print(menu)
            enableTX = True
        else:
            pot = serial_comm.read(size=5).decode("ascii")  # read 3 byte from the input buffer
            pot = pot.replace('\0', '')
            volt = str(3.3 * int(pot) / 1024)
            print("Potentiometer value: " + volt[:5] + " [Volt]")
            print("Please Push PB0 to display menu.")
            state = '7'
            enableTX = False

        time.sleep(delay)  # delay for accurate read/write operations on both ends
    return enableTX


def transmit_data(serial_comm, enableTX, delay=0.25):
    while serial_comm.out_waiting or enableTX:  # while the output buffer isn't empty
        global state
        state = input(" enter menu option: ")
        serial_comm.write(bytes(state, 'ascii'))
        time.sleep(delay)  # delay for accurate read/write operations on both
        enableTX = True
        while 1:
            # RX
            enableTX = receive_data(serial_comm, enableTX)
            # TX
            enableTX = transmit_data(serial_comm, enableTX)
        if state == '4':
            x = input("enter new delay: ")
            serial_comm.write(bytes(x + '\0', 'ascii'))
            time.sleep(delay)  # delay for accurate read/write operations on both ends
        if serial_comm.out_waiting == 0:
            return False
    return enableTX


def start_communication():
    serial_comm = ser.Serial('COM4', baudrate=9600, bytesize=ser.EIGHTBITS,
                             parity=ser.PARITY_NONE, stopbits=ser.STOPBITS_ONE,
                             timeout=1)
    serial_comm.reset_input_buffer()
    serial_comm.reset_output_buffer()
    enableTX = False
    while 1:
        # RX
        enableTX = receive_data(serial_comm, enableTX)
        # TX
        enableTX = transmit_data(serial_comm, enableTX)


def main():
    start_communication()


if __name__ == "__main__":
    main()
