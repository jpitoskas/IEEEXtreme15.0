# Python3 program to evaluate a given
# expression where tokens are
# separated by space.

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


# Function to find precedence
# of operators.
def precedence(op):

    if op == '+' or op == '-':
        return 1
    if op == '*':
        return 2
    return 0

# Function to perform arithmetic
# operations.
def applyOp(a, b, op):

    if op == '+': return a + b
    if op == '-': return a - b
    if op == '*': return a * b

# Function that returns value of
# expression after evaluation.
def evaluate(tokens):

    # stack to store integer values.
    values = []

    # stack to store operators.
    ops = []
    parens = []
    i = 0

    while i < len(tokens):

        # Current token is a whitespace,
        # skip it.
        if tokens[i] == ' ':
            i += 1
            continue

        # Current token is an opening
        # brace, push it to 'ops'
        elif tokens[i] == '(':
            if i-1 > 0 and (tokens[i-1].isdigit() or tokens[i-1] == ')'):
                print("invalid")
                return
            if i+1 < len(tokens) and tokens[i+1] == ')':
                print("invalid")
                return
            parens.append(tokens[i])

        # Current token is a number, push
        # it to stack for numbers.
        elif tokens[i].isdigit():
            val = 0

            # There may be more than one
            # digits in the number.
            while(i < len(tokens) and tokens[i].isdigit()):

                val = (val * 10) + int(tokens[i])
                i += 1

            values.append(val)

            # right now the i points to
            # the character next to the digit,
            # since the for loop also increases
            # the i, we would skip one
            #  token position; we need to
            # decrease the value of i by 1 to
            # correct the offset.
            i -= 1

        # Closing brace encountered,
        # solve entire brace.
        elif tokens[i] == ')':
            if i+1 < len(tokens) and tokens[i+1].isdigit():
                print("invalid")
                return
            if len(values) == 0:
                print("invalid")
                return
            while len(ops) != 0 and len(parens) != 0:
                if len(values) < 2:
                    print("invalid")
                    return
                val2 = values.pop()
                val1 = values.pop()
                op = ops.pop()

                values.append(applyOp(val1, val2, op))

            # pop opening brace.
            if len(parens) == 0:
                print("invalid")
                return
            parens.pop()

        # Current token is an operator.
        else:

            # While top of 'ops' has same or
            # greater precedence to current
            # token, which is an operator.
            # Apply operator on top of 'ops'
            # to top two elements in values stack.
            # Push current token to 'ops'.

            while (len(ops) != 0 and precedence(ops[-1]) >= precedence(tokens[i])):
                if len(values) < 2:
                    print("invalid")
                    return
                val2 = values.pop()
                val1 = values.pop()
                op = ops.pop()

                values.append(applyOp(val1, val2, op))

            if len(values) == 0:
                print("invalid")
                return
            ops.append(tokens[i])

        i += 1

    # Entire expression has been parsed
    # at this point, apply remaining ops
    # to remaining values.
    while len(ops) != 0:
        if len(values) < 2:
            print("invalid")
            return
        val2 = values.pop()
        val1 = values.pop()
        op = ops.pop()

        values.append(applyOp(val1, val2, op))

    # Top of 'values' contains result,
    # return it.
    if len(values) == 0:
        print("invalid")
        return
    if len(parens) > 0:
        print("invalid")
        return
    return values[-1]

# Driver Code
if __name__ == "__main__":
     t = get_number()
     for i in range(t):
         s = get_word()
         final = evaluate(s)
         if final != None:
            print(final % (1000000007))
