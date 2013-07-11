function clickMe(e) {
    window.location="http://www.google.com";
}

$(document).ready(function() {
    var theDiv = $('#theDiv');

    theDiv.css("background-color",  "blue");
    theDiv.click(function() {
	$('#theDiv').show(300);
    });
});