var events = require('events');
var eventEmitter = new events.EventEmitter();

function mainLoop() {
    console.log('Starting application');
    eventEmitter.emit('ApplicationStart');
    
    console.log('Running appplication');
    eventEmitter.emit('ApplicationRun');
    
    console.log('Stopping application');
    eventEmitter.emit('ApplicationStop');
}

function onApplicationStart() {
    console.log('Handling app start event');
}

function onApplicationRun() {
    console.log('Handling app run event');
}

function onApplicationStop() {
    console.log('Handling app stop event');
}

eventEmitter.on('ApplicationStart', onApplicationStart);
eventEmitter.on('ApplicationRun', onApplicationRun);
eventEmitter.on('ApplicationStop', onApplicationStop);

mainLoop();