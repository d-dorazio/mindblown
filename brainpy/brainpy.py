from .ast import Plus, Minus, ShiftL, ShiftR, In, Out, Loop
from .parser import parse


class State:
    def __init__(self):
        self.idx = 0
        self.cells = [0]

    def plus(self):
        self.cells[self.idx] += 1

    def minus(self):
        self.cells[self.idx] -= 1

    def shiftr(self):
        if len(self.cells) - 1 <= self.idx:
            self.cells.append(0)
        self.idx += 1

    def shiftl(self):
        if self.idx == 0:
            self.cells.insert(0, 0)  # ineffecient, but who cares :) ?
        else:
            self.idx -= 1

    def out(self):
        print(chr(self.cells[self.idx]), end='')

    def inp(self):
        inp = input()
        while len(inp) < 1:
            inp = input()

        self.cells[self.idx] = ord(inp[0])


def interpret_file(filename):
    program = ''

    with open(filename, 'rt') as f:
        program = f.read()

    interpret(parse(program))


def interpret_cli():
    state = State()
    line = input('> ').strip()

    while line != 'exit':
        if not line.endswith('\\'):
            interpret(parse(line), state)
            line = ''

        line += input('> ').strip()


def interpret(tokens, state=None):
    state = state or State()

    for tok in tokens:
        if isinstance(tok, Plus):
            state.plus()
        elif isinstance(tok, Minus):
            state.minus()
        elif isinstance(tok, ShiftR):
            state.shiftr()
        elif isinstance(tok, ShiftL):
            state.shiftl()
        elif isinstance(tok, Out):
            state.out()
        elif isinstance(tok, In):
            state.inp()
        elif isinstance(tok, Loop):
            while state.cells[state.idx] != 0:
                interpret(tok.inner, state)

    return state
