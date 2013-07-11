Backbone.emulateHTTP = true;
Backbone.emulateJSON = true;
var Person = Backbone.Model.extend({
    initialize: function() {
	this.on('all', function(e) {
	    console.log(this.get("name") + " event: " + e);
	});
    },
    defaults: {
	name: 'undefined',
	age: 'undefined'
    },
    urlRoot: "/person",
    url: function() {
	if(this.isNew()) {
	    return this.urlRoot;
	} else {
	    console.log(this.urlRoot + "/" + this.id);
	    return this.urlRoot + "/" + this.id;
	}
    }
});

var debnath = new Person({name:"Debnath", age:28});
debnath.save();

var People = Backbone.Collection.extend({
    initialize: function() {
	this.on('all', function(e) {
	    console.log("People event: " + e);
	});
    },
    model: Person,
    url: '/people'
});

var presidents = new People();
var painters = new People();
presidents.add([{name: "Obama"},{name: "Clinton"},{name: "Washington"}]);
painters.add([{name: "Leonardo"},{name: "Michaelangelo"},{name: "Raphael"}]);

