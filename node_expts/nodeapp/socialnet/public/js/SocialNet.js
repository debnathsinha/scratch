define(['router'], function(router) {
    var initialize = function() {
	runApp();
    };

    var checkLogin = function(callback) {
	$.ajax("/account/authenticated", {
	    method: "GET",
	    success: function() {
		return callback(true);
	    },
	    error: function() {
		return callback(false);
	    }
	});
    };

    var runApp = function(authenticated) {
	if(!authenticated) {
	    window.location.hash = 'login';
	} else {
	    window.location.hash = 'index';
	}
	Backbone.history.start();
    };

    return {
	initialize: initialize
    };
});