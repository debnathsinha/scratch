var Stooge = Backbone.Model.extend({
    defaults: {
	'name' : '',
	'power' : ''
	'friends': [],
    }
});

var Team = Backbone.Collections.extend({
    model: Stooge
});

var larry = new Stooge({ name: 'Larry', power: 'baldness', friends: ['curly', 'moe'] });
var moe = new Stooge({ name: 'Moe', power: 'All powers', friends: ['larry', 'curly'] });
var curly = new Stooge({ name: 'Curly', power: 'Hair', friends: ['larry', 'moe'] });

var threeStooges = new Team([larry, moe, curly]);