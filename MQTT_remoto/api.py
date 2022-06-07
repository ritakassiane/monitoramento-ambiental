import flask
import requests
import json
from flask import jsonify
from flask import request
# from flask_cors import CORS

app = flask.Flask(__name__)
# CORS(app)
app.config["DEBUG"] = True

data = [
    [
        {
            "temperatura": "22"
        },
        {
            "emperatura":"28"
        },
        {
            "temperatura":"27.8"
        }
    ],
    [
        {
            'humildade':'80'
        },
        {
            'humildade':'90'
        },
        {
            'humildade':'78.8'
        }
    ]
]
temp = [
    {
        "temperatura": "22"
    },
    {
        "emperatura":"28"
    },
    {
        "temperatura":"27.8"
    }
]

umid = [
    {
        'umidade':'22'
    },
    {
        'umidade':'28'
    },
    {
        'umidade':'27.8'
    }

]

@app.route('/', methods=['GET'])
def getData():
    return  jsonify(data)

@app.route('/temp', methods=['GET'])
def getTemp():
    return  jsonify(temp)

@app.route('/umid', methods=['GET'])
def getUmid():
    return  jsonify(umid)


@app.route('/enviar-temperatura', methods=['POST'])
def temperatura():
    print(request.json)
    temp.append(request.json)
    return  jsonify(temp)

@app.route('/enviar-umidade', methods=['POST'])
def umidade():
    print(request.json)
    umid.append(request.json)
    return  jsonify(umid)


app.run()