import ctypes
from threading import Thread
VALUE = 3
global retorno;

from threading import Thread

# gcc -fPIC -shared -o libfun.so IntLocal2.c DHT11.h readVoltage.c -lwiringPi -lwiringPiDev -lpthread
def getValue():
    for i in range(5):
        valorNovo = int(input('Digite um novo valor para alterar na função em C:'))
        VALUE = valorNovo


fun = ctypes.CDLL("/home/pi/TEC499/TP03/G01/PB3/libfun.so") # caminho do arquivo da biblioteca
print(fun)
fun.main.argtypes = [ctypes.c_int] # pegando a função e setando o tipo do parametro


t1 = Thread(target = fun.main , args = (VALUE,))
# t2 = Thread(target = getValue)
t1.start()
retorno = t1.value
print(retorno)
# t2.start()

