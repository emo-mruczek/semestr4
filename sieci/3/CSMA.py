from random import random, randint
from time import sleep

# kolorki
# z terminala ile razy ma sie wykonac

SIZE = 1
LENGTH = 10
MESSAGE = "X"

class Sender:
    def __init__(self, number):
        self.number = number
        self.sent = False
        self.wait, self.remove, self.collide = 0, False, 0

    def received(self):
        self.sent = False
        receive(self.number)
    def move(self, channel):
        if self.remove:
            make_move(channel, self.number)
            self.remove = False
            self.sent = True
        elif self.sent:
            return
        elif self.wait == 0:
            if random() < 0.1:
                make_move(channel, self.number)
                self.remove = False
                self.sent = True
        else:
            self.wait -= 1

    def collision(self): # to jest wazna funkcja
        self.remove = False
        self.collide += 1
        self.sent = False
        if self.collide < 10:
            self.wait = randint(1, 2 ** self.collide)
        else:
            print("\nNie można wysłać pakietu\n")
            self.collide = 0
            self.wait = 0

def create_channel():
    return [" " for _ in range(LENGTH)]

def print_channel(channel):
    obj = ""
    for elem in channel:
        obj += "[" + elem[0] + "]"
    print(obj)

def collision_in_channel():
    print("\nNastąpiła kolizja\n")
    return list(" " for _ in range(LENGTH))

def remove_channel(channel):
    return channel[0] == " "

def make_move(channel, number):
    if number == 1:
        channel[0] = (MESSAGE, 1)
    else:
        channel[-1] = (MESSAGE, -1)

def process(channel):
    channel_temp = [" " for _ in range(LENGTH)]

    receive_left, receive_right, collision = False, False, False

    for i in range(len(channel)):
        block = channel[i]

        if block == " ":
            continue  # Nie obchodzą nas puste miejsca

        position = i + block[1]

        if 0 <= position < LENGTH:
            if channel_temp[position] == " ":

                if channel[position] == " ":
                    channel_temp[position] = block
                elif block[1] == channel[position][1]:
                    channel_temp[position] = block
                else:
                    collision = True
                    break

            else:
                collision = True
                break

        elif position <= 0:
            receive_left = True

        else:
            receive_right = True

    return receive_left, receive_right, collision, channel_temp

def receive(number):
    if number == 1:
        print("\n2: otrzymałem przesyłkę od 1\n")
    else:
        print("\n1: otrzymałem przesyłkę od 2\n")


def main():
    tries = 5

    channel = create_channel()

    Alice = Sender(1)
    Bob = Sender(2)

    for _ in range(tries):
        while True:
            Alice.move(channel)
            Bob.move(channel)
            print_channel(channel)
            left, right, collision, channel = process(channel)

            if left:
                Bob.received()
                break
            if right:
                Alice.received()
                break
            if collision:
                channel = collision_in_channel()
                sleep(0.5)
                Alice.collision()
                Bob.collision()
                break
            sleep(0.05)
        #print(t)

if __name__ == "__main__":
    main()