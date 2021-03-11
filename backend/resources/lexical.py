from flask_restful import Resource, reqparse
import requests

class Lexical(Resource): 
    args = reqparse.RequestParser()
    args.add_argument('lexicalAnalyser',type=str, required=True, help="The field 'lexicalAnalyser' is required.")
    args.add_argument('code',type=str, required=True, help="The field 'code' is required.")
    args.add_argument('hash',type=str, required=True, help="The field 'hash' is required.")

    def get(self):
        dados = Lexical.args.parse_args()
        obj = {
            'lexicalAnalyser': dados["lexicalAnalyser"],
            'code': dados["code"],
            'hash': dados["hash"]
        }

        resp = requests.get('http://localhost:80/lexical', json=obj)
        if resp.status_code != 200:
            return {'message': 'Something went wrong!'}, 500

        return resp.json(), 200