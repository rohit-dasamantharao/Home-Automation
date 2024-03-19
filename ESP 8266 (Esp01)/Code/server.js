const express = require('express')
const app = express()
const port = 3000

var bulb = false;

var bodyParser = require('body-parser')
app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
  extended: true
})); 

app.get('/getstatus', (req, res) => {
  res.send(bulb);
})

app.post('/', (req, res) => {

    res.send('Hello World!');
    console.log("Got request from iot device ESP8600 with request "+req.body.hello)
  })

app.get('/',(req,res)=>{
    res.send("Welcome on");
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})