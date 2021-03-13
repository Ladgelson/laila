from flask import Flask
from flask_restful import Resource, Api
from flask_cors import CORS
from flask_request_id_header.middleware import RequestID
from resources.lexical import Lexical
from resources.sintatical import Sintatical

app = Flask(__name__)
# UNIQUE ID REQUESTS
app.config['REQUEST_ID_UNIQUE_VALUE_PREFIX'] = 'laila-'
RequestID(app)

CORS(app)
api = Api(app)

api.add_resource(Lexical, '/lexical')
api.add_resource(Sintatical, '/sintatical')

if __name__ == '__main__':
    app.run(debug=False, port=5001, host='0.0.0.0')
