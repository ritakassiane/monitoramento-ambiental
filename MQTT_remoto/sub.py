# python3.6
import requests
import json
import random

from paho.mqtt import client as mqtt_client

url = 'http://127.0.0.1:5000/send'
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


def enviarDado(data):
    r = requests.post(url, json=data)
    print(r.json())
    if 'errors' not in (r.json()):
        return r.json, r.status_code
    else:
        return 'err', r.status_code

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
        
        json_msg = json.dumps(mensagem, indent=2)
        data.append(json_msg)
        print(json_msg)
        enviarDado(json_msg)
    client.subscribe(topic2)
    client.on_message = on_message2


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()
