var StoogeRouter = Backbone.Router.extend({
    routes: {
	"certificates/:id": "getCertificate",
    },
    getCertificate: function(id) {
	new StoogeCertificateView({el: $("#certificate")});
    }
});

var router = new StoogeRouter;

Backbone.history.start();