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
    console.log("My name is: " + this.name);
};

var Person = mongoose.model('Person', personSchema);

var debnath = new Person({name:'Debnath Sinha', age:28});

console.log(debnath.name);

debnath.speak();

debnath.save( function(err, debnath) {
    if(err) {
	console.log('Could not save');
    }
});

Person.find({name:'Debnath'}, function(err, person) {
    if(err) {
	console.log('Could not find the person');
    } else {
	console.log(person[0].name + ": " + person[0].age);
    }
});