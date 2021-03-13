const axios = require("axios").default;
const fs = require("fs");

const env = {
  'analyser': 'http://0.0.0.0:5000',
  'dev': 'http://0.0.0.0:5001',
  'prod': 'http://200.129.3.5:8081/lexical',
}

function sendTestLexicalAnalyser(ind){
  const lexicalAnalyser = fs.readFileSync("myLex.l", 'utf-8');
  const codeExample = fs.readFileSync("main.lad", 'utf-8');

  axios({
      method: 'post',
      url: env.dev+"/lexical",
      data: {
        lexicalAnalyser: lexicalAnalyser,
        code: codeExample,
        hash: ""+ind
      }
    })
    .then(function (response) {
      console.log(response.data)
    });
}

function sendTestSintaticalAnalyser(ind){
  const lexicalAnalyser = fs.readFileSync("lexico.l", 'utf-8');
  const sintaticalAnalyser = fs.readFileSync("sintatico.y", 'utf-8');
  const codeExample = fs.readFileSync("entrada.lad", 'utf-8');
  //const util = fs.readFileSync("util.h", 'utf-8');

  axios({
      method: 'post',
      url: env.dev+'/sintatical',
      data: {
        lexicalAnalyser: lexicalAnalyser,
        sintaticalAnalyser: sintaticalAnalyser,
        //util: util,
        code: codeExample,
        hash: ""+ind
      }
    })
    .then(function (response) {
      console.log(response.data)
    });
}

for(let i=0; i < 1; ++i){
  //sendTestLexicalAnalyser(i)
  sendTestSintaticalAnalyser(i)
}