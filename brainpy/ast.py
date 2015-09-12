from collections import namedtuple

Plus = namedtuple('Plus', ())
Minus = namedtuple('Minus', ())
ShiftR = namedtuple('ShiftR', ())
ShiftL = namedtuple('ShiftL', ())
In = namedtuple('In', ())
Out = namedtuple('Out', ())
Loop = namedtuple('Loop', ('inner', ))
