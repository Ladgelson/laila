from flask_restful import Resource
from flask import request
from controllers.sintatical import SintaticalExecution
import os

class Sintatical(Resource): 
    def post(self):
        data = request.get_json()
        lexicalAnalyser = data["lexicalAnalyser"]
        sintaticalAnalyser = data["sintaticalAnalyser"]
        code = data["code"]
        hashId = data["hash"]
        input_ = data["input"]

        sin = SintaticalExecution(lexicalAnalyser, sintaticalAnalyser, code, hashId, input_)
        ret = sin.execute()
        return ret, 200