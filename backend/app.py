from flask import Flask
from flask_restful import Resource, Api
from flask_cors import CORS
from resources.lexical import Lexical
from resources.sintatical import Sintatical

app = Flask(__name__)
CORS(app)
api = Api(app)

api.add_resource(Lexical, '/lexical')
api.add_resource(Sintatical, '/sintatical')

if __name__ == '__main__':
    app.run(debug=False, port=5001, host='0.0.0.0')
