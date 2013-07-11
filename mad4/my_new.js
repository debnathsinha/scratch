function clickMe(e) {
// var jqxhr = $.ajax({
// 	url : "/info.txt",
// 	data: {
// 	    name : "Name",
// 	    desc : "Desc"
// 	}
// })
// 	.success (function(response) {
// 	    alert("Success: " + response);
// 	})
// 	.error (function() { alert("Error"); });
    //document.location = "myapp://someevent?groupings={a:1,b:2}";
    sendObjectMsg({componentId:'00a0000002',groupings: ['group1','group2'],
		   summaries: ['summary1','summary2']});

}

var sendObjectMsg = function(parameters) {
    var iframe = document.createElement('iframe');
    iframe.setAttribute('src', 'myapp:' + JSON.stringify(parameters));
    document.documentElement.appendChild(iframe);
    iframe.parentNode.removeChild(iframe);
    iframe = null;
}

$(document).ready(function() {
    var theDiv = $('#theDiv');

    theDiv.css("background-color",  "blue");
    theDiv.click(function() {
	$('#theDiv').show(300);
    });
});