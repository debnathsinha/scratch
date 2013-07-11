define(['text!templates/login.html'], function(loginTemplate) {
    var loginView = Backbone.view.extend({
	el: $('#content'),
	events: {
	    "submit form" : "login"
	},
	login: function() {
	    $.post('/register', {
		email: $('input[name=email]').val(),
		password: $('input[name=password]').val()
	    }, function(data) {
		console.log(data);
	    });
	    return false;
	},
	render: function() {
	    this.$el.html(registerTemplate);
	}
    });

    return registerView;
});