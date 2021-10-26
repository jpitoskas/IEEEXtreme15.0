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

R = get_number()
C = get_number()
Q = get_number()

table = []
for i in range(R):
    word = get_word()
    row = []
    for j in range(C):
        row.append(word[j])
    table.append(row)

table = np.array(table)



for _ in range(Q):

    sol = (R*C,R*C,R*C,R*C)

    found = False
    word = get_word()

    for i in range(R):
        c = 0
        while (c + len(word) <= C):
            if "".join(table[i][c:c+len(word)]) == word:
                found = True
                sol = min(sol,(i, c, i, c+len(word)-1))
            if "".join(table[i][c:c+len(word)]) == word[::-1]:
                found = True
                sol = min(sol,(i, c+len(word)-1, i, c))
            c += 1

    for j in range(C):
        r = 0

        while (r + len(word) <= R):

            if "".join(table[r:r+len(word),j]) == word:
                found = True
                sol = min(sol,(r, j, r+len(word)-1, j))
            if "".join(table[r:r+len(word),j]) == word[::-1]:
                found = True
                sol = min(sol,(r+len(word)-1, j, r, j))
            r += 1


    for i in range(R):
        for j in range(C):
            if (i + len(word) <= R) and (j + len(word) <= C):
                diag = []
                antidiag = []
                for k in range(len(word)):
                    element1 = table[i+k][j+k]
                    diag.append(element1)
                    element2 = table[i+k][j+len(word)-1-k]
                    antidiag.append(element2)

                if "".join(diag) == word:
                    found = True
                    sol = min(sol,(i,j,i+len(word)-1,j+len(word)-1))

                if "".join(diag) == word[::-1]:
                    found = True
                    sol = min(sol,(i+len(word)-1,j+len(word)-1,i,j))

                if  "".join(antidiag) == word:
                    found = True
                    sol = min(sol,(i,j+len(word)-1,i+len(word)-1,j))

                if  "".join(antidiag) == word[::-1]:
                    found = True
                    sol = min(sol,(i+len(word)-1,j,i,j+len(word)-1))



    if not found:
        print(-1)
    else:
        print(*sol)

    
