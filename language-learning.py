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
    K = get_number()

    words = []
    dict = {}
    for n in range(N):
        word = get_word()
        words.append(word)
        dict[word] = []

    for n in range(N):
        word = words[n]
        dict[word].append(n)









    
