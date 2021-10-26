# a simple parser for python. use get_number() and get_word() to read
def parser():
    while 1:
        data = list(input().split(' '))
        for number in data:
            if len(number) > 0:
                yield(number)

input_parser = parser()

def get_word():
    global input_parser
    return next(input_parser)

def get_number():
    data = get_word()
    try:
        return int(data)
    except ValueError:
        return float(data)


T = get_number()
for _ in range(T):
    N = get_number()
    alice = 0
    bob = 0
    die1 = []
    die2 = []
    aliceHasDie1 = True
    for n in range(N):
        a = get_number()
        b = get_number()

        alice += a
        bob += b

        if (aliceHasDie1):
            die1.append(a)
            die2.append(b)
        else:
            die1.append(b)
            die2.append(a)

        if (alice != bob):
            aliceHasDie1 = not aliceHasDie1

    die1_sum = sum(die1)
    die2_sum = sum(die2)

    print(1) if die1_sum > die2_sum else print(2)
