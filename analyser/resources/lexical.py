from flask_restful import Resource
from controllers.lexical import LexicalExecution
from flask import request
import os

class Lexical(Resource): 
    def post(self):
        data = request.get_json()
        lexicalAnalyser = data["lexicalAnalyser"]
        code = data["code"]
        hashId = data["hash"]

        lex = LexicalExecution(lexicalAnalyser, code, hashId)
        ret = lex.execute()
        return ret, 200