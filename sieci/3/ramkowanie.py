from zlib import crc32

INPUT = "Z.txt"
OUTPUT = "W.txt"
#CRC = 32 
FRAME = '01111110'


def encoding():
    with open(INPUT, "r") as f:
        print("Reading message: " + INPUT)
        message = f.read();

    # checking crc
    crc = "{0:b}".format(crc32(message.encode()))
    code = "0" * (32 - len(crc)) + crc + message 

    print("Encoding...")
    encoded = ""
    i = 0
    for val in code:
        if val == "1":
            i += 1
            encoded += "1"
            if i == 5:
                print("Adding zero bit")
                encoded += "0"
                i = 0
        else:
            encoded += "0"
            i = 0

    final_message = FRAME + encoded + FRAME

    with open(OUTPUT, "w") as f:
        f.write(final_message)

    print("Encoded message: " + final_message)

    print("Message saved to: " + OUTPUT)
    

def decoding():
    with open(OUTPUT, "r") as f:
        print("Reading encoded message: " + OUTPUT)
        message = f.read()

    print("Decoding...")
    code = message[8:-8] 
    decoded = ""
    i = 0 
    for val in code:
        if val == "0":
            if i != 5:
                decoded += "0"
            i = 0 
        else:
            decoded += "1"
            i += 1

    final_message = decoded[32:] 
    crc = decoded[:32]
    check_crc = '{0:b}'.format(crc32(final_message.encode()))
    check_crc = '0'*(32-len(check_crc)) + check_crc

    if check_crc != crc:
        print("There is something wrong with crc...")
        print(final_message)
    else: 
        print(final_message)

def main():
   encoding()
   decoding()

if __name__ == "__main__":
    main()
