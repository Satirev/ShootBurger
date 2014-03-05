function SceneLobby() {
};

SceneLobby.prototype.initialize = function () {
	console.log("SceneLobby.initialize()");
	$("div").delegate("#readyButton", "click", function(event) {
		console.log("[button click] ready");
		
		var json = {
			type : 'Ready',
			data : {
				status : true
			}
		};	
		websockets.sendMessage(JSON.stringify(json));
		
		event.stopPropagation();
	});
};

SceneLobby.prototype.show = function() {
	History.pushState({scene: '#SceneLobby'}, "Lobby", "?st=lobby");
};