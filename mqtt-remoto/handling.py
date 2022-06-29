import json

teste = '22/06/2022;22:47:30;022;063;125;328'

def convert(msg):
    msgConvert = msg.split(';')
    msgDict = {
        'data': msgConvert[0],
        'horario': msgConvert[1],
        'temperatura': msgConvert[3][1:3],
        'umidade': msgConvert[2][1:3],
        'pressao': msgConvert[4],
        'luminosidade': msgConvert[5]
    }

    msgjson = json.dumps(msgDict)
    return msgjson

print(convert(teste))
