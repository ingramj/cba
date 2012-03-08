from ctypes import *

_libcba = cdll.LoadLibrary('libcba.so')

def cba_true():
    return _libcba.cba_true()
