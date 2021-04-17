from flask_restful import Resource
import requests

class SintaticalCode(Resource): 
    def get(self):
        lex = open("lexico.l", "r")
        sin = open("sintatico.y", "r")
        _input = open("entrada.lad", "r")
        obj = {
            'lexicalAnalyser': lex.read(),
            'sintaticalAnalyser': sin.read(),
            'code': _input.read(),
        }
        return obj, 200