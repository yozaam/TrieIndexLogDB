# from `g++ -fPIC -shared -o main.so main.cpp`
import ctypes
import sys
import os 

dir_path = os.path.dirname(os.path.realpath(__file__))
handle = ctypes.CDLL(dir_path + "/main.so")     

handle.getKey.argtypes = [ctypes.c_char_p, ctypes.c_char_p] 
handle.getKey.restypes = ctypes.c_char_p
handle.setKey.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p] 
handle.setKey.restypes = ctypes.c_bool



def getKey(filename, key):
    return handle.api_get_db(filename, key)

def setKey(filename, key, value):
    return handle.api_set_db(filename, key, value)