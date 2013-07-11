var app = app || {};

app.Todo = Backbone.Model.extend({});

var todo1 = new Todo();
console.log(todo1);

var todo2 = nw Todo({
    title: 'New Todo',
    completed: true
});
console.log(todo2);