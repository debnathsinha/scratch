function forward() {
    var stateObj = { foo : "bar" };
    history.pushState( stateObj, "page 2", "bar.html" );
}

function back() {
    
}