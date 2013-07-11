var gCanvasElement;
var gDrawingContext;
var kBoardWidth = 9;
var kBoardHeight = 9;
var kPieceWidth = 50;
var kPieceHeight = 50;
var kPixelWidth = 1 + (kBoardWidth * kPieceWidth);
var kPixelHeight = 1 + (kBoardHeight * kPieceHeight);


function initGame() {
    createBoard();
}

function createBoard() {
    canvasElement = document.createElement("canvas");
    canvasElement.id = "mycanvas";
    gCanvasElement = canvasElement;
    document.body.appendChild(canvasElement);
    gCanvasElement.width = kPixelWidth;
    gCanvasElement.height = kPixelHeight;
    gCanvasElement.addEventListener("click", myCanvasOnClick, false);
    gDrawingContext = gCanvasElement.getContext("2d");
    drawBoard();
}

function drawBoard() {
    gDrawingContext.clearRect(0, 0, kPixelWidth, kPixelHeight);
    gDrawingContext.beginPath();

    /* vertical lines */
    for( var x = 0; x <= kPixelWidth; x += kPieceWidth ) {
	gDrawingContext.moveTo(0.5 + x, 0);
	gDrawingContext.lineTo(0.5 + x, kPixelHeight);
    }

    /* horizontal lines */
    for( var y = 0; y <= kPixelHeight; y += kPieceHeight ) {
	gDrawingContext.moveTo(0, 0.5 + y);
	gDrawingContext.lineTo(kPixelWidth, 0.5 + y);
    }

    gDrawingContext.strokeStyle = "#ccc";
    gDrawingContext.stroke();
}

function myCanvasOnClick(e) {
    var xPos = e.pageX;
    var yPos = e.pageY;
    alert("clicked on: " + xPos / kPieceWidth + ":" + yPos / kPieceHeight);
}