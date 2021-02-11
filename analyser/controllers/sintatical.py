import os
from controllers.util import Util

class SintaticalExecution:
    def __init__(self, lexicalAnalyser, sintaticalAnalyser, util, code, hashId):
        self.lexicalAnalyser = lexicalAnalyser
        self.sintaticalAnalyser = sintaticalAnalyser
        self.util = util
        self.code = code
        self.hashId = hashId

    def execute(self):
        lexicalFileName = f'{self.hashId}.l'
        sintaticalFileName = f'{self.hashId}.y'
        codeFileName = f'{self.hashId}.code'
        utilFileName = 'util.h'
        if os.system(f'mkdir {self.hashId}') != 0:
            os.system(f'rm -rf {self.hashId}')
            os.system(f'mkdir {self.hashId}')

        # write lexical analyser
        ret = Util.writeFile(self,f'{self.hashId}/{lexicalFileName}', self.lexicalAnalyser)
        if ret['status'] == False:
            return ret
        
        # write sintaticalAnalyser
        ret = Util.writeFile(self,f'{self.hashId}/sintatical.y', self.sintaticalAnalyser)
        if ret['status'] == False:
            return ret

        # write sintaticalAnalyser
        ret = Util.writeFile(self,f'{self.hashId}/util.h', self.util)
        if ret['status'] == False:
            return ret

        # write code example
        ret = Util.writeFile(self,f'{self.hashId}/entrada.lad', self.code)
        if ret['status'] == False:
            return ret

        # run lexical analyser
        if os.system(f'cd {self.hashId} && flex -i {lexicalFileName}') != 0:
            Util.deleteFolder(self, self.hashId)
            return {'status': False, 'message': 'Error trying to execute the os library.'}

        # run sintatical analyser
        sucess = os.system(f'cd {self.hashId} && bison sintatical.y 2> retorno.txt')
        ret = Util.fileToString(self, self.hashId, 'retorno.txt', ret, 'warning')
        if sucess != 0:
            Util.deleteFolder(self, self.hashId)
            ret['status'] = False
            ret['message'] = 'Error trying to execute the os library - Bison.'
            return ret
        
        # run c code genereted by bison
        sucess = os.system(f'cd {self.hashId} && gcc sintatical.tab.c -o analisador -lfl -lm 2> errorC > warning && ./analisador > retorno.txt ')
        ret = Util.fileToString(self, self.hashId, 'errorC', ret, 'errorC')
        ret = Util.fileToString(self, self.hashId, 'warning', ret, 'cOut')
        if sucess == 0:
            ret = Util.fileToString(self, self.hashId, 'retorno.txt', ret, 'return')
        else:
            ret['message'] = 'Error trying to execute the os library - FLEX.'
            ret['status'] = False

        Util.deleteFolder(self, self.hashId)
        return ret