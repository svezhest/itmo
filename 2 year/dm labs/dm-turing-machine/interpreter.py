import os
import sys

from lark import Lark
from lark import Transformer


# os.system("stty -echo")


def join(current_state, tapes_read, state_after, tapes_write):
    if compile_to_site:
        return test_out(current_state, tapes_read, state_after, tapes_write)
    else:
        return lab_out(current_state, tapes_read, state_after, tapes_write)


def test_out(current_state, tapes_read, state_after, tapes_write):
    return "\n" + ",".join([current_state, ",".join(tapes_read)]) + "\n" + \
           ",".join([state_after, ",".join([name for name, _ in tapes_write]),
                     ",".join([direction if direction != "^" else "-" for _, direction in tapes_write])])


def lab_out(current_state, tapes_read, state_after, tapes_write):
    return " ".join([current_state, *tapes_read, "->", state_after, *[" ".join(pair) for pair in tapes_write]])


class ExprTreeTransformer(Transformer):
    def same_state(self, expression):
        current_state, tapes_write = expression
        tapes_read = [pack for pack, direction in tapes_write]
        return self.another_state([current_state, tapes_read, current_state, tapes_write])

    def another_state(self, expression):
        current_state, tapes_read, state_after, tapes_write = expression
        assert len(tapes_read) == len(tapes_write)
        tapes_num = len(tapes_read)
        expressions = [expression]
        for i in range(tapes_num):
            temp = []
            for expression_to_unpack in expressions:
                current_state, tapes_read, state_after, tapes_write = expression_to_unpack
                read_pack = tapes_read[i]
                write_pack, direction = tapes_write[i]
                if len(write_pack) == 1:
                    for a in read_pack:
                        for b in write_pack:
                            tapes_read_copy = tapes_read.copy()
                            tapes_write_copy = tapes_write.copy()
                            tapes_read_copy[i] = a
                            tapes_write_copy[i] = [b, direction]
                            temp.append([current_state, tapes_read_copy, state_after, tapes_write_copy])
                else:
                    assert len(read_pack) == len(write_pack)
                    for a, b in list(zip(read_pack, write_pack)):
                        tapes_read_copy = tapes_read.copy()
                        tapes_write_copy = tapes_write.copy()
                        tapes_read_copy[i] = a
                        tapes_write_copy[i] = [b, direction]
                        temp.append([current_state, tapes_read_copy, state_after, tapes_write_copy])
            expressions = temp
        return [join(*expression_to_join) for expression_to_join in expressions]

    def read(self, array):
        return array

    def write(self, array):
        return [array[i: i + 2] for i in range(0, len(array), 2)]

    def state(self, pair):
        name, = pair
        return str(name)

    def LETTER(self, pair):
        ch, = pair
        return ch

    def DIGIT(self, pair):
        ch, = pair
        return ch

    def sym(self, pair):
        ch, = pair
        return str(ch)

    def single_sym(self, s):
        return s

    def list(self, array):
        return [''.join(x) for x in array]

    def on_tape(self, pair):
        ch, = pair
        return ch

    left = lambda self, _: "<"
    stay = lambda self, _: "^"
    right = lambda self, _: ">"
    underscore = lambda self, _: "_"
    asterisk = lambda self, _: "*"
    plus = lambda self, _: "+"
    minus = lambda self, _: "-"
    less = lambda self, _: "<"
    equals = lambda self, _: "="
    more = lambda self, _: ">"
    pipe = lambda self, _: "|"
    op_bracket = lambda self, _: "("
    cls_bracket = lambda self, _: ")"


def list_str(_list):
    if len(_list) == 1:
        return _list[0]
    return "[" + ", ".join(_list) + "]"


class Renamer(Transformer):
    def same_state(self, expression):
        current_state, tapes_write = expression
        current_state = prefix + current_state + postfix
        return [" ".join([current_state,
                          " ".join([" ".join([list_str(pack), direction]) for pack, direction in tapes_write])])]

    def another_state(self, expression):
        current_state, tapes_read, state_after, tapes_write = expression
        current_state = prefix + current_state + postfix
        state_after = prefix + state_after + postfix
        return [" ".join([current_state,
                          " ".join([list_str(pack) for pack in tapes_read]), "->",
                          state_after,
                          " ".join([" ".join([list_str(pack), direction]) for pack, direction in tapes_write])])]

    def read(self, array):
        return array

    def write(self, array):
        return [array[i: i + 2] for i in range(0, len(array), 2)]

    def state(self, pair):
        name, = pair
        return str(name)

    def LETTER(self, pair):
        ch, = pair
        return ch

    def DIGIT(self, pair):
        ch, = pair
        return ch

    def sym(self, pair):
        ch, = pair
        return str(ch)

    def single_sym(self, s):
        return s

    def list(self, array):
        return [''.join(x) for x in array]

    def on_tape(self, pair):
        ch, = pair
        return ch

    left = lambda self, _: "<"
    stay = lambda self, _: "^"
    right = lambda self, _: ">"
    underscore = lambda self, _: "_"
    asterisk = lambda self, _: "*"
    plus = lambda self, _: "+"
    minus = lambda self, _: "-"
    less = lambda self, _: "<"
    equals = lambda self, _: "="
    more = lambda self, _: ">"
    pipe = lambda self, _: "|"
    op_bracket = lambda self, _: "("
    cls_bracket = lambda self, _: ")"

# TODO: multiple digits for tapes; strings for symbols; all symbols
parser = Lark(r"""
    expr: DIGIT -> single_sym
        | state " " write -> same_state
        | state " " read " -> " state " " write -> another_state
        
    read: on_tape (" " on_tape)*
    
    write: on_tape " " dir (" " on_tape " " dir)*
        
    on_tape: single_sym | list
        
    single_sym: sym
    list: "[" sym (", " sym )* "]"
    
    state: CNAME
    sym: LETTER
        | DIGIT
        | "_" -> underscore
        | "*" -> asterisk
        | "+" -> plus
        | ">" -> more
        | "<" -> less
        | "=" -> equals
        | "-" -> minus
        | "|" -> pipe
        | "(" -> op_bracket
        | ")" -> cls_bracket
    
    dir: "<"   -> left
        | "^"  -> stay
        | ">"  -> right
    
    %import common.CNAME
    %import common.LETTER
    %import common.DIGIT
    %import common.WS
""", start="expr")

prefix = ""
postfix = ""

compile_to_site = True
rename_instead_of_transform = False

sys.stdin = open("raw/sorting_raw.out", "r")
_, s = input().split()
_, ac = input().split()
_, rj = input().split()
_, blank = input().split()

if rename_instead_of_transform:
    s = prefix + s + postfix
    ac = prefix + ac + postfix
    rj = prefix + rj + postfix
    # blank still be blank

if compile_to_site and not rename_instead_of_transform:
    out = ["", "name: DM lab testing", "init: " + s, "accept: " + ac]
else:
    out = ["start: " + s, "accept: " + ac, "reject: " + rj, "blank: " + blank]

while True:
    try:
        raw_input = input()
    except EOFError:
        break
    if not raw_input.strip() or raw_input.isspace():
        break

    # print(raw_input)
    if rename_instead_of_transform:
        out += Renamer().transform(parser.parse(raw_input))
    else:
        temp = ExprTreeTransformer().transform(parser.parse(raw_input))
        if not(compile_to_site and len(temp) == 1 and temp[0].isdigit()):
            out += temp

for _o in out:
    print(_o)
