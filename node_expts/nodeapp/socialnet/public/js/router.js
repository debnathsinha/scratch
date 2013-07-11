define(['views/index', 'views/register'],
       function(IndexView, RegisterView) {
	   var SocialRouter = Backbone.Router.extend({
	       currentView: null,
	       
	       routes: {
		   "index": "index",
		   "register": "register",
	       },
	       changeView: function(view) {
		   if( null != this.currentView ) {
		       this.currentView.undelegateEvents();
		   }
		   this.currentView = view;
		   this.currentView.render();
	       },
	       index: function() {
		   this.changeView( new IndexView() );
	       },
	       register: function() {
		   this.changeView( new RegisterView() );
	       }
	   });
	   return new SocialRouter();
       });