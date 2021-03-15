from flask_restful import Resource
from flask import request
import requests

class Lexical(Resource): 
    def post(self):
        data = request.get_json()
        uniqueId = request.environ.get("HTTP_X_REQUEST_ID")
        obj = {
            'lexicalAnalyser': data["lexicalAnalyser"],
            'code': data["code"],
            'hash': uniqueId
        }

        resp = requests.get('http://0.0.0.0:80/lexical', json=obj)
        # resp = requests.post('http://200.129.3.5:80/lexical', json=obj)
        if resp.status_code > 202:
            return {'message': 'Something went wrong!'}, 500

        return resp.json(), 200