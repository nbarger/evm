import sys

# token enums
TOK_LETTER = "TOK_LETTER" # abcdefghijk yeah you get it
TOK_NUMBER = "TOK_NUMBER"
TOK_PERIOD = "TOK_PERIOD"
TOK_COMMA = "TOK_COMMA" # like ,
TOK_PLUS = "TOK_PLUS" # like +
TOK_MINUS = "TOK_MINUS" # like -
TOK_HEXIND = "TOK_HEXIND"
TOK_BININD = "TOK_BININD"
TOK_LPAREN = "TOK_LPAREN"
TOK_RPAREN = "TOK_RPAREN"
TOK_WHITESPACE = "TOK_WHITESPACE"
TOK_SEMICOLON = "TOK_SEMICOLON"
TOK_NEWLINE = "TOK_NEWLINE"

NUMBERS = "1234567890"
LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"
WHITESPACE = " \t"

VERSION = 0.1

def printUsage():
    print("EVAssembler v{}, by Noah Barger. Public domain".format(VERSION))
    print("python3 assembler.py <file.evasm>")

def loadFile(p):
    with open(p, "r") as f:
        a = f.read()
    return a

def parseString(s):
    toks = []
    for c in s:
        if c in LETTERS:
            toks.append((TOK_LETTER, c))
        if c in NUMBERS:
            toks.append((TOK_NUMBER, int(c)))
        if c == ".":
            toks.append((TOK_PERIOD))
        if c == ",":
            toks.append((TOK_COMMA))
        if c == "+":
            toks.append((TOK_PLUS))
        if c == "-":
            toks.append((TOK_MINUS))
        if c == "$":
            toks.append((TOK_HEXIND))
        if c == "%":
            toks.append((TOK_BININD))
        if c == "(":
            toks.append((TOK_LPAREN))
        if c == ")":
            toks.append((TOK_RPAREN))
        if c in WHITESPACE:
            toks.append((TOK_WHITESPACE))
        if c == "\n":
            toks.append((TOK_NEWLINE))
    return toks

if len(sys.argv) < 2:
    print("No file given.")
    exit(1)
if sys.argv[1] == '-h' or sys.argv[1] == '--help':
    printUsage()
    exit(0)

try:
    s = loadFile(sys.argv[1])
except:
    print("Could not open file or does not exist.")
    exit(1)

tokens = parseString(s)

print(tokens)
