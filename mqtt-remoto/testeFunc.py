def without_keys(d, *keys):
    return {k: v for k, v in d.items() if k not in keys}

def sensor_filter(lista, chave1, chave2, chave3):
    sensorList = []
    for dado in lista:
        print(dado)
        sensorList.append(without_keys(dado, chave1, chave2, chave3))
    return sensorList

teste =[{
    "data": "07/09/2000",
    "horario": "14h30min35s",
    "luminosidade": 27,
    "pressao": 1,
    "temperatura": 25,
    "umidade": 38
    }]
print(sensor_filter(teste, 'pressao', 'temperatura', 'umidade'))