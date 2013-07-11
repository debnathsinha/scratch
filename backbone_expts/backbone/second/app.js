$(function() {
    
    var TodoModel = Backbone.Model.extend({
	defaults: function() {
	    return {
		title: 'Hello Todo',
		done: false
	    }
	},
	initialize: function() {
	    if(!this.get("title")) {
		this.set({ "title": this.defaults().title });
	    }
	},
	toggle: function() {
	    this.save({done: !this.get("done")});
	}
    });

    var TodoList = Backbone.Collection.extend({
	model: TodoModel
    });

    var Todos = new TodoList;
    Todos.add([
    	new TodoModel({ title: 'foo', done: false}),
    	new TodoModel({ title: 'bar', done: false}),
    	new TodoModel({ title: 'baz', done: false})
    ]);
    Todos.push(new TodoModel({title: 'foo', done: false}));
    window.Todos = Todos;
    Todos.add(new TodoModel({title : 'foobar', done: false}));

    $('#new-todo-text').bind('keypress', function(e) {
    	if( e.charCode == 13)
    	    Todos.push(new TodoModel({title: $('#new-todo-text').val(), done: false}));
    });
    
    var myTodo = new TodoModel({title: 'Constructing a todo', done: false});
    // myTodo.on("change", function() {
    // 	if(myTodo.hasChanged("title")) {
    // 	    console.log("The title has changed");
    // 	}
    // });
    // $('#todo-list').on('click', function(model, color) {
    // 	myTodo.set({title: 'New Hello Todo'});
    // 	myTodo1 = new TodoModel({title: 'Adding a todo', done: false});
    // });
    // 
    // var TodoView = Backbone.View.extend({
    // 	el: $('#todo-list'),
    // 	template: _.template($('#todo-view-template').html()),
    // 	events: {
    // 	    "click #list-container": "editTodo",
    // 	},
    // 	initialize: function() {
    // 	    this.listenTo(myTodo,'change', function() {
    // 		alert('the model has been changed');
    // 	    });
    // 	},
    // 	render: function() {
    // 	    this.$el.html(this.template({"title": 'foo', "done": false}));
    // 	    return this;
    // 	},
    // 	editTodo: function() {
    // 	    alert("Editing todos");
    // 	}
    // });

    var AppView = Backbone.View.extend({
    	el: $("#todoapp"),
    	render: function() {
    	    console.log("Helllo world");
    	}
    });

    var App = new AppView;
});