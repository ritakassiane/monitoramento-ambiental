import flask
import requests
import json
from flask import jsonify
from flask import request
from flask_cors import CORS

app = flask.Flask(__name__)
CORS(app)
app.config["DEBUG"] = True

allData = []

# A função a seguir recebe um dicionario, e parametros equivalentes à quais chaves devem ser excluidas
# Retorna um novo dicionario excluindo as chaves passadas pelo parametro
def without_keys(d, *keys):
    return {k: v for k, v in d.items() if k not in keys}

# A função abaixo itera uma lista de dicionários, aplica a função anterior e retorna outra lista de dicionários
def sensor_filter(lista, chave1, chave2, chave3):
    sensorList = []
    for dado in lista:
        print(dado)
        sensorList.append(without_keys(dado, chave1, chave2, chave3))
    return sensorList

@app.route('/send-data', methods=['POST'])
def data():
    print(request.json)
    allData.append(request.json)
    print(f'dado:{allData}')
    return  jsonify(allData)


@app.route('/', methods=['GET'])
def getData():
    return  jsonify(allData)

@app.route('/temperatura', methods=['GET'])
def getTemp():
    if len(allData) != 0:
        temp = sensor_filter(allData, 'luminosidade', 'pressao', 'umidade')
    else: 
        temp = []
    return  jsonify(temp)

@app.route('/umidade', methods=['GET'])
def getUmid():
    if len(allData) != 0:
        umid = sensor_filter(allData, 'luminosidade', 'pressao', 'temperatura')
    else: 
        umid = []
    return  jsonify(umid)

@app.route('/luminosidade', methods=['GET'])
def getLumin():
    if len(allData) != 0:
        lumen = sensor_filter(allData, 'umidade', 'pressao', 'temperatura')
    else: 
        lumen = []
    return  jsonify(lumen)

@app.route('/pressao', methods=['GET'])
def getPressao():
    if len(allData) != 0:
        pressao = sensor_filter(allData, 'umidade', 'luminosidade', 'temperatura')
    else: 
        pressao = []
    return  jsonify(pressao)

app.run()