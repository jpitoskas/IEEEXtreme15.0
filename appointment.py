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
# print(T)
for _ in range(T):
    N = get_number()
    L = []
    R = []
    idx = []
    isUsed = []
    ans = []
    for n in range(N):
        l = get_number()
        r = get_number()
        L.append(l)
        R.append(r)
        idx.append(n+1)
        isUsed.append(False)


    zipped_lists = zip(L, R, idx)
    sorted_pairs = sorted(zipped_lists) 
    tuples = zip(*sorted_pairs)
    sorted_L, sorted_R, sorted_idx = [list(tuple) for tuple in  tuples]
    # print(sorted_L)
    # print(sorted_R)
    # print(sorted_idx)

    # i = day
    for i in range(1, N+1):
        lo = N + 100
        curr = -1
        curr_idx = -1

        if ans == "impossible":
            break
        for j in range(N):

            if (L[j] == i) and (L[j] <= R[j]):
                if (R[j] < lo) and not isUsed[j]:
                    lo = R[j]
                    curr = j

        if (curr != -1):
            ans.append(idx[curr])
            isUsed[curr] = True
        else:
            ans = "impossible"
            break

        for j in range(N):
            if (L[j] == i) and (idx[j] != idx[curr]):
                L[j] += 1

    print(*ans)
