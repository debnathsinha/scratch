var a = "foo";
var el = document.getElementById('myid');

if( window.applicationCache ) {
    //alert("You have app cache");
} else {
    //alert("You do not have app cache");
}

function notEmpty() {
    var myTextField = document.getElementById('myText');
    if(myTextField.value != "")
	alert("You entered: " + myTextField.value);
    else
	alert("Would you like to enter some text?");
}

function draw() {
    var canvas=document.getElementById("myCanvas");
    if(canvas.getContext) {
	var ctx = canvas.getContext("2d");
	ctx.fillStyle = "rgb(200,200,0)";
	ctx.fillRect(10,10,55,50);
    }
}

function draw_b() {
    var b_canvas = document.getElementById("b");
    var b_context = b_canvas.getContext("2d");
    b_context.strokeStyle = "#000";
    b_context.stroke();
    //b_context.fillRect(50,25,150,100);
    b_context.strokeStyle = "#eee";
    b_context.stroke();
    for (var x = 0.5; x < 500; x += 10) {
    	b_context.moveTo(x, 0);
    	b_context.lineTo(x, 375);
    }
    for (var y = 0.5; y < 375; y += 10) {
    	b_context.moveTo(0, y);
    	b_context.lineTo(500, y);
    }
}

