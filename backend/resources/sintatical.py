from flask_restful import Resource, reqparse
import requests

class Sintatical(Resource): 
    args = reqparse.RequestParser()
    args.add_argument('lexicalAnalyser',type=str, required=True, help="The field 'lexicalAnalyser' is required.")
    args.add_argument('sintaticalAnalyser',type=str, required=True, help="The field 'sintaticalAnalyser' is required.")
    args.add_argument('code',type=str, required=True, help="The field 'code' is required.")
    args.add_argument('hash',type=str, required=True, help="The field 'hash' is required.")

    def get(self):
        dados = Sintatical.args.parse_args()
        obj = {
            'lexicalAnalyser': dados["lexicalAnalyser"],
            'sintaticalAnalyser': dados["sintaticalAnalyser"],
            'code': dados["code"],
            'hash': dados["hash"]
        }

        resp = requests.get('http://localhost:5000/sintatical', json=obj)
        if resp.status_code != 200:
            return {'message': 'Something went wrong!'}, 500

        return resp.json(), 200