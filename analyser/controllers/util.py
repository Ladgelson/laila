#!/bin/python
import os 

class Util:
    @staticmethod
    def writeFile(self, path, text):
        try:
            fw = open(path, "w")
            fw.write(text)
            fw.close()
        except:
            return {'status': False,'message': 'An error ocurred trying to creating/writing file.'}
        return {'status': True}

    @staticmethod
    def fileToString(self, hashId, fileName, obj, prop):
        str = ""
        try:
            fh = open(f'{hashId}/{fileName}', 'r')
            for line in fh:
                str += line
            fh.close()
        except FileNotFoundError:
            return {'status': False,'message': 'An error ocurred trying to handle the return message - file not acessible!.'}
        obj['status'] = True
        obj[prop] = str
        return obj

    @staticmethod
    def deleteFolder(self, folderName):
        os.system(f'rm -rf {folderName}')