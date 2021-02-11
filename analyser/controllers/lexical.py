import os
from controllers.util import Util

class LexicalExecution:
    def __init__(self, lexicalAnalyser, code, hashId):
        self.lexicalAnalyser = lexicalAnalyser
        self.code = code
        self.hashId = hashId

    def execute(self):
        lexicalFileName = f'{self.hashId}.l'
        codeFileName = f'{self.hashId}.code'
        if os.system(f'mkdir {self.hashId}') != 0:
            os.system(f'rm -rf {self.hashId}')
            os.system(f'mkdir {self.hashId}')

        # write lexical analyser
        ret = Util.writeFile(self,f'{self.hashId}/{lexicalFileName}', self.lexicalAnalyser)
        if ret['status'] == False:
            return ret
        
        # write code example
        ret = Util.writeFile(self,f'{self.hashId}/code', self.code)
        if ret['status'] == False:
            return ret

        # run lexical analyser
        if os.system(f'cd {self.hashId} && flex -i {lexicalFileName}') != 0:
            Util.deleteFolder(self, self.hashId)
            return {'status': False, 'message': 'Error trying to execute the os library.'}

        # run c code created by FLEX
        sucess = os.system(f'cd {self.hashId} && gcc lex.yy.c -o myCompiler -lfl 2> errorC > cOut && ./myCompiler > retorno.txt')
        ret = Util.fileToString(self, self.hashId, 'errorC', ret, 'errorC')
        ret = Util.fileToString(self, self.hashId, 'cOut', ret, 'cOut')
        if sucess == 0:
            ret = Util.fileToString(self, self.hashId, 'retorno.txt', ret, 'return')
        else:
            ret['message'] = 'Error trying to execute the os library - FLEX.'
            ret['status'] = False

        Util.deleteFolder(self, self.hashId)
        return ret