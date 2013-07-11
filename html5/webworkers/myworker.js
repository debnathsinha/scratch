var msg;
self.onmessage = function(event) {
    //msg = JSON.parse(event.data);
    self.postMessage({"fib": fibn(event.data["num"])});
};

function fibn(num) {
    if( num == 1 || num == 0 ) {
	return 1;
    } else {
	return fibn( num -1 ) + fibn( num -2 );
    }
}

// for( var i = 0; i < 10; i++ ) {
//     setTimeout(function() {
// 	self.postMessage({msg:count});
// 	count = count+1;
//     }, 1000);
//     sleep(i);
// }
