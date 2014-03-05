function SceneInit() {

};

SceneInit.prototype.initialize = function () {
	var sceneInit = $("#SceneInit");
	sceneInit.delegate("#initOk", "click", function(event) {
		var UserInput = sceneInit.find('input[name="name"]');
		var IpAddress = sceneInit.find('input[name="ip"]');
		var port = sceneInit.find('input[name="port"]');
		if(UserInput.is(':valid') && IpAddress.is(':valid') && port.is(':valid')){
			app.player_name = UserInput.val();
			app.global_ip = IpAddress.val();
			app.global_port = port.val();
			websockets = new Websockets(app.global_ip, app.global_port);
			scripts.switchScenes('#SceneMenu');
		}
		event.stopPropagation();
	});
};

SceneInit.prototype.show = function() {
	History.pushState({scene: '#SceneInit'}, "Init", "?st=Init");
};