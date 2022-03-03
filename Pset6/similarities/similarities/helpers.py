from nltk.tokenize import sent_tokenize
from cs50 import get_int
# la libreria  nltk. tokenize es el proceso mediante el cual una gran cantidad de texto se divide en partes más pequeñas llamadas tokens
def lines(a, b):
    """Return lines in both a and b"""
    a = set(a.splitlines())
    j = set(b.splitlines())

    return list (a & j)


def sentences(a, b):
    """Return sentences in both a and b"""

    a = set(sent_tokenize(a))
    j = set(sent_tokenize(b))
    return list (a & j)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    a = set(substringHelper(a, n))
    j = set(substringHelper(b, n))
    return list (a & j)

def substringHelper(a,n):

    l = []
    x = 0
    while x < n:
        y = x
        while  y < (len(a)+1-n):
            l.append(a[y:y+n])
            y+=n
        x+=1
    return set (l);
