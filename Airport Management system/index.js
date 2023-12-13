const express = require('express')
app = express();
require('express-async-errors')
const port=8080
bodyparser = require('body-parser');

const con = require('./connect');


emproutes = require('./controllers/rout')
app.use(bodyparser.json())
app.use(express.static(__dirname));

app.use('/',emproutes)

app.use((err, req, res, next)=>{
    console.log(err)
    res.status(err.status || 500).send("Something went wrong!")
})

con.query("select 1")
    .then(()=> {
        console.log('db connect')
        app.listen(port, ()=> console.log(`server started at ${port}`))
    })
    .catch(err => console.log('Error\n') + err)