 // js/routers/router.js

  // Todo Router
  // ----------

var Workspace = Backbone.Router.extend({
  routes:{
    'about': 'showAbout',
	'todo/:id': 'showTodo',
  },
  
  showTodo: function(id) {
	  console.log(id);
  },
  
  showAbout: function() {
	  console.log("Showing about");
  },

  setFilter: function( param ) {
    // Set the current filter to be used
    if (param) {
      param = param.trim();
    }
    app.TodoFilter = param || '';

    // Trigger a collection filter event, causing hiding/unhiding
    // of Todo view items
    app.Todos.trigger('filter');
  }
});

app.TodoRouter = new Workspace();
Backbone.history.start();