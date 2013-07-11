var express = require('express');
var app = express();

var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost/people');

var db = mongoose.connection;
db.on('error', console.error.bind(console,'connection error:'));
db.once('open', function callback() {

});


var personSchema = mongoose.Schema({
    name: String,
    age: Number
});

personSchema.methods.speak = function() {
    console.log("My name is: " + this.name + 'and my age is ' + this.age);
};

var Person = mongoose.model('Person', personSchema);

app.configure( function() {
    app.use(express.static(__dirname));
    app.use(express.bodyParser());
});

app.get('/', function(req, res) {
    console.log('Debug');

});

app.get('/person.html', function(req, res) {
    var model = JSON.parse(req.param('model', null));
    console.log(model.name+': '+model.age);
    var person = new Person({name:model.name, age:model.age});
    person.speak();
    res.send(200);
});

app.get('/person', function(req, res) {
    return Person.find(function(err, persons) {
	if(err) {
	    return console.log(err);
	} else {
	    res.send(persons);
	}
    });
});

app.get('/person/:id', function(req, res) {
    var req_name = req.param('name',null);
    console.log('Requesting : ' + req_name);
    Person.find({name: req_name}, function(err, person) {
	if(err) {
	    console.log('Could not find person');
	} else {
	    res.send(200,JSON.stringify(person));
	}
    });
    res.send(200);
});

app.post('/person', function(req, res) {
    //var model = JSON.parse(req.param('model', null));
    var model ={"name": req.body.name, "age": req.body.age};
    console.log(model);
    var person = new Person({name:model.name, age:model.age});
    person.save( function(err, person) {
	if(err) {
	    console.log('Could not save');
	} else {
	    console.log('Succeeded in saving');
	    res.send(person);
	}
    });
});

app.listen(3000);