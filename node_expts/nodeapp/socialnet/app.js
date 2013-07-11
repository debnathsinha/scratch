var express = require('express');
var nodemailer = require('nodemailer');
var MemoryStore = require('connect').session.MemoryStore;

var app = express();

var mongoose = require('mongoose');
// var config = {
//     mail: require('./config/mail')
// };

var Account = require('./public/js/models/Account')(mongoose, nodemailer);

app.configure( function() {
    app.set('view engine', 'jade');
    app.set('views', __dirname + '/public/views');
    app.use(express.static(__dirname + '/public'));
    app.use(express.bodyParser());
});

app.get('/', function(req, res) {
    console.log('Debug');
    res.render("index.jade", {layout: false});
});

app.get('/authenticated', function(req, res) {
    if( req.session.loggedIn ) {
	res.send(200);
    } else {
	res.send(401);
    }
});

app.post('/register', function(req, res) {
    var firstname = req.param('firstname', '');
    var lastname = req.param('lastname','');
    var email = req.param('email', null);
    var password = req.param('password', null);
    console.log(req);
    console.log(req.param);
    console.log(firstname + lastname + email+password);
    if( email == null || password == null) {
	res.send(400);
	return;
    }
    Account.register(email, password, firstname, lastname);
    res.send(200);
});

app.listen(8081);