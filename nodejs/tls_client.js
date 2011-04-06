var tls = require('tls');

function go() {

	var s = null;
	s = tls.connect(8000, '127.0.0.1', function() {
	setInterval( function() {
		s.write('hello\n');
	}, 5000);
	});
};

var i;
for( i = 0; i < 200; i++) {
	go();
}
