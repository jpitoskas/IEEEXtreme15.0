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

N = get_number()

ax = []
ay = []
# a_dist = []
a_manh = []
a_inf = []

for i in range(N):
    x = get_number()
    y = get_number()
    ax.append(x)
    ay.append(y)
    a_manh.append(max(x,y))
    a_inf.append(max(x,y))

bx = []
by = []
# b_dist = []
b_manh = []
b_inf = []

for i in range(N):
    x = get_number()
    y = get_number()
    bx.append(x)
    by.append(y)
    b_manh.append(x+y)
    b_inf.append(max(x,y))

cx = []
cy = []
c_dist = []
c_manh = []
c_inf = []

for i in range(N):
    x = get_number()
    y = get_number()
    cx.append(x)
    cy.append(y)
    c_manh.append(x+y)
    c_inf.append(max(x,y))

# import random

a = list(range(1,N+1))
b = list(range(1,N+1))
c = list(range(1,N+1))

# random.shuffle(a)
# random.shuffle(b)
# random.shuffle(c)

zipped_lists = zip(ax, a)
sorted_pairs = sorted(zipped_lists)
tuples = zip(*sorted_pairs)
_, a = [list(tuple) for tuple in  tuples]

zipped_lists = zip(bx, b)
sorted_pairs = sorted(zipped_lists)
tuples = zip(*sorted_pairs)
_, b = [list(tuple) for tuple in  tuples]

zipped_lists = zip(cx, c)
sorted_pairs = sorted(zipped_lists, reverse=True)
tuples = zip(*sorted_pairs)
_, c = [list(tuple) for tuple in  tuples]


for i in range(0, N):
    print(a[i],b[i],c[i])












    
