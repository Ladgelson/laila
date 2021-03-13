from flask_restful import Resource
from flask import request
import requests

class Sintatical(Resource): 
    def post(self):
        data = request.get_json()
        uniqueId = request.environ.get("HTTP_X_REQUEST_ID")
        obj = {
            'lexicalAnalyser': data["lexicalAnalyser"],
            'sintaticalAnalyser': data["sintaticalAnalyser"],
            'code': data["code"],
            'hash': uniqueId
        }

        resp = requests.post('http://localhost:80/sintatical', json=obj)
        # resp = requests.post('http://0.0.0.0:5000/sintatical', json=obj)
        if resp.status_code != 200:
            return {'message': 'Something went wrong!'}, 500

        return resp.json(), 200