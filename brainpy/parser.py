from .ast import Plus, Minus, ShiftL, ShiftR, In, Out, Loop
from collections import namedtuple


class ParseError(Exception):
    pass


def parse(stream):
    EoLoop = namedtuple('EOL', ())

    types_table = {
        '+': Plus,
        '-': Minus,
        '>': ShiftR,
        '<': ShiftL,
        '.': Out,
        ',': In,
        '[': Loop,
        ']': EoLoop
    }

    stack = []

    for c in stream:
        toktype = types_table.get(c, None)

        if toktype is None:
            continue

        if toktype == Loop:
            stack.append([])
        elif toktype == EoLoop:
            if len(stack) == 0:
                raise ParseError('brackets mismatch!!!')

            l = Loop(stack.pop())
            if len(stack) == 0:
                yield l
            else:
                stack[-1].append(l)
        else:
            if len(stack) == 0:
                yield toktype()
            else:
                stack[-1].append(toktype())

    if len(stack) > 1:
        raise ParseError('brackets mismatch!!!')

    if len(stack) == 1:
        yield iter(stack[0])
