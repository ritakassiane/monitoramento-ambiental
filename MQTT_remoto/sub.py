# python3.6
import requests
import json
import random

from paho.mqtt import client as mqtt_client

url = 'http://127.0.0.1:5000/enviar-temperatura'
broker = '10.0.0.101'
port = 1883
topic = "mqtt/umidade"
topic2 = "mqtt/temp"
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


# Função utilizada para realizar POST na rota /enviar-temperatura da API
# Essa fun~]ao recebe a mensagem sem tratamento, e dentro dela faz a chamada ao metodo que realiza a adequação e realiza o post
def enviarDado(data):
    temperatura = tratar_temperatura(data)
    r = requests.post(url, json=temperatura)
    print(r.json())
    if 'errors' not in (r.json()):
        print('Temperatura enviada com sucesso!')
        return r.json, r.status_code
    else:
        print('Shiiiii rapaz..')
        return 'err', r.status_code

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
    def on_message(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")

    client.subscribe(topic)
    client.on_message = on_message

    def on_message2(client, userdata, msg):
        print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
        mensagem = msg.payload.decode()
        enviarDado(mensagem)

    client.subscribe(topic2)
    client.on_message = on_message2


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()
