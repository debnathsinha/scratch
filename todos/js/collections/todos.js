 // js/collections/todos.js

var app = app || {};

// Todo Collection
// ---------------

// The collection of todos is backed by *localStorage* instead of a remote
// server.
var TodoList = Backbone.Collection.extend({

  // Reference to this collection's model.
  model: app.Todo,
  
  url : '/todos',

  // Save all of the todo items under the `"todos-backbone"` namespace.
  localStorage: new Backbone.LocalStorage('todos-backbone'),

  // We keep the Todos in sequential order, despite being saved by unordered
  // GUID in the database. This generates the next order number for new items.
  nextOrder: function() {
    if ( !this.length ) {
      return 1;
    }
    return this.last().get('order') + 1;
  },

  // Todos are sorted by their original insertion order.
  comparator: function( todo ) {
    return todo.get('order');
  }
});

// Create our global collection of **Todos**.
app.Todos = new TodoList();