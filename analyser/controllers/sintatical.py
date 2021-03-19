#!/bin/python
import os
from controllers.util import Util
from multiprocessing import Process, Queue

class SintaticalExecution:
    def __init__(self, lexicalAnalyser, sintaticalAnalyser, code, hashId, input_):
        self.lexicalAnalyser = lexicalAnalyser
        self.sintaticalAnalyser = sintaticalAnalyser
        self.code = code
        self.hashId = hashId
        self.input = input_

    def exec_c(self, q):
        sucess = os.system(f'cd {self.hashId} && gcc sintatical.tab.c -o analisador -lfl -lm 2> errorC > warning && ./analisador < input > retorno.txt ')
        q.put(sucess)

    def execute(self):
        q = Queue()
        lexicalFileName = f'{self.hashId}.l'
        sintaticalFileName = f'{self.hashId}.y'
        codeFileName = f'{self.hashId}.code'
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

        # write code example
        ret = Util.writeFile(self,f'{self.hashId}/entrada.lad', self.code)
        if ret['status'] == False:
            return ret

        # write input file
        ret = Util.writeFile(self,f'{self.hashId}/input', self.code)
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
        proc = Process(target=SintaticalExecution.exec_c, args=(self,q))
        proc.start()
        proc.join(5)

        if proc.is_alive():
            proc.terminate()
            proc.join()
            Util.deleteFolder(self, self.hashId)
            return {'success':False, 'message':'Timeout exceeded'}, 408

        sucess = q.get()
        ret = Util.fileToString(self, self.hashId, 'errorC', ret, 'errorC')
        ret = Util.fileToString(self, self.hashId, 'warning', ret, 'cOut')
        if sucess == 0:
            ret = Util.fileToString(self, self.hashId, 'retorno.txt', ret, 'return')
        else:
            ret['message'] = 'Error trying to execute the os library - FLEX.'
            ret['status'] = False

        Util.deleteFolder(self, self.hashId)
        return ret