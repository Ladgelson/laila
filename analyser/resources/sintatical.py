from flask_restful import Resource, reqparse
from controllers.sintatical import SintaticalExecution
import os

class Sintatical(Resource): 
    args = reqparse.RequestParser()
    args.add_argument('lexicalAnalyser',type=str, required=True, help="The field 'lexicalAnalyser' is required.")
    args.add_argument('sintaticalAnalyser',type=str, required=True, help="The field 'sintaticalAnalyser' is required.")
    args.add_argument('code',type=str, required=True, help="The field 'code' is required.")
    args.add_argument('hash',type=str, required=True, help="The field 'hash' is required.")

    def get(self):
        dados = Sintatical.args.parse_args()
        lexicalAnalyser = dados["lexicalAnalyser"]
        sintaticalAnalyser = dados["sintaticalAnalyser"]
        code = dados["code"]
        hashId = dados["hash"]

        sin = SintaticalExecution(lexicalAnalyser, sintaticalAnalyser, code, hashId)
        ret = sin.execute()
        return ret, 200