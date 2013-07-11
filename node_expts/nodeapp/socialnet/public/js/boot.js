require.config({
    paths: {
	jQuery: '/js/libs/jquery',
	Underscore: '/js/libs/underscore',
	Backbone: '/js/libs/backbone',
	text: '/js/libs/text',
	templates: '../templates',
	router: '/js/router'
    },
    shim: {
	'Backbone': ['Underscore', 'jQuery'],
	'SocialNet': ['Backbone','router']
    }
});

require(['SocialNet'], function(SocialNet) {
    SocialNet.initialize();
});