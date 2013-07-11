Stooge = BackBone.Model.extend({
    defaults: {
	'name': 'Guy Incognito',
	'power': 'Classified',
	'friends': [],
    },
    initialize: function() {
	//init
    }
});

var account = new Stooge({name: 'Larry', power: 'baldness', friends: ['Curly', 'Moe']});