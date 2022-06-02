import flask
import requests
import json
from flask import jsonify
from flask import request
# from flask_cors import CORS

app = flask.Flask(__name__)
# CORS(app)
app.config["DEBUG"] = True

data = []

@app.route('/', methods=['GET'])
def getData():
    return  jsonify(data)

@app.route('/send', methods=['POST'])
def sendData():
    print(request.json)
    data.append(request.json)
    return  jsonify(data)

app.run()