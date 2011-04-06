//http://journal.paul.querna.org/articles/2011/04/05/openssl-memory-use/
var tls = require('tls');
var fs = require('fs');

var options = {
	key: fs.readFileSync('test_key.pem'),
	cert: fs.readFileSync('test_cert.pem'),
};

tls.createServer(options, function(s) {
	s.write("welcome!\n");
	console.log('got client');
	s.pipe(s);
}).listen(8000);
console.log('127.0.0.1:8000');
