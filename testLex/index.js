const axios = require("axios").default;
const fs = require("fs");
const perf = require('execution-time')();

const env = {
  'analyser': 'http://0.0.0.0:5000',
  'dev': 'http://0.0.0.0:5001',
  'prod': 'http://200.129.3.5:8081',
}

function sendTestLexicalAnalyser(ind){
  const lexicalAnalyser = fs.readFileSync("myLex.l", 'utf-8');
  const codeExample = fs.readFileSync("main.lad", 'utf-8');
  
  axios({
    method: 'post',
    url: env.analyser+"/lexical",
    data: {
      lexicalAnalyser: lexicalAnalyser,
      code: codeExample,
      //hash: ""+ind,
      input: ""
    }
  })
  .then(function (response) {
    console.log(response.data)
  });
}

let cumulative = 0;
function sendTestSintaticalAnalyser(ind){
  const lexicalAnalyser = fs.readFileSync("lexico.l", 'utf-8');
  const sintaticalAnalyser = fs.readFileSync("sintatico.y", 'utf-8');
  const codeExample = fs.readFileSync("entrada.lad", 'utf-8');
  //const util = fs.readFileSync("util.h", 'utf-8');
  perf.start(ind+'');
  axios({
      method: 'post',
      url: env.prod+'/sintatical',
      data: {
        lexicalAnalyser: lexicalAnalyser,
        sintaticalAnalyser: sintaticalAnalyser,
        code: codeExample,
        //hash: ""+ind,
        input: ""
      }
    })
    .then(function (response) {
      const results = perf.stop(ind+'');
      console.log(response.data)
      console.log(`${results.time - cumulative} --- ${results.preciseWords}`);  // in words
      cumulative += results.time-cumulative;
    });
}

function testGetLexicalCode(){
  axios({
    method: 'get',
    url: env.dev+'/sintaticalCode'
  })
  .then((data)=> console.log(data))
}

testGetLexicalCode();

// console.log("Time/Executtion | SUM")
// for(let i=0; i < 1; ++i){
//   //sendTestLexicalAnalyser(i)
//   sendTestSintaticalAnalyser(i)
// }
