var DrawCanvas = {
    drawAxes : function() {
	var width = this.width;
	var height = this.height;
	var ctx = this.ctx;
	var xAxesMargin = this.xAxesMargin;
	var yAxesMargin = this.yAxesMargin;
    	ctx.strokeStyle = "black";
    	
    	/*y axis along left edge of canvas*/
    	ctx.beginPath();
    	ctx.moveTo(xAxesMargin,0);
    	ctx.lineTo(xAxesMargin,height - yAxesMargin);
    	ctx.stroke();
    	
    	/*x axis along bottom edge*/
    	ctx.moveTo(xAxesMargin,height-yAxesMargin);
    	ctx.lineTo(width - xAxesMargin,height-yAxesMargin);
    	ctx.stroke();
    },
    plotData : function(data) {
	var ctx = this.ctx;
	ctx.strokeStyle = "green";
	for(var i = 0; i < data.length; i++ ) {
	    this.drawRect(i * 20,0,10,data[i]);
	}
    },
    translate : function(x,y) {
	return { 'x': x + this.xAxesMargin, 'y': this.height - y - this.yAxesMargin };
    },
    drawRect : function(x,y,w,h) {
	var ctx = this.ctx;
	ctx.fillStyle = "blue";
	var transformed = this.translate(x,y);
	ctx.fillRect(transformed['x'], transformed['y'], w, -1 * h);
    },
    init : function(canvasElement, data) {
	var ctx = canvasElement.getContext("2d");
	this.width = canvasElement.width;
	this.height = canvasElement.height;
	this.ctx = ctx;
	this.xAxesMargin = 20;
	this.yAxesMargin=20;
	this.drawAxes(ctx, this.width, this.height);
	this.plotData(data);
    }
};