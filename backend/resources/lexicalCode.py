from flask_restful import Resource
import requests

class LexicalCode(Resource): 
    def get(self):
        lex = open("myLex.l", "r")
        _input = open("main.lad", "r")
        obj = {
            'lexicalAnalyser': lex.read(),
            'code': _input.read(),
        }
        return obj, 200