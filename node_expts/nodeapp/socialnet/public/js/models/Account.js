module.exports = function(mongoose, nodemailer) {
    var crypto = require('crypto');
    
    var AccountSchema = new mongoose.Schema({
	email: {type: String, unique: true},
	password: {type: String},
	name: {
	    first: {type: String},
	    last: {type: String}
	},
	photoUrl: {type: String},
	biography: {type: String}
    });

    var Account = mongoose.model('Account', AccountSchema);
    
    var registerCallback = function(err) {
	if(err) {
	    return console.log(err);
	} else {
	    return console.log("Account was created");
	}
    };

    var changePassword = function(accountId, newPassword) {
	var shaSum = crypto.createHash('sha256');
	shaSum.update(newPassword);
	var hashedPassword = shaSum.digest('hex');
	Account.update({_id: accountId},{$set: {password:hashedPassword}}, {upsert: false}, function ChangePasswordCallback(err) {
	    console.log('Change password done for account ' + accountId);
	});

    };

    var forgotPassword = function(email, resetPasswordUrl, callback) {
	var user = Account.findOne({email: email}, function findAccount(err, doc) {
	    if(err) {
		//Email address not on record
		callback(false);
	    } else {
		console.log('Coming...');
	    }
	});
    };
		

    var login = function(email, password, callback) {
	var shaSum = crypto.createHash('sha256');
	shaSum.update(password);
	var hashedPassword = shaSum.digest('hex');
	Account.findOne({email:email, password: hashedPassword}, function(err,doc) {
	    callback(null!=doc);
	});
    };

    var register = function(email, password, firstname, lastname) {
	var shaSum = crypto.createHash('sha256');
	shaSum.update(password);
	var hashedPassword = shaSum.digest('hex');
	console.log('Registering ' + email);
	var user = new Account({
	    email: email,
	    name: {
		first: firstname,
		last: lastname
	    },
	    password: hashedPassword
	});
	user.save(registerCallback);
	console.log('Save command sent');
    }

    return {
	register: register,
	forgotPassword: forgotPassword,
	changePassword: changePassword,
	login: login,
	Account: Account
    }
}