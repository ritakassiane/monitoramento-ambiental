# python3.6
import requests
import json
import random

from paho.mqtt import client as mqtt_client

url = 'http://127.0.0.1:5000/send-data'
broker = '10.0.0.101'
port = 1883
topic0 = "measuresSBC"
topic1 = "Timer"


# generate client ID with pub prefix randomly
client_id = f'python-mqtt-{random.randint(0, 100)}'
username = 'aluno'
password = 'aluno*123'
global data
data = []

## Funções secundárias ##

# Função pra tratar a mensagem para ser enviada 

# P.S: SUPONDO QUE O FORMATO DA MENSAGEM É: msg = f"messages:{msg_count}"
def tratar_temperatura(msg):
    print(msg.split(':')[1])
    valor = msg.split(':')[1]
    temperatura = {
        'temperatura':f'{valor}'
    }
    return json.dumps(temperatura)

# Funcao que recebe a string do topico geral do broker e trata ela da forma adequada 
# para o modelo json utilizado    
def convert(msg):
    msgConvert = msg.split(';')
    msgDict = {
        "data": msgConvert[0],
        "horario": msgConvert[1],
        "temperatura": msgConvert[3][1:3],
        "umidade": msgConvert[2][1:3],
        "pressao": msgConvert[4],
        "luminosidade": msgConvert[5]
    }

    msgjson = json.dumps(msgDict)
    return msgjson

# Função utilizada para realizar POST na rota /enviar-temperatura da API
# Essa funcao recebe a mensagem sem tratamento, e dentro dela faz a chamada ao metodo que realiza a adequação e realiza o post
def enviarDado(data):
    temperatura = convert(data)
    r = requests.post(url, json=temperatura)
    print(r)
    # if 'errors' not in (r.json()):
    #     print('Temperatura enviada com sucesso!')
    #     return r.json, r.status_code
    # else:
    #     print('Shiiiii rapaz..')
    #     return 'err', r.status_code

##################################

def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message0(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        mensagem = msg.payload.decode()
        print("Vai enviar agora!")
        enviarDado(mensagem)

    client.subscribe(topic0)
    client.on_message = on_message0

    def on_message1(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        mensagem = msg.payload.decode()
        enviarDado(mensagem)

        

    client.subscribe(topic1)
    client.on_message = on_message1

def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()
