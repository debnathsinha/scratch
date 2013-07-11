var w;
var count = 0;
function startWorker() {
    if( typeof(Worker) !== 'undefined' ) {
	if( typeof(w) == 'undefined' ) {
	    w = new Worker('myworker.js');
	}
	w.onmessage = function(event) {
	    console.log("Worker said " + event.data);
	}
	for( count = 0; count < 10; count++) {
	    var msg = {"num": count};
	    w.postMessage(msg);
	}
    } else {
	document.getElementById("result").innerHTML='Webworkers not supported';
    }
}

function stopWorker() {
  w.terminate();
}
