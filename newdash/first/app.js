$(function() {

    var DashboardComponentModel = Backbone.Model.extend({
	defaults: {
	    metadata : {},
	    data: {}
	},
	initialize: function() {
	    console.log('Init a dash');
	}
    });

    var Dashboard = Backbone.Collection.extend({
	model: DashboardComponentModel
    });

    var DashboardComponentView = Backbone.View.extend({
	el:$("canvascomponent1"),
	render: function() {
	    DrawCanvas.init(document.getElementById("canvascomponent1"), [80,95,85,78,92,95,79,80]);
	}
    });

    window.dashboardComponentView = new DashboardComponentView;
});
	

