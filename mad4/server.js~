var express = require('express');

var app = express();

app.get('/wines', function(req, res) {
    res.send([{name:'wine1'},{name:'wine2'}]);
});
app.get('wines/:id', function(req,res) {
    res.send({id:req.params.id, name:'The Name', description: "description"});
});

app.listen(3000);

console.log('Server running at http://127.0.0.1:3000');