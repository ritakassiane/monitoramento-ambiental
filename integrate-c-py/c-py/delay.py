import ctypes
from threading import Thread
VALUE = 5

from threading import Thread


def getValue():
    for i in range(5):
        valorNovo = int(input('Digite um novo valor para alterar na função em C:'))
        VALUE = valorNovo

fun = ctypes.CDLL("C:/UEFS/SD/pbl03-sistemasdigitais/integrate-c-py/c-py/libfun.so") # caminho do arquivo da biblioteca
print(fun)
fun.main.argtypes = [ctypes.c_int] # pegando a função e setando o tipo do parametro


t1 = Thread(target = fun.main , args = (VALUE,))
# t2 = Thread(target = getValue)
t1.start()
# t2.start()

