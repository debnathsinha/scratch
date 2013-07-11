define(['text!templates/register.html'], function(registerTemplate) {
    var registerView = Backbone.View.extend({
	el: $('#content'),
	events: {
	    "submit form" : "register"
	},
	register: function() {
	    $.post('/register', {
		firstname: $('input[name=firstname]').val(),
		lastname: $('input[name=lastname]').val(),
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