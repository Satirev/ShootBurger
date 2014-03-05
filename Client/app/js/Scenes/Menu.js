function SceneMenu() {

};

SceneMenu.prototype.initialize = function() {
	console.log("SceneMenu.initialize()");

	$("#menuCase").delegate("#start", "click", function(event) {
		console.log("[button click] start");
		
		var json = {
			type : "HelloRequest",
			data : {
				"name" : app.player_name
			}
		};
		
		websockets.sendMessage(JSON.stringify(json));
		
		scripts.switchScenes('#SceneLobby');
		event.stopPropagation();
	});
	$("#menuCase").delegate("#info", "click", function(event) {
		console.log("[button click] info");
		scripts.switchScenes('#SceneInfo');
		event.stopPropagation();
	});
	$("#menuCase").delegate("#options", "click", function(event) {
		console.log("[button click] options");
		scripts.switchScenes('#SceneOptions');
		event.stopPropagation();
	});
	$("#menuCase").delegate("#about", "click", function(event) {
		console.log("[button click] about");
		scripts.switchScenes('#SceneAbout');
		event.stopPropagation();
	});
	$("#menuCase").delegate("#options", "click", function(event) {
		console.log("[button click] option");
		//TODO: tutaj opcje
		// sf.core.exit(false);
		event.stopPropagation();
	});
};

SceneMenu.prototype.show = function() {
	History.pushState({scene: '#SceneMenu'}, "Menu", "?st=menu");
};