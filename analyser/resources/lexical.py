from flask_restful import Resource, reqparse
from controllers.lexical import LexicalExecution
import os

class Lexical(Resource): 
    args = reqparse.RequestParser()
    args.add_argument('lexicalAnalyser',type=str, required=True, help="The field 'lexicalAnalyser' is required.")
    args.add_argument('code',type=str, required=True, help="The field 'code' is required.")
    args.add_argument('hash',type=str, required=True, help="The field 'hash' is required.")

    def get(self):
        dados = Lexical.args.parse_args()
        lexicalAnalyser = dados["lexicalAnalyser"]
        code = dados["code"]
        hashId = dados["hash"]

        lex = LexicalExecution(lexicalAnalyser, code, hashId)
        ret = lex.execute()
        return ret, 200