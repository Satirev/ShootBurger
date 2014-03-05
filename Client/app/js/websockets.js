var Websockets = function(_ip, _port) {
	var ip = _ip || '106.116.69.190',
		port = _port || 1337,
		connection;

	if (!window.WebSocket) {
		scripts.showPopUp('WebSockets is not supported.');
		return false;
	}

	connection = new WebSocket('ws://' + ip + ':' + port);

	connection.onopen = function() {
		return true;
	};

	connection.onerror = function(error) {
		scripts.showPopUp('Sorry, but there\'s some problem with your '
				+ 'connection or the server is down.');
		return false;
	};

	connection.onmessage = function(msg) {
		console.log('[incoming message]');
		var json;
		try {
			json = JSON.parse(msg);
		} catch (e) {
			console.log('This doesn\'t look like a valid JSON: ', msg);
			json = msg;
		}
		message.process(json);		
	};

    setInterval(function() {
        if (connection.readyState !== 1) {
        	var txt = 'Sorry, but there\'s some problem with your connection or the server is down.';
        	scripts.showPopUp(txt, 'Menu', 'exit');
        }
    }, 3000);
	
	this.sendMessage = function(msg) {
		console.log("Wysylam", msg);
		connection.send(msg);
	};
};